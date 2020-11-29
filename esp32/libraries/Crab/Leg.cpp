#include "Leg.h"


Leg::Leg(int shoulderIndex, int elbowIndex, int wristIndex, float shoulderLinkLength, float elbowLinkLength, float wristLinkLength){  
    indices[0]=shoulderIndex;
    indices[1]=elbowIndex;
    indices[2]=wristIndex;

    linkLengths[0]=shoulderLinkLength;
    linkLengths[1]=elbowLinkLength;
    linkLengths[2]=wristLinkLength;
    
    //The speed of the CPU clock is lowered to avoid problems with the servomotor driver's I2C
    setCpuFrequencyMhz(16);

    //Servo driver setup
    pwm1 = Adafruit_PWMServoDriver(0x40);
    pwm2 = Adafruit_PWMServoDriver(0x41);

    pwm1.begin();
    pwm1.setOscillatorFrequency(27000000);
    pwm1.setPWMFreq(FREQUENCY);

    pwm2.begin();
    pwm2.setOscillatorFrequency(27000000);
    pwm2.setPWMFreq(FREQUENCY);

    //Leg starts in Start State
    setStart();
}

//Set new desired state, this is a promise, the angle is not set yet
void Leg::setLegState(int shoulderAngle, int elbowAngle, int wristAngle){
    
    futureAngles[0]=shoulderAngle;
    futureAngles[1]=elbowAngle;
    futureAngles[2]=180-wristAngle;
}

//Start the leg at a determined state
void Leg::setStart(){
    futureAngles[0]=90;
    futureAngles[1]=90;
    futureAngles[2]=90;

    updateLegPlease();
}

//Fulfill the promise to set the desired angle
void Leg::updateLegPlease(){
    for(int i = 0; i < 3; i++){
        moveServo(indices[i], futureAngles[i]);
        //once the promise is fulfilled, the register of the current angle is updated
        angles[i] = futureAngles[i];
    }
}

//Converts the angle into a period of time the pwm servo can understand
int Leg::pulseWidth(int angle)
{
    int pulse_wide, analog_value;
    pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
    analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
    return analog_value;
}

//Moves the servo depending on which side of the crab it is
void Leg::moveServo(int servoID, int angle) {
    if(servoID < 9){
        pwm1.setPWM(servoDriver[servoID], 0, pulseWidth(angle));
    }
    
    else{
        pwm2.setPWM(servoDriver[servoID], 0, pulseWidth(angle));
    }
}

int * Leg::angFromPos(float x, float y, float z){
    float l, alpha, beta, gamma, m, M, C, a, b, c;
    bool cond1 = false;
    bool cond2 = false;
    static int results [4] = {0,0,0,0};
    bool pos = false;

    // Serial.println(x);

    //These varaibles are asigned so the code is easier to read
    a = linkLengths[0];
    b = linkLengths[1];
    c = linkLengths[2];

    //These are intermediate values corresponding to the geometry of the robot
    l = sqrt(pow(z, 2) + pow(y,2));
    m = sqrt(pow(x,2) + pow(l-a,2));
    M = acos((pow(m,2)-pow(b,2)-pow(c,2))/(-2*b*c));
    C = asin((c*sin(M))/m);
    
    //These are the angles corresponding to the shoulder, elbow, and wrist respectively
    alpha = atan2(y, z) * 180 / M_PI;
    beta = (M_PI - atan2((l - a),-x) - C) * 180 / M_PI;
    gamma = (M_PI - M) * 180 / M_PI;

    //Rounding and cleaning data
    alpha < 90 ? alpha = ceil(alpha) : alpha = floor(alpha);
    beta < 90 ? beta = ceil(beta) : beta = floor(beta);
    gamma < 90 ? gamma = ceil(gamma) : gamma = floor(gamma);

    //Defining conditions
    cond1 = sqrt(pow(x,2)+pow(y,2)+pow(z,2)) <= a + b + c;
    cond2 = 0 <= alpha && alpha <= 180 && 0 <= beta && beta <= 180 && 0 <= gamma && gamma <= 180;

    //Check if the necessary conditions are met
    if(cond1 && cond2){
        pos = true;
    }

    

    results[0] = (int) alpha;
    results[1] = (int) beta;
    results[2] = (int) gamma;
    results[3] = (int) pos;

    return results;
}

//A cirlce in which a leg can move for a fixed value of x is obtained
float * Leg::mobilityCircle(float x){
    float alpha, beta, gamma, theta, ymin, ymax, z,d;

    //0 -> center , 1 -> center y, 2-> center z, 3->radius, 4 -> true center y
    static float circleParam [4];

    //These varaibles are asigned so the code is easier to read
    float a = linkLengths[0];
    float b = linkLengths[1];
    float c = linkLengths[2];

    //This is only valid for when x < 0

    // First ymax

    //We assume ymax happens when gamma = 0
    //We also are placing the circle at the center, so alpha must be 90
    gamma = 0;
    alpha = M_PI / 2;

    //d is the third side of the triangle formed by b and c
    d = sqrt( pow(b,2) + pow(c,2) - 2 * b * c * cos( M_PI - gamma ) );

    
    //Theta is the angle between b and d
    theta = asin( c / d * sin( M_PI - gamma ) );

    //analyzing the geometry the following equation is obtained
    beta = -acos( -x /(-d)) + M_PI - theta;
    
    //Once beta is obtained, ymax can be calculated using the geometry of the robot
    ymax = (a + d * sin( M_PI - beta - theta ) ) * sin( alpha );

    //Then ymnin
    
    //For simplicity ymin will be equal to the lenth of the first link
    ymin = a;

    //Then the center of the circle of movement is calculated.
    //This value is the one recieved given that the circle is on a plane, x component
    circleParam[0] = x;
    //This value is an average of ymin and ymax, this is the y component
    circleParam[1] = ( ymin + ymax ) / 2;
    //This value is equal to 0 because the circle must be centered on the leg's z plane
    circleParam[2] = 0;

    //Then the radio is calculated
    circleParam[3] = ( ymax - ymin ) / 2;

    //These values must recieve adjustments so that some clearance is guaranteed
    circleParam[3] = circleParam[3] * 0.9;
    circleParam[1] = circleParam[1] + circleParam[3] / 0.9 * 0.05;

    return circleParam;
}

//This functions traces a line inside the limits of the movility circle in the direction specified
//direction argument is defined as 0 along the y axis,it's positive in the direction of the z axis
float * Leg::traceLine(float direction, float x){

    static float *circle;

    //0 -> P1x, 1 -> P1y, 2 -> P1z
    //3 -> P2x, 4 -> P2y, 5 -> P2z
    float *points = new float[6];

    direction = direction * M_PI / 180;
    circle = mobilityCircle(x);

    points[0] = *(circle+0);
    points[1] = *(circle+3) * cos(direction) + *(circle+1);
    points[2] = *(circle+3) * sin(direction) + *(circle+2);
    points[3] = *(circle+0);
    points[4] = - *(circle+3) * cos(direction) + *(circle+1);
    points[5] = - *(circle+3) * sin(direction) + *(circle+2);

    return points;
}


// float * Leg::traceArc(float x){
//     static float *circle;
//     float rRot;

//     circle = mobilityCircle(x);
//     //0 -> P1x, 1 -> P1y, 2 -> P1z
//     //3 -> P2x, 4 -> P2y, 5 -> P2z
//     //6 -> radius of rotation circle
//     float *points = new float[6];

//     rRot = ;

    

//     return points;

// }

int * Leg::determineLegStateForHeight(float x){

    static float *circle;

    //0 -> Pcx, 1 -> Pcy, 2 -> Pcz
    int *angles = new int[6];

    circle = mobilityCircle(x);

    angles = angFromPos(*(circle+0), *(circle+1), *(circle+2));

    return angles;
}
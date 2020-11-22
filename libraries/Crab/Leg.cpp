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

float * Leg::angFromPos(float x, float y, float z){
    float l, alpha, beta, gamma, m, M, C, a, b, c;
    bool cond1 = false;
    bool cond2 = false;
    static float results[4];
    bool pos = false;

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
    beta = (M_PI - atan2((l - a),x) - C) * 180 / M_PI;
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

    results[0] = alpha;
    results[1] = beta;
    results[2] = gamma;
    results[3] = pos;

    return results;
}


//A cirlce in which a leg can move for a fixed value of x is obtained
float * Leg::movilityCircle(float x){
    float alpha, beta, gamma, theta, ymin, ymax, z,d;

    //0 -> centerx, 1 -> centery, 2-> centerz, 3->radius
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
    alpha = 90;

    //d is the third side of the triangle formed by b and c
    d = sqrt(pow(b,2)+pow(c,2)-2*b*c*cos(180-gamma));

    //Theta is the angle between b and d
    theta = c/d*sin(180-gamma);

    //analyzing the geometry the following equation is obtained
    beta = -acos( x /(-d)) + 180 - theta;

    //Once beta is obtained, ymax can be calculated using the geometry of the robot
    ymax = (a + d * sin(180-beta-theta))*sin(alpha);

    //Then ymnin
    
    //For simplicity ymin will be equal to the lenth of the first link
    ymin = a;

    //Then the center of the circle of movement is calculated.
    //This value is the one recieved given that the circle is on a plane
    circleParam[0] = x;
    //This value is an average of ymin and ymax but adjusted to give it some room
    circleParam[1] = ( ( ymin * 1.15 ) + ymax ) / 2;
    //Thjis value is equal to 0 because the circle must be centered
    circleParam[2] = 0;

    //Then the radio
    //This has another adjustment to give it room to work properly
    circleParam[3] = ( ymax - ymin * 1.15 ) / 2 * 0.9;

    return circleParam;
}

//This functions traces a line inside the limits of the movility circle in the direction specified
//direction argument is defined as 0 along the y axis,it's positive in the direction of the z axis
int * traceLine(float direction){
    
}
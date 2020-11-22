#include "Leg.h"
#include "esp32-hal-cpu.h"
#include <cmath>

Leg::Leg(int shoulderIndex, int elbowIndex, int wristIndex, int shoulderLinkLength, int elbowLinkLength, int wristLinkLength){  
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

void angFromPos(float x, float y, float z){
    // float l = sqrt(pow(x, 2) + pow(y,2));
    // float alpha = atan2(y, x);
    // float m = sqrt(pow(x,2));

}
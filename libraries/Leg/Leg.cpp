#include "Leg.h"

Leg::Leg(int shoulderIndex, int elbowIndex, int wristIndex, int shoulderLinkLength, int elbowLinkLength, int wristLinkLength){  
    Leg::shoulderIndex=shoulderIndex;
    Leg::elbowIndex=elbowIndex;
    Leg::wristIndex=wristIndex;

    Leg::shoulderLinkLength=shoulderLinkLength;
    Leg::elbowLinkLength=elbowLinkLength;
    Leg::wristLinkLength=wristLinkLength;

    

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

void Leg::setLegState(int shoulderAngle, int elbowAngle, int wristAngle){
    //Set new desired state, this is a promise, the angle is not set yet
    shoulderFutureAngle=shoulderAngle;
    elbowFutureAngle=elbowAngle;
    wristFutureAngle=wristAngle;
}

void Leg::setStart(){
    //Start the legs at a determined state
    Leg::shoulderFutureAngle=90;
    Leg::elbowFutureAngle=90;
    Leg::wristFutureAngle=90;

    updateLegPlease();
}

void Leg::updateLegPlease(){
    //Fulfill the promise of the desired angle
    moveServo(Leg::shoulderIndex, Leg::shoulderFutureAngle);
    moveServo(Leg::elbowIndex, 180-Leg::elbowFutureAngle);
    moveServo(Leg::wristIndex, Leg::wristFutureAngle);
    
    //once the promise is fulfilled, the register of the current angle is updated
    shoulderAngle = shoulderFutureAngle;
    elbowAngle = elbowFutureAngle;
    wristAngle = wristFutureAngle;
}

int Leg::pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}

void Leg::moveServo(int servoID, int angle) {
    if(servoID < 9){
        pwm1.setPWM(servoDriver[servoID], 0, pulseWidth(angle));

        
    }
    else{
        pwm2.setPWM(servoDriver[servoID], 0, pulseWidth(angle));
    }
}
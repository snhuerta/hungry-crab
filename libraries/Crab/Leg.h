#ifndef __Leg
#define __Leg
 
#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PULSE_WIDTH 550
#define MAX_PULSE_WIDTH 2399
#define FREQUENCY 50 // MG90s runs at  ~50 Hz updates

class Leg {
	public:
		int angleOffset;

		//0 -> shoulder, 1 -> elbow, 2 -> wrist
		int indices[3] = {0,0,0};
		int angles[3] = {0,0,0};
		int futureAngles [3] = {0,0,0};
		int linkLengths[3] = {0,0,0};

		Adafruit_PWMServoDriver pwm1;
    	Adafruit_PWMServoDriver pwm2;

		Leg(int shoulderIndex, int elbowIndex, int wristIndex, int shoulderLinkLength, int elbowLinkLength, int wristLinkLength);

		void setLegState(int shoulderAngle, int elbowAngle, int wristAngle);
		void setStart();
		void updateLegPlease();
		int pulseWidth(int angle);
		void moveServo(int servoID, int angle);
		void angFromPos(float x, float y, float z);

	private:
		uint8_t servoDriver[18] = {0,2,4,6,8,10,12,14,15,0,2,4,6,8,10,12,14,15};
};

#endif
#ifndef __Crab
#define __Crab
 
#include "Mano.h"
#include "Leg.h"
#include <Arduino.h>
#include "BluetoothSerial.h"
#include <string>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif



class Crab {
    public:
        bool updatingLegs;
        bool updatingLeg[6];
        String message;
        char incomingChar;
        float recievedDirection;
        bool recievedCW;
        bool moveFlag;
        bool rotateFlag;
        bool pickUpFlag;
        bool stopFlag;

        Leg legs[6] = {
            Leg(0,1,2,37,45,70),
            Leg(3,4,5,37,45,70),
            Leg(6,7,8,37,45,70),
            Leg(9,10,11,37,45,70),
            Leg(12,13,14,37,45,70),
            Leg(15,16,17,37,45,70)
        };

        BluetoothSerial SerialBT;
        Mano mano;

        Crab();
        
        void updateLegsSyncPlease();
        void checkAllMotors();
        void moveInALine(float direction, float x);
        void moveToAHeight(float x);
        void rotate(bool dir, float x);
        void grabSequence();
        void recieveMessage();
        void stopSequence();
};

#endif
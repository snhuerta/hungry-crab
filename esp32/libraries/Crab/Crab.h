#ifndef __Crab
#define __Crab
 
#include "Mano.h"
#include "Leg.h"
#include <Arduino.h>


class Crab {
    public:
        bool updatingLegs;
        bool updatingLeg[6];

        Leg legs[6] = {
            Leg(0,1,2,37,45,70),
            Leg(3,4,5,37,45,70),
            Leg(6,7,8,37,45,70),
            Leg(9,10,11,37,45,70),
            Leg(12,13,14,37,45,70),
            Leg(15,16,17,37,45,70)
        };

        Mano mano;

        Crab();
        
        void updateLegsSyncPlease();
        void checkAllMotors();
        void moveInALine(float direction, float x);
        void moveToAHeight(float height);
        void rotate(float x, bool dir);
        void grabSequence();
};

#endif
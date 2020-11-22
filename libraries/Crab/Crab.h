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
            Leg(0,1,2,10,10,10),
            Leg(3,4,5,10,10,10),
            Leg(6,7,8,10,10,10),
            Leg(9,10,11,10,10,10),
            Leg(12,13,14,10,10,10),
            Leg(15,16,17,10,10,10),
        };

        Mano mano;

        Crab();
        
        void updateLegsSyncPlease();
        void checkAllMotors();
};

#endif
#ifndef __Mano;
#define __Mano;

#include<Arduino.h>
#include <Stepper.h>

#define IN1 33
#define IN2 25
#define IN3 26
#define IN4 27

class Mano{
    public:
        void nomNom();
        void nomNomOpen();
        void nomNomClose();

        Mano();

    private:
        const int stepsPerRevolution = 2038;
        Stepper myStepper;
};

#endif
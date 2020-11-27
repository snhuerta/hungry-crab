#include "Mano.h"

Mano::Mano() : myStepper(stepsPerRevolution,IN1,IN3,IN2,IN4){

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    myStepper.setSpeed(15);
}

void Mano::nomNom(){
    myStepper.step(2*stepsPerRevolution);
    delay(1000);
    myStepper.step(-2*stepsPerRevolution);
    delay(5000);
}

void Mano::nomNomOpen(){
    myStepper.step(2.3*stepsPerRevolution);
    delay(1000);
}

void Mano::nomNomClose(){
    myStepper.step(-2.3*stepsPerRevolution);
    delay(1000);
}

#include <Crab.h>

Crab::Crab(){


}

void Crab::updateLegsSyncPlease(){
    updatingLegs = true;
    //do this for every leg
    for(int i = 0; i < 6 ; i++){
        //check if leg are already updated
        //if yes, keep getting closer to the goal value
        //if not, update legs by a predetermined value
        updatingLeg[i] = true;
        
        if(legs[i].shoulderAngle != legs[i].shoulderFutureAngle){
            if(legs[i].shoulderAngle < legs[i].shoulderFutureAngle){
                legs[i].shoulderAngle = legs[i].shoulderAngle + 2;
                legs[i].moveServo(legs[i].shoulderIndex, legs[i].shoulderAngle);
            }else{
                legs[i].shoulderAngle = legs[i].shoulderAngle - 2;
                legs[i].moveServo(legs[i].shoulderIndex, legs[i].shoulderAngle);
            }
        }

        if(legs[i].elbowAngle != legs[i].elbowFutureAngle){
            if(legs[i].elbowAngle < legs[i].elbowFutureAngle){
                legs[i].elbowAngle = legs[i].elbowAngle + 2;
                legs[i].moveServo(legs[i].elbowIndex, legs[i].elbowAngle);
            }else{
                legs[i].elbowAngle = legs[i].elbowAngle - 2;
                legs[i].moveServo(legs[i].elbowIndex, legs[i].elbowAngle);
            }
        }

        if(legs[i].wristAngle != legs[i].wristFutureAngle){
            if(legs[i].wristAngle < legs[i].wristFutureAngle){
                legs[i].wristAngle = legs[i].wristAngle + 2;
                legs[i].moveServo(legs[i].wristIndex, legs[i].wristAngle);
            }else{
                legs[i].wristAngle = legs[i].wristAngle - 2;
                legs[i].moveServo(legs[i].wristIndex, legs[i].wristAngle);
            }
        }

        if(legs[i].shoulderAngle == legs[i].shoulderFutureAngle && legs[i].elbowAngle == legs[i].elbowFutureAngle && legs[i].wristAngle == legs[i].wristFutureAngle){
            updatingLeg[i] = false;
        }

        
        delay(10);
    }

    if(!updatingLeg[0] && !updatingLeg[1] && !updatingLeg[2] && !updatingLeg[3] && !updatingLeg[4] && !updatingLeg[5]){
            updatingLegs = false;
    }
}
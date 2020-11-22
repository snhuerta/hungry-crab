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
        
        for(int j = 0 ; j < 3 ; j++){
            if(legs[i].angles[j] != legs[i].futureAngles[j]){
                if(legs[i].angles[j] < legs[i].futureAngles[j]){
                    legs[i].angles[j] = legs[i].angles[j] + 1;
                    legs[i].moveServo(legs[i].indices[j], legs[i].angles[j]);
                }else{
                    legs[i].angles[j] = legs[i].angles[j] - 1;
                    legs[i].moveServo(legs[i].indices[j], legs[i].angles[j]);
                }
            }
        }

        if(legs[i].angles[0] == legs[i].futureAngles[0] && legs[i].angles[1] == legs[i].futureAngles[1] && legs[i].angles[2] == legs[i].futureAngles[2]){
            updatingLeg[i] = false;
        }
        
        delay(2);
    }

    if(!updatingLeg[0] && !updatingLeg[1] && !updatingLeg[2] && !updatingLeg[3] && !updatingLeg[4] && !updatingLeg[5]){
            updatingLegs = false;
    }
}

void Crab::checkAllMotors(){
    for(int i = 0; i < 6 ; i++)
        legs[i].setLegState(90,50,180);
    
    do{
    updateLegsSyncPlease(); 
    }while(updatingLegs);

    for(int i = 0; i < 6 ; i++)
        legs[i].setLegState(90,180,20);

    do{
    updateLegsSyncPlease(); 
    }while(updatingLegs);

}
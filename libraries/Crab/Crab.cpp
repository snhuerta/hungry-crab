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
        
        delayMicroseconds(2000);
    }

    if(!updatingLeg[0] && !updatingLeg[1] && !updatingLeg[2] && !updatingLeg[3] && !updatingLeg[4] && !updatingLeg[5]){
            updatingLegs = false;
    }
}

void Crab::checkAllMotors(){
    for(int i = 0; i < 6 ; i++)
        legs[i].setLegState(50,50,180);
    
    do{
    updateLegsSyncPlease(); 
    }while(updatingLegs);

    for(int i = 0; i < 6 ; i++)
        legs[i].setLegState(130,180,20);

    do{
    updateLegsSyncPlease(); 
    }while(updatingLegs);
}

void Crab::moveInALine(float direction, float x){
    static float ajusteAng[6] = {-30,-90,-150,-210,-270,-330};
    float *defPts0;
    float *defPts1;
    float *defPts2;
    float *defPts3;
    float *defPts4;
    float *defPts5;
    int *angs0;
    int *angs1;
    int *angs2;
    int *angs3;
    int *angs4;
    int *angs5;

    //has to be even
    static int pasos = 200;

    int k;
    int clearance = 30;

    defPts0 = legs[0].traceLine( direction + ajusteAng[0], x );
    defPts1 = legs[1].traceLine( direction + ajusteAng[1], x );
    defPts2 = legs[2].traceLine( direction + ajusteAng[2], x );
    defPts3 = legs[3].traceLine( direction + ajusteAng[3], x );
    defPts4 = legs[4].traceLine( direction + ajusteAng[4], x );
    defPts5 = legs[5].traceLine( direction + ajusteAng[5], x );

    for(int j = 0; j < pasos/2 ; j++){
        angs0 = legs[0].angFromPos(*(defPts0+0) + (*(defPts0+3) - *(defPts0+0)) * j / pasos , *(defPts0+1) +  (*(defPts0+4) - *(defPts0+1)) * j / pasos,*(defPts0+2) + (*(defPts0+5) - *(defPts0+2)) * j / pasos);
        legs[0].setLegState(*(angs0+0),*(angs0+1),*(angs0+2));

        angs1 = legs[1].angFromPos(*(defPts1+0) + (*(defPts1+3) - *(defPts1+0)) * (j+pasos/2) / pasos , *(defPts1+1) +  (*(defPts1+4) - *(defPts1+1)) * (j+pasos/2) / pasos,*(defPts1+2) + (*(defPts1+5) - *(defPts1+2)) * (j+pasos/2) / pasos);
        legs[1].setLegState(*(angs1+0),*(angs1+1),*(angs1+2));

        angs2 = legs[2].angFromPos(*(defPts2+0) + (*(defPts2+3) - *(defPts2+0)) * j / pasos , *(defPts2+1) +  (*(defPts2+4) - *(defPts2+1)) * j / pasos,*(defPts2+2) + (*(defPts2+5) - *(defPts2+2)) * j / pasos);
        legs[2].setLegState(*(angs2+0),*(angs2+1),*(angs2+2));

        angs3 = legs[3].angFromPos(*(defPts3+0) + (*(defPts3+3) - *(defPts3+0)) * (j+pasos/2) / pasos , *(defPts3+1) +  (*(defPts3+4) - *(defPts3+1)) * (j+pasos/2) / pasos,*(defPts3+2) + (*(defPts3+5) - *(defPts3+2)) * (j+pasos/2) / pasos);
        legs[3].setLegState(*(angs3+0),*(angs3+1),*(angs3+2));

        angs4 = legs[4].angFromPos(*(defPts4+0) + (*(defPts4+3) - *(defPts4+0)) * j / pasos , *(defPts4+1) +  (*(defPts4+4) - *(defPts4+1)) * j / pasos,*(defPts4+2) + (*(defPts4+5) - *(defPts4+2)) * j / pasos);
        legs[4].setLegState(*(angs4+0),*(angs4+1),*(angs4+2));

        angs5 = legs[5].angFromPos(*(defPts5+0) + (*(defPts5+3) - *(defPts5+0)) * (j+pasos/2) / pasos , *(defPts5+1) +  (*(defPts5+4) - *(defPts5+1)) * (j+pasos/2) / pasos,*(defPts5+2) + (*(defPts5+5) - *(defPts5+2)) * (j+pasos/2) / pasos);
        legs[5].setLegState(*(angs5+0),*(angs5+1),*(angs5+2));

        do{
            updateLegsSyncPlease();
        }while(updatingLegs);        
    }

    defPts1 = legs[1].traceLine( direction + ajusteAng[1], x + clearance);
    defPts3 = legs[3].traceLine( direction + ajusteAng[3], x + clearance);
    defPts5 = legs[5].traceLine( direction + ajusteAng[5], x + clearance);

    for(int j = pasos/2; j <= pasos ; j++){
        angs0 = legs[0].angFromPos(*(defPts0+0) + (*(defPts0+3) - *(defPts0+0)) * j / pasos , *(defPts0+1) +  (*(defPts0+4) - *(defPts0+1)) * j / pasos,*(defPts0+2) + (*(defPts0+5) - *(defPts0+2)) * j / pasos);
        legs[0].setLegState(*(angs0+0),*(angs0+1),*(angs0+2));

        angs1 = legs[1].angFromPos(*(defPts1+0) + (*(defPts1+3) - *(defPts1+0)) * (pasos - (j - pasos / 2)*2) / pasos , *(defPts1+1) +  (*(defPts1+4) - *(defPts1+1)) * (pasos - (j - pasos / 2)*2) / pasos,*(defPts1+2) + (*(defPts1+5) - *(defPts1+2)) * (pasos - (j - pasos / 2)*2) / pasos);
        legs[1].setLegState(*(angs1+0),*(angs1+1),*(angs1+2));

        angs2 = legs[2].angFromPos(*(defPts2+0) + (*(defPts2+3) - *(defPts2+0)) * j / pasos , *(defPts2+1) +  (*(defPts2+4) - *(defPts2+1)) * j / pasos,*(defPts2+2) + (*(defPts2+5) - *(defPts2+2)) * j / pasos);
        legs[2].setLegState(*(angs2+0),*(angs2+1),*(angs2+2));

        angs3 = legs[3].angFromPos(*(defPts3+0) + (*(defPts3+3) - *(defPts3+0)) * (pasos - (j - pasos / 2)*2) / pasos , *(defPts3+1) +  (*(defPts3+4) - *(defPts3+1)) * (pasos - (j - pasos / 2)*2) / pasos,*(defPts3+2) + (*(defPts3+5) - *(defPts3+2)) * (pasos - (j - pasos / 2)*2) / pasos);
        legs[3].setLegState(*(angs3+0),*(angs3+1),*(angs3+2));

        angs4 = legs[4].angFromPos(*(defPts4+0) + (*(defPts4+3) - *(defPts4+0)) * j / pasos , *(defPts4+1) +  (*(defPts4+4) - *(defPts4+1)) * j / pasos,*(defPts4+2) + (*(defPts4+5) - *(defPts4+2)) * j / pasos);
        legs[4].setLegState(*(angs4+0),*(angs4+1),*(angs4+2));

        angs5 = legs[5].angFromPos(*(defPts5+0) + (*(defPts5+3) - *(defPts5+0)) * (pasos - (j - pasos / 2)*2) / pasos , *(defPts5+1) +  (*(defPts5+4) - *(defPts5+1)) * (pasos - (j - pasos / 2)*2) / pasos,*(defPts5+2) + (*(defPts5+5) - *(defPts5+2)) * (pasos - (j - pasos / 2)*2) / pasos);
        legs[5].setLegState(*(angs5+0),*(angs5+1),*(angs5+2));

        do{
            updateLegsSyncPlease();
        }while(updatingLegs);        
    }

    defPts0 = legs[0].traceLine( direction + ajusteAng[0], x + clearance);
    defPts1 = legs[1].traceLine( direction + ajusteAng[1], x );
    defPts2 = legs[2].traceLine( direction + ajusteAng[2],x+clearance);
    defPts3 = legs[3].traceLine( direction + ajusteAng[3], x );
    defPts4 = legs[4].traceLine( direction + ajusteAng[4],x+clearance);
    defPts5 = legs[5].traceLine( direction + ajusteAng[5], x );

    for(int j = pasos; j >= pasos/2 ; j--){
        angs0 = legs[0].angFromPos(*(defPts0+0) + (*(defPts0+3) - *(defPts0+0)) * (pasos - (pasos - j)*2) / pasos, *(defPts0+1) +  (*(defPts0+4) - *(defPts0+1)) * (pasos - (pasos - j)*2) / pasos,*(defPts0+2) + (*(defPts0+5) - *(defPts0+2)) * (pasos - (pasos - j)*2) / pasos);
        legs[0].setLegState(*(angs0+0),*(angs0+1),*(angs0+2));

        angs1 = legs[1].angFromPos(*(defPts1+0) + (*(defPts1+3) - *(defPts1+0)) * (pasos-j) / pasos , *(defPts1+1) +  (*(defPts1+4) - *(defPts1+1)) * (pasos-j) / pasos,*(defPts1+2) + (*(defPts1+5) - *(defPts1+2)) * (pasos-j) / pasos);
        legs[1].setLegState(*(angs1+0),*(angs1+1),*(angs1+2));

        angs2 = legs[2].angFromPos(*(defPts2+0) + (*(defPts2+3) - *(defPts2+0)) * (pasos - (pasos - j)*2) / pasos , *(defPts2+1) +  (*(defPts2+4) - *(defPts2+1)) * (pasos - (pasos - j)*2) / pasos,*(defPts2+2) + (*(defPts2+5) - *(defPts2+2)) * (pasos - (pasos - j)*2) / pasos);
        legs[2].setLegState(*(angs2+0),*(angs2+1),*(angs2+2));

        angs3 = legs[3].angFromPos(*(defPts3+0) + (*(defPts3+3) - *(defPts3+0)) * (pasos-j) / pasos , *(defPts3+1) +  (*(defPts3+4) - *(defPts3+1)) * (pasos-j) / pasos,*(defPts3+2) + (*(defPts3+5) - *(defPts3+2)) * (pasos-j) / pasos);
        legs[3].setLegState(*(angs3+0),*(angs3+1),*(angs3+2));

        angs4 = legs[4].angFromPos(*(defPts4+0) + (*(defPts4+3) - *(defPts4+0)) * (pasos - (pasos - j)*2) / pasos , *(defPts4+1) +  (*(defPts4+4) - *(defPts4+1)) * (pasos - (pasos - j)*2) / pasos,*(defPts4+2) + (*(defPts4+5) - *(defPts4+2)) * (pasos - (pasos - j)*2) / pasos);
        legs[4].setLegState(*(angs4+0),*(angs4+1),*(angs4+2));

        angs5 = legs[5].angFromPos(*(defPts5+0) + (*(defPts5+3) - *(defPts5+0)) * (pasos-j) / pasos , *(defPts5+1) +  (*(defPts5+4) - *(defPts5+1)) * (pasos-j) / pasos,*(defPts5+2) + (*(defPts5+5) - *(defPts5+2)) * (pasos-j) / pasos);
        legs[5].setLegState(*(angs5+0),*(angs5+1),*(angs5+2));

        do{
            updateLegsSyncPlease();
        }while(updatingLegs);
    }
}
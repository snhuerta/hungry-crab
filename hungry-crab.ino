#include <Crab.h>

Crab* pCrab = NULL;

void setup(){
    pCrab = new Crab();
    delay(10000);
}

void loop(){
  pCrab->legs[0].setLegState(90,150,60);
  pCrab->legs[1].setLegState(90,150,60);
  pCrab->legs[2].setLegState(90,150,60);
  pCrab->legs[3].setLegState(90,150,60);
  pCrab->legs[4].setLegState(90,150,60);
  pCrab->legs[5].setLegState(90,150,60);
  
  do{
    pCrab->updateLegsSyncPlease(); 
  }while(pCrab->updatingLegs);

  delay(1000);
  
  pCrab->legs[0].setLegState(90,150,60);
  pCrab->legs[1].setLegState(90,90,00);
  pCrab->legs[2].setLegState(90,150,60);
  pCrab->legs[3].setLegState(90,90,00);
  pCrab->legs[4].setLegState(90,150,60);
  pCrab->legs[5].setLegState(90,90,00);
  
  do{
    pCrab->updateLegsSyncPlease();
  }while(pCrab->updatingLegs);

  delay(1000);
}

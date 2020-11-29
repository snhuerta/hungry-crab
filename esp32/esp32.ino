#include <Crab.h>

Crab* pCrab = NULL;

void setup() {
  pCrab = new Crab();
  delay(1000);
}

void loop() {
  pCrab->recieveMessage();


  if(pCrab->moveFlag == true){
    pCrab->moveInALine(pCrab->recievedDirection,-105);
  }

  if(pCrab->rotateFlag == true){
    pCrab->rotate(pCrab->recievedCW, -105);
  }

  if(pCrab->pickUpFlag == true){
    pCrab->grabSequence();
  }

  if(pCrab->stopFlag == true){
    pCrab->stopSequence();
  }
}

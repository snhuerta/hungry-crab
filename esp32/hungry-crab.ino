#include <Crab.h>

Crab* pCrab = NULL;

int *variables;
float *circle;
float *points;

void setup(){
  pCrab = new Crab();
  delay(1000);
  Serial.begin(115200);

}

void loop(){
//  pCrab->moveInALine(0, -105);
  for(int i = 0 ; i < 5 ; i++)
    pCrab->rotate(-105, true);

  for(int i = 0 ; i < 5 ; i++)
    pCrab->rotate(-105, false);  
}

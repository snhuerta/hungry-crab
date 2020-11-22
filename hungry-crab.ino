#include <Crab.h>

Crab* pCrab = NULL;

float *variables;
float *circle;

void setup(){
  pCrab = new Crab();
  delay(1000);
  Serial.begin(115200);

}

void loop(){
//  pCrab->checkAllMotors();
  circle = pCrab->legs[0].movilityCircle(-35);
  Serial.print("x: ");
  Serial.print(*(circle+0));
  Serial.print(" y: ");
  Serial.print(*(circle+1));
  Serial.print(" z: ");
  Serial.print(*(circle+2));
  Serial.print(" rad: ");
  Serial.println(*(circle+3));
  

//  variables = pCrab->legs[0].angFromPos(116,37,0);
//
//  Serial.print("a: ");
//  Serial.print(*(variables+0));
//  Serial.print(" b: ");
//  Serial.print(*(variables+1));
//  Serial.print(" g: ");
//  Serial.print(*(variables+2));
//  Serial.print(" pos: ");
//  Serial.println(*(variables+3));
}

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *myMotor = AFMS.getStepper(400, 1);
Adafruit_StepperMotor *myMotor2 = AFMS.getStepper(400, 2);

int vertical = 0; // Max 3500
int horizontal = 600; // Max 1200

const int maxVertical = 3500;
const int maxHorizontal = 1200;

void setup() {
  Serial.begin(9600);
  AFMS.begin();
  
  myMotor->setSpeed(20);
  myMotor2->setSpeed(20); 
}

void loop() {
 int motorNumber = random(1,3);
 int stepDirection = random(1,3);

  Serial.println("vertical : " + vertical);
  Serial.println("horizontal : " + horizontal);
  
 //Serial.println(motorNumber);
 //Serial.println(stepDirection);

 if (motorNumber == 1)
 {
    if (stepDirection == 1)
    {
      //Serial.println("1 Forward");
      int steps = random(10, 200);

      if (horizontal - steps/2 > 0 && vertical - steps/2 > 0){
        //Serial.println(steps);
        myMotor->step(steps, FORWARD, SINGLE); 
        horizontal -= steps;
        vertical -= steps;
       }
    }
    else
    {
      //Serial.println("1 Backward");
      int steps = random(10, 200);

      if (horizontal + steps/2 < maxHorizontal && vertical + steps/2 < maxVertical){
        //Serial.println(steps);
        myMotor->step(steps, BACKWARD, SINGLE); 
        horizontal += steps;
        vertical += steps;
      }
    }
 }
 else
 {
    if (stepDirection == 1)
    {
      //Serial.println("2 Forward");
      int steps = random(10, 200);

      if (horizontal - steps/2 > 0 && vertical + steps/2 < maxVertical){
        //Serial.println(steps);
        myMotor2->step(steps, FORWARD, SINGLE); 
        horizontal -= steps;
        vertical += steps;
      }
    }
    else
    {
      //Serial.println("2 Backward");
      int steps = random(10, 200);

      if (horizontal + steps/2 < maxHorizontal && vertical - steps/2 > 0){
        //Serial.println(steps);
        myMotor2->step(steps, BACKWARD, SINGLE); 
        horizontal += steps;
        vertical -= steps;
      }
    }
 }
}

















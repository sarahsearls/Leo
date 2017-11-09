#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *myMotor1 = AFMS.getStepper(400, 2);
Adafruit_StepperMotor *myMotor2 = AFMS.getStepper(400, 1);

int loopCount = 1;
bool increase = false;
int pixelWidth = 40;
int rowWidth = 40;

void setup() {
  Serial.begin(9600);
  AFMS.begin();
  
  myMotor1->setSpeed(10);
  myMotor2->setSpeed(10); 

}

void loop() {
  BasicSquareWave(loopCount);
  loopCount += 2;
}

void BasicSquareWave(int steps){
  myMotor1->step(rowWidth, FORWARD, SINGLE);
  myMotor2->step(pixelWidth, FORWARD, SINGLE);
  myMotor1->step(rowWidth, BACKWARD, SINGLE);
  myMotor2->step(pixelWidth, FORWARD, SINGLE); 
  steps--;
  if (steps > 0)
  {
    BasicSquareWave(steps);
  }
}


void UndulatingWave() {
  myMotor1->step(rowWidth, FORWARD, SINGLE);
  myMotor2->step(pixelWidth, FORWARD, SINGLE);
  myMotor1->step(rowWidth, BACKWARD, SINGLE);
  myMotor2->step(pixelWidth, FORWARD, SINGLE);
  loopCount++;

  if (increase)
  {
    pixelWidth += 5;
  }
  else
  {
    pixelWidth -= 5;
  }

  
  if (pixelWidth == 25)
  {
    increase = false;
  }
  if (pixelWidth == 5)
  {
    increase = true;
  }
}

















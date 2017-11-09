#include <Adafruit_Motor_Shield_V2_Library/Wire.h>
#include <Adafruit_Motor_Shield_V2_Library/Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

void setup() {
  // put your setup code here, to run once:
  Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
  Adafruit_StepperMotor *myMotor = AFMS.getStepper(400, 1);
  setSpeed(30)

}

void loop() {
  // put your main code here, to run repeatedly:
  step(1, FORWARD, SINGLE) 
}

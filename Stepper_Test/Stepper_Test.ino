/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(400, 1);
Adafruit_StepperMotor *myMotor2 = AFMS.getStepper(400, 2);


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Stepper test!");

  Serial.println("Point 1a");
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  Serial.println("Point 1b");
  myMotor->setSpeed(20);  // 10 rpm  
  myMotor2->setSpeed(20); 
  
  Serial.println("Point 1c");
}

void loop() {
  Serial.println("Point 1d");
 int motorNumber = random(1,3);
 int stepDirection = random(1,3);
  Serial.println("Point 2");

 Serial.println(motorNumber);
 Serial.println(stepDirection);

 if (motorNumber == 1)
 {
    if (stepDirection == 1)
    {
      Serial.println("1 Forward");
      int steps = random(10, 200);
      Serial.println(steps);
        myMotor->step(steps, FORWARD, SINGLE); 
    }
    else
    {
      Serial.println("1 Backward");
            int steps = random(10, 200);
      Serial.println(steps);
        myMotor->step(steps, BACKWARD, SINGLE); 
    }
 }
 else
 {
    if (stepDirection == 1)
    {
      Serial.println("2 Forward");
            int steps = random(10, 200);
      Serial.println(steps);
        myMotor2->step(steps, FORWARD, SINGLE); 
    }
    else
    {
      Serial.println("2 Backward");
            int steps = random(10, 200);
      Serial.println(steps);
        myMotor2->step(steps, BACKWARD, SINGLE); 
    }
 }

}

















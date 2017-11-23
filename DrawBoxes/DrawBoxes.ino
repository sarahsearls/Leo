//TODO
//- One dimensional array - DONE
//- Execute the order - DONE
//-- Write draw function - DONE
//-- Write moveTo function - DONE
//- Two dimensional arrays, with multiple instructions - DONE
//- Import instructions - POSTPONED
//- Parse instructions into a two-dimensional array - POSTPONED
//- Add a feature so that it doesn't exceed the paper limits
//- Move to, through roads
//- Export shit from Python
//- Read data from SD card

//Concerns
//- This will just keep looping through those things, I need it to do one thing only one time

#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *myMotor1 = AFMS.getStepper(400, 1);
Adafruit_StepperMotor *myMotor2 = AFMS.getStepper(400, 2);

#define memory 100

int sensorPin = A0;

int maxX = 1200;
int maxY = 3500;

int corePosX = maxX/2;
int corePosY = 0;

bool movingRight = true; 

int soundLevel = 0;

int motorSpeed = 30;

int soundMemory[memory];

int instructions[][4] = {
                          {500,100,50,50},
                          {200,300,100,100},
                          {0,2000,200,200}
                          };
int totalOrders = 3;

void setup() {
  Serial.begin(9600);
  AFMS.begin();

  myMotor1->setSpeed(motorSpeed);  
  myMotor2->setSpeed(motorSpeed); 

  pinMode(sensorPin, INPUT);
}

void loop() {

  for(int i=0; i<totalOrders; i++){
    draw(instructions[i][0],instructions[i][1],instructions[i][2],instructions[i][3]);  
  }

  return;
}

void draw(int x, int y, int sizeX, int sizeY){
  moveTo(x,y);
  right(sizeX);
  down(sizeY);
  left(sizeX);
  up(sizeY);
}

void moveTo(int x, int y){
  
  if(x > corePosX) right(x-corePosX);
  else left(corePosX - x);

  if(y > corePosY) down(y-corePosY);
  else up(corePosY - y);
  
}

void up(int length) {
  drawVerticalLine(length, false);
  corePosY -= length;
}

void down(int length) {
  drawVerticalLine(length, true); 
  corePosY += length;
}

void right(int length) {
  drawHorizontalLine(length, false);
  corePosX += length;
}

void left(int length) {
  drawHorizontalLine(length, true);
  corePosX -= length;
}

void drawHorizontalLine(int length, bool leftToRight) {
  int motor = 1;
  while (length > 0){
    //listenSounds();
    if (motor == 1){
      myMotor1->step(1, leftToRight ? FORWARD : BACKWARD, SINGLE);
      motor = 2;
    }
    else
    {
      myMotor2->step(1, leftToRight ? FORWARD : BACKWARD, SINGLE);
      motor = 1;
    }
    length--;
  }
  
}

void drawVerticalLine(int length, bool topDown) {
  int motor = 1;
  while (length > 0){
    //listenSounds();
    if (motor == 1){
      myMotor1->step(1, topDown ? BACKWARD : FORWARD, SINGLE);
      motor = 2;
    }
    else
    {
      myMotor2->step(1, topDown ? FORWARD : BACKWARD, SINGLE);
      motor = 1;
    }
    length--;
  } 
}
















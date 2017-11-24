//TODO
//- One dimensional array - DONE
//- Execute the order - DONE
//-- Write draw function - DONE
//-- Write moveTo function - DONE
//- Two dimensional arrays, with multiple instructions - DONE
//- Export shit from Python
//-- Export current orders - IN PROGRESS
//-- Format them (size and exact shape)
//- Add a feature so that it doesn't exceed the paper limits

//FUTURE
//- Read data from SD card
//- Import instructions - POSTPONED
//- Parse instructions into a two-dimensional array - POSTPONED
//- Figure out how to draw texts
//- Move to, through roads

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

int instructions[][5] = {
                          {0, 600, 1188, 24, 8}, {552, 696, 96, 96, 2.2}, {564, 576, 84, 84, 3.0}, {636, 696, 72, 96, 2.6}, {480, 672, 84, 72, 2.5}, {504, 576, 72, 84, 2.8}, {648, 576, 24, 144, 7}, {564, 792, 84, 96, 5}, {564, 504, 84, 84, 2.9}, {672, 576, 84, 96, 2.1}, {696, 696, 96, 96, 2.7}, {432, 576, 84, 72, 2.4}, {408, 684, 84, 84, 2.6}, {756, 576, 24, 204, 7}, {504, 768, 48, 96, 5}, {564, 432, 84, 72, 2.6}, {672, 492, 72, 96, 2.1}, {360, 576, 84, 96, 2.5}, {780, 684, 96, 84, 2.8}, {348, 684, 72, 84, 2.5}, {648, 432, 24, 156, 7}, {480, 492, 84, 48, 5}, {780, 576, 96, 84, 2.7}, {576, 372, 72, 96, 2.5}, {264, 684, 96, 84, 2.9}, {288, 576, 84, 72, 2.5}, {780, 504, 96, 72, 2.3}, {876, 756, 24, 156, 7}, {648, 756, 84, 60, 5}, {780, 756, 96, 84, 2.1}, {672, 408, 72, 84, 2.5}, {864, 576, 72, 84, 2.7}, {564, 288, 84, 96, 2.3}, {900, 696, 72, 96, 2.7}, {684, 768, 192, 24, 7}, {552, 876, 96, 84, 5}, {648, 864, 72, 96, 2.1}, {708, 840, 72, 72, 2.6}, {228, 576, 72, 84, 2.9}, {672, 336, 84, 72, 2.8}, {780, 444, 96, 84, 2.3}, {252, 780, 24, 180, 7}, {432, 744, 72, 60, 5}, {276, 768, 84, 96, 3.0}, {768, 852, 72, 84, 2.2}, {924, 576, 84, 72, 3.0}, {636, 276, 84, 96, 2.3}, {180, 672, 72, 72, 2.9}, {276, 780, 228, 24, 7}, {468, 444, 96, 72, 5}, {480, 876, 72, 96, 2.5}, {396, 876, 96, 96, 2.3}, {744, 372, 96, 96, 2.1}, {960, 684, 96, 84, 2.2}, {144, 576, 96, 84, 2.2}, {384, 912, 24, 132, 7}, {408, 480, 60, 60, 5}, {900, 780, 72, 96, 2.8}, {348, 756, 84, 84, 2.6}, {408, 960, 84, 96, 2.3}, {828, 840, 96, 72, 2.7}, {312, 852, 72, 72, 2.0}, {1008, 576, 24, 96, 7}, {492, 372, 72, 84, 5}, {936, 516, 72, 72, 2.4}, {96, 672, 96, 72, 2.7}, {156, 756, 96, 96, 2.6}, {1032, 576, 84, 84, 2.5}, {1044, 672, 96, 72, 2.2}, {132, 576, 24, 240, 7}, {564, 948, 84, 72, 5}, {156, 504, 72, 96, 2.9}, {240, 864, 84, 84, 2.6}, {288, 936, 96, 84, 2.5}, {60, 576, 72, 96, 2.9}, {12, 672, 96, 72, 2.1}, {156, 408, 240, 24, 7}, {312, 480, 96, 48, 5}, {372, 384, 96, 72, 2.2}, {228, 480, 84, 72, 2.5}, {312, 384, 72, 84, 2.8}, {228, 384, 96, 84, 2.9}, {168, 828, 84, 84, 3.0}, {396, 1068, 24, 156, 7}, {648, 936, 60, 72, 5}, {420, 1020, 84, 72, 2.4}, {996, 480, 84, 84, 2.6}, {420, 1092, 84, 84, 3.0}, {300, 1020, 96, 96, 2.8}, {36, 492, 96, 72, 2.7}, {1116, 576, 24, 132, 7}, {564, 1032, 84, 84, 5}, {1068, 444, 96, 84, 2.6}, {0, 576, 72, 72, 2.3}, {168, 384, 72, 72, 2.7}, {324, 1080, 72, 72, 2.5}, {36, 432, 96, 96, 2.5}, {1140, 732, 24, 132, 7}, {468, 288, 96, 84, 5}, {1068, 744, 72, 84, 2.5}, {1044, 804, 96, 72, 2.0}, {336, 1164, 96, 96, 2.2}, {108, 336, 72, 96, 2.2}, {1104, 828, 84, 96, 2.7}, {1164, 576, 24, 240, 7}, {504, 948, 60, 72, 5}, {1080, 372, 84, 72, 3.0}, {1044, 504, 72, 72, 2.2}, {672, 276, 96, 96, 2.9}, {876, 864, 84, 96, 2.4}, {780, 372, 84, 96, 2.3}, {0, 744, 24, 144, 7}, {708, 924, 60, 60, 5}, {24, 732, 72, 72, 2.4}, {24, 804, 72, 84, 2.2}, {1116, 336, 72, 72, 2.0}, {900, 768, 96, 84, 2.3}, {900, 852, 96, 96, 2.1}, {12, 912, 24, 168, 7}, {540, 192, 96, 84, 5}, {36, 876, 84, 84, 2.5}
};
// Right now, x and y axises between the programs are messed up

int totalOrders = 100;

void setup() {
  Serial.begin(9600);
  AFMS.begin();

  myMotor1->setSpeed(motorSpeed);  
  myMotor2->setSpeed(motorSpeed); 

  pinMode(sensorPin, INPUT);

  delay(5000);
}

void loop() {

  for(int i=0; i<totalOrders; i++){
    draw(instructions[i][1],instructions[i][0],instructions[i][3],instructions[i][2]); // Don't forget that x and y axises are mixed up  
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
















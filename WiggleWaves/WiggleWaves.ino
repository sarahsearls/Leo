#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *myMotor1 = AFMS.getStepper(400, 1);
Adafruit_StepperMotor *myMotor2 = AFMS.getStepper(400, 2);

#define memory 100

int sensorPin = A0;
int sensorTime = 0;

int maxX = 1200;
int maxY = 3500;

int corePosX = maxX/2;
int corePosY = 0;

bool movingRight = true; 

int soundLevel = 0;

int motorSpeed = 30;

int soundMemory[memory];

void setup() {
  Serial.begin(9600);
  AFMS.begin();

  myMotor1->setSpeed(motorSpeed);  
  myMotor2->setSpeed(motorSpeed); 

  pinMode(sensorPin, INPUT);
}

void loop() {

  sensorTime++;
  
  if (corePosY > maxY) {
    return;
  }
  
  if(corePosX >= maxX || corePosX <= 0) {
    movingRight = !movingRight;
    down(60);
  }

  for(int i=0; i<2 ;i++){
    int wiggleY = random(-10,10);
    int wiggleX = random(-10,10);
    wiggle(wiggleX, wiggleY);
  }

  movingRight ? right(2) : left(2);
}

void wiggle(int deltaX, int deltaY){
  deltaX>0 ? right(deltaX) : left(deltaX * -1);
  deltaY>0 ? up(deltaY) : down(deltaY * -1);
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
    listenSounds();
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
    listenSounds();
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

void listenSounds(){
  
  int val = analogRead(sensorPin);

  int minSound = 1200;
  int maxSound = 0;

  soundMemory[memory-1] = val;
  
  for(int i=0; i<memory-1;i++) {
    soundMemory[i] = soundMemory[i+1];
    if(soundMemory[i] < minSound) minSound = soundMemory[i];
    if(soundMemory[i] > maxSound) maxSound = soundMemory[i];
  }

  soundLevel = maxSound - minSound;
  //if(soundLevel > 1) Serial.println (soundLevel);
  
  //Serial.println (soundMemory[4]);
  
}


void printInt(String label, int integer)
{
  Serial.print(label);
  Serial.print(integer);
  Serial.println("");
}



// Basic horizontal line algorithm: 
void BasicHorizontalLine(){
  if (corePosY > maxY) {
    return;
  }
  
  if(corePosX >= maxX || corePosX <= 0) {
    movingRight = !movingRight;
    down(50);
  }
  
  movingRight ? right(2) : left(2);
}

















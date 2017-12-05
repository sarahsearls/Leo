
#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *myMotor1 = AFMS.getStepper(400, 1);
Adafruit_StepperMotor *myMotor2 = AFMS.getStepper(400, 2);

#define intensity 7

//int sensorPin = A0;
int piezoPin = 7;

int maxX = 1200;
int maxY = 3500;

int currentAmplitude = 0;

int corePosX = maxX/2;
int corePosY = 0;

bool movingRight = true; 

int motorSpeed = 30;

void setup() {
  Serial.begin(9600);
  AFMS.begin();

  myMotor1->setSpeed(motorSpeed);  
  myMotor2->setSpeed(motorSpeed); 

  
  delay(5000);

}

void loop() {

  // Make sound
  tone(piezoPin, 250,5000);
  delay(5000);
  
  
  // Build 1st layer, boxes
  for(int i=0; i<intensity; i++){
    int boxSize = random(5,15)*50;
    build(random(500,1200),random(0, 2000), boxSize, boxSize);
  
  }

  moveTo(maxX/2, 1000);
  // Make sounds
  tone(piezoPin, 500,5000);
  delay(5000);

  
  
  // Build 2nd layer, waves
  for(int i=0; i<intensity*40; i++){
    
    int amp = random(-30,30);
    wave(amp);
  
  }
  

  // Make sounds
  moveTo(maxX/4, 400);
  tone(piezoPin, 750,5000);
  delay(5000);
  // Build 3rd layer, wiggles

  
  
  for(int i=0; i<intensity*10 ;i++){
    
    int wiggleY = random(-10,10);
    int wiggleX = random(-10,15);
    wiggle(wiggleX, wiggleY);
  
  }


  // Make sound
  tone(piezoPin, 1000, 10000);
  delay(10000);
  
  return;
}

void build(int x, int y, int sizeX, int sizeY){
    
  draw(x,y,sizeX,sizeY);
  
}

void wave(int newAmp){

  int moveAmp = newAmp - currentAmplitude;
  currentAmplitude = newAmp;
    
  if(moveAmp>=0){
    up(moveAmp);
  }
  else down(moveAmp*-1);
  
  if(movingRight) right(10);
  else left(10);

  if(corePosX >= maxX){
    down(65);
    movingRight = false;
  }
  else if(corePosX <= 0){
    down(65);
    movingRight = true;
  }
  
}

void wiggle(int deltaX, int deltaY){
  deltaX>0 ? right(deltaX) : left(deltaX * -1);
  deltaY>0 ? up(deltaY) : down(deltaY * -1);
}


void draw(int x, int y, int sizeX, int sizeY){
  moveTo(x,y);
  left(sizeX);
  down(sizeY);
  right(sizeX);
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
















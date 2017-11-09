#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *myMotor1 = AFMS.getStepper(400, 1);
Adafruit_StepperMotor *myMotor2 = AFMS.getStepper(400, 2);

#define memory 100

int sensorPin = A0;
int sensorTime = 0;

int maxX = 1200;
int maxY = 3500;
int posX = maxX/2;
int posY = 0;
int pastAmp = 0;
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
  int val = analogRead(sensorPin);
  //val = analogRead(sensorPin);
  //Serial.println (sensorTime);
  //if(val<52) 
  //delay(500);
  //Serial.println (val, DEC);


  
  if (posY > maxY) {
    return;
  }
  
  if(posX >= maxX || posX <= 0) {
    movingRight = !movingRight;
    down(60);
  }

  int amp = soundLevel*5;
  if (amp>50) amp = 50;

  myMotor1->setSpeed(amp);  
  myMotor2->setSpeed(amp); 
  
  Serial.println (amp);
  flux(amp-pastAmp);
  pastAmp = amp;

  movingRight ? right(2) : left(2);
}

void flux(int delta){
  if (delta > 0)
  {
    up(delta);
  }
  else
  {
    down(-1 * delta);
  }
}

void up(int length) {
  drawVerticalLine(length, false);
  posY -= length;
}

void down(int length) {
  drawVerticalLine(length, true); 
  posY += length;
}

void right(int length) {
  drawHorizontalLine(length, false);
  posX += length;
}

void left(int length) {
  drawHorizontalLine(length, true);
  posX -= length;
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
  if (posY > maxY) {
    return;
  }
  
  if(posX >= maxX || posX <= 0) {
    movingRight = !movingRight;
    down(50);
  }
  
  movingRight ? right(2) : left(2);
}

















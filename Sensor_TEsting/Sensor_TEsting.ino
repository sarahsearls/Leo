int sensorPin = A0;
int sensorTime = 0;

int maxX = 1200;
int maxY = 3500;
int posX = maxX/2;
int posY = 0;
int pastAmp = 0;
bool movingRight = true; 

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {

  int val = analogRead(sensorPin);
  //val = analogRead(sensorPin);
  //Serial.println (sensorTime);
  //if(val<52) 
  delay(50);
  Serial.println (val, DEC);
}

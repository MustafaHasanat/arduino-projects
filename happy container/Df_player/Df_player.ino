#include <Keypad.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mine(13, 12);
DFRobotDFPlayerMini player;

int strip1 = 2;
int strip2 = 3;
int strip3 = 4;

int trig1 = 5;
int echo1 = 6;

int trig2 = 7;
int echo2 = 8;
int trig3 = 10;
int echo3 = 9;

float read1;
float read2;
float read3;

float thr = 6.0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  return pulseIn(echoPin, HIGH);
}

void playIt() {
    player.play(1);
    delay(5000);
    Serial.println("finished !!!");
  }

void setup() {
  Serial.begin(9600);
  mine.begin(9600);
  
  pinMode(trig1 ,OUTPUT);  pinMode(echo1 ,INPUT);
  pinMode(trig2 ,OUTPUT);  pinMode(echo2 ,INPUT);
  pinMode(trig3 ,OUTPUT);  pinMode(echo3 ,INPUT);
  
  pinMode(strip1 ,OUTPUT);
  pinMode(strip2 ,OUTPUT);
  pinMode(strip3 ,OUTPUT);

  digitalWrite(strip1, HIGH);
  digitalWrite(strip2, HIGH);
  digitalWrite(strip3, HIGH);
  
  while(!player.begin(mine)) {
    Serial.println("Connecting to DFPlayer Mini failed!");
    delay(2000);}
    
    Serial.println("OK");
    player.volume(30);
}

void loop() {

  read1 = 0.01723 * readUltrasonicDistance(trig1, echo1);
  read2 = 0.01723 * readUltrasonicDistance(trig2, echo2);
  read3 = 0.01723 * readUltrasonicDistance(trig3, echo3); 

  if(read1 < thr) {
    digitalWrite(strip2, HIGH);
    digitalWrite(strip3, HIGH);
    for(int s=0; s<4; s++){
      digitalWrite(strip1, HIGH);
      delay(100);
      digitalWrite(strip1, LOW);
      delay(100);
      }
    playIt();
    } 
    
  else if(read2 < thr) {
     digitalWrite(strip1, HIGH);
    digitalWrite(strip3, HIGH);
     for(int s=0; s<4; s++){
      digitalWrite(strip2, HIGH);
      delay(100);
      digitalWrite(strip2, LOW);
      delay(100);
      }
    playIt();
    } 

  else if(read3 < thr) {
     digitalWrite(strip1, HIGH);
    digitalWrite(strip2, HIGH);
    for(int s=0; s<4; s++){
      digitalWrite(strip3, HIGH);
      delay(100);
      digitalWrite(strip3, LOW);
      delay(100);
      }
    playIt();
    }

    
  delay(10);
  
}

#include <Servo.h>
Servo myservo; 
int serv = 9;
int angle1 = 0;
int angle2 = 180;

// these pins for the 4 wheels 
int LF = 4;  
int LB = 5;  
int RB = 6;  
int RF = 7; 
char val;  
// left forward, left backward, right backward, right forward, received value

// these pins for distance sensor
long distance;
int Trig = 2;
int Echo = 3;
int thr = 10;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup() 
 { myservo.attach(serv); 
   myservo.write(angle1);
  
   pinMode(LF, OUTPUT);  
   pinMode(LB, OUTPUT);
   pinMode(RB, OUTPUT);
   pinMode(RF, OUTPUT);

   pinMode(Trig, OUTPUT);
   pinMode(Echo, INPUT);

   Serial.begin(9600); }


void control(bool x1, bool x2, bool x3, bool x4) 
 { digitalWrite(LF, x1);  
   digitalWrite(LB, x2);
   digitalWrite(RB, x3);
   digitalWrite(RF, x4); }


void sanitize(){
  control(LOW, LOW, LOW, LOW);
  Serial.println("sanitized");
  for(int j=angle1; j<angle2; j++){
  myservo.write(j);  delay(10);  }
  
  delay(5000);
  
  Serial.println("stop sanitizing");
  for(int k=angle2; k>angle1; k--){
  myservo.write(k);  delay(10);  }
  }


void loop()
{
  while (Serial.available() > 0) { val = Serial.read();  Serial.println(val); }

  distance = 0.01723 * readUltrasonicDistance(Trig, Echo);
  Serial.print("distance : "); Serial.println(distance);

       if (distance <= thr)  { sanitize();  }
  else if(val == 'F') { control(LOW, HIGH, HIGH, LOW); } // Forward
  else if(val == 'B') { control(HIGH, LOW, LOW, HIGH); } // Backward
  else if(val == 'L') { control(LOW, HIGH, LOW, HIGH); } //Left
  else if(val == 'R') { control(HIGH, LOW, HIGH, LOW); } //Right    
  else if(val == 'S') { control(LOW, LOW, LOW, LOW); }   //Stop
  else if(val == 'J') { control(LOW, LOW, LOW, HIGH); }  // Forward left
  else if(val == 'I') { control(LOW, LOW, HIGH, LOW); }  // Backward left 
  else if(val == 'H') { control(HIGH, LOW, LOW, LOW); }  // Forward right 
  else if(val == 'G') { control(LOW, HIGH, LOW, LOW); }  // Backward right 

  delay(1);

}

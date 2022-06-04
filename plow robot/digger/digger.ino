#include <Servo.h>
Servo myservo;

int LF = 4 ;  
int LB = 5;  
int RB = 6;  
int RF = 7; 

char val;  

int offset = 0;
int holes = 0;

void control(bool x1, bool x2, bool x3, bool x4) 
 { digitalWrite(LF, x1);  
   digitalWrite(LB, x2);
   digitalWrite(RB, x3);
   digitalWrite(RF, x4); 
   delay(200);
   digitalWrite(LF, LOW);  
   digitalWrite(LB, LOW);
   digitalWrite(RB, LOW);
   digitalWrite(RF, LOW);}

void startt(){
  for(int i = 0; i < holes; i++){
  control(LOW, HIGH, HIGH, LOW);
  digitalWrite(LF, LOW);  
   digitalWrite(LB, HIGH);
   digitalWrite(RB, HIGH);
   digitalWrite(RF, LOW);
  delay(offset);
  control(LOW, LOW, LOW, LOW);
    for(int j=0; j<160; j++){
      myservo.write(j); 
      delay(15);
    }
    delay(300);
    for(int j=160; j>0; j--){
      myservo.write(j); 
      delay(15);
    }
  }
}

void setup() 
 { pinMode(LF, OUTPUT);  
   pinMode(LB, OUTPUT);
   pinMode(RB, OUTPUT);
   pinMode(RF, OUTPUT);

   myservo.attach(9);
   myservo.write(0);
   Serial.begin(9600);
   }

void loop()
{
  while (Serial.available() > 0) { 
    val = Serial.read();  
    Serial.println(val); }
    
       if(val == 'F') { control(LOW, HIGH, HIGH, LOW); } // Forward
  else if(val == 'B') { control(HIGH, LOW, LOW, HIGH); } // Backward
  else if(val == 'L') { control(HIGH, LOW, HIGH, LOW); } //Left
  else if(val == 'R') { control(LOW, HIGH, LOW, HIGH); } //Right    
  else if(val == '1') { offset = offset + 500; }
  else if(val == '2') { offset = offset - 500; }
  else if(val == '3') { holes++; }
  else if(val == '4') { holes--; }
  else if(val == 'S') { startt(); } //start
  val = 'N';

  delay(100);

}

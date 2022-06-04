#define left A0
#define right A1

int LF = 4;  
int LB = 5;  
int RB = 6; 
int RF = 7; 
int S = 9;

void control(bool x1, bool x2, bool x3, bool x4) 
 { digitalWrite(LF, x1); 
 digitalWrite(LB, x2); 
 digitalWrite(RB, x3); 
 digitalWrite(RF, x4); }

void setup() {
 pinMode(LF, OUTPUT);  
 pinMode(LB, OUTPUT);  
 pinMode(RB, OUTPUT);  
 pinMode(RF, OUTPUT); 

 pinMode(S, OUTPUT);
  
  pinMode(left,INPUT);
  pinMode(right,INPUT);
  Serial.begin(9600);

  analogWrite(S, 120);
  
}

void loop(){
 
  //line detected by both
  if(digitalRead(left)==0 && digitalRead(right)==0){
    //Forward
    analogWrite(S, 100);
    control(HIGH, LOW, LOW, HIGH);
    Serial.println("Forward");
  }
  
  //line detected by left sensor
  else if(!digitalRead(left)==0 && digitalRead(right)==0){
    //turn left
    analogWrite(S, 120);
   control(LOW, HIGH, LOW, HIGH);
   Serial.println("Left");
  }
  
  //line detected by right sensor
  else if(digitalRead(left)==0 && !digitalRead(right)==0){
    //turn right
    analogWrite(S, 120);
    control(HIGH, LOW, HIGH, LOW);
    Serial.println("Right");
  }
  //line detected by none
  else if(!digitalRead(left)==0 && !digitalRead(right)==0){
    //stop
  control(LOW, LOW, LOW, LOW);
  Serial.println("Stop"); 
  }

  delay(10);
  
}

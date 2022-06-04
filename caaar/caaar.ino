int LF = 2;  
int LB = 3;  
int RB = 4;  
int RF = 5; 
char val;  
// left forward, left backward, right backward, right forward, received value
  
void setup() 
 { pinMode(LF, OUTPUT);  
   pinMode(LB, OUTPUT);
   pinMode(RB, OUTPUT);
   pinMode(RF, OUTPUT);
   pinMode(A4, OUTPUT);
   pinMode(A5, OUTPUT);
   Serial.begin(9600); }

void control(bool x1, bool x2, bool x3, bool x4) 
 { digitalWrite(LF, x1);  
   digitalWrite(LB, x2);
   digitalWrite(RB, x3);
   digitalWrite(RF, x4); }

void loop()
{
  if(Serial.available() > 0) {
     val = Serial.read();
     Serial.println(val); }
  else { control(LOW, LOW, LOW, LOW);  }

       if(val == 'F') { control(HIGH, LOW, LOW, HIGH); } // Forward
  else if(val == 'B') { control(LOW, HIGH, HIGH, LOW); } // Backward
  else if(val == 'L') { control(LOW, HIGH, LOW, HIGH); } //Left
  else if(val == 'R') { control(HIGH, LOW, HIGH, LOW); } //Right    
  else if(val == 'S') { control(LOW, LOW, LOW, LOW); }   //Stop
  else if(val == 'G') { control(LOW, LOW, LOW, HIGH); }  // Forward left
  else if(val == 'H') { control(LOW, LOW, HIGH, LOW); }  // Backward left 
  else if(val == 'I') { control(HIGH, LOW, LOW, LOW); }  // Forward right 
  else if(val == 'J') { control(LOW, HIGH, LOW, LOW); }
  
  delay(10);
  }
//  else if(val == '0') { analogWrite(A4, 0); analogWrite(A5, 0); }
//  else if(val == '1') { analogWrite(A4, 20); analogWrite(A5, 20); }
//  else if(val == '2') { analogWrite(A4, 40); analogWrite(A5, 40); }
//  else if(val == '3') { analogWrite(A4, 60); analogWrite(A5, 60); }
//  else if(val == '4') { analogWrite(A4, 80); analogWrite(A5, 80); }
//  else if(val == '5') { analogWrite(A4, 100); analogWrite(A5, 100); }
//  else if(val == '6') { analogWrite(A4, 120); analogWrite(A5, 120); }
//  else if(val == '7') { analogWrite(A4, 140); analogWrite(A5, 140); }
//  else if(val == '8') { analogWrite(A4, 160); analogWrite(A5, 160); }
//  else if(val == '9') { analogWrite(A4, 180); analogWrite(A5, 180); }
//  else if(val == 'q') { analogWrite(A4, 200); analogWrite(A5, 200); }}  // Backward right 
  



  

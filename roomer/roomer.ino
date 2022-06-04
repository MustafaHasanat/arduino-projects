#define left A0
#define right A1
#define check1 A2
#define check2 A3

char val = '0';
char r1 = '1';
char r2 = '2';
char Stop = 'S';
char Resume = 'R';

char Manual = 'm';
int manu_state = 0;

char Forward = 'f';
char Backward = 'b';
char Left = 'l';
char Right = 'r';

int LF = 4;  
int LB = 5;  
int RB = 6; 
int RF = 7; 
int Spe = 9;

String state = "stop";
int room = 0;

void control(bool x1, bool x2, bool x3, bool x4) 
 { digitalWrite(LF, x1); 
 digitalWrite(LB, x2); 
 digitalWrite(RB, x3); 
 digitalWrite(RF, x4); }

void circle(){
  //line detected by both
  if(digitalRead(left)==0 && digitalRead(right)==0){
    analogWrite(Spe, 100);
    control(HIGH, LOW, LOW, HIGH); } //Forward
  
  //line detected by left sensor
  else if(!digitalRead(left)==0 && digitalRead(right)==0){
   analogWrite(Spe, 140);
   control(LOW, HIGH, LOW, HIGH); } //turn left 
  
  //line detected by right sensor
  else if(digitalRead(left)==0 && !digitalRead(right)==0){
    analogWrite(Spe, 140);
    control(HIGH, LOW, HIGH, LOW); } //turn right 
    
  //line detected by none
  else if(!digitalRead(left)==0 && !digitalRead(right)==0){
  control(LOW, LOW, LOW, LOW); } //stop 

  delay(10);
  }

void manual(){
  manu_state = 1;
    while(manu_state==1){
       if(Serial.available() > 0){
          val = Serial.read(); Serial.println(val);
      if(val == 'F') { control(HIGH, LOW, LOW, HIGH); } // Forward
  else if(val == 'B') { control(LOW, HIGH, HIGH, LOW); } // Backward
  else if(val == 'L') { control(LOW, HIGH, LOW, HIGH); } //Left
  else if(val == 'R') { control(HIGH, LOW, HIGH, LOW); } //Right  
  else if(val == 'm') { manu_state = 0; } //Right    
  else { control(LOW, LOW, LOW, LOW); }   //Stop
  val = 'x';  }}
  }

void Room(int num){
   while(){
   circle();
        if(!digitalRead(check1)==0 && digitalRead(check1)==0){ control(LOW, LOW, LOW, LOW); }
   else if(!digitalRead(check2)==0 && !digitalRead(check2)==0){ room = 2; }
  }}

void setup() {
 pinMode(LF, OUTPUT); pinMode(LB, OUTPUT); pinMode(RB, OUTPUT); pinMode(RF, OUTPUT); 
 pinMode(Spe, OUTPUT);
 pinMode(left,INPUT); pinMode(right,INPUT); pinMode(check1,INPUT); pinMode(check2,INPUT);
 Serial.begin(9600);
 
 analogWrite(Spe, 120); 
}

void loop(){
 if(Serial.available() > 0){
   val = Serial.read(); Serial.println(val);

        if(val==r1) { state = "room1"; }
   else if(val==r2) { state = "room2"; }
   else if(val==Stop) { state = "stop"; }
   else if(val==Resume) { state = "loop"; }
   else if(val==Manual && manu_state==0) { state = "manual"; }
  }

      if(state == "loop"){ circle(); }
 else if(state=="room1") { room = 1; Room(1); }
 else if(state=="room2") { room = 2; Room(2); }
 else if(state=="stop") { control(LOW, LOW, LOW, LOW); }  
 else if(state=="manual") { manual(); }  
}

#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

float temp;
int LF = 2;  
int LB = 3;  
int RB = 4;  
int RF = 5; 
char val;

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


void get_temp(){
  for(int i=0; i<5; i++){
    temp = mlx.readObjectTempC();
    Serial.println(temp); 
    delay(50); }
}


void setup() {
  Serial.begin(9600);
   pinMode(LF, OUTPUT);  
   pinMode(LB, OUTPUT);
   pinMode(RB, OUTPUT);
   pinMode(RF, OUTPUT);
  mlx.begin();       
}

void loop() {

  if(Serial.available() > 0) {
     val = Serial.read(); }
  else { control(LOW, LOW, LOW, LOW);  }

       if(val == 'F') { control(HIGH, LOW, LOW, HIGH); } // Forward
  else if(val == 'B') { control(LOW, HIGH, HIGH, LOW); } // Backward
  else if(val == 'L') { control(LOW, HIGH, LOW, HIGH); } //Left
  else if(val == 'R') { control(HIGH, LOW, HIGH, LOW); } //Right   
  else if(val == 'T') { get_temp(); } 

  val = 'N';

  delay(100);
}

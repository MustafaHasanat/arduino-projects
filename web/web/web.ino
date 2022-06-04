#include <Servo.h>

Servo servo1;  

void setup() { 
  Serial.begin(9600);
  servo1.attach(6);      
}

void loop() {
    servo1.write(180); 
    delay(1000);
    servo1.write(90); 
    delay(1000);
}

#include <SPI.h>
#include <SD.h>
File f;

void setup() {

  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
  
  Serial.begin(9600);
  if(SD.begin(3))
    {Serial.println("SD is ready "); }
  else {Serial.println("SD failed"); return;}


  f = SD.open("nums.txt", FILE_READ);
  if(f){
    if(f.available()) {
     int a  = f.parseInt();
     int b  = f.parseInt();
     Serial.println(a);
     Serial.println(b);
     f.close();
    } else {Serial.println("error opening");}}
  

}


void loop() {

}

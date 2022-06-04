#include <SPI.h>
#include <SD.h>

char recv;
File file;

void setup() {
  Serial.begin(57600);
  if(SD.begin())
    {Serial.println("SD is ready "); }
  else {Serial.println("SD failed"); return;}
}

void loop() {
  if(Serial.available()){
    recv = Serial.read();
    Serial.println(recv);
  }

  if(recv == '^'){
    delay(5000);
    file = SD.open("NUMS.TXT", FILE_READ);
  if(file){
    if(file.available()) {
     float person1awards = file.parseFloat();
     float person2awards = file.parseFloat();
     Serial.println('^');
     Serial.println(person1awards);
     delay(2000);
     Serial.println('^');
     Serial.println(person2awards);
     file.close();
    } else {Serial.println("error opening");}}
   recv = " ";
  }

  if(recv == '%'){
    delay(2000);
    if(Serial.available()){
    while(Serial.read() != '^'){ }}
    float num1 = Serial.parseFloat();

    if(Serial.available()){
    while(Serial.read() != '^'){ }}
    float num2 = Serial.parseFloat();
        
    if(SD.exists("nums.txt")) { SD.remove("nums.txt"); }
    file = SD.open("nums.txt", FILE_WRITE);
    if(file){
      file.println(num1);
      file.println(num2);
      file.close();
    } else {Serial.println("error opening");} 

    Serial.println(num1);
    Serial.println(num2);
  }

  
}

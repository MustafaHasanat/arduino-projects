#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <virtuabotixRTC.h>
#include <Wire.h>

String x;
int X;

const int MPU_ADDR = 0x68; 
int16_t acc_x, acc_y, acc_z; 
int16_t gyro_x, gyro_y, gyro_z;
int16_t temp; 
char tmp_str[7]; 
char* convert(int16_t i) {
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void gyro() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); 
  Wire.endTransmission(false); 
  Wire.requestFrom(MPU_ADDR, 7*2, true); 

  acc_x = Wire.read()<<8 | Wire.read(); 
  acc_y = Wire.read()<<8 | Wire.read(); 
  acc_z = Wire.read()<<8 | Wire.read(); 
  temp = Wire.read()<<8 | Wire.read(); 
  gyro_x = Wire.read()<<8 | Wire.read(); 
  gyro_y = Wire.read()<<8 | Wire.read(); 
  gyro_z = Wire.read()<<8 | Wire.read(); 

  x = convert(acc_x); 
  X = x.toInt();
  delay(300);
}

SoftwareSerial mine(3, 2);
DFRobotDFPlayerMini player;
virtuabotixRTC myRTC(4, 5, 6);

void playIt(int num) {
    player.play(num);
    delay(10000);
    Serial.println("finished !!!");
  }

void setup() {
  Serial.begin(9600);
  mine.begin(9600);

  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
  // seconds, minutes, hours, day of the week, day of the month, month, year
  //myRTC.setDS1302Time(00, 55, 12, 5, 21, 10, 2021);

  pinMode(9, OUTPUT);

  while(!player.begin(mine)) {
      Serial.println("Connecting to DFPlayer Mini failed!");
      delay(2000);}
    Serial.println("OK");
    player.volume(30);
}

void loop() {

  myRTC.updateTime();
  int Dayofmonth = myRTC.dayofmonth;
  int Month = myRTC.month;
  int Year = myRTC.year;
  int Hour = myRTC.hours;
  int Min = myRTC.minutes;
  int Sec = myRTC.seconds;

  gyro();
  Serial.println(X);
  if(X < 10000) { 
    digitalWrite(9, HIGH); 
    }else{
      digitalWrite(9, LOW);  
    }
  
  delay(10);

  if((Min == 10)||(Min == 40)){ playIt(1); }
  else if((Min == 20)||(Min == 50)){ playIt(2); }
  else if((Min == 30)||(Min == 59)){ playIt(3); }
    
}

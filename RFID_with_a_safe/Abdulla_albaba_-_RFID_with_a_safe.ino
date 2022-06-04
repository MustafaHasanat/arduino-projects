#include <MFRC522.h>  // lib. for RFID sensor
#include <SPI.h>  // lib. for communication protocol
#include <Servo.h>  // lib. for servo motor

MFRC522 mfrc522(10, 9);  // initialize the sensor at pins 9,10
Servo myservo;  // initialize the servo

// define pins for LEDs and servo
int red_LED = 2;
int green_LED = 3;
int servo = 6;

void setup(){
  // begin the Serial monitor
  Serial.begin(9600);

  // attach the servo to its pin
  myservo.attach(servo);

  // attach LEDs to their pins
  pinMode(red_LED, OUTPUT);     digitalWrite(red_LED, HIGH);
  pinMode(green_LED, OUTPUT);   digitalWrite(green_LED, LOW);
  
  // begin the reading operation by the sensor
  while(!Serial);
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  mfrc522.PCD_DumpVersionToSerial();
  }


void loop(){

  // check for any card near the sensor (if any, print its ID)------------|
  if(!mfrc522.PICC_IsNewCardPresent()) {return;}  //                      |
  if(!mfrc522.PICC_ReadCardSerial()) {return;}    //                      |
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //                      |
  String content = "";                            //                      |
  byte letter;                                    //                      |  
  for(byte i=0; i<mfrc522.uid.size; i++){                     //          |
    Serial.print(mfrc522.uid.uidByte[i]<0x10 ? " 0":" ");     //          |
    Serial.print(mfrc522.uid.uidByte[i], HEX);                        //  |
    content.concat(String(mfrc522.uid.uidByte[i]<0x10 ? " 0":" "));   //  |
    content.concat(String(mfrc522.uid.uidByte[i], HEX));              //  |
    }                                                                 //  |
  content.toUpperCase();                                              //  |
  //----------------------------------------------------------------------|

  // if the ID of the last card detected was this one, open the safe for 5 seconds
  // but if it is not the one or nothing is near the sensor, close the safe 
  if(content.substring(1)=="2A E4 5D 1A"){
    myservo.write(0);                            // rotate the sensor to 0 degrees 
    digitalWrite(green_LED, HIGH);               // turn on the green LED
    digitalWrite(red_LED, LOW);                  // turn off the red LED
    delay(5000);
    digitalWrite(green_LED, LOW);
    digitalWrite(red_LED, HIGH);
    myservo.write(120);
    } else{
      myservo.write(120);                        // rotate the sensor to 120 degrees
      digitalWrite(green_LED, LOW);
      digitalWrite(red_LED, HIGH);
      }
  }

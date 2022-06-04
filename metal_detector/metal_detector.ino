#include <Servo.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>
#include <HX711_ADC.h>
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif

Servo servo; 
LiquidCrystal lcd(A5, A4, A3, A2, A1, A0);
MFRC522 mfrc522(10, 9);
HX711_ADC LoadCell(4, 5); // HX711_dout, HX711_sck
const int calVal_eepromAdress = 0;
unsigned long t = 0;

int metal = 2;
int red = 7;
int blue = 8;
float weight;
float award;
float Old;
float New;

String person1 = "Ahmed";
String person1ID = "07 8C 87 52";
float person1awards = 0;

String person2 = "Osama";
String person2ID = "F2 36 14 2C";
float person2awards = 0;

String selected = "none";


void setup() {
  Serial.begin(57600);   delay(3000);
  servo.attach(6); 
  Serial.println();
  Serial.println("Starting...");
  
  LoadCell.begin();
  float calibrationValue;
  calibrationValue = 696.0;
#if defined(ESP8266)|| defined(ESP32)
#endif
  EEPROM.get(calVal_eepromAdress, calibrationValue); unsigned long stabilizingtime = 2000;
  boolean _tare = true; 
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell.setCalFactor(calibrationValue);
    Serial.println("Startup is complete");
  }

  lcd.begin(16, 2);
  lcd.clear();  
  while (!Serial);   
  SPI.begin();     
  mfrc522.PCD_Init(); 
  delay(4);      
  mfrc522.PCD_DumpVersionToSerial(); 
  pinMode(metal, INPUT);
  pinMode(red, INPUT);
  pinMode(blue, INPUT);

  delay(500);
  Serial.println();
  Serial.println('^');
  delay(3000);

  if(Serial.available()){
    while(Serial.read() != '^'){ }}
  person1awards = Serial.parseFloat();
    
  if(Serial.available()){
    while(Serial.read() != '^'){ }}
  person2awards = Serial.parseFloat();

  Serial.println(person1awards);
  Serial.println(person2awards);

}


void loop() {
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Show your ID :");

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
    }                                                             
    content.toUpperCase();
    
   if(content.substring(1) == person1ID){ 
     selected = person1; }
   else if(content.substring(1) == person2ID){ 
     selected = person2; }

   if(selected != "none"){
     lcd.setCursor(0, 1);
     if(selected == person1) {lcd.print("Welcome Ahmed !");}
     else if(selected == person2) {lcd.print("Welcome Osama !");}
     delay(2000);

     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Metal Detecting ...");
     while(!digitalRead(metal)){
     if(!digitalRead(blue)){  // for displaying credits 
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(person1); lcd.print(": "); lcd.print(person1awards);
        lcd.setCursor(0, 1);
        lcd.print(person2); lcd.print(": "); lcd.print(person2awards);
        delay(5000);
         }
    
         if(!digitalRead(red)){  // for clearing credits 
            Serial.println('%');
            delay(1000);

            Serial.println('^');
            Serial.println(0.0);
            delay(2000);
            Serial.println('^');
            Serial.println(0.0);
            person1awards = 0;
            person2awards = 0;
            
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Data deleted !!!");
            delay(5000);
         }
      lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Metal Detecting ...");
      
      }

     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Weighting ...");

     for(int kk=0; kk<500; kk++){
        static boolean newDataReady = 0;
        const int serialPrintInterval = 0;
        if (LoadCell.update()) newDataReady = true;
        if (newDataReady) {
          if (millis() > t + serialPrintInterval) {
            float i = LoadCell.getData();  weight = i;  
            Serial.print("Load_cell output val: ");
            Serial.println(i);
            newDataReady = 0;
            t = millis();
          }}
        if (Serial.available() > 0) {
        char inByte = Serial.read();
        if (inByte == 't') LoadCell.tareNoDelay();}
        if (LoadCell.getTareStatus() == true) {
        Serial.println("Tare complete");}
        delay(10);
        }

        award = weight/100;
        lcd.setCursor(0, 1);
        lcd.print(weight); lcd.print("       "); 
        delay(3000);

     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Weight = "); lcd.print(weight);
     lcd.setCursor(0, 1);
     lcd.print("Award = "); lcd.print(award);
     delay(3000);

     if(selected == person1){ 
        Old = person1awards;
        New = person1awards + award;
        person1awards = New;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Old = "); lcd.print(Old);
        lcd.setCursor(0, 1);
        lcd.print("New = "); lcd.print(New);
        }
        
     else if(selected == person2){ 
        Old = person2awards;
        New = person2awards + award;
        person2awards = New; 
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Old = "); lcd.print(Old);
        lcd.setCursor(0, 1);
        lcd.print("New = "); lcd.print(New);
        }

      Serial.println('%');
      delay(1000);
  
      Serial.println('^');
      Serial.println(person1awards);
      delay(2000);
      Serial.println('^');
      Serial.println(person2awards);

      servo.write(-180); 
      delay(500);
      servo.write(90);
      delay(500);
       
      servo.write(180); 
      delay(800);
      servo.write(90);
      delay(500);
     
     delay(4000);
     selected = "none";   }
     
 
   delay(50);
}

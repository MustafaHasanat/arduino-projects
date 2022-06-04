#include <MFRC522.h>  // lib. for RFID sensor
#include <SPI.h>  // lib. for communication protocol
#include <LiquidCrystal.h>  // include the library for LCD
#include <DHT.h>            // include the library for DHT

// LCD initialization
LiquidCrystal lcd(32, 30, 28, 26, 24, 22); // initialize the library and connect its pins

// DHT sensor initialization
DHT dht(7, DHT11);  // initialize the library and connect its pin at pin7 with the sensor type DHT11
float humidity;         // a variable for humidity
float temperature;      // a variable for temperature

// RFID sensor initialization
MFRC522 mfrc522(53, 49);  // initialize the sensor at pins 5, 6
String myID = "3A 19 7D 80";
bool access = false;

// a function to print on the LCD screen
void lcd_print(int row, int col, String txt, String type) {
  if(type == "temp") {
    lcd.setCursor(row, col); lcd.print("                "); 
    lcd.setCursor(row, col); lcd.print("Temp. : ");  lcd.print(txt); lcd.print(" C");
    }
  else if(type == "humd") {
    lcd.setCursor(row, col); lcd.print("                "); 
    lcd.setCursor(row, col); lcd.print("Humd. : ");  lcd.print(txt); lcd.print(" %");
    }
  else{
    lcd.setCursor(row, col); lcd.print("                "); 
    lcd.setCursor(row, col); lcd.print(txt); 
    }
  }


void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows, and activate it 
  dht.begin();       // activate the DHT sensor 

  lcd.print("Waiting ...");
  
//   begin the reading operation by the RFID sensor
  while(!Serial);
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  mfrc522.PCD_DumpVersionToSerial();
  }


void loop(){

  humidity = dht.readHumidity();         // read humidity from the sensor
  temperature = dht.readTemperature();   // read temperature from the sensor

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

  // if my ID card has been passed the RFID sensor, allow access to the LCD to print data 
  if(content.substring(1) == myID){ 
    access = true;  
    } else{
      access = false; 
      }
      
    // check for the variable "access" and operate based on it
    if(access)
    {
      lcd_print(0, 0, String(temperature), "temp");  // print temp. reading on the LCD
      lcd_print(0, 1, String(humidity), "humd");     // print humd. reading on the LCD
      delay(5000);
      lcd_print(0, 0, "  ", "none");  // clear the LCD screen
      lcd_print(0, 1, "  ", "none");  // clear the LCD screen
    } else{
         lcd_print(0, 0, "Access denied !!!", "none");
         lcd_print(0, 1, "  ", "none");  // clear the LCD screen
      }
      
   delay(10);
  }

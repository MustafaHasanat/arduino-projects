#include <EEPROM.h>
#include "GravityTDS.h"
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// hoisting
int readTDS();
float readPH();
float calculatePH (float voltage);

int pHSensePin = A0;
int TdsSensorPin = A1;
int buzzerPin = 8;
int ONE_WIRE_BUS = 7;
float adc_resolution = 1024.0;
GravityTDS gravityTds;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup()
{
    Serial.begin(115200);
    lcd.begin(16,2);
    sensors.begin();
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(adc_resolution);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization
}

void loop()
{
    float temperature = readTemp();
    int tdsValue = readTDS(temperature);
    float phValue = readPH();

    if ( phValue<6.5 || phValue>9.0 || tdsValue<50 || tdsValue>1100){
        tone(buzzerPin, 450);
        delay(500);
        noTone(buzzerPin);
      }
    
    printOnLCD(tdsValue, phValue);

    delay(500);
}

//----------functions-------------
float readTemp(){
    sensors.requestTemperatures();
    float temperature = sensors.getTempCByIndex(0);
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
    return temperature;
}
 

int readTDS(float temperature){
    int tdsValue = 0;
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate 
    tdsValue = gravityTds.getTdsValue();  // then get the value
    Serial.print(tdsValue);
    Serial.println("ppm");
    return tdsValue;
}

float readPH(){
    int measurings=0;
    int samples = 10;
    for (int i = 0; i < samples; i++){
        measurings += analogRead(pHSensePin);
        delay(10);
    }
    float avgVoltage = 5 / adc_resolution * measurings/samples;
    float phValue = calculatePH(avgVoltage);
    Serial.print("pH= ");
    Serial.println(phValue);
    return phValue;
}

float calculatePH (float voltage) {
    return 7 + ((2.5 - voltage) / 0.18);
}

void printOnLCD(int tdsValue, float phValue){
    lcd.setCursor(0, 0);
    lcd.print("TDS: ");
    lcd.print(tdsValue,0);
    lcd.print(" PPM");
 
    lcd.setCursor(0, 1);
    lcd.print("PH: ");
    lcd.print(phValue);
    
    delay(1500);
    lcd.clear();
}

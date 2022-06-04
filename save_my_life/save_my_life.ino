#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS     1000
PulseOximeter pox;
uint32_t tsLastReport = 0;
void onBeatDetected()
{Serial.println("Beat!");}
int x=3;


float HeartRate;
float O2;
int flowState = 0;
int pin1 = 6;  int pin2 = 7;  int pin3 = 8;  int pin4 = 9;
int steps = 0;

void control(bool x1, bool x2, bool x3, bool x4){
  digitalWrite(pin1, x1);  digitalWrite(pin2, x2); 
  digitalWrite(pin3, x3);  digitalWrite(pin4, x4); 
  }

void on_step(){
    control(HIGH,LOW,LOW,LOW); delay(2);
    control(LOW,HIGH,LOW,LOW); delay(2);
    control(LOW,LOW,HIGH,LOW); delay(2);
    control(LOW,LOW,LOW,HIGH); delay(2);
}

void setup()
{ Serial.begin(115200);
  pinMode(3,OUTPUT);
  Serial.print("Initializing pulse oximeter..");
   if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
    pox.setOnBeatDetectedCallback(onBeatDetected);

   pinMode(pin1, OUTPUT);  pinMode(pin2, OUTPUT);
   pinMode(pin3, OUTPUT);  pinMode(pin4, OUTPUT);
   for(int i = 0; i<130; i++){
        on_step();  
      }
}



void loop()

{
    pox.update();
   if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        HeartRate = pox.getHeartRate();
        Serial.print(HeartRate);
        Serial.print("bpm / SpO2:");
        O2 = pox.getSpO2();        
        Serial.print(O2);
        Serial.println("%");
        tsLastReport = millis();
    }

    if((HeartRate > 85.0)&&(flowState == 0)){
      for(int i = 0; i<130; i++){
        on_step();  
      }
      flowState = 1;}

}

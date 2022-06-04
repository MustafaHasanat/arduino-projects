#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <SoftwareSerial.h>
SoftwareSerial mine(D7, D6);

float temp;

char auth[] = "xy6gBDXNPkGJk2VZFxjtmzfyf9QHT0mu";
char ssid[] = "Umniah-evo-Home-EE63";
char pass[] = "87654321";

BLYNK_READ(V5)
{ 
  temp = mine.parseFloat();
  if(temp != 0.0) { 
    Serial.println(temp);
    Blynk.virtualWrite(V5, temp);
}}

void setup()
{
  Serial.begin(115200);
  mine.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{ Blynk.run(); }

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "HX711.h"

char auth[] = "PnE1BXMojx-wkfcsOKVLuu7Or12fS5AG";
char ssid[] = "Umniah-evo-Home-EE63";
char pass[] = "87654321";

//char ssid[] = "Umniah_4E538";
//char pass[] = "startpchayyed550";

HX711 scale;
long reading;

BLYNK_READ(V5)
{
if(scale.is_ready()) {
    reading = scale.read();
    Blynk.virtualWrite(V5, reading);
    Serial.print("HX711 reading: ");
    Serial.println(reading);
  } else {Serial.println("HX711 not found.");}  
  delay(100);
}

void setup() {
  Blynk.begin(auth, ssid, pass);
  Serial.begin(115200);
  scale.begin(D6, D5);
  scale.set_scale(415.f);
  scale.tare();
  delay(2000);
}

void loop() { Blynk.run(); }

  

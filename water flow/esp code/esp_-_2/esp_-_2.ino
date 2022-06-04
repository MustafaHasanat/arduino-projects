#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "bpbFZuyi9ybvR7lISduS6IxS8PFdyFLk"; 
char ssid[] = "Umniah-evo-Home-EE63";
char pass[] = "87654321";

float water;

BLYNK_READ(V5)
{ 
   water = Serial2.parseFloat();
   if(water != 0.0){
     Blynk.virtualWrite(V5, water);
     Serial.println(water);
   }
}

void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}

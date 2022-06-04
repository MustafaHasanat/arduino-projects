#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "BlQGPPH5dKi-JGbXkDQVkEfvyefIXdYh";
char ssid[] = "ORANGE_4498";
char pass[] = "qwer12345";

int recv;

BLYNK_READ(V5)
{ 
   recv = analogRead(A0);
   Serial.println(recv);
   if(recv > 200){ 
      Blynk.virtualWrite(V5, 1); } 
   else { 
      Blynk.virtualWrite(V5, 0); }
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(A0, INPUT);
}

void loop()
{
  Blynk.run();
}

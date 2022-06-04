#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>

#include <SoftwareSerial.h>
SoftwareSerial mine(D7, D6);

char auth[] = "NnzrY4EZDyJMOpiz5FO2g0GRcCFzbZ5S";
char ssid[] = "Galaxy A21s2CE1";
char pass[] = "12345678";

int recv;

BLYNK_READ(V5)
{ 
   recv = mine.parseInt();
   
   if(recv == 1){ Blynk.virtualWrite(V5, 1);  Serial.println(11); }
   else if(recv == 5){ Blynk.virtualWrite(V5, 0);  Serial.println(10); }
   
   if(recv == 2){ Blynk.virtualWrite(V2, 1);  Serial.println(21); }
   else if(recv == 6){ Blynk.virtualWrite(V2, 0);  Serial.println(20); }
   
   if(recv == 3){ Blynk.virtualWrite(V3, 1);  Serial.println(31); }
   else if(recv == 7){ Blynk.virtualWrite(V3, 0);  Serial.println(30); }
   
   if(recv == 4){ Blynk.virtualWrite(V4, 1);  Serial.println(41); }
   else if(recv == 8){ Blynk.virtualWrite(V4, 0);  Serial.println(40); }
}

void setup()
{
  Serial.begin(115200);
  mine.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}

#include <ESP8266WiFi.h>

const char* ssid = "Umniah_4E538";             
const char* password = "startpchayyed550";   

const char* apiKey = "WMFQvawdt2tMjVfe8Wr0s";
const char* eventName = "ESP";
const char* host = "maker.ifttt.com";
const int port = 80;

int buttonPin = D5;
char* buttonState = "Idle";

void setup() 
{  
  Serial.begin(115200);
  Serial.println("\n\nIFTTT Test\n");
  WiFi.begin(ssid, password);

  Serial.print("Connecting to network");
  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(200);    
    if (++counter > 100) 
      ESP.restart();
    Serial.print( "." );
  }
  Serial.println("\nWiFi connected");
  pinMode(buttonPin, INPUT);
  Serial.println("All configured. Waiting for button press...");
}

void loop() 
{
  if(digitalRead(buttonPin) == HIGH)
  {
    Serial.print("Blue button is presssed !");
    int r=0; int g=0; int b=0; 
    
    for(int j=0; j<3; j++){
     for(int i=2; i<NUM_LEDS; i++) {
      if(j==0){r=0; g=0; b=1;}
      if(j==1){r=0; g=1; b=0;}
      if(j==2){r=1; g=0; b=0;}
      leds[i] = CRGB(255*r, 255*g, 255*b);
      FastLED.show(); 
      delay(50); }}

        
    Serial.print("Connecting to "); Serial.print(host); Serial.print(':'); Serial.println(port);
    WiFiClient client;
    
    if (!client.connect(host, port)) 
    { Serial.println("connection failed"); delay(5000); return; }

    if (client.connected()) 
    { String url = "/trigger/"; url += eventName; url += "/with/key/"; url += apiKey;
      Serial.println("Sending trigger to server"); Serial.println(url);
      client.print(String("POST ") + url + " HTTP/1.1\r\n" +
             "Host: " + host + "\r\n" + 
             "Content-Type: application/x-www-form-urlencoded\r\n" + 
             "Content-Length: 15\r\n\r\n" +
             "value1=" + buttonState + "\r\n"); }
    Serial.println("Trigger sent. Waiting for a bit..."); delay(1*60*1000); 
    Serial.println("Ready for new trigger");  
  }
}

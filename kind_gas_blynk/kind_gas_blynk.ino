#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <FastLED.h>

char auth[] = "PnE1BXMojx-wkfcsOKVLuu7Or12fS5AG";
char ssid[] = "Umniah_4E538";
char pass[] = "startpchayyed550";  

//const char* ssid = "Umniah-evo-Home-EE63";             
//const char* password = "87654321";   

int blue = D5;
int red = D6;

int redState = 0;
int blueState = 0;

#define LED_PIN     D7
#define NUM_LEDS    15
CRGB leds[NUM_LEDS];


BLYNK_READ(V5)
{
  redState = digitalRead(red);
  blueState = digitalRead(blue);
  
  if(blueState){
    Blynk.virtualWrite(V5, 1);
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
  } else {
      Blynk.virtualWrite(V5, 0);
    }

  if(redState){
    Serial.println("Red button is presssed !");
    for(int i=0; i<NUM_LEDS; i++) {
      leds[i] = CRGB(0, 0, 0);
      FastLED.show(); 
      delay(30); }
  }
}

void setup() 
 { 
  Blynk.begin(auth, ssid, pass);
  Serial.begin(115200);

   FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
   pinMode(red, INPUT);
   pinMode(blue, INPUT);
   }


void loop()
{ Blynk.run(); }

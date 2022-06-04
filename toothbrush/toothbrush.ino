#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#include <FastLED.h>
#define LED_PIN     9
#define NUM_LEDS    12
CRGB leds[NUM_LEDS];

SoftwareSerial mine(3, 2);
DFRobotDFPlayerMini player;

int relay = 5;
int ir = 4;

int counter = 0;

void playIt() {
    player.play(1);
    delay(5000);
    Serial.println("finished !!!");
  }
  
void setup() {
   pinMode(relay, OUTPUT);
   pinMode(ir, INPUT);

   mine.begin(9600);
   FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
   
}

void loop() {
   int ir_read = digitalRead(ir);

   if(ir_read == 1){
     digitalWrite(relay, LOW);
     for(int i=0; i<NUM_LEDS; i++) {
      leds[i] = CRGB(0, 0, 0);
      FastLED.show();
    }
   } else {
     digitalWrite(relay, HIGH);
     for(int i=0; i<NUM_LEDS; i++) {
      leds[i] = CRGB(255, 0, 0);
      FastLED.show();
    }
   }

   if(counter > 500) { playIt(); counter = 0;}

   counter++;
   delay(10);
}

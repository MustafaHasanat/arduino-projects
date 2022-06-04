#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Servo.h>

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);  
DallasTemperature sensors(&oneWire);

#include <FastLED.h>
#define LED_PIN     5
#define NUM_LEDS    12
CRGB leds[NUM_LEDS];

Servo mine;

float temp;
char val;
int relay = 7;

void setup(void)
{ sensors.begin(); 
  Serial.begin(9600); 
  pinMode(relay, OUTPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  mine.attach(9, 500, 2500);
  mine.write(120);
}

void loop(void)
{ 
  while(Serial.available()>0) { 
    val = Serial.read();
    Serial.print(val);}
  
  sensors.requestTemperatures(); 
  temp = sensors.getTempCByIndex(0);
  Serial.print(temp);

  if(val == 'F'){
    mine.write(0);
    delay(500);
    mine.write(120); }

  if(val == 'R')
    {for(int i=0; i<NUM_LEDS; i++) {
      leds[i] = CRGB(255, 0, 0);
      FastLED.show(); }}

  else if(val == 'G')
    {for(int i=0; i<NUM_LEDS; i++) {
      leds[i] = CRGB(0, 255, 0);
      FastLED.show(); }}

  else if(val == 'B')
    {for(int i=0; i<NUM_LEDS; i++) {
      leds[i] = CRGB(0, 0, 255);
      FastLED.show(); }}

  else if(val == 'S')
    {for(int i=0; i<NUM_LEDS; i++) {
      leds[i] = CRGB(0, 0, 0);
      FastLED.show(); }}

  val = ' ';
  
  delay(100);
}

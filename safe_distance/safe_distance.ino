#include <FastLED.h>
#define LED_PIN     3
#define NUM_LEDS    20
CRGB leds[NUM_LEDS];

int LF = 4 ;  
int LB = 5;  
int RB = 6;  
int RF = 7; 
char val;  

long distance1;
int Trig1 = 10;
int Echo1 = 11;

long distance2;
int Trig2 = 8;
int Echo2 = 9;

float thr1 = 10;
float thr2 = 30;
float thr3 = 50;

bool connectState = false;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void control(bool x1, bool x2, bool x3, bool x4) 
 { digitalWrite(LF, x1);  
   digitalWrite(LB, x2);
   digitalWrite(RB, x3);
   digitalWrite(RF, x4); }

void light(int thr){
  if(thr == 1){
    for(int i=0; i<NUM_LEDS; i++) {
      leds[i] = CRGB(255, 0, 0);
      FastLED.show();
    }}
  else if(thr == 2){
    for(int i=0; i<NUM_LEDS; i++) {
      leds[i] = CRGB(0, 0, 255);
      FastLED.show();
    }}
  else if(thr == 3){
    for(int i=0; i<NUM_LEDS; i++) {
      leds[i] = CRGB(0, 255, 0);
      FastLED.show();
    }}
  else{
    for(int i=0; i<NUM_LEDS; i++) {
      leds[i] = CRGB(0, 0, 0);
      FastLED.show();
    }}
  }

void setup() 
 { FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
   
   pinMode(LF, OUTPUT);  
   pinMode(LB, OUTPUT);
   pinMode(RB, OUTPUT);
   pinMode(RF, OUTPUT);

   pinMode(Trig1, OUTPUT);  pinMode(Echo1, INPUT);
   pinMode(Trig2, OUTPUT);  pinMode(Echo2, INPUT);

   Serial.begin(9600); }

void loop()
{
  while (Serial.available() > 0) { 
    connectState = true;
    val = Serial.read();  
    Serial.println(val); }

  distance1 = 0.01723 * readUltrasonicDistance(Trig1, Echo1);
  distance2 = 0.01723 * readUltrasonicDistance(Trig2, Echo2);

  if(connectState){     
           if ((distance1 <= thr1)||(distance2 <= thr1))  { light(1); }
      else if ((distance1 <= thr2)||(distance2 <= thr2))  { light(2); }
      else if ((distance1 <= thr3)||(distance2 <= thr3))  { light(3); }
      else { light(0); }}     
  
       if(val == 'F') { control(LOW, HIGH, HIGH, LOW); } // Forward
  else if(val == 'B') { control(HIGH, LOW, LOW, HIGH); } // Backward
  else if(val == 'L') { control(HIGH, LOW, HIGH, LOW); } //Left
  else if(val == 'R') { control(LOW, HIGH, LOW, HIGH); } //Right    
  else if(val == 'S') { control(LOW, LOW, LOW, LOW); }   //Stop
  else if(val == 'H') { control(LOW, LOW, LOW, HIGH); }  // Forward left
  else if(val == 'G') { control(LOW, LOW, HIGH, LOW); }  // Backward left 
  else if(val == 'J') { control(HIGH, LOW, LOW, LOW); }  // Forward right 
  else if(val == 'I') { control(LOW, HIGH, LOW, LOW); }  // Backward right 

  delay(100);

}

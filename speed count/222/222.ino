#include <LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);

int pin2;
int pin3;
float prev = 0.0;
float curr;
float V;
float t;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0,0); lcd.print("V = ");
  lcd.setCursor(0,1); lcd.print("t = ");
  pinMode(2, INPUT);
  pinMode(3, INPUT);
}

void loop() {
  pin2 = digitalRead(2);
  pin3 = digitalRead(3);
  if(!pin2){
    prev = millis();
    while(pin3){ 
      pin3 = digitalRead(3);  }
    curr = millis();
    t = (curr - prev)/1000;
    V = 6.5 / t ;  
    lcd.setCursor(3, 0); lcd.print(V); lcd.print(" cm/s    ");
    lcd.setCursor(3, 1); lcd.print(t); lcd.print(" s     ");
  }
  pin2 = 1;
  pin3 = 1;
  prev = 0.0;
  curr = 0.0;
  V = 0.0;
  delay(10);
}

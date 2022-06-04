#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

#define wall1 A0
#define wall2 A1
#define wall3 A3
#define wall4 A2

int reading1;
int reading2;
int reading3;
int reading4;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Start detection");
  delay(2000);
  pinMode(wall1, INPUT);
  pinMode(wall2, INPUT);
  pinMode(wall3, INPUT);
  pinMode(wall4, INPUT);

  pinMode(9, OUTPUT);
}

void act(int wall){
  Serial.print(wall); Serial.print(" ");
  delay(1500);
  if(wall==1){ lcd.setCursor(6, 0);  }
  else if(wall==2){ lcd.setCursor(15, 0); }
  else if(wall==3){ lcd.setCursor(6, 1);  }
  else if(wall==4){ lcd.setCursor(15, 1); }
  
  lcd.print("1");
  digitalWrite(9, HIGH);
}

void noAct(int Wall){
  Serial.print(Wall + 4);  Serial.print(" ");
  delay(1500);
  if(Wall==1){ lcd.setCursor(6, 0);  }
  else if(Wall==2){ lcd.setCursor(15, 0); }
  else if(Wall==3){ lcd.setCursor(6, 1);  }
  else if(Wall==4){ lcd.setCursor(15, 1); }
  
  lcd.print("0");
  digitalWrite(9, LOW);
}

void loop() {
  reading1 = analogRead(wall1);
  reading2 = analogRead(wall2);
  reading3 = analogRead(wall3);
  reading4 = analogRead(wall4);

  lcd.setCursor(0,0);
  lcd.print("Wall1:");
  lcd.setCursor(7,0);
  lcd.print(", Wall2:");
  lcd.setCursor(0,1);
  lcd.print("Wall3:");
  lcd.setCursor(7,1);
  lcd.print(", Wall4:");

  if(reading1 < 900){ act(1); } else{ noAct(1); }
  if(reading2 < 900){ act(2); } else{ noAct(2); }
  if(reading3 < 900){ act(3); } else{ noAct(3); }
  if(reading4 < 900){ act(4); } else{ noAct(4); }

  delay(10);
  

}

#include <DHT.h>
DHT dht(7, DHT11);
float temp;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  dht.begin();
}

void loop() {
  temp = dht.readTemperature();
  Serial.print(temp); Serial.print(" "); 

  if(temp > 30){
    digitalWrite(9, LOW);
    } else {
      digitalWrite(9, HIGH);
      }
      
  delay(1500);
}

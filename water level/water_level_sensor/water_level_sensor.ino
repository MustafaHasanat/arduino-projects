float reading = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin(9600);
  pinMode(5, OUTPUT);  // buzzer 
  pinMode(6, INPUT);  // Echo-6 
  pinMode(7, OUTPUT);  // Trig-7 
}

void loop()
{
  reading = 0.01723 * readUltrasonicDistance(7, 6); // Trig-7  -  Echo-6
  
  Serial.print("Hieght : ");  
  Serial.println(reading);
  
  if (reading > 10) {
    Serial.println("low water-level");
    tone(5, 10000, 500); // play tone 100 (E8 = 5274 Hz)
  } else {
    Serial.println("regular water-level");
    noTone(5);
  }
  delay(10);
}

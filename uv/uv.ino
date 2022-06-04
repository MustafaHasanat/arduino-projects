int relay = 9;
int trig = 6;
int echo = 7;
float reading;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  return pulseIn(echoPin, HIGH);
}

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);  
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
}

void loop() {
  reading = 0.01723 * readUltrasonicDistance(trig, echo);

  if(reading < 15) { 
    digitalWrite(relay, LOW); 
    delay(6000); }
  else { digitalWrite(relay, HIGH); }




  
}

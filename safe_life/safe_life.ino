#include <MPU6050_tockn.h>
#include <Wire.h>
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

MPU6050 mpu6050(Wire);
const int led = 12;
const int flamePin = 11;
int Flame = HIGH;
int one = 4;
int two = 5;
int three = 6;
int four = 7;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  pinMode(led, OUTPUT);
  pinMode(flamePin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(one, OUTPUT);
  pinMode(two, OUTPUT);
  pinMode(three, OUTPUT);
  pinMode(four, OUTPUT);
  Serial.begin(250000);    // Set your Serial Monitor is set at 250000
  Dabble.begin(9600);      // This is the baude rate of the blutooth
  pinMode(8, OUTPUT);
}

void loop() {
  mpu6050.update();
//  Serial.print("angleX : ");
//  Serial.print(mpu6050.getAngleX());
//  Serial.print("\tangleY : ");
//  Serial.print(mpu6050.getAngleY());
//  Serial.print("\tangleZ : ");
//  Serial.println(mpu6050.getAngleZ());

  if (mpu6050.getAngleX() >= 66 || mpu6050.getAngleX() <= -66) {
    digitalWrite(8, HIGH);
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(100);                       // wait for a second
  }

  else if (mpu6050.getAngleY() >= 89 || mpu6050.getAngleY() <= -89) {
    digitalWrite(8, HIGH);
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(100);                       // wait for a second
  }

  else {  digitalWrite (led, LOW);  digitalWrite(8, LOW); }

  Flame = digitalRead(flamePin);
  if (Flame == LOW)
  {
    digitalWrite(8, HIGH);
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(100);                       // wait for a second
  }
  else   { digitalWrite(led, LOW);   digitalWrite(8, LOW); }

  Dabble.processInput();  // This line is crucial in grabbing our data

  if (GamePad.isUpPressed())
  {
    digitalWrite(one, HIGH);
    digitalWrite(two, LOW);

    digitalWrite(three, HIGH);
    digitalWrite(four, LOW);
  }

  else if (GamePad.isDownPressed())
  {
    digitalWrite(one, LOW);
    digitalWrite(two, HIGH);

    digitalWrite(three, LOW);
    digitalWrite(four, HIGH);
  }

  else if (GamePad.isLeftPressed())
  {
    digitalWrite(one, HIGH);
    digitalWrite(two, LOW);

    digitalWrite(three, LOW);
    digitalWrite(four, LOW);
  }

  else if (GamePad.isRightPressed())
  {
    digitalWrite(one, LOW);
    digitalWrite(two, LOW);

    digitalWrite(three, HIGH);
    digitalWrite(four, LOW);
  }
  else
  {
    digitalWrite(one, LOW);
    digitalWrite(two, LOW);

    digitalWrite(three, LOW);
    digitalWrite(four, LOW);
  }
}

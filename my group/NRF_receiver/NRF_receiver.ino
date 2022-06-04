#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[][6] = {"00001", "00002"};
char sent = 'X';
char recv = ' ';

void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  radio.begin();
  radio.openWritingPipe(address[0]);
  radio.openReadingPipe(1, address[1]);
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  
  delay(5);
  radio.startListening();
  if (radio.available()) {
    radio.read(&recv, sizeof(recv));
//    if(recv == 'X'){
      digitalWrite(6, LOW);
      Serial.println(recv);
//      } else {
//        digitalWrite(6, HIGH);
//        Serial.println("Wrong message !");  } 
  } else{
    digitalWrite(6, HIGH);
    Serial.println("Nothing !!!");
    }

    delay(5);
  radio.stopListening();
  radio.write(&sent, sizeof(sent));
  
}

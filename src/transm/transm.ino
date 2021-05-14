#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9,10);

const byte rxAddr[9] = "00001aa1";
int button [7];

uint8_t pin_list[] = {2,3,4,5,6,7,8};

void setup(){
  radio.begin();
  radio.openWritingPipe(rxAddr);
  radio.enableAckPayload();
  radio.stopListening();

  for(int i=0;i<(sizeof(pin_list) / sizeof(pin_list[0]));i++){
    int current_pin = pin_list[i];
    pinMode(current_pin,INPUT_PULLUP);
  }
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A6, INPUT_PULLUP);
  pinMode(A7, INPUT_PULLUP);
}

void loop(){

  for(int i=0;i<(sizeof(pin_list) / sizeof(pin_list[0]));i++){
    int cPin = pin_list[i];
    button[i] = digitalRead(pin_list[i]);
  }

  delay(100);

//  int analogA0 = analogRead(A0) < 100 ? 0 : 1;
//  int analogA1 = analogRead(A1) < 100 ? 0 : 1;
//  int analogA2 = analogRead(A2) < 100 ? 0 : 1;
//  int analogA3 = analogRead(A3) < 100 ? 0 : 1;
//  int analogA4 = analogRead(A4) < 100 ? 0 : 1;
//  int analogA5 = analogRead(A5) < 100 ? 0 : 1;
//  int analogA6 = analogRead(A6) < 100 ? 0 : 1;
//  int analogA7 = analogRead(A7) < 100 ? 0 : 1;

//  button[15] = analogA0;
//  button[14] = analogA1;
//  button[13] = analogA2;
//  button[12] = analogA3;
//  button[11] = analogA4;
//  button[10] = analogA5;
//  button[9]  = analogA6;
//  button[8]  = analogA7;
  
  radio.write(&button, sizeof(button));
}

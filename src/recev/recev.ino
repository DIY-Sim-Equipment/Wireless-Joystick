#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "printf.h"
#include <Joystick.h>

RF24 radio(7,8);
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  7, 0,                  // Button Count, Hat Switch Count
  false, false, false,   // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

const byte rxAddr[9] = "00001aa1";
int data;

void setup()
{
  Joystick.begin();
  
  if (!radio.begin()) {
  }
  radio.openReadingPipe(0, rxAddr);
  radio.enableAckPayload();
  radio.startListening();

  for(int i=0;i<32;i++){
    Joystick.setButton(i,0);
  }
}

void loop()
{
  while(radio.available()){
    int data[7];
    radio.read(&data, sizeof(data));
    for(int i=0;i<sizeof(data);i++){
      Joystick.setButton(i,!data[i]);
    }
  }
}

//This and that routine
#include <Arduino.h>
#include <wire.h>
#include "helpers.h"
#include "debugmsg.h"
#include "globals.h"
#include "retrodev.h"

void SerMouseIRQHandler()
{
  //Interrupt Handler for mouse driver initialization. Triggered by RTS falling
  if (debugMessage) Serial.println("RTS fall detected! Waiting for RTS Raise!");
  //unsigned long timeout=millis()+250;
  //while((digitalRead(SerMouseIRQPin)==LOW)&&(millis()<timeout));
    //Wait for RTS to raise again
  //if (debugMessage) Serial.println("RTS up again, sending mouse ID");
  delay(14); //wait 14ms, where the mouse driver expects the M identification
  switch (SerMouseMode) {
    case 0:Serial2.print("M");if (debugMessage) Serial.println("M");break; //M indicates Microsoft Mouse
    case 1:Serial2.print("M");Serial2.print("M3");if (debugMessage) Serial.println("3");break; //M3 indicates Logitech 3-Button Mouse
  }  
}

void initInput() {
  pinMode (DebugModePin,INPUT);
  debugMessage=digitalRead (DebugModePin);//Debug Messages, easier for development steps without output shield
  pinMode (KbdModePin1,INPUT);
  pinMode (KbdModePin2,INPUT);
  pinMode (SerMouseModePin,INPUT);
  pinMode (DJoyModePin,INPUT);
  pinMode (AMouseModePin,INPUT);
  KbdHigh(PS2MouseClock);
  KbdHigh(PS2MouseData);
  pinMode (PS2MousePower,INPUT_PULLUP);

  KbdMode=digitalRead(KbdModePin2)*4+digitalRead(KbdModePin1)*2+digitalRead(KbdModePin0);
  pinMode(KbdPower,INPUT);


}

void initOutput()
{
  //set outputs to respective modes
  //Mouse
  if (debugMessage) Serial.println("Setup Serial Mouse Driver Interrupt Routine and set up port");
  pinMode (SerMouseIRQPin, INPUT_PULLUP);
  switch (SerMouseMode) {
    case 0:Serial2.begin(1200,SERIAL_7N1);if (debugMessage) Serial.println("1200 7N1");break;
    case 1:Serial2.begin(1200,SERIAL_7N1);if (debugMessage) Serial.println("1200 7N1");break;
  }
  attachInterrupt(digitalPinToInterrupt(SerMouseIRQPin),&SerMouseIRQHandler,FALLING);
  //Analogue Joystick
  if (debugMessage) Serial.println("Initilaizing Analogue Joystick Port");
  Wire.begin();
  Wire.beginTransmission(B0101000); //0101=DS1803, 000=Address of Joystick 1
  Wire.write(B10101111); //10101=Command, 111=Both potentiometers
  Wire.write(128); //Center position
  Wire.endTransmission();
  Wire.beginTransmission(B0101001); //0101=DS1803, 001=Address of Joystick 2
  Wire.write(B10101111); //10101=Command, 111=Both potentiometers
  Wire.write(128); //Center position
  Wire.endTransmission();
  pinMode(AJoyB1,OUTPUT);
  pinMode(AJoyB2,OUTPUT);
  pinMode(AJoyB3,OUTPUT);
  pinMode(AJoyB4,OUTPUT);
  digitalWrite(AJoyB1,HIGH); //Joystick buttons are inverted, LOW shorts to ground, which is "Active"
  digitalWrite(AJoyB2,HIGH);
  digitalWrite(AJoyB3,HIGH);
  digitalWrite(AJoyB4,HIGH);
  if (debugMessage) Serial.println("Set up Digital Joystick");
  pinMode(DJoyLf,OUTPUT);
  pinMode(DJoyRg,OUTPUT);
  pinMode(DJoyUp,OUTPUT);
  pinMode(DJoyDn,OUTPUT);
  pinMode(DJoyB1,OUTPUT);
  pinMode(DJoyB2,OUTPUT);
  digitalWrite(DJoyLf,HIGH);
  digitalWrite(DJoyRg,HIGH);
  digitalWrite(DJoyUp,HIGH);
  digitalWrite(DJoyDn,HIGH);
  digitalWrite(DJoyB1,HIGH);
  digitalWrite(DJoyB2,HIGH);
  if (debugMessage) Serial.println("Set up Amiga/Atari Mouse Pins");
  pinMode(AMouseYPin,OUTPUT);
  pinMode(AMouseYQPin,OUTPUT);
  pinMode(AMouseXPin,OUTPUT);
  pinMode(AMouseXQPin,OUTPUT);
  pinMode(AMouseB1Pin,OUTPUT);
  pinMode(AMouseB2Pin,OUTPUT);
  pinMode(AMouseB3Pin,OUTPUT);
  digitalWrite(AMouseB1Pin,1);digitalWrite(AMouseB2Pin,1);digitalWrite(AMouseB3Pin,1);
  digitalWrite(AMouseXPin,PulseMouseXYPattern[PulseMouseXPos]);digitalWrite(AMouseXQPin,PulseMouseXYQPattern[PulseMouseXPos]);
  digitalWrite(AMouseYPin,PulseMouseXYPattern[PulseMouseYPos]);digitalWrite(AMouseYQPin,PulseMouseXYQPattern[PulseMouseYPos]);
}

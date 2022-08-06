//Keyboard, Mouse and Joystick helper stuff that does not communicate with the USB libraries - everything that writes to USB host libraries goes into the main RetroArduInput_FW.ino Sketch

#include "Scancodes.h"
#include "globals.h"
#include "debugmsg.h"
#include <string.h>
#include <Arduino.h>
#include "retrodev.h"
#include <Wire.h>


//AT and PS/2 High and Low - Looks strange but avoids requiring pullup resistors for AT keyboards
void KbdLow(int KbdPin) {
  digitalWrite(KbdPin,LOW);
  pinMode(KbdPin,OUTPUT);
}

void KbdHigh(int KbdPin) {
  pinMode(KbdPin,INPUT);
  digitalWrite(KbdPin,HIGH);
}

void AMouseWrite() //write to Amiga/Atari mouse
{
  if (amouselbutton) {
    digitalWrite(AMouseB1Pin,LOW);
    if (DJoyMode==1) digitalWrite(AJoyB1,LOW);
  }
  else {
    digitalWrite(AMouseB1Pin,HIGH);
    if (DJoyMode==1) digitalWrite(AJoyB1,HIGH);
  }
  if (amouserbutton) {
    digitalWrite(AMouseB2Pin,LOW);
    if (DJoyMode==1) digitalWrite(AJoyB2,LOW);
  }
  else {
    digitalWrite(AMouseB2Pin,HIGH);
    if (DJoyMode==1) digitalWrite(AJoyB2,HIGH);
  }
  if (amousembutton) digitalWrite(AMouseB3Pin,LOW);
  else digitalWrite(AMouseB3Pin,HIGH);
  if (debugMessage) {
    Serial.print("DX=");Serial.print(amousedx);Serial.print(", DY=");Serial.println(amousedy);
  }
  amousedx=amousedx/2;
  amousedy=amousedy/2;
  while ((amousedx!=0)||(amousedy!=0)) {
    if (amousedx>0) {
      //if (debugMessage) Serial.print(PulseMouseXYPattern[PulseMouseXPos]);
      //if (debugMessage) Serial.print(PulseMouseXYQPattern[PulseMouseXPos]);
      //if (debugMessage) Serial.print("X-");
      switch(PulseMouseXPos) {
        case 0: PulseMouseXPos=3;break;
        case 1: PulseMouseXPos=0;break;
        case 2: PulseMouseXPos=1;break;
        case 3: PulseMouseXPos=2;break;
      }
      //if (debugMessage) Serial.print(PulseMouseXYPattern[PulseMouseXPos]);
      //if (debugMessage) Serial.println(PulseMouseXYQPattern[PulseMouseXPos]);
      amousedx--;
      if (DJoyMode==1) digitalWrite(DJoyLf,LOW);
    }
    else if (amousedx<0) {
      //if (debugMessage) Serial.print(PulseMouseXYPattern[PulseMouseXPos]);
      //if (debugMessage) Serial.print(PulseMouseXYQPattern[PulseMouseXPos]);
      //if (debugMessage) Serial.print("X+");
      switch(PulseMouseXPos) {
        case 0: PulseMouseXPos=1;break;
        case 1: PulseMouseXPos=2;break;
        case 2: PulseMouseXPos=3;break;
        case 3: PulseMouseXPos=0;break;
      }
      //if (debugMessage) Serial.print(PulseMouseXYPattern[PulseMouseXPos]);
      //if (debugMessage) Serial.println(PulseMouseXYQPattern[PulseMouseXPos]);
      amousedx++;
      if (DJoyMode==1) digitalWrite(DJoyRg,LOW);
    }
    if (amousedy>0) {
      //if (debugMessage) Serial.print(PulseMouseXYPattern[PulseMouseYPos]);
      //if (debugMessage) Serial.print(PulseMouseXYQPattern[PulseMouseYPos]);
      //if (debugMessage) Serial.print("Y-");
      switch(PulseMouseYPos) {
        case 0: PulseMouseYPos=1;break;
        case 1: PulseMouseYPos=2;break;
        case 2: PulseMouseYPos=3;break;
        case 3: PulseMouseYPos=0;break;
      }
      //if (debugMessage) Serial.print(PulseMouseXYPattern[PulseMouseYPos]);
      //if (debugMessage) Serial.println(PulseMouseXYQPattern[PulseMouseYPos]);
      amousedy--;
      if (DJoyMode==1) digitalWrite(DJoyUp,LOW);
    }
    else if (amousedy<0) {
      //if (debugMessage) Serial.print(PulseMouseXYPattern[PulseMouseYPos]);
      //if (debugMessage) Serial.print(PulseMouseXYQPattern[PulseMouseYPos]);
      //if (debugMessage) Serial.print("Y+");
      switch(PulseMouseYPos) {
        case 0: PulseMouseYPos=3;break;
        case 1: PulseMouseYPos=0;break;
        case 2: PulseMouseYPos=1;break;
        case 3: PulseMouseYPos=2;break;
      }
      //if (debugMessage) Serial.print(PulseMouseXYPattern[PulseMouseYPos]);
      //if (debugMessage) Serial.println(PulseMouseXYQPattern[PulseMouseYPos]);
      amousedy++;
      if (DJoyMode==1) digitalWrite(DJoyDn,LOW);
    }
    digitalWrite(AMouseXPin,PulseMouseXYPattern[PulseMouseXPos]);digitalWrite(AMouseXQPin,PulseMouseXYQPattern[PulseMouseXPos]);
    digitalWrite(AMouseYPin,PulseMouseXYPattern[PulseMouseYPos]);digitalWrite(AMouseYQPin,PulseMouseXYQPattern[PulseMouseYPos]);
    delayMicroseconds(150);
   if (DJoyMode==1) {digitalWrite(DJoyLf,LOW);digitalWrite(DJoyRg,LOW);digitalWrite(DJoyUp,LOW);digitalWrite(DJoyDn,LOW);}
  }
}

byte MouseReadPS2() {
  if (debugMessage) Serial.println("PS2 Mouse Read");
  //while (digitalRead(PS2MouseClock)==LOW);
  //delayMicroseconds(40);
  if (debugMessage) Serial.println("PS2 Mouse Send Handshake completed, start reading host command");
  byte readbyte=0;
  byte parity=0;
  byte paritycheck=1; //parity odd
  byte tempread=0;
  delayMicroseconds(20);
  KbdLow(PS2MouseClock);
  delayMicroseconds(40);
  KbdHigh(PS2MouseClock);  
  delayMicroseconds(20);
  for (int i=0;i<8;i++) {
    tempread=digitalRead(PS2MouseData);
    readbyte=readbyte+(tempread<<i);
    paritycheck=(paritycheck+tempread)%2;
    delayMicroseconds(20);
    KbdLow(PS2MouseClock);
    delayMicroseconds(40);
    KbdHigh(PS2MouseClock);
    delayMicroseconds(20);
  }
  parity=digitalRead(PS2MouseData);
  delayMicroseconds(20);
  KbdLow(PS2MouseClock);
  delayMicroseconds(40);
  KbdHigh(PS2MouseClock);//let the Stop Bit happen
  delayMicroseconds(40);
  KbdLow(PS2MouseData); //Send ACK
  KbdLow(PS2MouseClock);
  delayMicroseconds(40);
  KbdHigh(PS2MouseClock);
  delayMicroseconds(20); 
  KbdHigh(PS2MouseData);
  if (debugMessage) Serial.println("Read done");
  if (paritycheck!=parity) if (debugMessage) Serial.println("Parity Error");
  if (debugMessage) Serial.println(readbyte);
  return readbyte;
}

void MouseWritePS2(byte value) // routine that writes to the data and clock lines to the PS/2 Mouse - Pretty much the same as AT/PS/2 Keyboard
{
  if (digitalRead(PS2MousePower)==LOW) return; 
  PS2MouseLastByte=value;
  byte tempvalue=value;
  if (debugMessage) Serial.print("PS/2 Mouse Scancode:");
  if (debugMessage) Serial.println(tempvalue,HEX);
  //if (tempvalue==0) return;

  byte bits[8];  
   for (int i = 0; i < 8; i++)
  {
    bits[i] = tempvalue & 1; // grab least significant bit of value byte  
    tempvalue >>= 1; // right-shift the value byte by one bit
  }
  //while (digitalRead(PS2MouseClock)==LOW) MouseHostToDevicePS2();
  while ((digitalRead(PS2MouseClock)==LOW)||digitalRead(PS2MouseData)==LOW);

  KbdLow(PS2MouseData);
  delayMicroseconds(20);
  KbdLow(PS2MouseClock);
  delayMicroseconds(40);
  KbdHigh(PS2MouseClock);
  delayMicroseconds(20);
  int parity=1;
  for (int i = 0; i < 8; i++) {
    switch (bits[i]) {
      case 0:KbdLow(PS2MouseData);break;
      default:KbdHigh(PS2MouseData);break;
    }
    delayMicroseconds(20);
    KbdLow(PS2MouseClock);
    delayMicroseconds(40);
    KbdHigh(PS2MouseClock);
    parity=(parity+bits[i])%2;
  } 
  switch(parity) {
    case 0:KbdLow(PS2MouseData);break;
    default:KbdHigh(PS2MouseData);break;
  }
  delayMicroseconds(20);
  KbdLow(PS2MouseClock);
  delayMicroseconds(40);
  KbdHigh(PS2MouseClock);
  delayMicroseconds(20);
  KbdHigh(PS2MouseData); //Stop-Bit 1
  delayMicroseconds(20);
  KbdLow(PS2MouseClock);
  delayMicroseconds(40);
  KbdHigh(PS2MouseClock);
  //delay(1);
  //if ((digitalRead(PS2MouseClock)==LOW)&&(digitalRead(PS2MouseData)==HIGH)) MouseHostToDevicePS2();
  if (debugMessage) Serial.println("PS/2 Write Success");
}

void MouseHostToDevicePS2(){
  int readbyte=0;
  int readbyte2=0;
  if (debugMessage) Serial.println("PS/2 Mouse Transmit Inhibit - Check for Send Request");
  unsigned long kbdtimeoutmillis=millis();
  byte kbdtimeout=0;
  while ((digitalRead(PS2MouseClock)==LOW)&&(!kbdtimeout)) {
    kbdtimeout=(kbdtimeoutmillis+45)<millis();
  }
  if (kbdtimeout) {
    if (debugMessage) Serial.println("PS/2 Mouse Read Timeout");
    return;            
  }
  if (digitalRead(PS2MouseData)==LOW) readbyte=MouseReadPS2();
  else return;
  if ((PS2MouseMode==PS2Mwrap)&&((readbyte!=0xFF)||(readbyte!=0xEC))) {
    MouseWritePS2(readbyte);
    return;
  }
  //while ((digitalRead(PS2MouseClock)==LOW)||(digitalRead(PS2MouseData)==LOW));
  switch(readbyte) {
    case 0xE6: //Set Scaling 1:1 (and save and ignore it :-))
      if (debugMessage) Serial.println("PS/2 Mouse Scaling 1:1");
      MouseWritePS2(0xFA);
      //while ((digitalRead(PS2MouseClock)==LOW));
      //MouseWritePS2(0xFA);
      PS2MouseScaling=0;
      break;
    case 0xE7: //Set Scaling 2:1 (and save and ignore it :-))
      if (debugMessage) Serial.println("PS/2 Mouse Scaling 2:1");
      MouseWritePS2(0xFA);
      //while ((digitalRead(PS2MouseClock)==LOW));
      //MouseWritePS2(0xFA);
      PS2MouseScaling=1;
      break;
    case 0xE8: //Set Resolution (and save and ignore it :-))
      if (debugMessage) Serial.println("PS/2 Mouse Set Resolution");
      MouseWritePS2(0xFA);
      //while ((digitalRead(PS2MouseClock)==LOW)||(digitalRead(PS2MouseData)==LOW));
      PS2MouseRes=MouseReadPS2();
      //while ((digitalRead(PS2MouseClock)==LOW)||(digitalRead(PS2MouseData)==LOW));
      MouseWritePS2(0xFA);
      break;
    case 0xE9: //Status Request - here is why we ignoe but save the data before
      if (debugMessage) Serial.println("PS/2 Mouse Status Request");
      MouseWritePS2(0xFA);
      readbyte2=0;
      if (PS2MouseMode==PS2Mdisable) {
        if (PS2MousePreDisable==PS2Mremote) readbyte2=64; //Remote and disabled
      } else if (PS2MouseMode==PS2Mremote) readbyte2=96; //Remote and enabled
      readbyte2=readbyte2+(PS2MouseScaling*16)+(mouselbutton*4)+(mousembutton*2)+mouserbutton; //Scaling 2:1 and buttons
      while ((digitalRead(PS2MouseClock)==LOW)||(digitalRead(PS2MouseData)==LOW));
      MouseWritePS2(readbyte2);
      while ((digitalRead(PS2MouseClock)==LOW)||(digitalRead(PS2MouseData)==LOW));
      MouseWritePS2(PS2MouseRes);
      while ((digitalRead(PS2MouseClock)==LOW)||(digitalRead(PS2MouseData)==LOW));
      MouseWritePS2(PS2MouseSampling);
      break;
    case 0xEA: //Set Stream Mode - Let's Go!
      if (debugMessage) Serial.println("PS/2 Mouse Stream Mode (Push Data to Host)");
      MouseWritePS2(0xFA);
      PS2MouseMode=PS2Mstream;
      break;
    case 0xEB: //Read Movement Data in Remote Mode
      if (debugMessage) Serial.println("PS/2 Mouse Read Data in Remote Mode");
      MouseWritePS2(0xFA);
      if (PS2MouseMode==PS2Mremote) {
        //implement stream send
      }
      break;
    case 0xEC: //Reset Wrap Mode
      if (debugMessage) Serial.println("PS/2 Mouse Reset Wrap Mode");
      MouseWritePS2(0xFA);
      if (PS2MouseMode==PS2Mwrap) {
        PS2MouseMode=PS2MousePreWrap;
        //reset counters to be implemented
      }
      break;
    case 0xEE: //Set Stream Mode - Let's Go!
      if (debugMessage) Serial.println("PS/2 Mouse Stream Mode (Push Data to Host)");
      MouseWritePS2(0xFA);
      PS2MouseMode=PS2Mstream;
      break;
    case 0xF0: //Set Remote Mode
      if (debugMessage) Serial.println("PS/2 Mouse Remote Mode (Host Polling)");
      MouseWritePS2(0xFA);
      PS2MouseMode=PS2Mremote;
      break;
    case 0xF2: //Read Device ID
      if (debugMessage) Serial.println("PS/2 Mouse Read Device ID");
      MouseWritePS2(0xFA);
      if (debugMessage) Serial.println("PS/2 Mouse Read Device ID");
      while ((digitalRead(PS2MouseClock)==LOW)||(digitalRead(PS2MouseData)==LOW));
      MouseWritePS2(0x00);
      break;
    case 0xF3: //Set Sample Rate (and ignore it :-))
      if (debugMessage) Serial.println("PS/2 Mouse Set Sample RAte");
      MouseWritePS2(0xFA);
      //while ((digitalRead(PS2MouseClock)==LOW)||(digitalRead(PS2MouseData)==LOW));
      readbyte2=MouseReadPS2();
      MouseWritePS2(0xFA);
      break;
    case 0xF4: //Enable Data Reporting
      if (debugMessage) Serial.println("PS/2 Mouse Enable Data Reporting");
      MouseWritePS2(0xFA);
      if (PS2MouseMode==PS2Mdisable) {
        if (PS2MousePreDisable==PS2Mdisable) PS2MouseMode=PS2Mstream;
        else PS2MouseMode=PS2MousePreDisable;
      }
      break;
    case 0xF5: //Disable Data Reporting
      if (debugMessage) Serial.println("PS/2 Mouse Disable Data Reporting");
      MouseWritePS2(0xFA);
      PS2MousePreDisable=PS2MouseMode;
      PS2MouseMode=PS2Mdisable;
      break;
    case 0xF6: //Set Defaults
      if (debugMessage) Serial.println("PS/2 Mouse Set Defaults");
      MouseWritePS2(0xFA);
      PS2MouseMode=PS2Mdisable;
      PS2MouseScaling=0;
      PS2MouseSampling=100;
      PS2MouseRes=4;
      break;
    case 0xFE: //Resend
      if (debugMessage) Serial.println("PS/2 Mouse Resend last byte");
      MouseWritePS2(PS2MouseLastByte);
      break;
    case 0xFF: //Reset
      if (debugMessage) Serial.println("PS/2 Mouse Reset");
      MouseWritePS2(0xFA);
      //while ((digitalRead(PS2MouseClock)==LOW)||(digitalRead(PS2MouseData)==LOW));
      MouseWritePS2(0xAA);
      //while ((digitalRead(PS2MouseClock)==LOW)||(digitalRead(PS2MouseData)==LOW));
      MouseWritePS2(0x00);
      PS2MouseMode=PS2Mdisable;
      PS2MouseScaling=0;
      PS2MouseSampling=100;
      PS2MouseRes=4;
      break;
    default: break;
  }
  /*kbdtimeoutmillis=millis();
  kbdtimeout=0;
  while ((digitalRead(PS2MouseClock)==HIGH)&&(digitalRead(PS2MouseData)==HIGH)&&(!kbdtimeout)) { //wait for next init request
    kbdtimeout=(kbdtimeoutmillis+10000)<millis();
  }
  if (!kbdtimeout) MouseHostToDevicePS2();*/
}

void SerMouseWrite() //write to serial mouse
{
  byte datawords[3]={0,0,0};
  byte datawordsps2[3]={0,0,0};
  byte allzero = ((mousedx==0)&&(mousedy==0)); //Mouse Middle Button Release with no movement special handling for Logitech 3 Button Mode
  auto dxtemp = constrain(mousedx, -127, 127);
  auto dytemp = constrain(mousedy, -127, 127);
  noInterrupts();
  if (PS2MouseMode==PS2Mstream) {
    datawordsps2[0]=((dytemp>0)*32)+((dxtemp<0)*16)+8+mousembutton*4+mouserbutton*2+mouselbutton;
    if (dxtemp<0) datawordsps2[1]=255+dxtemp;
    else datawordsps2[1]=dxtemp;
    if (dytemp>0) datawordsps2[2]=255-dytemp;
    else datawordsps2[2]=abs(dytemp);
    MouseWritePS2(datawordsps2[0]);
    MouseWritePS2(datawordsps2[1]);
    MouseWritePS2(datawordsps2[2]);
  }
  switch (SerMouseMode) {
    case 0: //Microsoft 2 Button
      datawords[1]=dxtemp&0x3F;
      datawords[2]=dytemp&0x3F;
      dxtemp=(dxtemp>>6)&0x3;
      dytemp=(dytemp>>6)&0x3;
      //if (debugMessage) Serial.println(dxtemp,BIN);
      //if (debugMessage) Serial.println(dytemp,BIN);
      datawords[0]=64+32*mouselbutton+16*mouserbutton+dytemp*4+dxtemp;
      //if (debugMessage) Serial.println((int)datawords[0],BIN);
      //if (debugMessage) Serial.println((int)datawords[1],BIN);
      //if (debugMessage) Serial.println((int)datawords[2],BIN);
      Serial2.write(datawords,3);
      //Serial2.write(datawords[1]);
      //Serial2.write(datawords[2]);
      break;
    case 1: //Logitech Systems 3 Button
      datawords[1]=dxtemp&0x3F;
      datawords[2]=dytemp&0x3F;
      dxtemp=(dxtemp>>6)&0x3;
      dytemp=(dytemp>>6)&0x3;
      //if (debugMessage) Serial.println(dxtemp,BIN);
      //if (debugMessage) Serial.println(dytemp,BIN);
      datawords[0]=64+32*mouselbutton+16*mouserbutton+dytemp*4+dxtemp;
      //if (debugMessage) Serial.println((int)datawords[0],BIN);
      //if (debugMessage) Serial.println((int)datawords[1],BIN);
      //if (debugMessage) Serial.println((int)datawords[2],BIN);
      Serial2.write(datawords,3);
      if ((allzero)&&(!mousembutton)) Serial2.write(0x00);
      if (mousembutton) Serial2.write(0x20); //Mouse Middle Button Release with no movement special handling for Logitech 3 Button Mode
      //Serial2.write(datawords[1]);
      //Serial2.write(datawords[2]);
      break;
  }    
  interrupts();
}

uint8_t JoyCalibrate(uint8_t value, uint8_t center) {
  long offset = (long)center-128;
  if (value==center) {
    return(128);
  }
  if (value>center) {
    return((uint8_t)(((((long)value-(long)center)*128)/(128-offset))+128));
  }
  else {
    return((uint8_t)(((long)value*128)/(long)center));
  }
}

void JoyWrite()
{
  if (debugMessage) Serial.print("X1=");
  if (debugMessage) Serial.print(Joy1X);
  if (debugMessage) Serial.print(";Y1=");
  if (debugMessage) Serial.print(Joy1Y);
  if (debugMessage) Serial.print(";X2=");
  if (debugMessage) Serial.print(Joy2X);
  if (debugMessage) Serial.print(";Y2=");
  if (debugMessage) Serial.print(Joy2Y);
  if (debugMessage) Serial.print(";B1=");
  if (debugMessage) Serial.print(JoyB1);
  if (debugMessage) Serial.print(";B2=");
  if (debugMessage) Serial.print(JoyB2);
  if (debugMessage) Serial.print(";B3=");
  if (debugMessage) Serial.print(JoyB3);
  if (debugMessage) Serial.print(";B4=");
  if (debugMessage) Serial.println(JoyB4);
  Wire.beginTransmission(B0101000); //0101=DS1803, 000=Address of Joystick 1
  Wire.write(B10101001); //10101=Command, 101=Poti 1 - Joy1X
  Wire.write(255-Joy1X);
  Wire.write(255-Joy1X);
  Wire.endTransmission();
  Wire.beginTransmission(B0101000); //0101=DS1803, 000=Address of Joystick 1
  Wire.write(B10101010); //10101=Command, 110=Poti 2 - Joy1Y
  Wire.write(255-Joy1Y);
  Wire.write(255-Joy1Y);
  Wire.endTransmission();
  Wire.beginTransmission(B0101001); //0101=DS1803, 001=Address of Joystick 2
  Wire.write(B10101001); //10101=Command, 101=Poti 1 - Joy2X
  Wire.write(255-Joy2X);
  Wire.write(255-Joy2X);
  Wire.endTransmission();
  Wire.beginTransmission(B0101001); //0101=DS1803, 001=Address of Joystick 2
  Wire.write(B10101010); //10101=Command, 110=Poti 2 - Joy2Y
  Wire.write(255-Joy2Y);
  Wire.write(255-Joy2Y);
  Wire.endTransmission(); 
  if (debugMessage) Serial.println("Potis set");
  if (DJoyMode==0) { //To Digital Joystick only when Mode=0, Mode=1 is 1350 Joystick Mouse Mode
    if ((Joy1X+DJoyDeadZone)<128) digitalWrite(DJoyLf,LOW);  //Joystick buttons and DJoy Axis are inverted, LOW shorts to ground, which is "Active"
     else digitalWrite(DJoyLf,HIGH);
    if ((Joy1X-DJoyDeadZone)>128) digitalWrite(DJoyRg,LOW);
     else digitalWrite(DJoyRg,HIGH);
    if ((Joy1Y+DJoyDeadZone)<128) digitalWrite(DJoyUp,LOW);
     else digitalWrite(DJoyUp,HIGH);
    if ((Joy1Y-DJoyDeadZone)>128) digitalWrite(DJoyDn,LOW);
     else digitalWrite(DJoyDn,HIGH);    
  }
  if (JoyB1) {
    digitalWrite(AJoyB1,LOW);
    if (DJoyMode==0) digitalWrite(DJoyB1,LOW);
  }
  else {
    digitalWrite(AJoyB1,HIGH);
    if (DJoyMode==0) digitalWrite(DJoyB1,HIGH);
  }
  if (JoyB2) {
    digitalWrite(AJoyB2,LOW);
    if (DJoyMode==0) digitalWrite(DJoyB2,LOW);
  }
  else {
    digitalWrite(AJoyB2,HIGH);
    if (DJoyMode==0) digitalWrite(DJoyB2,HIGH);
  }
  if (JoyB3) {
    digitalWrite(AJoyB3,LOW);
  }
  else {
    digitalWrite(AJoyB3,HIGH);
  }
  if (JoyB4) {
    digitalWrite(AJoyB4,LOW);
  }
  else {
    digitalWrite(AJoyB4,HIGH);
  }
  if (debugMessage) Serial.println("Digital Joystick set");
}

void HardResetAmiga() {
  if (debugMessage) Serial.println("Amiga Hard Reset");
  digitalWrite(KbdClock,LOW);
  digitalWrite(KbdReset,LOW);//for Amiga 500 - Comment out if this makes trouble on Amiga 2000
  delay(550);
  digitalWrite(KbdReset,HIGH);//for Amiga 500 - Comment out if this makes trouble on Amiga 2000
  digitalWrite(KbdClock,HIGH);
}

byte KbdWriteAmigaNoSpecialHandling(byte value,byte make) // routine that writes to the data and clock lines to the XT - Stolen from sendToTandy from the PS2 to Tandy 1000 by Adrian Black, with potential adaptions
{
  int cnt=0;
  byte tempvalue=0;
  
  if (debugMessage) Serial.print("Amiga KbdScancode:");
  if (debugMessage) Serial.println(tempvalue,BIN);

  byte bits[8];  
  for (int i = 0; i < 7; i++)
  {
    bits[6-i]= tempvalue & 1; // grab least significant bit of value byte  
    tempvalue >>= 1; // right-shift the value byte by one bit
  }
  bits[7]=tempvalue & 1;
  
  digitalWrite(KbdData, LOW);
  delayMicroseconds(20);
  digitalWrite(KbdData, HIGH);
  delayMicroseconds(110);
  for (int i=0;i<8;i++)
  {
    digitalWrite(KbdData, !bits[i]);
    delayMicroseconds(10);
    digitalWrite(KbdClock, LOW);
    delayMicroseconds(19);
    digitalWrite(KbdClock, HIGH);
    delayMicroseconds(45);
  } 
  delayMicroseconds(10);
  digitalWrite(KbdData, HIGH);

  byte success=0;
  uint32_t timeout=millis()+5;
  while (millis()<timeout) {
    if (digitalRead(KbdData)==LOW) success=1;
  }
}

void KbdPowerUpAmiga(byte CAA) {
  while ((digitalRead(KbdClock)==LOW)||(digitalRead(KbdData)==LOW));
  KbdWriteAmigaNoSpecialHandling(110,0);
  if (CAA&1) KbdWriteAmigaNoSpecialHandling(102,0); //Keyboard should report all pressed keys - assuming that nobody presses keys during startup except Ctrl Amiga Amiga during a reset, concentrating on these keys
  if ((CAA>>1)&1) KbdWriteAmigaNoSpecialHandling(105,0);
  if ((CAA>>2)&1) KbdWriteAmigaNoSpecialHandling(109,0);
  KbdWriteAmigaNoSpecialHandling(110,1);
}

byte ResetWarningAmiga() {
  if (debugMessage) Serial.println("Amiga Reset Warning");
  byte success=KbdWriteAmigaNoSpecialHandling(113,0);
  if (!success) {
    HardResetAmiga();
    return 0;
  }
  success=KbdWriteAmigaNoSpecialHandling(113,0);
  uint32_t timeout=millis()+250;
  success=0;
  while ((timeout<millis())&&(!success)) {
    if (digitalRead(KbdData)==LOW) success=1;
  }
  if (!success) {
    HardResetAmiga();
    return 0;
  }
  timeout=millis()+10000;
  success=0;
  while ((timeout<millis())&&(!success)) {
    if (digitalRead(KbdData)==HIGH) success=1;
  }
  return 1;
}

void KbdPutBufferAT(byte value,byte make) {
  if (ATKbdBufferPos<8) {
    ATKbdBuffer[ATKbdBufferPos][0]=value;
    ATKbdBuffer[ATKbdBufferPos][1]=make;
    if (debugMessage) {
      Serial.print("Key ");
      Serial.print(value);
      Serial.print(" Make/Break ");
      Serial.print(make);
      Serial.print(" buffered at position ");
      Serial.println(ATKbdBufferPos);
    }
    ATKbdBufferPos++;  
  }
  else if (debugMessage) Serial.println("Buffer full");
}

byte KbdReadAT() {
  if (debugMessage) Serial.println("AT Keyboard Read");
  //while (digitalRead(KbdData==LOW));
  delayMicroseconds(40);
  if (debugMessage) Serial.println("AT Keyboard Send Handshake completed, start reading host command");
  byte readbyte=0;
  byte parity=0;
  byte paritycheck=1; //parity odd
  byte tempread=0;
  delayMicroseconds(20);
  KbdLow(KbdClock);
  delayMicroseconds(40);
  KbdHigh(KbdClock);  
  delayMicroseconds(20);
  for (int i=0;i<8;i++) {
    tempread=digitalRead(KbdData);
    readbyte=readbyte+(tempread<<i);
    paritycheck=(paritycheck+tempread)%2;
    delayMicroseconds(20);
    KbdLow(KbdClock);
    delayMicroseconds(40);
    KbdHigh(KbdClock);
    delayMicroseconds(20);
  }
  parity=digitalRead(KbdData);
  delayMicroseconds(20);
  KbdLow(KbdClock);
  delayMicroseconds(40);
  KbdHigh(KbdClock);//let the Stop Bit happen
  delayMicroseconds(40);
  KbdLow(KbdData); //Send ACK
  KbdLow(KbdClock);
  delayMicroseconds(40);
  KbdHigh(KbdClock);
  delayMicroseconds(20); 
  KbdHigh(KbdData);
  if (debugMessage) Serial.println("Read done");
  if (paritycheck!=parity) if (debugMessage) Serial.println("Parity Error");
  if (debugMessage) Serial.println(readbyte);
  return readbyte;
}

byte ATKbdTypematicKey(byte USBScanCode) {
  //No typematic repeat for certain keys. Some modifiers like Ctrl, Alt, Shift already suppressed by the implementation of the USB parser
  switch (USBScanCode) {
    case 0x39:return(0);break; //Caps
    case 0x46:return(0);break; //Printscreen
    case 0x47:return(0);break; //Scroll
    case 0x48:return(0);break; //Pause
    case 0x53:return(0);break; //Num
    case 0x65:return(0);break; //Context Menu
    default:return(1);
  }
}

void sendToTandy(byte value) // routine that writes to the data and clock lines to the Tandy - Stolen from sendToTandy from the PS2 to Tandy 1000 by Adrian Black
{
  if (value==0) return; //no key defined, don't send out anything, Tandy does not have a scancode 0
  if (debugMessage) {
    Serial.print("Tandy 1000 KbdScancode:");
    Serial.print(value);
    Serial.print("\n");;  
  }

  byte bits[8];  

  for (int i = 0; i < 8; i++)
  {
    bits[i] = value & 1; // grab least significant bit of value byte  
    value >>= 1; // right-shift the value byte by one bit
  }

  while (digitalRead(KbdClock) != LOW);

  for (int i = 0; i < 8; i++)
  {
    digitalWrite(KbdData, bits[i]);
    delayMicroseconds(5);
    digitalWrite(KbdClock, HIGH);
    delayMicroseconds(7);
    digitalWrite(KbdClock, HIGH);
    delayMicroseconds(5);
    digitalWrite(KbdClock, LOW);
  } 

  digitalWrite(KbdClock, LOW);
  delayMicroseconds(10);
  digitalWrite(KbdData, LOW);
  delayMicroseconds(5);
  digitalWrite(KbdData, HIGH);
  delay(10);

}

byte ADBSync() {
  if (digitalRead(ADBData)==HIGH) return(0); //no result
  uint32_t ADBmicros=micros();
  while ((digitalRead(ADBData)==LOW)&&((ADBmicros+1000)>micros()));
  uint32_t result=micros()-ADBmicros;
  if (result<750) return (0); //776 microseconds minimum for Attention signal - Add some slack, so 750 - if below, then something is wrong
  else if (result<850) return(1);//824 microseconds maximum for Attention signal - Add some slack, so 850 - if higher, it is likely a reset signal
  else return(2);
}

byte ADBReadCommand() {
  uint32_t ADBmicros=micros();
  byte command=0;
  while ((digitalRead(ADBData)==HIGH)&&((ADBmicros+80)>micros()));
  if ((ADBmicros+80)<micros()) return(255); //72 is the maximum sync length, let's call 80 a timeout
  for (byte i=0;i<8;i++) {
    ADBmicros=micros();
    while ((digitalRead(ADBData)==LOW)&&((ADBmicros+80)>micros()));
    uint32_t Lowtime=micros()-ADBmicros;
    ADBmicros=micros();
    while ((digitalRead(ADBData)==HIGH)&&((ADBmicros+80)>micros()));
    uint32_t Hightime=micros()-ADBmicros;
    if ((Lowtime+Hightime)>120) return(255); //100 microseconds should be one phase, let's call >120 a timeout
    if (Hightime>Lowtime) command+=1<<(7-i); //durations should be 65 low + 35 high for a 0 and 35 low and 65 high for a 1, so if Hightime>Lowtime, add a 1 on the particular position
  }
  if (debugMessage) {Serial.print("ADB Command: ");Serial.println(command);}
  return(command);
}

void ADBWriteByte(byte value) {
  byte is_one=0;
  uint32_t ADBmicros=micros();
  while ((digitalRead(ADBData)==HIGH)&&((ADBmicros+260)>micros()));
  if (((micros()-ADBmicros)<140)||((micros()-ADBmicros)>260)) return; //160-240 is the delay w
  KbdLow(ADBData);
  delayMicroseconds(65);
  KbdHigh(ADBData);
  delayMicroseconds(35);
  for (byte i=0;i<8;i++) {
    is_one=(value>>(7-i))&&1;
    KbdLow(ADBData);
    if (is_one) {
      delayMicroseconds(65);
      KbdHigh(ADBData);
      delayMicroseconds(35);
    }
    else {
      delayMicroseconds(65);
      KbdHigh(ADBData);
      delayMicroseconds(35);
    }
  }
  KbdLow(ADBData);
  delayMicroseconds(65);
  KbdHigh(ADBData);
}

void ADBWriteTwoBytes(byte value1,byte value2) {
  byte is_one=0;
  uint32_t ADBmicros=micros();
  KbdLow(ADBData);
  delayMicroseconds(65);
  KbdHigh(ADBData);
  delayMicroseconds(35);
  for (byte i=0;i<8;i++) {
    is_one=(value1>>(7-i))&&1;
    KbdLow(ADBData);
    if (is_one) {
      delayMicroseconds(65);
      KbdHigh(ADBData);
      delayMicroseconds(35);
    }
    else {
      delayMicroseconds(65);
      KbdHigh(ADBData);
      delayMicroseconds(35);
    }
  }
  for (byte i=0;i<8;i++) {
    is_one=(value2>>(7-i))&&1;
    KbdLow(ADBData);
    if (is_one) {
      delayMicroseconds(65);
      KbdHigh(ADBData);
      delayMicroseconds(35);
    }
    else {
      delayMicroseconds(65);
      KbdHigh(ADBData);
      delayMicroseconds(35);
    }
  }
  KbdLow(ADBData);
  delayMicroseconds(65);
  KbdHigh(ADBData);
}

void MouseWriteADB() {
  auto dxtemp = constrain(mousedx, -63, 63);
  auto dytemp = constrain(mousedy, -63, 63);
  byte byte1=0;
  byte byte2=0;
  if (mouselbutton) byte2=128;
  if (dxtemp<0) {
    byte1+=64;
    byte1+=(64-abs(mousedx));
  }
  else {
    byte1+=mousedx;
  }
  if (dytemp<0) {
    byte2+=64;
    byte2+=(64-abs(mousedy));
  }
  else {
    byte2+=mousedy;
  }
  while (!digitalRead(ADBData));while(digitalRead(ADBData));
  ADBWriteTwoBytes(byte1,byte2);
}

void MouseWriteADBReg3() {
  while (!digitalRead(ADBData));while(digitalRead(ADBData));
  ADBWriteTwoBytes(0x01,0x03);
}

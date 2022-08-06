#include <hidboot.h>
#include <usbhub.h>
#include <hiduniversal.h>
#include "globals.h"
#include "Scancodes.h"
#include "debugmsg.h"
#include "retrodev.h"
#include "helpers.h"

// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
#include <Wire.h>

#define KBD_IF 0

//To-Do-Liste in fertigen Modulen:
//286: Verhalten nach Strg+Alt+Del immer noch seltsam
//AT generell: Verhalten Caps/Num/Scroll-Lock-Tasten (Up/Down-Verhalten ggf. gelöst, ohne Debug-Nachrichten prüfen) -> CheckIt LED Status falsch und keine Reaktivierung von Data Report Enabled

//Write Routines Header
void KbdWriteAT(byte value,byte make,byte overridedisable); // routine that writes to the data and clock lines to the AT - Stolen from sendToTandy from the PS2 to Tandy 1000 by Adrian Black, with adaptions
void KbdWriteXT(byte value,byte make); // routine that writes to the data and clock lines to the XT - Stolen from sendToTandy from the PS2 to Tandy 1000 by Adrian Black, with adaptions
void KbdWriteT1000(byte value,byte make); // routine that writes to the data and clock lines to the Tandy - Stolen from sendToTandy from the PS2 to Tandy 1000 by Adrian Black, with adaptions
void KbdHostToDeviceAT(); //Header for Host to Device communication
void MouseHostToDevicePS2(); //Header for Host to Device communication
void KbdWriteAmiga(byte value,byte make); // routine that writes to the data and clock lines to the XT - Stolen from sendToTandy from the PS2 to Tandy 1000 by Adrian Black, with potential adaptions
void KbdWriteADB(byte value,byte make); 

//USB Routines

#if !defined(__HIDJOYSTICKRPTPARSER_H__)
#define __HIDJOYSTICKRPTPARSER_H__

struct GamePadEventData
{
  uint32_t value1;
  uint8_t value2;
  uint8_t value3;
  uint8_t value4;
  uint8_t value5;
  uint8_t value6;
  uint8_t value7;
};

class JoystickEvents
{
public:
  virtual void OnGamePadChanged(const GamePadEventData *evt);
};

#define RPT_GAMEPAD_LEN sizeof(GamePadEventData)/sizeof(uint8_t)

class JoystickReportParser : public HIDReportParser
{
  JoystickEvents    *joyEvents;

  uint8_t oldPad[RPT_GAMEPAD_LEN];

public:
  JoystickReportParser(JoystickEvents *evt);

  virtual void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

JoystickReportParser::JoystickReportParser(JoystickEvents *evt) :
  joyEvents(evt)
{}

void JoystickReportParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
  bool match = true;

  // Checking if there are changes in report since the method was last called
  for (uint8_t i=0; i<RPT_GAMEPAD_LEN; i++) {
    if( buf[i] != oldPad[i] ) {
      match = false;
      break;
    }
  }
    // Calling Game Pad event handler
  if (!match && joyEvents) {
    joyEvents->OnGamePadChanged((const GamePadEventData*)buf);

    for (uint8_t i=0; i<RPT_GAMEPAD_LEN; i++) oldPad[i] = buf[i];
  }
}

void JoystickEvents::OnGamePadChanged(const GamePadEventData *evt)
{
  uint16_t myX = 0;
  uint16_t myY = 0;
  uint8_t myHat = 0;
  uint8_t myT = 0;
  uint8_t myBA = 0;
  uint8_t mySl = 0;
  uint8_t myBB = 0;
  uint8_t myB1 = 0;
  uint8_t myB2 = 0;
  uint8_t myB3 = 0;
  uint8_t myB4 = 0;
 
 switch (JoyType) {
  case JoyTypeCompetition:
    //Speedlink Competition Pro USB
    myX = evt->value1&0xFF;
    myY = ((evt->value1)>>8)&0xFF;
    myHat = 0;
    myT = 0;
    myBA = ((evt->value1)>>16)&0xFF;
    mySl = 0;
    myBB = 0;
    myB1 = myBA&1;
    myB2 = (myBA>>1)&1;
    myB3 = (myBA>>2)&1;
    myB4 = (myBA>>3)&1;
    break;
  case JoyTypeSLPhantom:
  //Speedlink Phantom Hawk
    myX = evt->value1&0xFF;
    myY = ((evt->value1)>>8)&0xFF;
    myHat = 0;
    myT = ((evt->value1)>>16)&0xFF;
    myBA = evt->value3; 
    mySl = ((evt->value1)>>24)&0xFF;
    myBB = evt->value4; 
    myB1 = ((myBA>>4)&1)||(myBB&1)||((myBB>>3)&1)||((myBB>>5)&1);
    myB2 = ((myBA>>6)&1)||((myBB>>2)&1)||((myBB>>4)&1)||((myBB>>6)&1);
    myB3 = ((myBA>>5)&1)||((myBA>>7)&1);
    myB4 = ((myBB>>1)&1)||((myBB>>7)&1);
    if (JoyCalibration) {
      JoyCenterX1=myX;
      JoyCenterY1=myY;
      JoyCenterX2=myT;
      JoyCalibration=0;
      if ((JoyCenterX1==0)||(JoyCenterY1==0)||(JoyCenterX2==0)) JoyCalibration=1;
    }
    myX=JoyCalibrate(myX,JoyCenterX1);
    myY=JoyCalibrate(myY,JoyCenterY1);
    myT=JoyCalibrate(myT,JoyCenterX2);
    break;
  case JoyTypeLogitechE3DP:
    //Logitech Extreme 3D
    myX = (evt->value1&0x3FF)>>2;
    myY = (((evt->value1)>>10)&0x3FF)>>2;
    myHat = ((evt->value1)>>20)&0xF;
    myT = ((evt->value1)>>24)&0xFF;
    myBA = evt->value2;
    mySl = evt->value3;
    myBB = evt->value4; 
    myB1 = (myBA&1)||((myBA>>4)&1)||(myBB&1);
    myB2 = ((myBA>>1)&1)||((myBA>>5)&1)||((myBB>>1)&1);
    myB3 = ((myBA>>2)&1)||((myBA>>6)&1)||((myBB>>2)&1);
    myB4 = ((myBA>>3)&1)||((myBA>>7)&1)||((myBB>>3)&1);
    break;
  case JoyTypeTMAirbus:
    //Thrustmaster TC Sidestick Airbus Edition, very likely also maps to the Hotas FCS Stick
    myX = ((evt->value1>>8)&0xFFFF)>>6;
    myY = (((evt->value2)<<8)+(((evt->value1)>>24)&0xFF))>>6;
    myHat = ((evt->value1)>>20)&0xF;
    myT =  evt->value3;
    myBA = evt->value6;
    mySl = evt->value4;
    myBB = evt->value7; 
    myB1 = (myBA&1)||((myBA>>6)&1)||((myBB>>4)&1)||((myBB>>6)&1);
    myB2 = ((myBA>>2)&1)||((myBA>>5)&1)||((myBB>>3)&1)||((myBB>>5)&1);
    myB3 = ((myBA>>3)&1)||((myBA>>4)&1)||((myBB>>2)&1)||((myBA>>7)&1);
    myB4 = ((myBA>>1)&1)||((myBB>>1)&1)||((myBB>>7)&1)||(myBB&1);
    break;
  case JoyTypeTLP_PS2DA:
    //Trio Linker Plus + Playstation 2 Dual Analogue
    myX = ((evt->value1)>>16)&0xFF; //D-Pad or Analogue 1 X
    myY = ((evt->value1)>>24)&0xFF; //D-Pad or Analogue 1 Y
    myHat = 0;
    myT = evt->value2; //D-Pad Mirror or Analogue 2 X
    myBA = (evt->value1)&0xFF;
    mySl = evt->value3; //D-Pad Mirror or Analogue 2 Y
    myBB = 0;
    myB1 = (myBA&1)||((myBA>>4)&1);
    myB2 = ((myBA>>1)&1)||((myBA>>5)&1);
    myB3 = ((myBA>>2)&1)||((myBA>>6)&1);
    myB4 = ((myBA>>3)&1)||((myBA>>7)&1);
    break;
  case JoyTypeTLP_DC:
    //Trio Linker Plus + Dreamcast Controller
    myX = ((evt->value1)>>16)&0xFF; //D-Pad or Analogue X
    myY = ((evt->value1)>>24)&0xFF; //D-Pad or Analogue Y
    myHat = 0;
    mySl = evt->value2; //Left trigger
    myBA = (evt->value1)&0xFF;
    myT = evt->value3; //Right trigger
    myBB = 0;
    myB1 = (myBA&1);
    myB2 = ((myBA>>1)&1);
    myB3 = ((myBA>>2)&1);
    myB4 = ((myBA>>3)&1);
    break;
  case JoyTypeTLP_GC:
    //Trio Linker Plus + Gamecube Controller - I don't have one but assume a very similar mapping to the PS2 Dual Analogue
    myX = ((evt->value1)>>16)&0xFF; //D-Pad or Analogue 1 X
    myY = ((evt->value1)>>24)&0xFF; //D-Pad or Analogue 1 Y
    myHat = 0;
    myT = evt->value2; //D-Pad Mirror or Analogue 2 X
    myBA = (evt->value1)&0xFF;
    mySl = evt->value3; //D-Pad Mirror or Analogue 2 Y
    myBB = 0;
    myB1 = (myBA&1)||((myBA>>4)&1);
    myB2 = ((myBA>>1)&1)||((myBA>>5)&1);
    myB3 = ((myBA>>2)&1)||((myBA>>6)&1);
    myB4 = ((myBA>>3)&1)||((myBA>>7)&1);
    break;
  case JoyTypeLogitechFGamepad:
    //Logitech F710 and similar
    myX = ((evt->value1)>>8)&0xFF; //D-Pad or Analogue 1 X
    myY = ((evt->value1)>>16)&0xFF; //D-Pad or Analogue 1 Y
    myHat = 0;
    myT = ((evt->value1)>>24)&0xFF; //Analogue 2 X
    myBA = evt->value3;
    mySl = evt->value2; //Analogue 2 Y
    myBB = evt->value4;
    myB1 = ((myBA>>4)&1)||((myBB)&1);
    myB2 = ((myBA>>5)&1)||((myBB>>1)&1);
    myB3 = ((myBA>>6)&1)||((myBB>>2)&1);
    myB4 = ((myBA>>7)&1)||((myBB>>3)&1);
    break;
  default:
  //Assumung this as a default matching for random joysticks
    myX = evt->value1&0xFF;
    myY = ((evt->value1)>>8)&0xFF;
    myHat = 0;
    myT = ((evt->value1)>>16)&0xFF;
    myBA = evt->value3; 
    mySl = ((evt->value1)>>24)&0xFF;
    myBB = evt->value4; 
    myB1 = ((myBA>>4)&1)||(myBA&1);
    myB2 = ((myBA>>5)&1)||((myBA>>1)&1);
    myB3 = ((myBA>>6)&1)||((myBA>>2)&1);
    myB4 = ((myBB>>7)&1)||((myBB>>3)&1);
    if (JoyCalibration) {
      JoyCenterX1=myX;
      JoyCenterY1=myY;
      JoyCenterX2=myT;
      JoyCalibration=0;
      if ((JoyCenterX1==0)||(JoyCenterY1==0)||(JoyCenterX2==0)) JoyCalibration=1;
    }
    myX=JoyCalibrate(myX,JoyCenterX1);
    myY=JoyCalibrate(myY,JoyCenterY1);
    myT=JoyCalibrate(myT,JoyCenterX2);
    break;
 }
  Joy1X=myX;Joy1Y=myY;Joy2X=myT;Joy2Y=mySl;JoyB1=myB1;JoyB2=myB2;JoyB3=myB3;JoyB4=myB4;
  Serial.print("Raw 1 (32b): ");
  PrintHex<uint32_t>(evt->value1, 0x80);
  Serial.print(" Raw 2 (8b): ");
  PrintHex<uint8_t>(evt->value2, 0x80);
  Serial.print(" Raw 3 (8b): ");
  PrintHex<uint8_t>(evt->value3, 0x80);
  Serial.print(" Raw 4 (8b): ");
  PrintHex<uint8_t>(evt->value4, 0x80);
  Serial.print(" Raw 5 (8b): ");
  PrintHex<uint8_t>(evt->value5, 0x80);
  Serial.print(" Raw 6 (8b): ");
  PrintHex<uint8_t>(evt->value6, 0x80);
  Serial.print(" Raw 7 (8b): ");
  PrintHex<uint8_t>(evt->value7, 0x80);
  Serial.println("");
  Serial.println("Analogue:");
  Serial.print("X1: ");
  PrintHex<uint16_t>(myX, 0x80);
  Serial.print(" Y1: ");
  PrintHex<uint16_t>(myY, 0x80);
  Serial.print(" X2: ");
  PrintHex<uint8_t>(myT, 0x80);
  Serial.print(" Y2: ");
  PrintHex<uint8_t>(mySl, 0x80);
  Serial.print(" B1: ");
  PrintHex<uint8_t>(myB1, 0x80);
  Serial.print(" B2: ");
  PrintHex<uint8_t>(myB2, 0x80);
  Serial.print(" B3: ");
  PrintHex<uint8_t>(myB3, 0x80);
  Serial.print(" B4: ");
  PrintHex<uint8_t>(myB4, 0x80);
  Serial.println("");
  JoyWrite();
}
#endif // __HIDJOYSTICKRPTPARSER_H__


class MouseRptParser : public MouseReportParser
{
  protected:
    void OnMouseMove(MOUSEINFO *mi);
    void OnLeftButtonUp(MOUSEINFO *mi);
    void OnLeftButtonDown(MOUSEINFO *mi);
    void OnRightButtonUp(MOUSEINFO *mi);
    void OnRightButtonDown(MOUSEINFO *mi);
    void OnMiddleButtonUp(MOUSEINFO *mi);
    void OnMiddleButtonDown(MOUSEINFO *mi);
};
void MouseRptParser::OnMouseMove(MOUSEINFO *mi)
{
  //if (debugMessage) Serial.print("dx=");
  //if (debugMessage) Serial.print(mi->dX, DEC);
  //if (debugMessage) Serial.print(" dy=");
  //if (debugMessage) Serial.println(mi->dY, DEC);
  int tempdx=mi->dX;
  int tempdy=mi->dY;
  mousedx=mousedx+tempdx;
  mousedy=mousedy+tempdy;
  amousedx=amousedx+tempdx;
  amousedy=amousedy+tempdy;  
};
void MouseRptParser::OnLeftButtonUp  (MOUSEINFO *mi)
{
  mouselbutton=0;
  mousebuttonchange=1;
  amouselbutton=0;
  amousebuttonchange=1;
  //if (debugMessage) Serial.println("L Butt Up");
};
void MouseRptParser::OnLeftButtonDown (MOUSEINFO *mi)
{
  mouselbutton=1;
  mousebuttonchange=1;
  amouselbutton=1;
  amousebuttonchange=1;
  //if (debugMessage) Serial.println("L Butt Dn");
};
void MouseRptParser::OnRightButtonUp  (MOUSEINFO *mi)
{
  mouserbutton=0;
  mousebuttonchange=1;
  amouserbutton=0;
  amousebuttonchange=1;
  //if (debugMessage) Serial.println("R Butt Up");
};
void MouseRptParser::OnRightButtonDown  (MOUSEINFO *mi)
{
  mouserbutton=1;
  mousebuttonchange=1;
  amouserbutton=1;
  amousebuttonchange=1;
  //if (debugMessage) Serial.println("R Butt Dn");
};
void MouseRptParser::OnMiddleButtonUp (MOUSEINFO *mi)
{
  mousembutton=0;
  if (SerMouseMode) {
    mousembutton=0;
    mousebuttonchange=1;
  }
  amousembutton=0;
  amousebuttonchange=1;
  //if (debugMessage) Serial.println("M Butt Up");
};
void MouseRptParser::OnMiddleButtonDown (MOUSEINFO *mi)
{
  mousembutton=1;
  if (SerMouseMode) {
    mousembutton=1;
    mousebuttonchange=1;
  }
  amousembutton=1;
  amousebuttonchange=1;
  //if (debugMessage) Serial.println("M Butt Dn");
};

class KbdRptParser : public KeyboardReportParser
{
    void PrintKey(uint8_t mod, uint8_t key);

  protected:
    void OnControlKeysChanged(uint8_t before, uint8_t after);
    void OnKeyDown  (uint8_t mod, uint8_t key);
    void OnKeyUp  (uint8_t mod, uint8_t key);
    void OnKeyPressed(uint8_t key);
};

void KbdRptParser::PrintKey(uint8_t m, uint8_t key)
{
  MODIFIERKEYS mod;
  *((uint8_t*)&mod) = m;
  if (debugMessage) Serial.print((mod.bmLeftCtrl   == 1) ? "C" : " ");
  if (debugMessage) Serial.print((mod.bmLeftShift  == 1) ? "S" : " ");
  if (debugMessage) Serial.print((mod.bmLeftAlt    == 1) ? "A" : " ");
  if (debugMessage) Serial.print((mod.bmLeftGUI    == 1) ? "G" : " ");

  if (debugMessage) Serial.print(" >");
  PrintHex<uint8_t>(key, 0x80);
  if (debugMessage) Serial.print("< ");

  if (debugMessage) Serial.print((mod.bmRightCtrl   == 1) ? "C" : " ");
  if (debugMessage) Serial.print((mod.bmRightShift  == 1) ? "S" : " ");
  if (debugMessage) Serial.print((mod.bmRightAlt    == 1) ? "A" : " ");
  if (debugMessage) Serial.println((mod.bmRightGUI    == 1) ? "G" : " ");
};

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
  if (debugMessage) Serial.print("DN ");
  PrintKey(mod, key);
  uint8_t c = OemToAscii(mod, key);
  switch (KbdMode)
  {
    case KbdModeAT: KbdWriteAT((byte)key,0,0);break;
    case KbdModeXT: KbdWriteXT((byte)key,0);break;
    case KbdModeAmiga: KbdWriteAmiga((byte)key,0);break;
    case KbdModeApple: KbdWriteADB((byte)key,0);break;
    case KbdModeT1000: KbdWriteT1000((byte)key,0);break;
  }
  TypematicKey=key;
  TypematicPhase=TypematicDelay1;
  TypematicMillis=millis();
  if (c)
    OnKeyPressed(c);
}

void KbdRptParser::OnControlKeysChanged(uint8_t before, uint8_t after) {

  MODIFIERKEYS beforeMod;
  *((uint8_t*)&beforeMod) = before;

  MODIFIERKEYS afterMod;
  *((uint8_t*)&afterMod) = after;

  if (beforeMod.bmLeftCtrl != afterMod.bmLeftCtrl) {
    if (debugMessage) Serial.println("LeftCtrl changed");
    switch (KbdMode)
    {
      case KbdModeAT: KbdWriteAT(102,beforeMod.bmLeftCtrl,0);break; //as afterMod is 1 on down and 0 on up and beforeMod the opposite, and I already programmed the whole lookup tables for all keyboards with make 0 and break 1, this the dirty trick was to just use beforeMod
      case KbdModeXT: KbdWriteXT(102,beforeMod.bmLeftCtrl);break;
      case KbdModeAmiga: KbdWriteAmiga(102,beforeMod.bmLeftCtrl);break;
      case KbdModeT1000: KbdWriteT1000(102,beforeMod.bmLeftCtrl);break;
    }
  }
  if (beforeMod.bmLeftShift != afterMod.bmLeftShift) {
    if (debugMessage) Serial.println("LeftShift changed");
    switch (KbdMode)
    {
      case KbdModeAT: KbdWriteAT(103,beforeMod.bmLeftShift,0);break;
      case KbdModeXT: KbdWriteXT(103,beforeMod.bmLeftShift);break;
      case KbdModeAmiga: KbdWriteAmiga(103,beforeMod.bmLeftShift);break;
      case KbdModeT1000: KbdWriteT1000(103,beforeMod.bmLeftShift);break;
    }
  }
  if (beforeMod.bmLeftAlt != afterMod.bmLeftAlt) {
    if (debugMessage) Serial.println("LeftAlt changed");
    switch (KbdMode)
    {
      case KbdModeAT: KbdWriteAT(104,beforeMod.bmLeftAlt,0);break;
      case KbdModeXT: KbdWriteXT(104,beforeMod.bmLeftAlt);break;
      case KbdModeAmiga: KbdWriteAmiga(104,beforeMod.bmLeftAlt);break;
      case KbdModeT1000: KbdWriteT1000(104,beforeMod.bmLeftAlt);break;
    }
  }
  if (beforeMod.bmLeftGUI != afterMod.bmLeftGUI) {
    if (debugMessage) Serial.println("LeftGUI changed");
    switch (KbdMode)
    {
      case KbdModeAT: KbdWriteAT(105,beforeMod.bmLeftGUI,0);break;
      case KbdModeXT: KbdWriteXT(105,beforeMod.bmLeftGUI);break;
      case KbdModeAmiga: KbdWriteAmiga(105,beforeMod.bmLeftGUI);break;
      case KbdModeT1000: KbdWriteT1000(105,beforeMod.bmLeftGUI);break;
    }
  }

  if (beforeMod.bmRightCtrl != afterMod.bmRightCtrl) {
    if (debugMessage) Serial.println("RightCtrl changed");
    switch (KbdMode)
    {
      case KbdModeAT: KbdWriteAT(106,beforeMod.bmRightCtrl,0);break;
      case KbdModeXT: KbdWriteXT(106,beforeMod.bmRightCtrl);break;
      case KbdModeAmiga: KbdWriteAmiga(106,beforeMod.bmRightCtrl);break;
      case KbdModeT1000: KbdWriteT1000(106,beforeMod.bmRightCtrl);break;
    }
  }
  if (beforeMod.bmRightShift != afterMod.bmRightShift) {
    if (debugMessage) Serial.println("RightShift changed");
    switch (KbdMode)
    {
      case KbdModeAT: KbdWriteAT(107,beforeMod.bmRightShift,0);break;
      case KbdModeXT: KbdWriteXT(107,beforeMod.bmRightShift);break;
      case KbdModeAmiga: KbdWriteAmiga(107,beforeMod.bmRightShift);break;
      case KbdModeT1000: KbdWriteT1000(107,beforeMod.bmRightShift);break;
    }
  }
  if (beforeMod.bmRightAlt != afterMod.bmRightAlt) {
    if (debugMessage) Serial.println("RightAlt changed");
    switch (KbdMode)
    {
      case KbdModeAT: KbdWriteAT(108,beforeMod.bmRightAlt,0);break;
      case KbdModeXT: KbdWriteXT(108,beforeMod.bmRightAlt);break;
      case KbdModeAmiga: KbdWriteAmiga(108,beforeMod.bmRightAlt);break;
      case KbdModeT1000: KbdWriteT1000(108,beforeMod.bmRightAlt);break;
    }
  }
  if (beforeMod.bmRightGUI != afterMod.bmRightGUI) {
    if (debugMessage) Serial.println("RightGUI changed");
    switch (KbdMode)
    {
      case KbdModeAT: KbdWriteAT(109,beforeMod.bmRightGUI,0);break;
      case KbdModeXT: KbdWriteXT(109,beforeMod.bmRightGUI);break;
      case KbdModeAmiga: KbdWriteAmiga(109,beforeMod.bmRightGUI);break;
      case KbdModeT1000: KbdWriteT1000(109,beforeMod.bmRightGUI);break;
    }
  }

}

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
  if (debugMessage) Serial.print("UP ");
  PrintKey(mod, key);
  switch (KbdMode)
  {
    case KbdModeAT: KbdWriteAT((byte)key,1,0);break;
    case KbdModeXT: KbdWriteXT((byte)key,1);break;
    case KbdModeApple: KbdWriteADB((byte)key,1);break;
    case KbdModeAmiga: KbdWriteAmiga((byte)key,1);break;
    case KbdModeT1000: KbdWriteT1000((byte)key,1);break;
  }
  if (TypematicKey==key) TypematicKey=0;
}

void KbdRptParser::OnKeyPressed(uint8_t key)
{
  if (debugMessage) Serial.print("ASCII: ");
  if (debugMessage) Serial.println((char)key);
  //switch (KbdMode)
  //{
    //case KbdModeAT: KbdWriteAT((byte)key,0,0);break;
    //case KbdModeXT: KbdWriteXT((byte)key,0);break;
    //case KbdModeT1000: KbdWriteT1000((byte)key,0);break;
  //}
};

USB     Usb;
USBHub  Hub1(&Usb);
USBHub  Hub2(&Usb);
USBHub  Hub3(&Usb);
USBHub  Hub4(&Usb);

HIDBoot < USB_HID_PROTOCOL_KEYBOARD | USB_HID_PROTOCOL_MOUSE > HidComposite(&Usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);
HIDBoot<USB_HID_PROTOCOL_MOUSE>    HidMouse(&Usb);

KbdRptParser KbdPrs;
MouseRptParser MousePrs;


void KbdWriteT1000(byte value,byte make) // routine to parse and handle the USB keys to tandy scancodes - strongly adapted to USB from the PS2 to Tandy 1000 by Adrian Black
{
  if (!make) switch (value) {
          case kbdcapsscan:
            kbdcaps =! kbdcaps;
            kbdleds = ( kbdcaps ) ? kbdleds |= 2 : kbdleds &= ~2;       // set or clear bit 1 of LED report byte
            break;
          case kbdnumscan:
            kbdnum =! kbdnum;
            kbdleds = ( kbdnum ) ? kbdleds |= 1 : kbdleds &= ~1;           // set or clear bit 0 of LED report byte
            break;
          case kbdscrollscan:
            kbdscroll =! kbdscroll;
            kbdleds = ( kbdscroll ) ? kbdleds |= 4 : kbdleds &= ~4;   // set or clear bit 2 of LED report byte
            break;    
  }
  HidKeyboard.SetReport( 0, KBD_IF, 0x02, 0, 1, &kbdleds) ;

  switch(value) {//handle special keys or fire out standard scancode on normal keys
    case 85: //Keypad * -> Shift + 8
      switch (make) {
        case 0:
          sendToTandy(KbdScancode[107][make][0]);
          sendToTandy(KbdScancode[37][make][0]);
          break;
        case 1:
          sendToTandy(KbdScancode[37][make][0]);
          sendToTandy(KbdScancode[107][make][0]);
          break;
        default:
          break;
      }
    case 87: //Keypad + -> Shift + =
      switch (make) {
        case 0:
          sendToTandy(KbdScancode[107][make][0]);
          sendToTandy(KbdScancode[46][make][0]);
          break;
        case 1:
          sendToTandy(KbdScancode[46][make][0]);
          sendToTandy(KbdScancode[107][make][0]);
          break;
        default:
          break;
      }
    case 103: //Right Shift
      switch (make) {
        case 0:
          TandyShiftPress|=1;
          sendToTandy(KbdScancode[value][make][0]);
          break;
        case 1:
          TandyShiftPress&=2;
          sendToTandy(KbdScancode[value][make][0]);
          break;
        default:
          break;
      }
    case 107: //Right Shift
      switch (make) {
        case 0:
          TandyShiftPress|=2;
          sendToTandy(KbdScancode[value][make][0]);
          break;
        case 1:
          TandyShiftPress&=1;
          sendToTandy(KbdScancode[value][make][0]);
          break;
        default:
          break;
      }
    case 83: //Num Lock - No Break Code on release, Break on repeated press when turning off
      switch (make) {
        case 0:
          sendToTandy(KbdScancode[value][!kbdnum][0]);
          break;
        case 1:
          break;
        default:
          break;
      }
    case 57: //Caps Lock - No Break Code on release, Break on repeated press when turning off
      switch (make) {
        case 0:
          sendToTandy(KbdScancode[value][!kbdcaps][0]);
          break;
        case 1:
          break;
        default:
          break;
      }
    case 71: //Scroll Lock - No Break Code on release, Break on repeated press when turning off
      switch (make) {
        case 0:
          sendToTandy(KbdScancode[value][!kbdnum][0]);
          break;
        case 1:
          break;
        default:
          break;
      }
    case 49: //Backslash/Pipe - Immediate Make and Break with Numlock involvement
      if (TandyShiftPress==0) { //Shift off: Backslash via Keypad 7 with numlock off
        switch (make) {
          case 0:
            if (kbdnum) sendToTandy(KbdScancode[107][1][0]);
            sendToTandy(KbdScancode[95][0][0]);
            sendToTandy(KbdScancode[95][1][0]);
            if (kbdnum) sendToTandy(KbdScancode[107][0][0]);
            break;
          case 1:
            break;
          default:
            break;
        }
      }
      else { //Shift pressed: Pipe via Keypad 4 with numlock on
        switch (make) {
          case 0:
            if (!kbdnum) sendToTandy(KbdScancode[107][0][0]);
            sendToTandy(KbdScancode[92][0][0]);
            sendToTandy(KbdScancode[92][1][0]);
            if (!kbdnum) sendToTandy(KbdScancode[107][1][0]);
            break;
          case 1:
            break;
          default:
            break;
        }        
      }
      break;
    case 53: //Grave/Tilde - Immediate Make and Break with Numlock involvement
      if (TandyShiftPress==0) { //Shift off: Grave via Keypad 2 with numlock off
        switch (make) {
          case 0:
            if (kbdnum) sendToTandy(KbdScancode[107][1][0]);
            sendToTandy(KbdScancode[90][0][0]);
            sendToTandy(KbdScancode[90][1][0]);
            if (kbdnum) sendToTandy(KbdScancode[107][0][0]);
            break;
          case 1:
            break;
          default:
            break;
        }
      }
      else { //Shift pressed: Tilde via Keypad 8 with numlock on
        switch (make) {
          case 0:
            if (!kbdnum) sendToTandy(KbdScancode[107][0][0]);
            sendToTandy(KbdScancode[96][0][0]);
            sendToTandy(KbdScancode[96][1][0]);
            if (!kbdnum) sendToTandy(KbdScancode[107][1][0]);
            break;
          case 1:
            break;
          default:
            break;
        }        
      }
      break;
      case 73://Insert
      case 75://PgUp
      case 76://Delete 
      case 77://End
      case 78://PgDn all handled immediate make-break with force numlock off
        switch (make) {
          case 0:
            if (kbdnum) sendToTandy(KbdScancode[107][1][0]);
            sendToTandy(KbdScancode[value][0][0]);
            sendToTandy(KbdScancode[value][1][0]);
            if (kbdnum) sendToTandy(KbdScancode[107][0][0]);
            break;
          case 1:
            break;
          default:
            break;
        }                
    default:
      sendToTandy(KbdScancode[value][make][0]);
      break;
  }

}

void KbdWriteXT(byte value,byte make) // routine that writes to the data and clock lines to the XT - Stolen from sendToTandy from the PS2 to Tandy 1000 by Adrian Black, with potential adaptions
{
  if (debugMessage) Serial.println(value);if (debugMessage) Serial.println(make);
  if (!make) switch (value) {
          case kbdcapsscan:
            kbdcaps =! kbdcaps;
            kbdleds = ( kbdcaps ) ? kbdleds |= 2 : kbdleds &= ~2;       // set or clear bit 1 of LED report byte
            break;
          case kbdnumscan:
            kbdnum =! kbdnum;
            kbdleds = ( kbdnum ) ? kbdleds |= 1 : kbdleds &= ~1;           // set or clear bit 0 of LED report byte
            break;
          case kbdscrollscan:
            kbdscroll =! kbdscroll;
            kbdleds = ( kbdscroll ) ? kbdleds |= 4 : kbdleds &= ~4;   // set or clear bit 2 of LED report byte
            break;    
  }
  HidKeyboard.SetReport( 0, KBD_IF, 0x02, 0, 1, &kbdleds) ;

  int cnt=0;
  while ((cnt<9)&&(KbdScancode[value][make][cnt]!=0)) {
    byte tempvalue=KbdScancode[value][make][cnt];
    if (debugMessage) Serial.print("XT KbdScancode:");
    //if (debugMessage) Serial.println(tempvalue,BIN);
    if (tempvalue==0) return;
  
    byte bits[8];  

    for (int i = 0; i < 8; i++)
    {
      bits[i] = tempvalue & 1; // grab least significant bit of value byte  
      tempvalue >>= 1; // right-shift the value byte by one bit
    }

    while (digitalRead(KbdClock)==LOW);
  
    digitalWrite(KbdClock, LOW);
    digitalWrite(KbdData, HIGH);
    delayMicroseconds(120);
    digitalWrite(KbdClock, HIGH);
    delayMicroseconds(66);
    digitalWrite(KbdClock, LOW);
    delayMicroseconds(30);
    digitalWrite(KbdClock, HIGH);
    for (int i = 0; i < 8; i++)
    {
      digitalWrite(KbdClock, HIGH);
      digitalWrite(KbdData, bits[i]);
      delayMicroseconds(95);
      digitalWrite(KbdClock, LOW);
      digitalWrite(KbdData, LOW);
    } 

    digitalWrite(KbdData, LOW);
    digitalWrite(KbdClock, HIGH);
    delay(1);
    cnt++;
  }
}

void KbdWriteADB(byte value,byte make) 
{
  if (debugMessage) Serial.println(value);if (debugMessage) Serial.println(make);
  if ((digitalRead(ADBPwr)==HIGH)&&(!make)) switch (value) {
          case kbdcapsscan:
            kbdcaps =! kbdcaps;
            kbdleds = ( kbdcaps ) ? kbdleds |= 2 : kbdleds &= ~2;       // set or clear bit 1 of LED report byte
            break;
          case kbdnumscan:
            kbdnum =! kbdnum;
            kbdleds = ( kbdnum ) ? kbdleds |= 1 : kbdleds &= ~1;           // set or clear bit 0 of LED report byte
            break;
          case kbdscrollscan:
            kbdscroll =! kbdscroll;
            kbdleds = ( kbdscroll ) ? kbdleds |= 4 : kbdleds &= ~4;   // set or clear bit 2 of LED report byte
            break;    
  }
  HidKeyboard.SetReport( 0, KBD_IF, 0x02, 0, 1, &kbdleds) ;
 
  if (KbdScancode[value][0][0]==0x7F) {
    digitalWrite(ADBPwrSwitch,!make);
  }
  KbdPutBufferAT(value,make); //As the ADB host polls data, we will use the same buffer used while PS/2 keyboard disabled to buffer keypresses and output this once ADB host polls
}

void ResetAmiga() {
  if (kbdcaps) {
    kbdcaps=0;
    kbdleds = ( kbdcaps ) ? kbdleds |= 2 : kbdleds &= ~2;       // set or clear bit 1 of LED report byte
  }
  HidKeyboard.SetReport( 0, KBD_IF, 0x02, 0, 1, &kbdleds) ;
  KbdWriteAmigaNoSpecialHandling(kbdcapsscan,1); //switch off Caps Lock
  byte success=ResetWarningAmiga();
  byte CtrlAmigaAmiga2=CtrlAmigaAmigaPress;
  CtrlAmigaAmigaPress=0;
  CtrlAmigaAmigaTime=0;
  if (success) HardResetAmiga();
  KbdPowerUpAmiga(CtrlAmigaAmiga2);
}

void KbdWriteAmiga(byte value,byte make) // routine that writes to the data and clock lines to the XT - Stolen from sendToTandy from the PS2 to Tandy 1000 by Adrian Black, with potential adaptions
{
  if ((value==57)&&(make==1)) return; //don't send break on release of Caps Lock
  if (debugMessage) Serial.println(value);if (debugMessage) Serial.println(make);
  if (!make) switch (value) {
          case kbdcapsscan:
            kbdcaps =! kbdcaps;
            kbdleds = ( kbdcaps ) ? kbdleds |= 2 : kbdleds &= ~2;       // set or clear bit 1 of LED report byte
            break;
          default:break;
  }
  HidKeyboard.SetReport( 0, KBD_IF, 0x02, 0, 1, &kbdleds) ;

  if ((CtrlAmigaAmigaPress==7)&&(make)&&((value==101)||(value==102)||(value==105)||(value==106)||(value==109))) {
   ResetAmiga();
  }
  
  int cnt=0;
  byte tempvalue=0;
  
  if (value==57) tempvalue=KbdScancode[value][!kbdcaps][0];
  else tempvalue=KbdScancode[value][make][0];
  if (debugMessage) Serial.print("Amiga KbdScancode:");
  if (debugMessage) Serial.println(tempvalue,BIN);
  if ((tempvalue==0)&&(value!=53)) return;

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
  timeout=millis()+5;
  if (success) while ((digitalRead(KbdData)==LOW)&&(millis()<timeout));  
  switch (value) {
    case 102: //left Ctrl = Amiga Ctrl
      if (!make) CtrlAmigaAmigaPress|=1;
      else CtrlAmigaAmigaPress&=6;
      break;
    case 106: //right Ctrl = Amiga Ctrl Mirrored  
      if (!make) CtrlAmigaAmigaPress|=1;
      else CtrlAmigaAmigaPress&=6;
      break;
    case 105: //left Meta = Left Amiga  
      if (!make) CtrlAmigaAmigaPress|=2;
      else CtrlAmigaAmigaPress&=5;
      break;
    case 109: //right Meta = Right Amiga  
      if (!make) CtrlAmigaAmigaPress|=4;
      else CtrlAmigaAmigaPress&=3;
      break;
    case 101: //Windows Menu= Right Amiga Mirrored
      if (!make) CtrlAmigaAmigaPress|=4;
      else CtrlAmigaAmigaPress&=3;
      break;
    default:
      break;
  }
  if (CtrlAmigaAmigaPress==7) {
    CtrlAmigaAmigaTime=millis()+500;
  }
}


void KbdAckXT() // Send ACK on Power On Self Test
{
  byte tempvalue=0xAA; //ACK
  if (debugMessage) Serial.print("POST: XT KbdScancode ACK:");
  //if (debugMessage) Serial.println(tempvalue,BIN);
  
  byte bits[8];  

  for (int i = 0; i < 8; i++)
  {
    bits[i] = tempvalue & 1; // grab least significant bit of value byte  
    tempvalue >>= 1; // right-shift the value byte by one bit
  }

  while (digitalRead(KbdClock)==LOW);
  
  digitalWrite(KbdClock, LOW);
  digitalWrite(KbdData, HIGH);
  delayMicroseconds(120);
  digitalWrite(KbdClock, HIGH);
  delayMicroseconds(66);
  digitalWrite(KbdClock, LOW);
  delayMicroseconds(30);
  digitalWrite(KbdClock, HIGH);
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(KbdClock, HIGH);
    digitalWrite(KbdData, bits[i]);
    delayMicroseconds(95);
    digitalWrite(KbdClock, LOW);
    digitalWrite(KbdData, LOW);
  } 

  digitalWrite(KbdData, LOW);
  digitalWrite(KbdClock, HIGH);
  delay(1);
  kbdcaps=0;kbdnum=0;kbdscroll=0;kbdleds=0;
  HidKeyboard.SetReport( 0, KBD_IF, 0x02, 0, 1, &kbdleds) ;
  
}

void KbdOutputBufferAT() {
  byte i=0;
  while (i<ATKbdBufferPos) { //I did not use a for loop because there might be something added to the buffer as USB has interrupt priority during writing the buffer, not sure about the behavior of while and for on increasing numbers during a running loop, but chances on while are better
    KbdWriteAT(ATKbdBuffer[i][0],ATKbdBuffer[i][1],1);
    if (debugMessage){
      Serial.print("Output Buffer Pos ");
      Serial.println(i);
    }
    i++;
  }
  ATKbdBufferPos=0;
}

void KbdWriteAT(byte value,byte make,byte overridedisable) // routine that writes to the data and clock lines to the AT - Stolen from sendToTandy from the PS2 to Tandy 1000 by Adrian Black, with potential adaptions
{
  if ((!ATKbdEnable)&&(!overridedisable)) {
    KbdPutBufferAT(value,make);
    return;
  }
  if (!make) {
    if ((value<110)&&(KbdRst)) {
      KbdRst=0; //A make code voids the break code suppression after keyboard reset
      if (debugMessage) Serial.println("Break Code Suppression Revoke");          
    }
  }
  else {
    if ((KbdRst)&&(value<110)) {
      if (debugMessage) Serial.println("Break Code Suppressed");      
      return; //suppress break codes after keyboard reset
    }
  }
  int cnt=0; 
  char TempScancode[9];
  if ((value==72)&&(KbdScancode[113][0][0]==2)) { //get 72 Pause and 70 Print/SysReq covered (extremely long scan codes) for Scancode Set 2
    if (make==0) {
      strcpy(TempScancode,"\xE1\x14\x77\xE1\xF0\x14\xF0\x77\x00");
    } else {
      strcpy(TempScancode,"\x00");
    }
  } else if ((value==70)&&(KbdScancode[113][0][0]==2)) {
    if (make==0) {
      strcpy(TempScancode,"\xE0\x12\xE0\x7C\x00");
    } else {
      strcpy(TempScancode,"\xE0\xF0\x7C\xE0\xF0\x12");
    }
  }
  else {
    strcpy(TempScancode,KbdScancode[value][make]);
  }
  while ((cnt<8)&&(TempScancode[cnt]!=0)) {
    byte tempvalue=TempScancode[cnt];
    ATKbdLastByteSent=tempvalue;
    if (debugMessage) Serial.print("AT KbdScancode:");
    if (debugMessage) Serial.println(tempvalue,HEX);
    if (tempvalue==0) return;

    byte bits[8];  
     for (int i = 0; i < 8; i++)
    {
      bits[i] = tempvalue & 1; // grab least significant bit of value byte  
      tempvalue >>= 1; // right-shift the value byte by one bit
    }
     while (digitalRead(KbdClock)==LOW) KbdHostToDeviceAT();

    KbdLow(KbdData);
    delayMicroseconds(20);
    KbdLow(KbdClock);
    delayMicroseconds(40);
    KbdHigh(KbdClock);
    delayMicroseconds(20);
    int parity=1;
    for (int i = 0; i < 8; i++) {
      switch (bits[i]) {
        case 0:KbdLow(KbdData);break;
        default:KbdHigh(KbdData);break;
      }
      delayMicroseconds(20);
      KbdLow(KbdClock);
      delayMicroseconds(40);
      KbdHigh(KbdClock);
      parity=(parity+bits[i])%2;
    } 
    switch(parity) {
      case 0:KbdLow(KbdData);break;
      default:KbdHigh(KbdData);break;
    }
    delayMicroseconds(20);
    KbdLow(KbdClock);
    delayMicroseconds(40);
    KbdHigh(KbdClock);
    delayMicroseconds(20);
    KbdHigh(KbdData); //Stop-Bit 1
    delayMicroseconds(20);
    KbdLow(KbdClock);
    delayMicroseconds(40);
    KbdHigh(KbdClock);
    //delay(1);
    cnt++;
  }
  if ((digitalRead(KbdClock)==LOW)&&(digitalRead(KbdData)==HIGH)&&(!overridedisable)) KbdHostToDeviceAT();
}

void KbdHostToDeviceAT() {
  if ((digitalRead(PS2MouseClock)==LOW)&&(digitalRead(PS2MouseData)==HIGH)&&(digitalRead(PS2MousePower)==HIGH)) MouseHostToDevicePS2();
  int readbyte=0;
  int readbyte2=0;
  int rawdelay=0;
  int rawrate=0;
  if (debugMessage) Serial.println("AT Keyboard Transmit Inhibit - Check for Send Request");
  unsigned long kbdtimeoutmillis=millis();
  byte kbdtimeout=0;
  while ((digitalRead(KbdClock)==LOW)&&(!kbdtimeout)) {
    kbdtimeout=(kbdtimeoutmillis+45)<millis();
  }
  if (kbdtimeout) {
    if (debugMessage) Serial.println("Keyboard Read Timeout");
    return;            
  }
  if (digitalRead(KbdData)==LOW) readbyte=KbdReadAT();
  else return;
  switch(readbyte) {
    case 0xED: //Set Status LEDs
      ATKbdEnable=0;
      if (debugMessage) Serial.println("Set Status LEDs");
      KbdWriteAT(110,0,1); //Send 0xFA Ack
      while (digitalRead(KbdClock)==LOW);
      readbyte2=KbdReadAT();
      KbdWriteAT(110,0,1); //Send 0xFA Ack
      if (debugMessage) Serial.println(readbyte2,BIN);
      kbdscroll=readbyte2&1;
      kbdnum=(readbyte2>>1)&1;
      kbdcaps=(readbyte2>>2)&1;
      if (debugMessage) {Serial.print("Scroll=");Serial.print(kbdscroll);Serial.print(", Num=");Serial.print(kbdnum);Serial.print(", Caps=");Serial.println(kbdcaps);}
      kbdleds=kbdnum+(kbdcaps<<1)+(kbdscroll<<2);
      HidKeyboard.SetReport( 0, KBD_IF, 0x02, 0, 1, &kbdleds) ;
      ATKbdEnable=1;
      break;
    case 0xEE: //Echo
      if (debugMessage) Serial.println("Keyboard Echo");
      KbdWriteAT(112,0,1); //hidden behind "misused" USB KbdScancode 112 is the Echo
      break;
    case 0xF0: //Set KbdScancode set
       if (debugMessage) Serial.println("Set KbdScancode Set");
      while (digitalRead(KbdClock)==HIGH);
      while (digitalRead(KbdClock)==LOW);
      readbyte2=KbdReadAT();
      KbdWriteAT(110,0,1); //Send 0xFA Ack
       switch (readbyte2) {
          case 0: //write back 
            if (debugMessage) Serial.println("Host wants to read back current KbdScancode set");
            KbdWriteAT(113,0,1);
            break; 
          case 1: //Set KbdScancode Set 1
            if (debugMessage) Serial.println("Set to KbdScancode 1");
            initScancodeATSet1();
            break;
          case 2: //Set KbdScancode Set 2
            if (debugMessage) Serial.println("Set to KbdScancode 2");
            initScancodeATSet2();
            break;
          case 3: //Set KbdScancode Set 3
            if (debugMessage) Serial.println("Set to KbdScancode 3");
            initScancodeATSet3();
            break;
       }
       break;
    case 0xF2: //Read Device ID
      if (debugMessage) Serial.println("Device ID requested");
      KbdWriteAT(111,0,1); //hidden behind "misused" USB KbdScancode 111 is the Device ID
      break;
    case 0xF3: //Typematic Rate Set
      if (debugMessage) Serial.println("Typematic Rate Set");
      KbdWriteAT(110,0,1); //Send 0xFA Ack
      while (digitalRead(KbdClock)==LOW);
      readbyte2=KbdReadAT();
      KbdWriteAT(110,0,1); //Send 0xFA Ack
      rawdelay=(readbyte2>>5)&3;
      rawrate=readbyte2&31;
      if (debugMessage) Serial.print("Delay ");if (debugMessage) Serial.print(rawdelay);if (debugMessage) Serial.print(" Rate ");if (debugMessage) Serial.println(rawrate);
      switch (rawdelay) {
        case 0:TypematicDelay1=250;break;
        case 1:TypematicDelay1=500;break;
        case 2:TypematicDelay1=750;break;
        case 3:TypematicDelay1=1000;break;
      }
      switch(rawrate) {
        case 0:TypematicDelay2=33;break;
        case 1:TypematicDelay2=38;break;
        case 2:TypematicDelay2=42;break;
        case 3:TypematicDelay2=46;break;
        case 4:TypematicDelay2=48;break;
        case 5:TypematicDelay2=54;break;
        case 6:TypematicDelay2=59;break;
        case 7:TypematicDelay2=63;break;
        case 8:TypematicDelay2=67;break;
        case 9:TypematicDelay2=75;break;
        case 10:TypematicDelay2=83;break;
        case 11:TypematicDelay2=92;break;
        case 12:TypematicDelay2=100;break;
        case 13:TypematicDelay2=109;break;
        case 14:TypematicDelay2=116;break;
        case 15:TypematicDelay2=125;break;
        case 16:TypematicDelay2=133;break;
        case 17:TypematicDelay2=149;break;
        case 18:TypematicDelay2=167;break;
        case 19:TypematicDelay2=182;break;
        case 20:TypematicDelay2=200;break;
        case 21:TypematicDelay2=217;break;
        case 22:TypematicDelay2=233;break;
        case 23:TypematicDelay2=250;break;
        case 24:TypematicDelay2=270;break;
        case 25:TypematicDelay2=303;break;
        case 26:TypematicDelay2=333;break;
        case 27:TypematicDelay2=370;break;
        case 28:TypematicDelay2=400;break;
        case 29:TypematicDelay2=434;break;
        case 30:TypematicDelay2=476;break;
        case 31:TypematicDelay2=500;break;
      }
      break;
    case 0xF4: //Enable Keyboard
      KbdWriteAT(110,0,1);  //hidden behind "misused" USB KbdScancode 110 is the Init ACK
      if (!ATKbdEnabling) {
        ATKbdEnabling=1;
        delayMicroseconds(80);
        KbdOutputBufferAT();
        ATKbdEnable=1;
        ATKbdEnabling=0;
      }
      break;
    case 0xF5: //Disable Keyboard
      ATKbdEnable=0;
      KbdWriteAT(110,0,1);  //hidden behind "misused" USB KbdScancode 110 is the Init ACK
      break;
    case 0xF6: //Reset to Default
      KbdWriteAT(110,0,1);  //hidden behind "misused" USB KbdScancode 110 is the Init ACK
      if (debugMessage) Serial.println("Reset to Default");
      initScancodeATSet2();
      TypematicDelay1=500;
      TypematicDelay2=92;
    case 0xFE: //Resend Request
      KbdResendAT(); //hidden behind "misused" USB KbdScancode 110 is the Init ACK
      break;
    case 0xFF: //Reset Request
      KbdRst=1;
      KbdWriteAT(110,0,1); //hidden behind "misused" USB KbdScancode 110 is the Init ACK
      if (debugMessage) Serial.println("Keyboard Reset");
      kbdleds=0b111; //Blink the USB Keyboard LEDs in AT Init Style
      HidKeyboard.SetReport( 0, KBD_IF, 0x02, 0, 1, &kbdleds) ;
      delay(550);
      kbdleds=0b000;
      HidKeyboard.SetReport( 0, KBD_IF, 0x02, 0, 1, &kbdleds) ;
      KbdWriteAT(110,1,1); //hidden behind "misused" USB KbdScancode 110 is the Init Reset ACK
      kbdcaps=0; //And zero the internal status for the LEDs
      kbdnum=0;
      kbdscroll=0;
      break;
    default: break;
  }
}

void KbdResendAT() {
    char tempvalue=ATKbdLastByteSent;
    
    if (tempvalue==0) return;
  
    byte bits[8];  

    for (int i = 0; i < 8; i++)
    {
      bits[i] = tempvalue & 1; // grab least significant bit of value byte  
      tempvalue >>= 1; // right-shift the value byte by one bit
    }

    while (digitalRead(KbdClock)==LOW);
  
    KbdLow(KbdData);
    delayMicroseconds(20);
    KbdLow(KbdClock);
    delayMicroseconds(40);
    KbdHigh(KbdClock);
    delayMicroseconds(20);
    int parity=1;
    for (int i = 0; i < 8; i++) {
      switch (bits[i]) {
        case 0:KbdLow(KbdData);break;
        default:KbdHigh(KbdData);break;
      }
      delayMicroseconds(20);
      KbdLow(KbdClock);
      delayMicroseconds(40);
      KbdHigh(KbdClock);
      parity=(parity+bits[i])%2;
    } 
    switch(parity) {
      case 0:KbdLow(KbdData);break;
      default:KbdHigh(KbdData);break;
    }
  delayMicroseconds(20);
  KbdLow(KbdClock);
  delayMicroseconds(40);
  KbdHigh(KbdClock);
  delayMicroseconds(20);
  KbdHigh(KbdData); //Stop-Bit 1
  delayMicroseconds(20);
  KbdLow(KbdClock);
  delayMicroseconds(40);
  KbdHigh(KbdClock);
  //delay(1);
  if ((digitalRead(KbdClock)==LOW)&&(digitalRead(KbdData)==HIGH)) KbdHostToDeviceAT();
}


HIDUniversal HidJoy(&Usb);
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents);

void setup()
{
  initInput();
  
  debugSetup();
  if (Usb.Init() == -1)
    if (debugMessage) Serial.println("OSC did not start.");

  pinMode(ADBPwr, INPUT);
  pinMode(ADBPwrSwitch, OUTPUT);
  digitalWrite(ADBPwrSwitch, HIGH);
  KbdHigh(ADBData);

  switch (KbdMode)
  {
    case KbdModeAT: //Value 0 - All off
      if (debugMessage) Serial.println("IBM/Compatible PC/AT, Tandy 1000SL/TL and PS/2 Keyboard");
      initScancodeATSet2(); //Start with Scan Code Set 2, Host Command can trigger switch to different set
      KbdHigh(KbdClock);
      KbdHigh(KbdData);
      break;
    case KbdModeXT: //Value 1 - XT set
      if (debugMessage) Serial.println("IBM/Compatible PC/XT Keyboard");
      initScancodeXT();
      pinMode(KbdData, OUTPUT); 
      pinMode(KbdClock, OUTPUT); 
      digitalWrite(KbdClock, HIGH); 
      digitalWrite(KbdData, LOW); 
      break;
    case KbdModeAmiga: //Value 3 - Amiga set
      if (debugMessage) Serial.println("Amiga Keyboard");
      initScancodeAmiga();
      pinMode(KbdData,OUTPUT);
      pinMode(KbdClock,OUTPUT);
      pinMode(KbdReset,OUTPUT);
      digitalWrite(KbdReset,HIGH);
      digitalWrite(KbdClock, HIGH);
      digitalWrite(KbdClock, HIGH);
      break;
    case KbdModeApple: //Value 2 - Apple ADB set
      if (debugMessage) Serial.println("Apple ADB Keyboard");
      initScancodeApple();
      break;
    case KbdModeT1000: //Value 4 - Tandy set
      if (debugMessage) Serial.println("Tandy 1000 Keyboard - All routing switches need to be set to T1000 or Keyboard/Arduino can be damaged");
      initScancodeT1000();
      pinMode(KbdData, OUTPUT); 
      pinMode(KbdClock, OUTPUT); 
      digitalWrite(KbdClock, LOW); 
      digitalWrite(KbdData, HIGH); 
      break;
    default: //Values 5-7 - Tandy and other mode switches set
      if (debugMessage) Serial.println("PC/Amiga Switch and XT/AT Switch ignored in Tandy Mode - All routing switches need to be set to T1000 or Keyboard/Arduino can be damaged");
      KbdMode=KbdModeT1000;
      initScancodeT1000();
      break;
  }
  SerMouseMode=digitalRead(SerMouseModePin);
  switch (SerMouseMode)
  {
    case 0: if (debugMessage) Serial.println("Serial Mouse in 2-Button Microsoft mode");break;
    case 1: if (debugMessage) Serial.println("Serial Mouse in 3-Button Logitech mode");break;
    default: if (debugMessage) Serial.println("Something went wrong reading out digital joystick mode - Defaulting Microsoft Mouse");SerMouseMode=0;break;
  }
  
  DJoyMode=digitalRead(DJoyModePin);
  switch (DJoyMode)
  {
    case 0: if (debugMessage) Serial.println("Digital joystick port in Joystick mode - USB Joystick will be reference");break;
    case 1: if (debugMessage) Serial.println("Digital joystick port in Commodore 1350 Joystick-Mouse mode - USB Mouse will be reference");break;
    default: if (debugMessage) Serial.println("Something went wrong reading out digital joystick mode - Defaulting to Joystick mode - USB Joystick will be reference");DJoyMode=0;break;
  }

    switch(digitalRead(AMouseModePin))
  {
    case 0: 
      if (debugMessage) Serial.println("Amiga Mouse");
      AMouseYPin=33; //To Pin 3
      AMouseYQPin=35; //To Pin 1
      AMouseXPin=31; //To Pin 2
      AMouseXQPin=29; //To Pin 4
      break;
    case 1:
      if (debugMessage) Serial.println("Atari Mouse");
      AMouseYPin=33; //To Pin 3
      AMouseYQPin=29; //To Pin 4
      AMouseXPin=31; //To Pin 2
      AMouseXQPin=35; //To Pin 1
      break;
    default: 
      AMouseYPin=35; //To Pin 1
      AMouseYQPin=33; //To Pin 3
      AMouseXPin=31; //To Pin 2
      AMouseXQPin=29; //To Pin 4
      if (debugMessage) Serial.println("Something went wrong reading out pulse mouse mode - Defaulting to Amiga Mouse");
      break;
  }
  delay( 200 );
  
  initOutput();
  
  HidComposite.SetReportParser(0, &KbdPrs);
  HidComposite.SetReportParser(1, &MousePrs);
  HidKeyboard.SetReportParser(0, &KbdPrs);
  HidMouse.SetReportParser(0, &MousePrs);
  HidJoy.SetReportParser(0, &Joy);
}

void loop()
{
/*  byte PS2PowerTemp=digitalRead(PS2MousePower);
  if (PS2PowerTemp!=PS2MousePowered) {
    switch (PS2PowerTemp) {
      case 0:
        PS2MousePowered=0;//PS2MouseInitSuccess=0;
        if (debugMessage) Serial.println("PS/2 Mouse Power Off");
      case 1:
        PS2MousePowered=1;//PS2MouseInitSuccess=0;
        if (debugMessage) Serial.println("PS/2 Mouse Power On");
    }
  }
  if (PS2MousePowered!=PS2MouseInitSuccess) {
    PS2MousePowerOnHandshake();
  }*/
  if (KbdPowerState!=digitalRead(KbdPower)) {
    KbdPowerState=digitalRead(KbdPower);
    if (KbdPowerState) {
      switch(KbdMode) {
        case KbdModeAmiga:
          KbdPowerUpAmiga(0);
          break;
        default:break;
      }
    }
    else {
      if (debugMessage) Serial.println("Keyboard Power Off. Switching off keyboard LEDs");
      kbdscroll=0;kbdnum=0;kbdcaps=0;kbdleds=0;
      HidKeyboard.SetReport( 0, KBD_IF, 0x02, 0, 1, &kbdleds) ;
    }
  }
  if ((CtrlAmigaAmigaTime>0)&&(CtrlAmigaAmigaTime<millis())) ResetAmiga();
  byte ADBCommandRaw; byte listenResult;
  switch (KbdMode)
  {
    case KbdModeAT:
      if ((digitalRead(KbdClock)==LOW)&&(digitalRead(KbdData)==HIGH)) KbdHostToDeviceAT();
      break;
    case KbdModeXT:
      if ((digitalRead(KbdClock)==LOW)&&(digitalRead(KbdData)==HIGH)) {
        delay(10);
        KbdAckXT();
      }
      break;
    case KbdModeApple:
      switch(ADBSync()) {
        case 1: //Attention
          ADBCommandRaw=ADBReadCommand();
          if (ADBCommandRaw!=255) { //255=Timeout
            ADBRegister=ADBCommandRaw&3; //Bit 0/1
            ADBCommand=(ADBCommandRaw>>2)&3; //Bit 2/3;
            ADBAddress=(ADBCommandRaw>>4)&15; //Bit 4-7
          }
          switch(ADBCommand) {
            case ADBCmdTALK:
              switch(ADBAddress) {
                case ADBAddrKbd:
                  break;
                case ADBAddrMouse:
                  if (ADBRegister==0) {
                    MouseWriteADB();
                  }
                  else if (ADBRegister==3) {
                    MouseWriteADBReg3();
                  }
                  break;
                default:
                  break;
              }
              break;
            case ADBCmdLISTEN:
              while (digitalRead(ADBData)==LOW);
              while (digitalRead(ADBData)==HIGH);
              if (ADBSync()==1) {
                listenResult=ADBReadCommand();
              }
              if (debugMessage) {Serial.print("Listen Result: ");Serial.println(listenResult);}
              if (ADBRegister==2) { //Register 2 = among others LEDs in bits 0-2
                
              }
              break; //Whatever is listened to, is still to be implemented
            case ADBCmdFLUSH: 
              break; //Flush to be implemented or ignored
          }
          break;
        case 2: //Reset to be implemented or ignored
          break;
        default: //Timeout etc.
          break;
      }
    case KbdModeAmiga:
      break;
    case KbdModeT1000:
      break;
  }
  if ((digitalRead(PS2MouseClock)==LOW)&&(digitalRead(PS2MouseData)==HIGH)&&(digitalRead(PS2MousePower)==HIGH)) MouseHostToDevicePS2();
  if ((TypematicKey>0)&&(millis()>(TypematicPhase+TypematicMillis))&&(!KbdRst)&&ATKbdTypematicKey((byte)TypematicKey)) { //Repeat sending Make codes while key pressed, only for last key down, except after keyboard reset
    if (TypematicPhase==TypematicDelay1) TypematicPhase=TypematicDelay2;
    switch (KbdMode)
    {
      case KbdModeAT: KbdWriteAT((byte)TypematicKey,0,0);break;
      case KbdModeXT: KbdWriteXT((byte)TypematicKey,0);break;
      case KbdModeAmiga: break; //Amiga typematics itself
      case KbdModeT1000: KbdWriteT1000((byte)TypematicKey,0);break;
    }  
    TypematicMillis=millis();  
  }
  Usb.Task();
  if ((SerMouseClear)&&(mousebuttonchange||mousedx||mousedy)) {
    mousedx=mousedx/4; //Tame the beast - USB mouse resolution is very high ;-)
    mousedy=mousedy/4;
    //Write to all mouse ports
    SerMouseWrite();
    AMouseWrite();
    //ADBMouseWrite();
    //Clear mousedx and mousedy
    mousedx=0;mousedy=0;
    mousebuttonchange=0;
    //if (debugMessage) Serial.println("Serial Mouse write");
    SerMouseClear=0;
    SerMouseMillis=millis();
  }
  else if (millis()>(SerMouseInterval+SerMouseMillis)) {
    SerMouseClear=1;SerMouseMillis=millis();
  }
}

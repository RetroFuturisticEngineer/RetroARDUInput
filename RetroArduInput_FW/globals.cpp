#include "globals.h"
#include <Arduino.h>

//****************************************Change here for your preferred joystick type****************************************
byte JoyType=JoyTypeLogitechFGamepad;
//********************************************Below no custom changes required************************************************

byte Joy1X=128;
byte Joy1Y=128;
byte Joy2X=128;
byte Joy2Y=128;
byte JoyB1=0;
byte JoyB2=0;
byte JoyB3=0;
byte JoyB4=0;
byte JoyCalibration=1;
uint8_t JoyCenterX1=128;
uint8_t JoyCenterY1=128;
uint8_t JoyCenterX2=128;
uint8_t JoyCenterY2=128;
byte AMouseXPin; //Variables initialized in setup() due to Amiga Atari Pin Swap
byte AMouseXQPin;
byte AMouseYPin;
byte AMouseYQPin;

byte PulseMouseXYPattern[4]={LOW,LOW,HIGH,HIGH};
byte PulseMouseXYQPattern[4]={LOW,HIGH,HIGH,LOW};
byte PulseMouseXPos=0;
byte PulseMouseYPos=0;

byte PS2MouseMode=0;
byte PS2MousePreWrap=0;
byte PS2MousePreDisable=0;
byte PS2MouseLastByte=0;
byte PS2MouseScaling=0;
byte PS2MouseSampling=100;
byte PS2MouseRes=4;
byte KbdMode=0;
unsigned char kbdleds=0;
byte kbdcaps=0;
byte kbdnum=0;
byte kbdscroll=0;
byte KbdRst=0;

byte SerMouseMode=0;
byte DJoyMode=0;
byte mouselbutton=0;
byte mousembutton=0;
byte mouserbutton=0;
byte mousebuttonchange=0;
byte amouselbutton=0;
byte amousembutton=0;
byte amouserbutton=0;
byte amousebuttonchange=0;
int mousedx=0;
int mousedy=0;
int amousedx=0;
int amousedy=0;

unsigned long SerMouseMillis = millis();
unsigned long AMouseMillis = millis();
byte SerMouseClear=1;
int TypematicDelay1=500; //Typematic Rate Default - Can be modified through AT Keyboard Command
int TypematicDelay2=92; //Default: 500ms until first repeat, 10,9cps = rounded up 92ms for following repeats
unsigned long TypematicMillis; //Last key pressed will have repeated Make sent out
int TypematicPhase;
byte TypematicKey;
byte CtrlAmigaAmigaPress=0;
long CtrlAmigaAmigaTime=0;
byte KbdPowerState=0;

byte TandyShiftPress=0;

byte ADBRegister=0;
byte ADBCommand=0;
byte ADBAddress=0;

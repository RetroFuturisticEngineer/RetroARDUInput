#include <Arduino.h>

//Joystick types:

#define JoyTypeDefault 0 // Buttons are buttons, Main X/Y are X/Y 1 and Throttle/Twist X/Y 2
#define JoyTypeCompetition 1 //Speedlink Competition Pro USB
#define JoyTypeSLPhantom 2 //Speedlink Phantom Hawk
#define JoyTypeLogitechE3DP 3 //Logitech Extreme 3D Pro (10 Bit Resolution)
#define JoyTypeTMAirbus 4 //Thrustmaster TC Sidestick Airbus Edition (14 Bit Resolution), very likely also maps to the Hotas FCS Stick
#define JoyTypeLogitechFGamepad 5 //Logitech F Series Gamepad 
#define JoyTypeTLP_PS2DA 6 //Trio Linker Plus + Playstation 2 Dual Analogue
#define JoyTypeTLP_DC 7 //Trio Linker Plus + Dreamcast
#define JoyTypeTLP_GC 8 //Trio Linker Plus + Gamecube

extern byte JoyType;

//Constants Mode Switch Pins
#define KbdModeAT 0
#define KbdModeXT 1
#define KbdModeAmiga 3
#define KbdModeApple 2
#define KbdModeT1000 4

#define DebugModePin 30 //Wait for Serial/Serial output on USB Serial
#define KbdModePin0 32 //XT/AT Switch for PC mode, ignored in Tandy and Amiga mode
#define KbdModePin1 34 //PC/Amiga, ignored in Tandy mode
#define KbdModePin2 36 //PC+Amiga/Tandy Switch
#define SerMouseModePin 38 //2/3 Button Switch
#define DJoyModePin 40 //Digital Joystick or 1350 Joystick Mouse
#define AMouseModePin 42 //Amiga or Atari Mode (Swap two lines)

//Constants IRQ handlers
#define SerMouseIRQPin 19

//Constants I/O Pins
//Serial Mouse using 17/18 via Serial Mode
#define PS2MouseClock 5 //PS/2 Clock, Connector Pin 5
#define PS2MouseData 4 //PS/2 Data, Connector Pin 1
#define PS2MousePower 46 //Power Sensing for PS/2 Mouse, Connector Pin 4 via Pulldown Resistor
//PS/2 Connector Pin 3=Gnd Pin 4=+5V
#define KbdReset 49 //Reserved but so far ignored
#define KbdBusy 47 //dito
#define KbdData 45 //Keyboard Clock
#define KbdClock 43 //Keyboard Data
#define KbdPower 44 //Keyboard Power Sensing, Connector Pin 5 on both, Tandy and PC/Amiga, via Pulldown Resistor
#define DJoyLf 27 //Pin 3
#define DJoyRg 26 //Pin 4
#define DJoyUp 25 //Pin 1
#define DJoyDn 24 //Pin 2
#define DJoyB1 22 //Pin 6
#define DJoyB2 23 //Pin 9 - Additional: Gnd on Pin 8
#define ADBPwr 28 //Pin 3 via Pulldown Resistor - Pin 4 is Gnd
#define ADBPwrSwitch 7 //Pin 2
#define ADBData 6 //Pin 1

//#define AJoyB1 50 //Pin 2
//#define AJoyB2 51 //Pin 7
//#define AJoyB3 52 //Pin 10
//#define AJoyB4 53 //Pin 14
#define AJoyB1 8 //Pin 2
#define AJoyB2 9 //Pin 7
#define AJoyB3 10 //Pin 10
#define AJoyB4 11 //Pin 14
#define DJoyDeadZone 40 //Digital Joystick "Deadzone" around the center
extern byte Joy1X;
extern byte Joy1Y;
extern byte Joy2X;
extern byte Joy2Y;
extern byte JoyB1;
extern byte JoyB2;
extern byte JoyB3;
extern byte JoyB4;
extern byte JoyCalibration;
extern uint8_t JoyCenterX1;
extern uint8_t JoyCenterY1;
extern uint8_t JoyCenterX2;
extern uint8_t JoyCenterY2;
extern byte AMouseXPin; //Variables initialized in setup() due to Amiga Atari Pin Swap
extern byte AMouseXQPin;
extern byte AMouseYPin;
extern byte AMouseYQPin;
#define AMouseB1Pin 41 //To Pin 6
#define AMouseB2Pin 39 //To Pin 9
#define AMouseB3Pin 37 //To Pin 5Optional middle button

//Constants Atari/Amiga Mouse Pulse Pattern - 4 states that get cycled either forward or backward
extern byte PulseMouseXYPattern[4];
extern byte PulseMouseXYQPattern[4];
extern byte PulseMouseXPos;
extern byte PulseMouseYPos;

//Variables Operation Modes and operation
#define PS2Mdisable 0 //Data Report Disable
#define PS2Mstream 1 //Standard mode - mouse sends data
#define PS2Mremote 2 //Host requests mouse movement counter
#define PS2Mwrap 3 //Echo mode 
extern byte PS2MouseMode;
extern byte PS2MousePreWrap;
extern byte PS2MousePreDisable;
extern byte PS2MouseLastByte;
extern byte PS2MouseScaling;
extern byte PS2MouseSampling;
extern byte PS2MouseRes;
extern byte KbdMode;
extern unsigned char kbdleds;
extern byte kbdcaps;
extern byte kbdnum;
extern byte kbdscroll;
extern byte KbdRst;
#define kbdcapsscan 57
#define kbdnumscan 83
#define kbdscrollscan 71 
extern byte SerMouseMode;
extern byte DJoyMode;
extern byte mouselbutton;
extern byte mousembutton;
extern byte mouserbutton;
extern byte mousebuttonchange;
extern byte amouselbutton;
extern byte amousembutton;
extern byte amouserbutton;
extern byte amousebuttonchange;
extern int mousedx;
extern int mousedy;
extern int amousedx;
extern int amousedy;
#define SerMouseInterval 25 //limit serial port to 40 data packets each 3/4/max. 5 words per second
extern unsigned long SerMouseMillis;
extern unsigned long AMouseMillis;
extern byte SerMouseClear;
extern int TypematicDelay1; //Typematic Rate Default - Can be modified through AT Keyboard Command
extern int TypematicDelay2; //Default: 500ms until first repeat, 10,9cps = rounded up 92ms for following repeats
extern unsigned long TypematicMillis; //Last key pressed will have repeated Make sent out
extern int TypematicPhase;
extern byte TypematicKey;
extern byte CtrlAmigaAmigaPress;
extern long CtrlAmigaAmigaTime;
extern byte KbdPowerState;
extern byte TandyShiftPress;

#define ADBCmdTALK 3
#define ADBCmdLISTEN 2
#define ADBCmdFLUSH 0

#define ADBAddrKbd 2
#define ADBAddrMouse 3

extern byte ADBRegister;
extern byte ADBCommand;
extern byte ADBAddress;

#include <Arduino.h>
//Keyboard Scancode Array
//Empty Scancode Lookup Table
extern char KbdScancode[114][2][4];
extern char ATKbdLastByteSent;
extern byte ATKbdEnable;
extern byte ATKbdBufferPos;
extern byte ATKbdBuffer[8][2];
extern byte ATKbdEnabling;

void initScancodeATSet1();
void initScancodeATSet2();
void initScancodeATSet3();

void initScancodeXT();

void initScancodeT1000();

void initScancodeAmiga();

void initScancodeApple();

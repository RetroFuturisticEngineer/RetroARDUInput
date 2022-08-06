#include "Scancodes.h"
#include <string.h>
#include <Arduino.h>

char KbdScancode[114][2][4];
char ATKbdLastByteSent='\x00';
byte ATKbdEnable=1;
byte ATKbdBufferPos=0;
byte ATKbdBuffer[8][2];
byte ATKbdEnabling=0;

void initScancodeATSet1() //not yet fully double-checked, modifier keys etc.
{
  strcpy(KbdScancode[0][0],"\x00"); //No Key
  strcpy(KbdScancode[0][1],"\x00");
  strcpy(KbdScancode[1][0],"\x00"); //Keyboard Error
  strcpy(KbdScancode[1][1],"\x00");
  strcpy(KbdScancode[2][0],"\x00"); //POST Fail
  strcpy(KbdScancode[2][1],"\x00");  
  strcpy(KbdScancode[3][0],"\x00"); //undefined error
  strcpy(KbdScancode[3][1],"\x00");
  strcpy(KbdScancode[4][0],"\x1E\x00"); //a
  strcpy(KbdScancode[4][1],"\x9E\x00");
  strcpy(KbdScancode[5][0],"\x30\x00"); //b
  strcpy(KbdScancode[5][1],"\xB0\x00");
  strcpy(KbdScancode[6][0],"\x2E\x00"); //c
  strcpy(KbdScancode[6][1],"\xAE\x00");
  strcpy(KbdScancode[7][0],"\x20\x00"); //d
  strcpy(KbdScancode[7][1],"\xA0\x00");
  strcpy(KbdScancode[8][0],"\x12\x00"); //e
  strcpy(KbdScancode[8][1],"\x92\x00");
  strcpy(KbdScancode[9][0],"\x21\x00"); //f
  strcpy(KbdScancode[9][1],"\xA1\x00");
  strcpy(KbdScancode[10][0],"\x22\x00"); //g
  strcpy(KbdScancode[10][1],"\xA2\x00");
  strcpy(KbdScancode[11][0],"\x23\x00"); //h
  strcpy(KbdScancode[11][1],"\xA3\x00");
  strcpy(KbdScancode[12][0],"\x17\x00"); //i
  strcpy(KbdScancode[12][1],"\x97\x00");
  strcpy(KbdScancode[13][0],"\x24\x00"); //j
  strcpy(KbdScancode[13][1],"\xA4\x00");
  strcpy(KbdScancode[14][0],"\x25\x00"); //k
  strcpy(KbdScancode[14][1],"\xA5\x00"); 
  strcpy(KbdScancode[15][0],"\x26\x00"); //l
  strcpy(KbdScancode[15][1],"\xA6\x00");
  strcpy(KbdScancode[16][0],"\x32\x00"); //m
  strcpy(KbdScancode[16][1],"\xB2\x00");
  strcpy(KbdScancode[17][0],"\x31\x00"); //n
  strcpy(KbdScancode[17][1],"\xB1\x00");
  strcpy(KbdScancode[18][0],"\x18\x00"); //o
  strcpy(KbdScancode[18][1],"\x98\x00");
  strcpy(KbdScancode[19][0],"\x19\x00"); //p
  strcpy(KbdScancode[19][1],"\x99\x00");
  strcpy(KbdScancode[20][0],"\x10\x00"); //q
  strcpy(KbdScancode[20][1],"\x90\x00");
  strcpy(KbdScancode[21][0],"\x13\x00"); //r
  strcpy(KbdScancode[21][1],"\x93\x00");
  strcpy(KbdScancode[22][0],"\x1F\x00"); //s
  strcpy(KbdScancode[22][1],"\x9F\x00");
  strcpy(KbdScancode[23][0],"\x14\x00"); //t
  strcpy(KbdScancode[23][1],"\x94\x00");
  strcpy(KbdScancode[24][0],"\x16\x00"); //u
  strcpy(KbdScancode[24][1],"\x96\x00");
  strcpy(KbdScancode[25][0],"\x2F\x00"); //v
  strcpy(KbdScancode[25][1],"\xAF\x00");
  strcpy(KbdScancode[26][0],"\x11\x00"); //w
  strcpy(KbdScancode[26][1],"\x91\x00");
  strcpy(KbdScancode[27][0],"\x2D\x00"); //x
  strcpy(KbdScancode[27][1],"\xAD\x00");
  strcpy(KbdScancode[28][0],"\x15\x00"); //y
  strcpy(KbdScancode[28][1],"\x95\x00");
  strcpy(KbdScancode[29][0],"\x2C\x00"); //z
  strcpy(KbdScancode[29][1],"\xAC\x00");
  strcpy(KbdScancode[30][0],"\x02\x00"); //1
  strcpy(KbdScancode[30][1],"\x82\x00");
  strcpy(KbdScancode[31][0],"\x03\x00"); //2
  strcpy(KbdScancode[31][1],"\x83\x00");
  strcpy(KbdScancode[32][0],"\x04\x00"); //3
  strcpy(KbdScancode[32][1],"\x84\x00");
  strcpy(KbdScancode[33][0],"\x05\x00"); //4
  strcpy(KbdScancode[33][1],"\x85\x00");
  strcpy(KbdScancode[34][0],"\x06\x00"); //5
  strcpy(KbdScancode[34][1],"\x86\x00");
  strcpy(KbdScancode[35][0],"\x07\x00"); //6
  strcpy(KbdScancode[35][1],"\x87\x00");
  strcpy(KbdScancode[36][0],"\x08\x00"); //7
  strcpy(KbdScancode[36][1],"\x88\x00");
  strcpy(KbdScancode[37][0],"\x09\x00"); //8
  strcpy(KbdScancode[37][1],"\x89\x00");
  strcpy(KbdScancode[38][0],"\x0A\x00"); //9
  strcpy(KbdScancode[38][1],"\x8A\x00");
  strcpy(KbdScancode[39][0],"\x0B\x00"); //0
  strcpy(KbdScancode[39][1],"\x8B\x00");
  strcpy(KbdScancode[40][0],"\x1C\x00"); //Enter
  strcpy(KbdScancode[40][1],"\x9C\x00");
  strcpy(KbdScancode[41][0],"\x01\x00"); //Esc
  strcpy(KbdScancode[41][1],"\x81\x00");
  strcpy(KbdScancode[42][0],"\x0E\x00"); //Backspace
  strcpy(KbdScancode[42][1],"\x8E\x00");
  strcpy(KbdScancode[43][0],"\x0F\x00"); //Tab
  strcpy(KbdScancode[43][1],"\x8F\x00");
  strcpy(KbdScancode[44][0],"\x39\x00"); //Space
  strcpy(KbdScancode[44][1],"\xB9\x00");
  strcpy(KbdScancode[45][0],"\x0C\x00"); //Minus
  strcpy(KbdScancode[45][1],"\x8C\x00");
  strcpy(KbdScancode[46][0],"\x0D\x00"); //Equal
  strcpy(KbdScancode[46][1],"\x8D\x00");
  strcpy(KbdScancode[47][0],"\x1A\x00"); //Left brace
  strcpy(KbdScancode[47][1],"\x9A\x00");
  strcpy(KbdScancode[48][0],"\x1B\x00"); //right brace
  strcpy(KbdScancode[48][1],"\x9B\x00");
  strcpy(KbdScancode[49][0],"\x2B\x00"); //Backslash
  strcpy(KbdScancode[49][1],"\xAB\x00");
  strcpy(KbdScancode[50][0],"\x2A\x00"); //Hash+Tilde for Non-US
  strcpy(KbdScancode[50][1],"\xAA\x00");
  strcpy(KbdScancode[51][0],"\x27\x00"); //Semicolon
  strcpy(KbdScancode[51][1],"\xA7\x00");
  strcpy(KbdScancode[52][0],"\x28\x00"); //Apostrophe
  strcpy(KbdScancode[52][1],"\xA8\x00");
  strcpy(KbdScancode[53][0],"\x29\x00"); //Grave and Tilde
  strcpy(KbdScancode[53][1],"\xA9\x00");
  strcpy(KbdScancode[54][0],"\x33\x00"); //Comma
  strcpy(KbdScancode[54][1],"\xB3\x00");
  strcpy(KbdScancode[55][0],"\x34\x00"); //Dot
  strcpy(KbdScancode[55][1],"\xB4\x00");
  strcpy(KbdScancode[56][0],"\x35\x00"); //Slash
  strcpy(KbdScancode[56][1],"\xB5\x00");
  strcpy(KbdScancode[57][0],"\x3A\x00"); //Capslock
  strcpy(KbdScancode[57][1],"\xBA\x00");
  strcpy(KbdScancode[58][0],"\x3B\x00"); //F1
  strcpy(KbdScancode[58][1],"\xBB\x00");
  strcpy(KbdScancode[59][0],"\x3C\x00"); //F2
  strcpy(KbdScancode[59][1],"\xBC\x00");
  strcpy(KbdScancode[60][0],"\x3D\x00"); //F3
  strcpy(KbdScancode[60][1],"\xBD\x00");
  strcpy(KbdScancode[61][0],"\x3E\x00"); //F4
  strcpy(KbdScancode[61][1],"\xBE\x00");
  strcpy(KbdScancode[62][0],"\x3F\x00"); //F5
  strcpy(KbdScancode[62][1],"\xBF\x00");
  strcpy(KbdScancode[63][0],"\x40\x00"); //F6
  strcpy(KbdScancode[63][1],"\xC0\x00");
  strcpy(KbdScancode[64][0],"\x41\x00"); //F7
  strcpy(KbdScancode[64][1],"\xC1\x00");
  strcpy(KbdScancode[65][0],"\x42\x00"); //F8
  strcpy(KbdScancode[65][1],"\xC2\x00");
  strcpy(KbdScancode[66][0],"\x43\x00"); //F9
  strcpy(KbdScancode[66][1],"\xC3\x00");
  strcpy(KbdScancode[67][0],"\x44\x00"); //F10
  strcpy(KbdScancode[67][1],"\xC4\x00");
  strcpy(KbdScancode[68][0],"\x00"); //F11
  strcpy(KbdScancode[68][1],"\x00");
  strcpy(KbdScancode[69][0],"\x00"); //F12
  strcpy(KbdScancode[69][1],"\x00");
  strcpy(KbdScancode[70][0],"\x37\x00"); //SysReq/PrintScreen
  strcpy(KbdScancode[70][1],"\xB7\x00");
  strcpy(KbdScancode[71][0],"\x46\x00"); //ScrollLock
  strcpy(KbdScancode[71][1],"\xC6\x00");
  strcpy(KbdScancode[72][0],"\x00"); //Pause/Break - XT KbdScancode unknown
  strcpy(KbdScancode[72][1],"\x00");
  strcpy(KbdScancode[73][0],"\xE0\x52\x00"); //Insert
  strcpy(KbdScancode[73][1],"\xE0\xD2\x00");
  strcpy(KbdScancode[74][0],"\xE0\x47\x00"); //Home
  strcpy(KbdScancode[74][1],"\xE0\xC7\x00");
  strcpy(KbdScancode[75][0],"\xE0\x49\x00"); //PgUp
  strcpy(KbdScancode[75][1],"\xE0\xC9\x00");
  strcpy(KbdScancode[76][0],"\xE0\x53\x00"); //Delete
  strcpy(KbdScancode[76][1],"\xE0\xD3\x00");
  strcpy(KbdScancode[77][0],"\xE0\x4F\x00"); //End
  strcpy(KbdScancode[77][1],"\xE0\xCD\x00");
  strcpy(KbdScancode[78][0],"\xE0\x51\x00"); //PgDn
  strcpy(KbdScancode[78][1],"\xE0\xD1\x00");
  strcpy(KbdScancode[79][0],"\xE0\x4D\x00"); //Right
  strcpy(KbdScancode[79][1],"\xE0\xCD\x00");
  strcpy(KbdScancode[80][0],"\xE0\x4B\x00"); //Left
  strcpy(KbdScancode[80][1],"\xE0\xCB\x00");
  strcpy(KbdScancode[81][0],"\xE0\x50\x00"); //Down
  strcpy(KbdScancode[81][1],"\xE0\xD0\x00");
  strcpy(KbdScancode[82][0],"\xE0\x48\x00"); //Up
  strcpy(KbdScancode[82][1],"\xE0\xC8\x00");
  strcpy(KbdScancode[83][0],"\x45\x00"); //Numlock
  strcpy(KbdScancode[83][1],"\xC5\x00");
  strcpy(KbdScancode[84][0],"\x00"); //Keypad Slash
  strcpy(KbdScancode[84][1],"\x00");
  strcpy(KbdScancode[85][0],"\x00"); //Keypad Asterisk
  strcpy(KbdScancode[85][1],"\x00");
  strcpy(KbdScancode[86][0],"\x4A\x00"); //Keypad Minus
  strcpy(KbdScancode[86][1],"\xCA\x00");
  strcpy(KbdScancode[87][0],"\x4E\x00"); //Keypad Plus
  strcpy(KbdScancode[87][1],"\xCE\x00");
  strcpy(KbdScancode[88][0],"\x1C\x00"); //Keypad Enter
  strcpy(KbdScancode[88][1],"\x9C\x00");
  strcpy(KbdScancode[89][0],"\x4F\x00"); //Keypad 1/End
  strcpy(KbdScancode[89][1],"\xCF\x00");
  strcpy(KbdScancode[90][0],"\x50\x00"); //Keypad 2/Dn
  strcpy(KbdScancode[90][1],"\xD0\x00");
  strcpy(KbdScancode[91][0],"\x51\x00"); //Keypad 3/PgDn
  strcpy(KbdScancode[91][1],"\xD1\x00");
  strcpy(KbdScancode[92][0],"\x4B\x00"); //Keypad 4/Left
  strcpy(KbdScancode[92][1],"\xCB\x00");
  strcpy(KbdScancode[93][0],"\x4C\x00"); //Keypad 5
  strcpy(KbdScancode[93][1],"\xCC\x00");
  strcpy(KbdScancode[94][0],"\x4D\x00"); //Keypad 6/Right
  strcpy(KbdScancode[94][1],"\xCD\x00");
  strcpy(KbdScancode[95][0],"\x47\x00"); //Keypad 7/Home
  strcpy(KbdScancode[95][1],"\xC7\x00");
  strcpy(KbdScancode[96][0],"\x48\x00"); //Keypad 8/Up
  strcpy(KbdScancode[96][1],"\xC8\x00");
  strcpy(KbdScancode[97][0],"\x49\x00"); //Keypad 9/PgUp
  strcpy(KbdScancode[97][1],"\xC9\x00");
  strcpy(KbdScancode[98][0],"\x52\x00"); //Keypad 0/Insert
  strcpy(KbdScancode[98][1],"\xD2\x00");
  strcpy(KbdScancode[99][0],"\x53\x00"); //Keypad ./Delete 
  strcpy(KbdScancode[99][1],"\xD3\x00");
  strcpy(KbdScancode[100][0],"\x56\x00"); //INT 1 a.k.a. 102nd Key Backslash/Pipe Non-US
  strcpy(KbdScancode[100][1],"\xD6\x00"); 
  strcpy(KbdScancode[101][0],"\x00"); //Windows Menu
  strcpy(KbdScancode[101][1],"\x00"); 
  strcpy(KbdScancode[102][0],"\x1D\x00"); //LeftCtrl - From here, misusing of untypical KbdScancodes like F13 onwards for modifier keys starts
  strcpy(KbdScancode[102][1],"\x9D\x00"); 
  strcpy(KbdScancode[103][0],"\x2A\x00"); //LeftShift
  strcpy(KbdScancode[103][1],"\xAA\x00");
  strcpy(KbdScancode[104][0],"\x38\x00"); //LeftAlt
  strcpy(KbdScancode[104][1],"\xB8\x00");
  strcpy(KbdScancode[105][0],"\x00"); //LeftMeta
  strcpy(KbdScancode[105][1],"\x00");
  strcpy(KbdScancode[106][0],"\x1D\x00"); //RightCtrl
  strcpy(KbdScancode[106][1],"\x9D\x00");
  strcpy(KbdScancode[107][0],"\x36\x00"); //RightShift
  strcpy(KbdScancode[107][1],"\xB6\x00");
  strcpy(KbdScancode[108][0],"\x38\x00"); //RightAlt/AltGr
  strcpy(KbdScancode[108][1],"\xB8\x00");
  strcpy(KbdScancode[109][0],"\x00"); //RightMeta
  strcpy(KbdScancode[109][1],"\x00");
  strcpy(KbdScancode[110][0],"\x00"); //Reset Ack - Does not apply to this KbdScancode set
  strcpy(KbdScancode[110][1],"\x00");
  strcpy(KbdScancode[111][0],"\x00"); //Keyboard ID - Does not apply to this KbdScancode set
  strcpy(KbdScancode[111][1],"\x00");
  strcpy(KbdScancode[112][0],"\x00"); //Echo - Does not apply to this KbdScancode set
  strcpy(KbdScancode[112][1],"\x00");  
  strcpy(KbdScancode[113][0],"\x01"); //Current KbdScancode Set
  strcpy(KbdScancode[113][1],"\x01");
}

void initScancodeATSet2()
{
  strcpy(KbdScancode[0][0],"\x00"); //No Key
  strcpy(KbdScancode[0][1],"\x00");
  strcpy(KbdScancode[1][0],"\x00"); //Keyboard Error
  strcpy(KbdScancode[1][1],"\x00");
  strcpy(KbdScancode[2][0],"\x00"); //POST Fail
  strcpy(KbdScancode[2][1],"\x00");  
  strcpy(KbdScancode[3][0],"\x00"); //undefined error
  strcpy(KbdScancode[3][1],"\x00");
  strcpy(KbdScancode[4][0],"\x1C\x00"); //a
  strcpy(KbdScancode[4][1],"\xF0\x1C\x00");
  strcpy(KbdScancode[5][0],"\x32\x00"); //b
  strcpy(KbdScancode[5][1],"\xF0\x32\x00");
  strcpy(KbdScancode[6][0],"\x21\x00"); //c
  strcpy(KbdScancode[6][1],"\xF0\x21\x00");
  strcpy(KbdScancode[7][0],"\x23\x00"); //d
  strcpy(KbdScancode[7][1],"\xF0\x23\x00");
  strcpy(KbdScancode[8][0],"\x24\x00"); //e
  strcpy(KbdScancode[8][1],"\xF0\x24\x00");
  strcpy(KbdScancode[9][0],"\x2B\x00"); //f
  strcpy(KbdScancode[9][1],"\xF0\x2B\x00");
  strcpy(KbdScancode[10][0],"\x34\x00"); //g
  strcpy(KbdScancode[10][1],"\xF0\x34\x00");
  strcpy(KbdScancode[11][0],"\x33\x00"); //h
  strcpy(KbdScancode[11][1],"\xF0\x33\x00");
  strcpy(KbdScancode[12][0],"\x43\x00"); //i
  strcpy(KbdScancode[12][1],"\xF0\x43\x00");
  strcpy(KbdScancode[13][0],"\x3B\x00"); //j
  strcpy(KbdScancode[13][1],"\xF0\x3B\x00");
  strcpy(KbdScancode[14][0],"\x42\x00"); //k
  strcpy(KbdScancode[14][1],"\xF0\x42\x00"); 
  strcpy(KbdScancode[15][0],"\x4B\x00"); //l
  strcpy(KbdScancode[15][1],"\xF0\x4B\x00");
  strcpy(KbdScancode[16][0],"\x3A\x00"); //m
  strcpy(KbdScancode[16][1],"\xF0\x3A\x00");
  strcpy(KbdScancode[17][0],"\x31\x00"); //n
  strcpy(KbdScancode[17][1],"\xF0\x31\x00");
  strcpy(KbdScancode[18][0],"\x44\x00"); //o
  strcpy(KbdScancode[18][1],"\xF0\x44\x00");
  strcpy(KbdScancode[19][0],"\x4D\x00"); //p
  strcpy(KbdScancode[19][1],"\xF0\x4D\x00");
  strcpy(KbdScancode[20][0],"\x15\x00"); //q
  strcpy(KbdScancode[20][1],"\xF0\x15\x00");
  strcpy(KbdScancode[21][0],"\x2D\x00"); //r
  strcpy(KbdScancode[21][1],"\xF0\x2D\x00");
  strcpy(KbdScancode[22][0],"\x1B\x00"); //s
  strcpy(KbdScancode[22][1],"\xF0\x1B\x00");
  strcpy(KbdScancode[23][0],"\x2C\x00"); //t
  strcpy(KbdScancode[23][1],"\xF0\x2C\x00");
  strcpy(KbdScancode[24][0],"\x3C\x00"); //u
  strcpy(KbdScancode[24][1],"\xF0\x3C\x00");
  strcpy(KbdScancode[25][0],"\x2A\x00"); //v
  strcpy(KbdScancode[25][1],"\xF0\x2A\x00");
  strcpy(KbdScancode[26][0],"\x1D\x00"); //w
  strcpy(KbdScancode[26][1],"\xF0\x1D\x00");
  strcpy(KbdScancode[27][0],"\x22\x00"); //x
  strcpy(KbdScancode[27][1],"\xF0\x22\x00");
  strcpy(KbdScancode[28][0],"\x35\x00"); //y
  strcpy(KbdScancode[28][1],"\xF0\x35\x00");
  strcpy(KbdScancode[29][0],"\x1A\x00"); //z
  strcpy(KbdScancode[29][1],"\xF0\x1A\x00");
  strcpy(KbdScancode[30][0],"\x16\x00"); //1
  strcpy(KbdScancode[30][1],"\xF0\x16\x00");
  strcpy(KbdScancode[31][0],"\x1E\x00"); //2
  strcpy(KbdScancode[31][1],"\xF0\x1E\x00");
  strcpy(KbdScancode[32][0],"\x26\x00"); //3
  strcpy(KbdScancode[32][1],"\xF0\x26\x00");
  strcpy(KbdScancode[33][0],"\x25\x00"); //4
  strcpy(KbdScancode[33][1],"\xF0\x25\x00");
  strcpy(KbdScancode[34][0],"\x2E\x00"); //5
  strcpy(KbdScancode[34][1],"\xF0\x2E\x00");
  strcpy(KbdScancode[35][0],"\x36\x00"); //6
  strcpy(KbdScancode[35][1],"\xF0\x36\x00");
  strcpy(KbdScancode[36][0],"\x3D\x00"); //7
  strcpy(KbdScancode[36][1],"\xF0\x3D\x00");
  strcpy(KbdScancode[37][0],"\x3E\x00"); //8
  strcpy(KbdScancode[37][1],"\xF0\x3E\x00");
  strcpy(KbdScancode[38][0],"\x46\x00"); //9
  strcpy(KbdScancode[38][1],"\xF0\x46\x00");
  strcpy(KbdScancode[39][0],"\x45\x00"); //0
  strcpy(KbdScancode[39][1],"\xF0\x45\x00");
  strcpy(KbdScancode[40][0],"\x5A\x00"); //Enter
  strcpy(KbdScancode[40][1],"\xF0\x5A\x00");
  strcpy(KbdScancode[41][0],"\x76\x00"); //Esc
  strcpy(KbdScancode[41][1],"\xF0\x76\x00");
  strcpy(KbdScancode[42][0],"\x66\x00"); //Backspace
  strcpy(KbdScancode[42][1],"\xF0\x66\x00");
  strcpy(KbdScancode[43][0],"\x0D\x00"); //Tab
  strcpy(KbdScancode[43][1],"\xF0\x0D\x00");
  strcpy(KbdScancode[44][0],"\x29\x00"); //Space
  strcpy(KbdScancode[44][1],"\xF0\x29\x00");
  strcpy(KbdScancode[45][0],"\x4E\x00"); //Minus
  strcpy(KbdScancode[45][1],"\xF0\x4e\x00");
  strcpy(KbdScancode[46][0],"\x55\x00"); //Equal
  strcpy(KbdScancode[46][1],"\xF0\x55\x00");
  strcpy(KbdScancode[47][0],"\x54\x00"); //Left brace, German Ü
  strcpy(KbdScancode[47][1],"\xF0\x54\x00");
  strcpy(KbdScancode[48][0],"\x5B\x00"); //right brace, German +*~
  strcpy(KbdScancode[48][1],"\xF0\x5B\x00");
  strcpy(KbdScancode[49][0],"\x5D\x00"); //Backslash
  strcpy(KbdScancode[49][1],"\xF0\x5D\x00");
  strcpy(KbdScancode[50][0],"\x5D\x00"); //INT 2 - Hash+Tilde for UK, Hash and Apostrophe for German
  strcpy(KbdScancode[50][1],"\xF0\x5D\x00");
  strcpy(KbdScancode[51][0],"\x4C\x00"); //Semicolon
  strcpy(KbdScancode[51][1],"\xF0\x4C\x00");
  strcpy(KbdScancode[52][0],"\x52\x00"); //Apostrophe, German Ä
  strcpy(KbdScancode[52][1],"\xF0\x52\x00");
  strcpy(KbdScancode[53][0],"\x0E\x00"); //Grave and Tilde
  strcpy(KbdScancode[53][1],"\xF0\x0E\x00");
  strcpy(KbdScancode[54][0],"\x41\x00"); //Comma
  strcpy(KbdScancode[54][1],"\xF0\x41\x00");
  strcpy(KbdScancode[55][0],"\x49\x00"); //Dot
  strcpy(KbdScancode[55][1],"\xF0\x49\x00");
  strcpy(KbdScancode[56][0],"\x4A\x00"); //Slash
  strcpy(KbdScancode[56][1],"\xF0\x4A\x00");
  strcpy(KbdScancode[57][0],"\x58\x00"); //Capslock
  strcpy(KbdScancode[57][1],"\xF0\x58\x00");
  strcpy(KbdScancode[58][0],"\x05\x00"); //F1
  strcpy(KbdScancode[58][1],"\xF0\x05\x00");
  strcpy(KbdScancode[59][0],"\x06\x00"); //F2
  strcpy(KbdScancode[59][1],"\xF0\x06\x00");
  strcpy(KbdScancode[60][0],"\x04\x00"); //F3
  strcpy(KbdScancode[60][1],"\xF0\x04\x00");
  strcpy(KbdScancode[61][0],"\x0C\x00"); //F4
  strcpy(KbdScancode[61][1],"\xF0\x0C\x00");
  strcpy(KbdScancode[62][0],"\x03\x00"); //F5
  strcpy(KbdScancode[62][1],"\xF0\x03\x00");
  strcpy(KbdScancode[63][0],"\x0B\x00"); //F6
  strcpy(KbdScancode[63][1],"\xF0\x0B\x00");
  strcpy(KbdScancode[64][0],"\x83\x00"); //F7
  strcpy(KbdScancode[64][1],"\xF0\x83\x00");
  strcpy(KbdScancode[65][0],"\x0A\x00"); //F8
  strcpy(KbdScancode[65][1],"\xF0\x0A\x00");
  strcpy(KbdScancode[66][0],"\x01\x00"); //F9
  strcpy(KbdScancode[66][1],"\xF0\x01\x00");
  strcpy(KbdScancode[67][0],"\x09\x00"); //F10
  strcpy(KbdScancode[67][1],"\xF0\x09\x00");
  strcpy(KbdScancode[68][0],"\x78\x00"); //F11
  strcpy(KbdScancode[68][1],"\xF0\x78\x00");
  strcpy(KbdScancode[69][0],"\x07\x00"); //F12
  strcpy(KbdScancode[69][1],"\xF0\x07\x00");
  strcpy(KbdScancode[70][0],"\x00"); //SysReq/PrintScreen scancode extraordinary long, covered in KbdWriteAT routine to keep the array smaller
  strcpy(KbdScancode[70][1],"\x00");
  strcpy(KbdScancode[71][0],"\x7E\x00"); //ScrollLock
  strcpy(KbdScancode[71][1],"\xF0\x7E\x00");
  strcpy(KbdScancode[72][0],"\x00"); //Pause/Break scancode extraordinary long, covered in KbdWriteAT routine to keep the array smaller
  strcpy(KbdScancode[72][1],"\x00");
  strcpy(KbdScancode[73][0],"\xE0\x70\x00"); //Insert
  strcpy(KbdScancode[73][1],"\xE0\xF0\x70\x00");
  strcpy(KbdScancode[74][0],"\xE0\x6C\x00"); //Home
  strcpy(KbdScancode[74][1],"\xE0\xF0\x6C\x00");
  strcpy(KbdScancode[75][0],"\xE0\x7D\x00"); //PgUp
  strcpy(KbdScancode[75][1],"\xE0\xF0\x7D\x00");
  strcpy(KbdScancode[76][0],"\xE0\x71\x00"); //Delete
  strcpy(KbdScancode[76][1],"\xE0\xF0\x71\x00");
  strcpy(KbdScancode[77][0],"\xE0\x69\x00"); //End
  strcpy(KbdScancode[77][1],"\xE0\xF0\x69\x00");
  strcpy(KbdScancode[78][0],"\xE0\x7A\x00"); //PgDn
  strcpy(KbdScancode[78][1],"\xE0\xF0\x7A\x00");
  strcpy(KbdScancode[79][0],"\xE0\x74\x00"); //Right
  strcpy(KbdScancode[79][1],"\xE0\xF0\x74\x00");
  strcpy(KbdScancode[80][0],"\xE0\x6B\x00"); //Left
  strcpy(KbdScancode[80][1],"\xE0\xF0\x6B\x00");
  strcpy(KbdScancode[81][0],"\xE0\x72\x00"); //Down
  strcpy(KbdScancode[81][1],"\xE0\xF0\x72\x00");
  strcpy(KbdScancode[82][0],"\xE0\x75\x00"); //Up
  strcpy(KbdScancode[82][1],"\xE0\xF0\x75\x00");
  strcpy(KbdScancode[83][0],"\x77\x00"); //Numlock
  strcpy(KbdScancode[83][1],"\xF0\x77\x00");
  strcpy(KbdScancode[84][0],"\xE0\x4A\x00"); //Keypad Slash
  strcpy(KbdScancode[84][1],"\xE0\xF0\x4A\x00");
  strcpy(KbdScancode[85][0],"\x7C\x00"); //Keypad Asterisk
  strcpy(KbdScancode[85][1],"\xF0\x7C\x00");
  strcpy(KbdScancode[86][0],"\x7B\x00"); //Keypad Minus
  strcpy(KbdScancode[86][1],"\xF0\x7B\x00");
  strcpy(KbdScancode[87][0],"\x79\x00"); //Keypad Plus
  strcpy(KbdScancode[87][1],"\xF0\x79\x00");
  strcpy(KbdScancode[88][0],"\xE0\x5A\x00"); //Keypad Enter
  strcpy(KbdScancode[88][1],"\xE0\xF0\x5A\x00");
  strcpy(KbdScancode[89][0],"\x69\x00"); //Keypad 1/End
  strcpy(KbdScancode[89][1],"\xF0\x69\x00");
  strcpy(KbdScancode[90][0],"\x72\x00"); //Keypad 2/Dn
  strcpy(KbdScancode[90][1],"\xF0\x72\x00");
  strcpy(KbdScancode[91][0],"\x7A\x00"); //Keypad 3/PgDn
  strcpy(KbdScancode[91][1],"\xF0\x7A\x00");
  strcpy(KbdScancode[92][0],"\x6B\x00"); //Keypad 4/Left
  strcpy(KbdScancode[92][1],"\xF0\x6B\x00");
  strcpy(KbdScancode[93][0],"\x73\x00"); //Keypad 5
  strcpy(KbdScancode[93][1],"\xF0\x73\x00");
  strcpy(KbdScancode[94][0],"\x74\x00"); //Keypad 6/Right
  strcpy(KbdScancode[94][1],"\xF0\x74\x00");
  strcpy(KbdScancode[95][0],"\x6C\x00"); //Keypad 7/Home
  strcpy(KbdScancode[95][1],"\xF0\x6C\x00");
  strcpy(KbdScancode[96][0],"\x75\x00"); //Keypad 8/Up
  strcpy(KbdScancode[96][1],"\xF0\x75\x00");
  strcpy(KbdScancode[97][0],"\x7D\x00"); //Keypad 9/PgUp
  strcpy(KbdScancode[97][1],"\xF0\x7D\x00");
  strcpy(KbdScancode[98][0],"\x70\x00"); //Keypad 0/Insert
  strcpy(KbdScancode[98][1],"\xF0\x70\x00");
  strcpy(KbdScancode[99][0],"\x71\x00"); //Keypad ./Delete 
  strcpy(KbdScancode[99][1],"\xF0\x71\x00");
  strcpy(KbdScancode[100][0],"\x61\x00"); //INT 1 a.k.a. 102nd Key Backslash/Pipe Non-US, German <>|
  strcpy(KbdScancode[100][1],"\xF0\x61\x00"); 
  strcpy(KbdScancode[101][0],"\xE0\x2F\x00"); //Windows Menu
  strcpy(KbdScancode[101][1],"\xE0\xF0\x2F\x00"); 
  strcpy(KbdScancode[102][0],"\x14\x00"); //LeftCtrl - From here, misusing of untypical KbdScancodes like F13 onwards for modifier keys starts
  strcpy(KbdScancode[102][1],"\xF0\x14\x00"); 
  strcpy(KbdScancode[103][0],"\x12\x00"); //LeftShift
  strcpy(KbdScancode[103][1],"\xF0\x12\x00");
  strcpy(KbdScancode[104][0],"\x11\x00"); //LeftAlt
  strcpy(KbdScancode[104][1],"\xF0\x11\x00");
  strcpy(KbdScancode[105][0],"\xE0\x1F\x00"); //LeftMeta
  strcpy(KbdScancode[105][1],"\xE0\xF0\x1F\x00");
  strcpy(KbdScancode[106][0],"\xE0\x14\x00"); //RightCtrl
  strcpy(KbdScancode[106][1],"\xE0\xF0\x14\x00");
  strcpy(KbdScancode[107][0],"\x59\x00"); //RightShift
  strcpy(KbdScancode[107][1],"\xF0\x59\x00");
  strcpy(KbdScancode[108][0],"\xE0\x11\x00"); //RightAlt/AltGr
  strcpy(KbdScancode[108][1],"\xE0\xF0\x11\x00");
  strcpy(KbdScancode[109][0],"\xE0\x27\x00"); //RightMeta
  strcpy(KbdScancode[109][1],"\xE0\xF0\x27\x00");
  strcpy(KbdScancode[110][0],"\xFA\x00"); //Reset Ack
  strcpy(KbdScancode[110][1],"\xAA\x00");
  strcpy(KbdScancode[111][0],"\xFA\xAB\x83\x00"); //Keyboard ID
  strcpy(KbdScancode[111][1],"\xFA\xAB\x83\x00");
  strcpy(KbdScancode[112][0],"\xEE\x00"); //Echo
  strcpy(KbdScancode[112][1],"\xEE\x00");
  strcpy(KbdScancode[113][0],"\x02\x00"); //Current KbdScancode Set - Pre-Initialized as 2
  strcpy(KbdScancode[113][1],"\x02\x00");
}

void initScancodeATSet3() //Some keys still to be checked
{
  strcpy(KbdScancode[0][0],"\x00"); //No Key
  strcpy(KbdScancode[0][1],"\x00");
  strcpy(KbdScancode[1][0],"\x00"); //Keyboard Error
  strcpy(KbdScancode[1][1],"\x00");
  strcpy(KbdScancode[2][0],"\x00"); //POST Fail
  strcpy(KbdScancode[2][1],"\x00");  
  strcpy(KbdScancode[3][0],"\x00"); //undefined error
  strcpy(KbdScancode[3][1],"\x00");
  strcpy(KbdScancode[4][0],"\x1C\x00"); //a
  strcpy(KbdScancode[4][1],"\xF0\x1C\x00");
  strcpy(KbdScancode[5][0],"\x32\x00"); //b
  strcpy(KbdScancode[5][1],"\xF0\x32\x00");
  strcpy(KbdScancode[6][0],"\x21\x00"); //c
  strcpy(KbdScancode[6][1],"\xF0\x21\x00");
  strcpy(KbdScancode[7][0],"\x23\x00"); //d
  strcpy(KbdScancode[7][1],"\xF0\x23\x00");
  strcpy(KbdScancode[8][0],"\x24\x00"); //e
  strcpy(KbdScancode[8][1],"\xF0\x24\x00");
  strcpy(KbdScancode[9][0],"\x2B\x00"); //f
  strcpy(KbdScancode[9][1],"\xF0\x2B\x00");
  strcpy(KbdScancode[10][0],"\x34\x00"); //g
  strcpy(KbdScancode[10][1],"\xF0\x34\x00");
  strcpy(KbdScancode[11][0],"\x33\x00"); //h
  strcpy(KbdScancode[11][1],"\xF0\x33\x00");
  strcpy(KbdScancode[12][0],"\x43\x00"); //i
  strcpy(KbdScancode[12][1],"\xF0\x43\x00");
  strcpy(KbdScancode[13][0],"\x3B\x00"); //j
  strcpy(KbdScancode[13][1],"\xF0\x3B\x00");
  strcpy(KbdScancode[14][0],"\x42\x00"); //k
  strcpy(KbdScancode[14][1],"\xF0\x42\x00"); 
  strcpy(KbdScancode[15][0],"\x4B\x00"); //l
  strcpy(KbdScancode[15][1],"\xF0\x4B\x00");
  strcpy(KbdScancode[16][0],"\x3A\x00"); //m
  strcpy(KbdScancode[16][1],"\xF0\x3A\x00");
  strcpy(KbdScancode[17][0],"\x31\x00"); //n
  strcpy(KbdScancode[17][1],"\xF0\x31\x00");
  strcpy(KbdScancode[18][0],"\x44\x00"); //o
  strcpy(KbdScancode[18][1],"\xF0\x44\x00");
  strcpy(KbdScancode[19][0],"\x4D\x00"); //p
  strcpy(KbdScancode[19][1],"\xF0\x4D\x00");
  strcpy(KbdScancode[20][0],"\x15\x00"); //q
  strcpy(KbdScancode[20][1],"\xF0\x15\x00");
  strcpy(KbdScancode[21][0],"\x2D\x00"); //r
  strcpy(KbdScancode[21][1],"\xF0\x2D\x00");
  strcpy(KbdScancode[22][0],"\x1B\x00"); //s
  strcpy(KbdScancode[22][1],"\xF0\x1B\x00");
  strcpy(KbdScancode[23][0],"\x2C\x00"); //t
  strcpy(KbdScancode[23][1],"\xF0\x2C\x00");
  strcpy(KbdScancode[24][0],"\x3C\x00"); //u
  strcpy(KbdScancode[24][1],"\xF0\x3C\x00");
  strcpy(KbdScancode[25][0],"\x2A\x00"); //v
  strcpy(KbdScancode[25][1],"\xF0\x2A\x00");
  strcpy(KbdScancode[26][0],"\x1D\x00"); //w
  strcpy(KbdScancode[26][1],"\xF0\x1D\x00");
  strcpy(KbdScancode[27][0],"\x22\x00"); //x
  strcpy(KbdScancode[27][1],"\xF0\x22\x00");
  strcpy(KbdScancode[28][0],"\x35\x00"); //y
  strcpy(KbdScancode[28][1],"\xF0\x35\x00");
  strcpy(KbdScancode[29][0],"\x1A\x00"); //z
  strcpy(KbdScancode[29][1],"\xF0\x1A\x00");
  strcpy(KbdScancode[30][0],"\x16\x00"); //1
  strcpy(KbdScancode[30][1],"\xF0\x16\x00");
  strcpy(KbdScancode[31][0],"\x1E\x00"); //2
  strcpy(KbdScancode[31][1],"\xF0\x1E\x00");
  strcpy(KbdScancode[32][0],"\x26\x00"); //3
  strcpy(KbdScancode[32][1],"\xF0\x26\x00");
  strcpy(KbdScancode[33][0],"\x25\x00"); //4
  strcpy(KbdScancode[33][1],"\xF0\x25\x00");
  strcpy(KbdScancode[34][0],"\x2E\x00"); //5
  strcpy(KbdScancode[34][1],"\xF0\x2E\x00");
  strcpy(KbdScancode[35][0],"\x36\x00"); //6
  strcpy(KbdScancode[35][1],"\xF0\x36\x00");
  strcpy(KbdScancode[36][0],"\x3D\x00"); //7
  strcpy(KbdScancode[36][1],"\xF0\x3D\x00");
  strcpy(KbdScancode[37][0],"\x3E\x00"); //8
  strcpy(KbdScancode[37][1],"\xF0\x3E\x00");
  strcpy(KbdScancode[38][0],"\x46\x00"); //9
  strcpy(KbdScancode[38][1],"\xF0\x46\x00");
  strcpy(KbdScancode[39][0],"\x45\x00"); //0
  strcpy(KbdScancode[39][1],"\xF0\x45\x00");
  strcpy(KbdScancode[40][0],"\x5A\x00"); //Enter
  strcpy(KbdScancode[40][1],"\xF0\x5A\x00");
  strcpy(KbdScancode[41][0],"\x08\x00"); //Esc
  strcpy(KbdScancode[41][1],"\xF0\x08\x00");
  strcpy(KbdScancode[42][0],"\x66\x00"); //Backspace
  strcpy(KbdScancode[42][1],"\xF0\x66\x00");
  strcpy(KbdScancode[43][0],"\x0D\x00"); //Tab
  strcpy(KbdScancode[43][1],"\xF0\x0D\x00");
  strcpy(KbdScancode[44][0],"\x29\x00"); //Space
  strcpy(KbdScancode[44][1],"\xF0\x29\x00");
  strcpy(KbdScancode[45][0],"\x4E\x00"); //Minus
  strcpy(KbdScancode[45][1],"\xF0\x4e\x00");
  strcpy(KbdScancode[46][0],"\x55\x00"); //Equal
  strcpy(KbdScancode[46][1],"\xF0\x55\x00");
  strcpy(KbdScancode[47][0],"\x54\x00"); //Left brace, German Ü
  strcpy(KbdScancode[47][1],"\xF0\x54\x00");
  strcpy(KbdScancode[48][0],"\x5B\x00"); //right brace, German +*~
  strcpy(KbdScancode[48][1],"\xF0\x5B\x00");
  strcpy(KbdScancode[49][0],"\x5C\x00"); //Backslash
  strcpy(KbdScancode[49][1],"\xF0\x5C\x00");
  strcpy(KbdScancode[50][0],"\x5D\x00"); //INT 2 - Hash+Tilde for UK, Hash and Apostrophe for German (To be checked)
  strcpy(KbdScancode[50][1],"\xF0\x5D\x00");
  strcpy(KbdScancode[51][0],"\x4C\x00"); //Semicolon
  strcpy(KbdScancode[51][1],"\xF0\x4C\x00");
  strcpy(KbdScancode[52][0],"\x52\x00"); //Apostrophe, German Ä
  strcpy(KbdScancode[52][1],"\xF0\x52\x00");
  strcpy(KbdScancode[53][0],"\x0E\x00"); //Grave and Tilde
  strcpy(KbdScancode[53][1],"\xF0\x0E\x00");
  strcpy(KbdScancode[54][0],"\x41\x00"); //Comma
  strcpy(KbdScancode[54][1],"\xF0\x41\x00");
  strcpy(KbdScancode[55][0],"\x49\x00"); //Dot
  strcpy(KbdScancode[55][1],"\xF0\x49\x00");
  strcpy(KbdScancode[56][0],"\x4A\x00"); //Slash
  strcpy(KbdScancode[56][1],"\xF0\x4A\x00");
  strcpy(KbdScancode[57][0],"\x14\x00"); //Capslock
  strcpy(KbdScancode[57][1],"\xF0\x14\x00");
  strcpy(KbdScancode[58][0],"\x07\x00"); //F1
  strcpy(KbdScancode[58][1],"\xF0\x07\x00");
  strcpy(KbdScancode[59][0],"\x0F\x00"); //F2
  strcpy(KbdScancode[59][1],"\xF0\x0F\x00");
  strcpy(KbdScancode[60][0],"\x17\x00"); //F3
  strcpy(KbdScancode[60][1],"\xF0\x17\x00");
  strcpy(KbdScancode[61][0],"\x1F\x00"); //F4
  strcpy(KbdScancode[61][1],"\xF0\x1F\x00");
  strcpy(KbdScancode[62][0],"\x27\x00"); //F5
  strcpy(KbdScancode[62][1],"\xF0\x27\x00");
  strcpy(KbdScancode[63][0],"\x2F\x00"); //F6
  strcpy(KbdScancode[63][1],"\xF0\x2F\x00");
  strcpy(KbdScancode[64][0],"\x37\x00"); //F7
  strcpy(KbdScancode[64][1],"\xF0\x37\x00");
  strcpy(KbdScancode[65][0],"\x3F\x00"); //F8
  strcpy(KbdScancode[65][1],"\xF0\x3F\x00");
  strcpy(KbdScancode[66][0],"\x47\x00"); //F9
  strcpy(KbdScancode[66][1],"\xF0\x47\x00");
  strcpy(KbdScancode[67][0],"\x4F\x00"); //F10
  strcpy(KbdScancode[67][1],"\xF0\x4F\x00");
  strcpy(KbdScancode[68][0],"\x56\x00"); //F11
  strcpy(KbdScancode[68][1],"\xF0\x56\x00");
  strcpy(KbdScancode[69][0],"\x5F\x00"); //F12
  strcpy(KbdScancode[69][1],"\xF0\x5F\x00");
  strcpy(KbdScancode[70][0],"\x57\x00"); //SysReq/PrintScreen scancode extraordinary long, covered in KbdWriteAT routine to keep the array smaller
  strcpy(KbdScancode[70][1],"\xF0\x57\x00");
  strcpy(KbdScancode[71][0],"\x5F\x00"); //ScrollLock
  strcpy(KbdScancode[71][1],"\xF0\x5F\x00");
  strcpy(KbdScancode[72][0],"\x62\x00"); //Pause/Break scancode extraordinary long, covered in KbdWriteAT routine to keep the array smaller
  strcpy(KbdScancode[72][1],"\xF0\x62\x00");
  strcpy(KbdScancode[73][0],"\x67\x00"); //Insert
  strcpy(KbdScancode[73][1],"\xF0\x67\x00");
  strcpy(KbdScancode[74][0],"\x6E\x00"); //Home
  strcpy(KbdScancode[74][1],"\xF0\x6E\x00");
  strcpy(KbdScancode[75][0],"\x6F\x00"); //PgUp
  strcpy(KbdScancode[75][1],"\xF0\x6F\x00");
  strcpy(KbdScancode[76][0],"\x64\x00"); //Delete
  strcpy(KbdScancode[76][1],"\xF0\x64\x00");
  strcpy(KbdScancode[77][0],"\x65\x00"); //End
  strcpy(KbdScancode[77][1],"\xF0\x65\x00");
  strcpy(KbdScancode[78][0],"\x6D\x00"); //PgDn
  strcpy(KbdScancode[78][1],"\xF0\x6D\x00");
  strcpy(KbdScancode[79][0],"\x6A\x00"); //Right
  strcpy(KbdScancode[79][1],"\xF0\x6A\x00");
  strcpy(KbdScancode[80][0],"\x61\x00"); //Left
  strcpy(KbdScancode[80][1],"\xF0\x61\x00");
  strcpy(KbdScancode[81][0],"\x60\x00"); //Down
  strcpy(KbdScancode[81][1],"\xF0\x60\x00");
  strcpy(KbdScancode[82][0],"\x63\x00"); //Up
  strcpy(KbdScancode[82][1],"\xF0\x63\x00");
  strcpy(KbdScancode[83][0],"\x76\x00"); //Numlock
  strcpy(KbdScancode[83][1],"\xF0\x76\x00");
  strcpy(KbdScancode[84][0],"\x4A\x00"); //Keypad Slash
  strcpy(KbdScancode[84][1],"\xF0\x4A\x00");
  strcpy(KbdScancode[85][0],"\x7E\x00"); //Keypad Asterisk
  strcpy(KbdScancode[85][1],"\xF0\x7E\x00");
  strcpy(KbdScancode[86][0],"\x4E\x00"); //Keypad Minus
  strcpy(KbdScancode[86][1],"\xF0\x4E\x00");
  strcpy(KbdScancode[87][0],"\x7C\x00"); //Keypad Plus
  strcpy(KbdScancode[87][1],"\xF0\x7C\x00");
  strcpy(KbdScancode[88][0],"\x79\x00"); //Keypad Enter
  strcpy(KbdScancode[88][1],"\xF0\x79\x00");
  strcpy(KbdScancode[89][0],"\x69\x00"); //Keypad 1/End
  strcpy(KbdScancode[89][1],"\xF0\x69\x00");
  strcpy(KbdScancode[90][0],"\x72\x00"); //Keypad 2/Dn
  strcpy(KbdScancode[90][1],"\xF0\x72\x00");
  strcpy(KbdScancode[91][0],"\x7A\x00"); //Keypad 3/PgDn
  strcpy(KbdScancode[91][1],"\xF0\x7A\x00");
  strcpy(KbdScancode[92][0],"\x6B\x00"); //Keypad 4/Left
  strcpy(KbdScancode[92][1],"\xF0\x6B\x00");
  strcpy(KbdScancode[93][0],"\x73\x00"); //Keypad 5
  strcpy(KbdScancode[93][1],"\xF0\x73\x00");
  strcpy(KbdScancode[94][0],"\x74\x00"); //Keypad 6/Right
  strcpy(KbdScancode[94][1],"\xF0\x74\x00");
  strcpy(KbdScancode[95][0],"\x6C\x00"); //Keypad 7/Home
  strcpy(KbdScancode[95][1],"\xF0\x6C\x00");
  strcpy(KbdScancode[96][0],"\x75\x00"); //Keypad 8/Up
  strcpy(KbdScancode[96][1],"\xF0\x75\x00");
  strcpy(KbdScancode[97][0],"\x7D\x00"); //Keypad 9/PgUp
  strcpy(KbdScancode[97][1],"\xF0\x7D\x00");
  strcpy(KbdScancode[98][0],"\x70\x00"); //Keypad 0/Insert
  strcpy(KbdScancode[98][1],"\xF0\x70\x00");
  strcpy(KbdScancode[99][0],"\x71\x00"); //Keypad ./Delete 
  strcpy(KbdScancode[99][1],"\xF0\x71\x00");
  strcpy(KbdScancode[100][0],"\x61\x00"); //INT 1 a.k.a. 102nd Key Backslash/Pipe Non-US, German <>| Wrong to be checked
  strcpy(KbdScancode[100][1],"\xF0\x61\x00"); 
  strcpy(KbdScancode[101][0],"\xE0\x2F\x00"); //Windows Menu to be checked
  strcpy(KbdScancode[101][1],"\xE0\xF0\x2F\x00"); 
  strcpy(KbdScancode[102][0],"\x11\x00"); //LeftCtrl - From here, misusing of untypical KbdScancodes like F13 onwards for modifier keys starts
  strcpy(KbdScancode[102][1],"\xF0\x11\x00"); 
  strcpy(KbdScancode[103][0],"\x12\x00"); //LeftShift
  strcpy(KbdScancode[103][1],"\xF0\x12\x00");
  strcpy(KbdScancode[104][0],"\x19\x00"); //LeftAlt
  strcpy(KbdScancode[104][1],"\xF0\x19\x00");
  strcpy(KbdScancode[105][0],"\xE0\x8B\x00"); //LeftMeta
  strcpy(KbdScancode[105][1],"\xE0\xF0\x8B\x00");
  strcpy(KbdScancode[106][0],"\xE0\x58\x00"); //RightCtrl
  strcpy(KbdScancode[106][1],"\xE0\xF0\x58\x00");
  strcpy(KbdScancode[107][0],"\x59\x00"); //RightShift
  strcpy(KbdScancode[107][1],"\xF0\x59\x00");
  strcpy(KbdScancode[108][0],"\x39\x00"); //RightAlt/AltGr
  strcpy(KbdScancode[108][1],"\xF0\x39\x00");
  strcpy(KbdScancode[109][0],"\x8C\x00"); //RightMeta
  strcpy(KbdScancode[109][1],"\xF0\x8C\x00");
  strcpy(KbdScancode[110][0],"\xFA\x00"); //Reset Ack
  strcpy(KbdScancode[110][1],"\xAA\x00");
  strcpy(KbdScancode[111][0],"\xFA\xAB\x83\x00"); //Keyboard ID
  strcpy(KbdScancode[111][1],"\xFA\xAB\x83\x00");
  strcpy(KbdScancode[112][0],"\xEE\x00"); //Echo
  strcpy(KbdScancode[112][1],"\xEE\x00");
  strcpy(KbdScancode[113][0],"\x03\x00"); //Current KbdScancode Set
  strcpy(KbdScancode[113][1],"\x03\x00");
}

void initScancodeXT()
{
  strcpy(KbdScancode[0][0],"\x00"); //No Key
  strcpy(KbdScancode[0][1],"\x00");
  strcpy(KbdScancode[1][0],"\x00"); //Keyboard Error
  strcpy(KbdScancode[1][1],"\x00");
  strcpy(KbdScancode[2][0],"\x00"); //POST Fail
  strcpy(KbdScancode[2][1],"\x00");  
  strcpy(KbdScancode[3][0],"\x00"); //undefined error
  strcpy(KbdScancode[3][1],"\x00");
  strcpy(KbdScancode[4][0],"\x1E\x00"); //a
  strcpy(KbdScancode[4][1],"\x9E\x00");
  strcpy(KbdScancode[5][0],"\x30\x00"); //b
  strcpy(KbdScancode[5][1],"\xB0\x00");
  strcpy(KbdScancode[6][0],"\x2E\x00"); //c
  strcpy(KbdScancode[6][1],"\xAE\x00");
  strcpy(KbdScancode[7][0],"\x20\x00"); //d
  strcpy(KbdScancode[7][1],"\xA0\x00");
  strcpy(KbdScancode[8][0],"\x12\x00"); //e
  strcpy(KbdScancode[8][1],"\x92\x00");
  strcpy(KbdScancode[9][0],"\x21\x00"); //f
  strcpy(KbdScancode[9][1],"\xA1\x00");
  strcpy(KbdScancode[10][0],"\x22\x00"); //g
  strcpy(KbdScancode[10][1],"\xA2\x00");
  strcpy(KbdScancode[11][0],"\x23\x00"); //h
  strcpy(KbdScancode[11][1],"\xA3\x00");
  strcpy(KbdScancode[12][0],"\x17\x00"); //i
  strcpy(KbdScancode[12][1],"\x97\x00");
  strcpy(KbdScancode[13][0],"\x24\x00"); //j
  strcpy(KbdScancode[13][1],"\xA4\x00");
  strcpy(KbdScancode[14][0],"\x25\x00"); //k
  strcpy(KbdScancode[14][1],"\xA5\x00"); 
  strcpy(KbdScancode[15][0],"\x26\x00"); //l
  strcpy(KbdScancode[15][1],"\xA6\x00");
  strcpy(KbdScancode[16][0],"\x32\x00"); //m
  strcpy(KbdScancode[16][1],"\xB2\x00");
  strcpy(KbdScancode[17][0],"\x31\x00"); //n
  strcpy(KbdScancode[17][1],"\xB1\x00");
  strcpy(KbdScancode[18][0],"\x18\x00"); //o
  strcpy(KbdScancode[18][1],"\x98\x00");
  strcpy(KbdScancode[19][0],"\x19\x00"); //p
  strcpy(KbdScancode[19][1],"\x99\x00");
  strcpy(KbdScancode[20][0],"\x10\x00"); //q
  strcpy(KbdScancode[20][1],"\x90\x00");
  strcpy(KbdScancode[21][0],"\x13\x00"); //r
  strcpy(KbdScancode[21][1],"\x93\x00");
  strcpy(KbdScancode[22][0],"\x1F\x00"); //s
  strcpy(KbdScancode[22][1],"\x9F\x00");
  strcpy(KbdScancode[23][0],"\x14\x00"); //t
  strcpy(KbdScancode[23][1],"\x94\x00");
  strcpy(KbdScancode[24][0],"\x16\x00"); //u
  strcpy(KbdScancode[24][1],"\x96\x00");
  strcpy(KbdScancode[25][0],"\x2F\x00"); //v
  strcpy(KbdScancode[25][1],"\xAF\x00");
  strcpy(KbdScancode[26][0],"\x11\x00"); //w
  strcpy(KbdScancode[26][1],"\x91\x00");
  strcpy(KbdScancode[27][0],"\x2D\x00"); //x
  strcpy(KbdScancode[27][1],"\xAD\x00");
  strcpy(KbdScancode[28][0],"\x15\x00"); //y
  strcpy(KbdScancode[28][1],"\x95\x00");
  strcpy(KbdScancode[29][0],"\x2C\x00"); //z
  strcpy(KbdScancode[29][1],"\xAC\x00");
  strcpy(KbdScancode[30][0],"\x02\x00"); //1
  strcpy(KbdScancode[30][1],"\x82\x00");
  strcpy(KbdScancode[31][0],"\x03\x00"); //2
  strcpy(KbdScancode[31][1],"\x83\x00");
  strcpy(KbdScancode[32][0],"\x04\x00"); //3
  strcpy(KbdScancode[32][1],"\x84\x00");
  strcpy(KbdScancode[33][0],"\x05\x00"); //4
  strcpy(KbdScancode[33][1],"\x85\x00");
  strcpy(KbdScancode[34][0],"\x06\x00"); //5
  strcpy(KbdScancode[34][1],"\x86\x00");
  strcpy(KbdScancode[35][0],"\x07\x00"); //6
  strcpy(KbdScancode[35][1],"\x87\x00");
  strcpy(KbdScancode[36][0],"\x08\x00"); //7
  strcpy(KbdScancode[36][1],"\x88\x00");
  strcpy(KbdScancode[37][0],"\x09\x00"); //8
  strcpy(KbdScancode[37][1],"\x89\x00");
  strcpy(KbdScancode[38][0],"\x0A\x00"); //9
  strcpy(KbdScancode[38][1],"\x8A\x00");
  strcpy(KbdScancode[39][0],"\x0B\x00"); //0
  strcpy(KbdScancode[39][1],"\x8B\x00");
  strcpy(KbdScancode[40][0],"\x1C\x00"); //Enter
  strcpy(KbdScancode[40][1],"\x9C\x00");
  strcpy(KbdScancode[41][0],"\x01\x00"); //Esc
  strcpy(KbdScancode[41][1],"\x81\x00");
  strcpy(KbdScancode[42][0],"\x0E\x00"); //Backspace
  strcpy(KbdScancode[42][1],"\x8E\x00");
  strcpy(KbdScancode[43][0],"\x0F\x00"); //Tab
  strcpy(KbdScancode[43][1],"\x8F\x00");
  strcpy(KbdScancode[44][0],"\x39\x00"); //Space
  strcpy(KbdScancode[44][1],"\xB9\x00");
  strcpy(KbdScancode[45][0],"\x0C\x00"); //Minus
  strcpy(KbdScancode[45][1],"\x8C\x00");
  strcpy(KbdScancode[46][0],"\x0D\x00"); //Equal
  strcpy(KbdScancode[46][1],"\x8D\x00");
  strcpy(KbdScancode[47][0],"\x1A\x00"); //Left brace
  strcpy(KbdScancode[47][1],"\x9A\x00");
  strcpy(KbdScancode[48][0],"\x1B\x00"); //right brace
  strcpy(KbdScancode[48][1],"\x9B\x00");
  strcpy(KbdScancode[49][0],"\x2B\x00"); //Backslash
  strcpy(KbdScancode[49][1],"\xAB\x00");
  strcpy(KbdScancode[50][0],"\x2A\x00"); //Hash+Tilde for Non-US
  strcpy(KbdScancode[50][1],"\xAA\x00");
  strcpy(KbdScancode[51][0],"\x27\x00"); //Semicolon
  strcpy(KbdScancode[51][1],"\xA7\x00");
  strcpy(KbdScancode[52][0],"\x28\x00"); //Apostrophe
  strcpy(KbdScancode[52][1],"\xA8\x00");
  strcpy(KbdScancode[53][0],"\x29\x00"); //Grave and Tilde
  strcpy(KbdScancode[53][1],"\xA9\x00");
  strcpy(KbdScancode[54][0],"\x33\x00"); //Comma
  strcpy(KbdScancode[54][1],"\xB3\x00");
  strcpy(KbdScancode[55][0],"\x34\x00"); //Dot
  strcpy(KbdScancode[55][1],"\xB4\x00");
  strcpy(KbdScancode[56][0],"\x35\x00"); //Slash
  strcpy(KbdScancode[56][1],"\xB5\x00");
  strcpy(KbdScancode[57][0],"\x3A\x00"); //Capslock
  strcpy(KbdScancode[57][1],"\xBA\x00");
  strcpy(KbdScancode[58][0],"\x3B\x00"); //F1
  strcpy(KbdScancode[58][1],"\xBB\x00");
  strcpy(KbdScancode[59][0],"\x3C\x00"); //F2
  strcpy(KbdScancode[59][1],"\xBC\x00");
  strcpy(KbdScancode[60][0],"\x3D\x00"); //F3
  strcpy(KbdScancode[60][1],"\xBD\x00");
  strcpy(KbdScancode[61][0],"\x3E\x00"); //F4
  strcpy(KbdScancode[61][1],"\xBE\x00");
  strcpy(KbdScancode[62][0],"\x3F\x00"); //F5
  strcpy(KbdScancode[62][1],"\xBF\x00");
  strcpy(KbdScancode[63][0],"\x40\x00"); //F6
  strcpy(KbdScancode[63][1],"\xC0\x00");
  strcpy(KbdScancode[64][0],"\x41\x00"); //F7
  strcpy(KbdScancode[64][1],"\xC1\x00");
  strcpy(KbdScancode[65][0],"\x42\x00"); //F8
  strcpy(KbdScancode[65][1],"\xC2\x00");
  strcpy(KbdScancode[66][0],"\x43\x00"); //F9
  strcpy(KbdScancode[66][1],"\xC3\x00");
  strcpy(KbdScancode[67][0],"\x44\x00"); //F10
  strcpy(KbdScancode[67][1],"\xC4\x00");
  strcpy(KbdScancode[68][0],"\x00"); //F11
  strcpy(KbdScancode[68][1],"\x00");
  strcpy(KbdScancode[69][0],"\x00"); //F12
  strcpy(KbdScancode[69][1],"\x00");
  strcpy(KbdScancode[70][0],"\x37\x00"); //SysReq/PrintScreen
  strcpy(KbdScancode[70][1],"\xB7\x00");
  strcpy(KbdScancode[71][0],"\x46\x00"); //ScrollLock
  strcpy(KbdScancode[71][1],"\xC6\x00");
  strcpy(KbdScancode[72][0],"\x00"); //Pause/Break - XT KbdScancode unknown
  strcpy(KbdScancode[72][1],"\x00");
  strcpy(KbdScancode[73][0],"\xE0\x52\x00"); //Insert
  strcpy(KbdScancode[73][1],"\xE0\xD2\x00");
  strcpy(KbdScancode[74][0],"\xE0\x47\x00"); //Home
  strcpy(KbdScancode[74][1],"\xE0\xC7\x00");
  strcpy(KbdScancode[75][0],"\xE0\x49\x00"); //PgUp
  strcpy(KbdScancode[75][1],"\xE0\xC9\x00");
  strcpy(KbdScancode[76][0],"\xE0\x53\x00"); //Delete
  strcpy(KbdScancode[76][1],"\xE0\xD3\x00");
  strcpy(KbdScancode[77][0],"\xE0\x4F\x00"); //End
  strcpy(KbdScancode[77][1],"\xE0\xCD\x00");
  strcpy(KbdScancode[78][0],"\xE0\x51\x00"); //PgDn
  strcpy(KbdScancode[78][1],"\xE0\xD1\x00");
  strcpy(KbdScancode[79][0],"\xE0\x4D\x00"); //Right
  strcpy(KbdScancode[79][1],"\xE0\xCD\x00");
  strcpy(KbdScancode[80][0],"\xE0\x4B\x00"); //Left
  strcpy(KbdScancode[80][1],"\xE0\xCB\x00");
  strcpy(KbdScancode[81][0],"\xE0\x50\x00"); //Down
  strcpy(KbdScancode[81][1],"\xE0\xD0\x00");
  strcpy(KbdScancode[82][0],"\xE0\x48\x00"); //Up
  strcpy(KbdScancode[82][1],"\xE0\xC8\x00");
  strcpy(KbdScancode[83][0],"\x45\x00"); //Numlock
  strcpy(KbdScancode[83][1],"\xC5\x00");
  strcpy(KbdScancode[84][0],"\x00"); //Keypad Slash
  strcpy(KbdScancode[84][1],"\x00");
  strcpy(KbdScancode[85][0],"\x00"); //Keypad Asterisk
  strcpy(KbdScancode[85][1],"\x00");
  strcpy(KbdScancode[86][0],"\x4A\x00"); //Keypad Minus
  strcpy(KbdScancode[86][1],"\xCA\x00");
  strcpy(KbdScancode[87][0],"\x4E\x00"); //Keypad Plus
  strcpy(KbdScancode[87][1],"\xCE\x00");
  strcpy(KbdScancode[88][0],"\x1C\x00"); //Keypad Enter
  strcpy(KbdScancode[88][1],"\x9C\x00");
  strcpy(KbdScancode[89][0],"\x4F\x00"); //Keypad 1/End
  strcpy(KbdScancode[89][1],"\xCF\x00");
  strcpy(KbdScancode[90][0],"\x50\x00"); //Keypad 2/Dn
  strcpy(KbdScancode[90][1],"\xD0\x00");
  strcpy(KbdScancode[91][0],"\x51\x00"); //Keypad 3/PgDn
  strcpy(KbdScancode[91][1],"\xD1\x00");
  strcpy(KbdScancode[92][0],"\x4B\x00"); //Keypad 4/Left
  strcpy(KbdScancode[92][1],"\xCB\x00");
  strcpy(KbdScancode[93][0],"\x4C\x00"); //Keypad 5
  strcpy(KbdScancode[93][1],"\xCC\x00");
  strcpy(KbdScancode[94][0],"\x4D\x00"); //Keypad 6/Right
  strcpy(KbdScancode[94][1],"\xCD\x00");
  strcpy(KbdScancode[95][0],"\x47\x00"); //Keypad 7/Home
  strcpy(KbdScancode[95][1],"\xC7\x00");
  strcpy(KbdScancode[96][0],"\x48\x00"); //Keypad 8/Up
  strcpy(KbdScancode[96][1],"\xC8\x00");
  strcpy(KbdScancode[97][0],"\x49\x00"); //Keypad 9/PgUp
  strcpy(KbdScancode[97][1],"\xC9\x00");
  strcpy(KbdScancode[98][0],"\x52\x00"); //Keypad 0/Insert
  strcpy(KbdScancode[98][1],"\xD2\x00");
  strcpy(KbdScancode[99][0],"\x53\x00"); //Keypad ./Delete 
  strcpy(KbdScancode[99][1],"\xD3\x00");
  strcpy(KbdScancode[100][0],"\x56\x00"); //INT 1 a.k.a. 102nd Key Backslash/Pipe Non-US
  strcpy(KbdScancode[100][1],"\xD6\x00"); 
  strcpy(KbdScancode[101][0],"\x00"); //Windows Menu
  strcpy(KbdScancode[101][1],"\x00"); 
  strcpy(KbdScancode[102][0],"\x1D\x00"); //LeftCtrl - From here, misusing of untypical KbdScancodes like F13 onwards for modifier keys starts
  strcpy(KbdScancode[102][1],"\x9D\x00"); 
  strcpy(KbdScancode[103][0],"\x2A\x00"); //LeftShift
  strcpy(KbdScancode[103][1],"\xAA\x00");
  strcpy(KbdScancode[104][0],"\x38\x00"); //LeftAlt
  strcpy(KbdScancode[104][1],"\xB8\x00");
  strcpy(KbdScancode[105][0],"\x00"); //LeftMeta
  strcpy(KbdScancode[105][1],"\x00");
  strcpy(KbdScancode[106][0],"\x1D\x00"); //RightCtrl
  strcpy(KbdScancode[106][1],"\x9D\x00");
  strcpy(KbdScancode[107][0],"\x36\x00"); //RightShift
  strcpy(KbdScancode[107][1],"\xB6\x00");
  strcpy(KbdScancode[108][0],"\x38\x00"); //RightAlt/AltGr
  strcpy(KbdScancode[108][1],"\xB8\x00");
  strcpy(KbdScancode[109][0],"\x00"); //RightMeta
  strcpy(KbdScancode[109][1],"\x00");
  strcpy(KbdScancode[110][0],"\x00"); //Reset Ack - Does not apply to this KbdScancode set
  strcpy(KbdScancode[110][1],"\x00");
  strcpy(KbdScancode[111][0],"\x00"); //Keyboard ID - Does not apply to this KbdScancode set
  strcpy(KbdScancode[111][1],"\x00");
  strcpy(KbdScancode[112][0],"\x00"); //Echo - Does not apply to this KbdScancode set
  strcpy(KbdScancode[112][1],"\x00");  
  strcpy(KbdScancode[113][0],"\x00"); //Current KbdScancode Set - Does not apply to this KbdScancode set
  strcpy(KbdScancode[113][1],"\x00");
}

void initScancodeT1000()
{
  strcpy(KbdScancode[0][0],"\x00"); //No Key
  strcpy(KbdScancode[0][1],"\x00");
  strcpy(KbdScancode[1][0],"\x00"); //Keyboard Error
  strcpy(KbdScancode[1][1],"\x00");
  strcpy(KbdScancode[2][0],"\x00"); //POST Fail
  strcpy(KbdScancode[2][1],"\x00");  
  strcpy(KbdScancode[3][0],"\x00"); //undefined error
  strcpy(KbdScancode[3][1],"\x00");
  strcpy(KbdScancode[4][0],"\x1E\x00"); //a
  strcpy(KbdScancode[4][1],"\x9E\x00");
  strcpy(KbdScancode[5][0],"\x30\x00"); //b
  strcpy(KbdScancode[5][1],"\xB0\x00");
  strcpy(KbdScancode[6][0],"\x2E\x00"); //c
  strcpy(KbdScancode[6][1],"\xAE\x00");
  strcpy(KbdScancode[7][0],"\x20\x00"); //d
  strcpy(KbdScancode[7][1],"\xA0\x00");
  strcpy(KbdScancode[8][0],"\x12\x00"); //e
  strcpy(KbdScancode[8][1],"\x92\x00");
  strcpy(KbdScancode[9][0],"\x21\x00"); //f
  strcpy(KbdScancode[9][1],"\xA1\x00");
  strcpy(KbdScancode[10][0],"\x22\x00"); //g
  strcpy(KbdScancode[10][1],"\xA2\x00");
  strcpy(KbdScancode[11][0],"\x23\x00"); //h
  strcpy(KbdScancode[11][1],"\xA3\x00");
  strcpy(KbdScancode[12][0],"\x17\x00"); //i
  strcpy(KbdScancode[12][1],"\x97\x00");
  strcpy(KbdScancode[13][0],"\x24\x00"); //j
  strcpy(KbdScancode[13][1],"\xA4\x00");
  strcpy(KbdScancode[14][0],"\x25\x00"); //k
  strcpy(KbdScancode[14][1],"\xA5\x00"); 
  strcpy(KbdScancode[15][0],"\x26\x00"); //l
  strcpy(KbdScancode[15][1],"\xA6\x00");
  strcpy(KbdScancode[16][0],"\x32\x00"); //m
  strcpy(KbdScancode[16][1],"\xB2\x00");
  strcpy(KbdScancode[17][0],"\x31\x00"); //n
  strcpy(KbdScancode[17][1],"\xB1\x00");
  strcpy(KbdScancode[18][0],"\x18\x00"); //o
  strcpy(KbdScancode[18][1],"\x98\x00");
  strcpy(KbdScancode[19][0],"\x19\x00"); //p
  strcpy(KbdScancode[19][1],"\x99\x00");
  strcpy(KbdScancode[20][0],"\x10\x00"); //q
  strcpy(KbdScancode[20][1],"\x90\x00");
  strcpy(KbdScancode[21][0],"\x13\x00"); //r
  strcpy(KbdScancode[21][1],"\x93\x00");
  strcpy(KbdScancode[22][0],"\x1F\x00"); //s
  strcpy(KbdScancode[22][1],"\x9F\x00");
  strcpy(KbdScancode[23][0],"\x14\x00"); //t
  strcpy(KbdScancode[23][1],"\x94\x00");
  strcpy(KbdScancode[24][0],"\x16\x00"); //u
  strcpy(KbdScancode[24][1],"\x96\x00");
  strcpy(KbdScancode[25][0],"\x2F\x00"); //v
  strcpy(KbdScancode[25][1],"\xAF\x00");
  strcpy(KbdScancode[26][0],"\x11\x00"); //w
  strcpy(KbdScancode[26][1],"\x91\x00");
  strcpy(KbdScancode[27][0],"\x2D\x00"); //x
  strcpy(KbdScancode[27][1],"\xAD\x00");
  strcpy(KbdScancode[28][0],"\x15\x00"); //y
  strcpy(KbdScancode[28][1],"\x95\x00");
  strcpy(KbdScancode[29][0],"\x2C\x00"); //z
  strcpy(KbdScancode[29][1],"\xAC\x00");
  strcpy(KbdScancode[30][0],"\x02\x00"); //1
  strcpy(KbdScancode[30][1],"\x82\x00");
  strcpy(KbdScancode[31][0],"\x03\x00"); //2
  strcpy(KbdScancode[31][1],"\x83\x00");
  strcpy(KbdScancode[32][0],"\x04\x00"); //3
  strcpy(KbdScancode[32][1],"\x84\x00");
  strcpy(KbdScancode[33][0],"\x05\x00"); //4
  strcpy(KbdScancode[33][1],"\x86\x00");
  strcpy(KbdScancode[34][0],"\x06\x00"); //5
  strcpy(KbdScancode[34][1],"\x86\x00");
  strcpy(KbdScancode[35][0],"\x07\x00"); //6
  strcpy(KbdScancode[35][1],"\x87\x00");
  strcpy(KbdScancode[36][0],"\x08\x00"); //7
  strcpy(KbdScancode[36][1],"\x88\x00");
  strcpy(KbdScancode[37][0],"\x09\x00"); //8
  strcpy(KbdScancode[37][1],"\x89\x00");
  strcpy(KbdScancode[38][0],"\x0A\x00"); //9
  strcpy(KbdScancode[38][1],"\x8A\x00");
  strcpy(KbdScancode[39][0],"\x0B\x00"); //0
  strcpy(KbdScancode[39][1],"\x8B\x00");
  strcpy(KbdScancode[40][0],"\x1C\x00"); //Enter
  strcpy(KbdScancode[40][1],"\x9C\x00");
  strcpy(KbdScancode[41][0],"\x01\x00"); //Esc
  strcpy(KbdScancode[41][1],"\x81\x00");
  strcpy(KbdScancode[42][0],"\x0E\x00"); //Backspace
  strcpy(KbdScancode[42][1],"\x8E\x00");
  strcpy(KbdScancode[43][0],"\x0F\x00"); //Tab
  strcpy(KbdScancode[43][1],"\x8F\x00");
  strcpy(KbdScancode[44][0],"\x39\x00"); //Space
  strcpy(KbdScancode[44][1],"\xB9\x00");
  strcpy(KbdScancode[45][0],"\x0C\x00"); //Minus
  strcpy(KbdScancode[45][1],"\x8C\x00");
  strcpy(KbdScancode[46][0],"\x0D\x00"); //Equal
  strcpy(KbdScancode[46][1],"\x8D\x00");
  strcpy(KbdScancode[47][0],"\x1A\x00"); //Left brace
  strcpy(KbdScancode[47][1],"\x9A\x00");
  strcpy(KbdScancode[48][0],"\x1B\x00"); //right brace
  strcpy(KbdScancode[48][1],"\x9B\x00");
  strcpy(KbdScancode[49][0],"\x00"); //Backslash Special Handling required
  strcpy(KbdScancode[49][1],"\x00");
  strcpy(KbdScancode[50][0],"\x00"); //Hash+Tilde for Non-US Does not exist on Tandy
  strcpy(KbdScancode[50][1],"\x00");
  strcpy(KbdScancode[51][0],"\x27\x00"); //Semicolon
  strcpy(KbdScancode[51][1],"\xA7\x00");
  strcpy(KbdScancode[52][0],"\x28\x00"); //Apostrophe
  strcpy(KbdScancode[52][1],"\xA8\x00");
  strcpy(KbdScancode[53][0],"\x50\x00"); //Grave and Tilde Special Handling required
  strcpy(KbdScancode[53][1],"\xD0\x00");
  strcpy(KbdScancode[54][0],"\x33\x00"); //Comma
  strcpy(KbdScancode[54][1],"\xB3\x00");
  strcpy(KbdScancode[55][0],"\x34\x00"); //Dot
  strcpy(KbdScancode[55][1],"\xC4\x00");
  strcpy(KbdScancode[56][0],"\x35\x00"); //Slash
  strcpy(KbdScancode[56][1],"\xB5\x00");
  strcpy(KbdScancode[57][0],"\x3A\x00"); //Capslock
  strcpy(KbdScancode[57][1],"\xBA\x00");
  strcpy(KbdScancode[58][0],"\x3B\x00"); //F1
  strcpy(KbdScancode[58][1],"\xBB\x00");
  strcpy(KbdScancode[59][0],"\x3C\x00"); //F2
  strcpy(KbdScancode[59][1],"\xBC\x00");
  strcpy(KbdScancode[60][0],"\x3D\x00"); //F3
  strcpy(KbdScancode[60][1],"\xBD\x00");
  strcpy(KbdScancode[61][0],"\x3E\x00"); //F4
  strcpy(KbdScancode[61][1],"\xBE\x00");
  strcpy(KbdScancode[62][0],"\x3F\x00"); //F5
  strcpy(KbdScancode[62][1],"\xBF\x00");
  strcpy(KbdScancode[63][0],"\x40\x00"); //F6
  strcpy(KbdScancode[63][1],"\xC0\x00");
  strcpy(KbdScancode[64][0],"\x41\x00"); //F7
  strcpy(KbdScancode[64][1],"\xC1\x00");
  strcpy(KbdScancode[65][0],"\x42\x00"); //F8
  strcpy(KbdScancode[65][1],"\xC2\x00");
  strcpy(KbdScancode[66][0],"\x43\x00"); //F9
  strcpy(KbdScancode[66][1],"\xC3\x00");
  strcpy(KbdScancode[67][0],"\x44\x00"); //F10
  strcpy(KbdScancode[67][1],"\xC4\x00");
  strcpy(KbdScancode[68][0],"\x59\x00"); //F11
  strcpy(KbdScancode[68][1],"\xD9\x00");
  strcpy(KbdScancode[69][0],"\x5A\x00"); //F12
  strcpy(KbdScancode[69][1],"\xDA\x00");
  strcpy(KbdScancode[70][0],"\x00"); //SysReq/PrintScreen Requires special handling, does not exist in Adrians source
  strcpy(KbdScancode[70][1],"\x00");
  strcpy(KbdScancode[71][0],"\x46\x00"); //ScrollLock
  strcpy(KbdScancode[71][1],"\xC6\x00");
  strcpy(KbdScancode[72][0],"\x54\x00"); //Pause/Break
  strcpy(KbdScancode[72][1],"\xD4\x00");
  strcpy(KbdScancode[73][0],"\x52\x00"); //Insert
  strcpy(KbdScancode[73][1],"\xD2\x00");
  strcpy(KbdScancode[74][0],"\x58\x00"); //Home
  strcpy(KbdScancode[74][1],"\xD8\x00");
  strcpy(KbdScancode[75][0],"\x48\x00"); //PgUp
  strcpy(KbdScancode[75][1],"\xC8\x00");
  strcpy(KbdScancode[76][0],"\x56\x00"); //Delete
  strcpy(KbdScancode[76][1],"\xD6\x00");
  strcpy(KbdScancode[77][0],"\x4F\x00"); //End
  strcpy(KbdScancode[77][1],"\xCF\x00");
  strcpy(KbdScancode[78][0],"\x51\x00"); //PgDn
  strcpy(KbdScancode[78][1],"\xD1\x00");
  strcpy(KbdScancode[79][0],"\x4D\x00"); //Right
  strcpy(KbdScancode[79][1],"\xCD\x00");
  strcpy(KbdScancode[80][0],"\x4B\x00"); //Left
  strcpy(KbdScancode[80][1],"\xCB\x00");
  strcpy(KbdScancode[81][0],"\x50\x00"); //Down
  strcpy(KbdScancode[81][1],"\xD0\x00");
  strcpy(KbdScancode[82][0],"\x48\x00"); //Up
  strcpy(KbdScancode[82][1],"\xC8\x00");
  strcpy(KbdScancode[83][0],"\x45\x00"); //Numlock
  strcpy(KbdScancode[83][1],"\xC5\x00");
  strcpy(KbdScancode[84][0],"\x35\x00"); //Keypad Slash
  strcpy(KbdScancode[84][1],"\xB5\x00");
  strcpy(KbdScancode[85][0],"\x00"); //Keypad Asterisk
  strcpy(KbdScancode[85][1],"\x00");
  strcpy(KbdScancode[86][0],"\x0C\x00"); //Keypad Minus
  strcpy(KbdScancode[86][1],"\x8C\x00");
  strcpy(KbdScancode[87][0],"\x00"); //Keypad Plus - Handled with an exception, no scancode
  strcpy(KbdScancode[87][1],"\x00");
  strcpy(KbdScancode[88][0],"\x57\x00"); //Keypad Enter
  strcpy(KbdScancode[88][1],"\xD7\x00");
  strcpy(KbdScancode[89][0],"\x4F\x00"); //Keypad 1/End
  strcpy(KbdScancode[89][1],"\xCF\x00");
  strcpy(KbdScancode[90][0],"\x50\x00"); //Keypad 2/Dn
  strcpy(KbdScancode[90][1],"\xD0\x00");
  strcpy(KbdScancode[91][0],"\x51\x00"); //Keypad 3/PgDn
  strcpy(KbdScancode[91][1],"\xD1\x00");
  strcpy(KbdScancode[92][0],"\x4B\x00"); //Keypad 4/Left
  strcpy(KbdScancode[92][1],"\xCB\x00");
  strcpy(KbdScancode[93][0],"\x4C\x00"); //Keypad 5
  strcpy(KbdScancode[93][1],"\xCC\x00");
  strcpy(KbdScancode[94][0],"\x4D\x00"); //Keypad 6/Right
  strcpy(KbdScancode[94][1],"\xCD\x00");
  strcpy(KbdScancode[95][0],"\x47\x00"); //Keypad 7/Home
  strcpy(KbdScancode[95][1],"\xC7\x00");
  strcpy(KbdScancode[96][0],"\x48\x00"); //Keypad 8/Up
  strcpy(KbdScancode[96][1],"\xC8\x00");
  strcpy(KbdScancode[97][0],"\x49\x00"); //Keypad 9/PgUp
  strcpy(KbdScancode[97][1],"\xC9\x00");
  strcpy(KbdScancode[98][0],"\x52\x00"); //Keypad 0/Insert
  strcpy(KbdScancode[98][1],"\xD2\x00");
  strcpy(KbdScancode[99][0],"\x56\x00"); //Keypad ./Delete 
  strcpy(KbdScancode[99][1],"\xD6\x00");
  strcpy(KbdScancode[100][0],"\x00"); //INT 1 a.k.a. 102nd Key Backslash/Pipe Non-US
  strcpy(KbdScancode[100][1],"\x00"); 
  strcpy(KbdScancode[101][0],"\x00"); //Windows Menu
  strcpy(KbdScancode[101][1],"\x00"); 
  strcpy(KbdScancode[102][0],"\x1D\x00"); //LeftCtrl - From here, misusing of untypical KbdScancodes like F13 onwards for modifier keys starts
  strcpy(KbdScancode[102][1],"\x9D\x00"); 
  strcpy(KbdScancode[103][0],"\x2A\x00"); //LeftShift
  strcpy(KbdScancode[103][1],"\xAA\x00");
  strcpy(KbdScancode[104][0],"\x38\x00"); //LeftAlt
  strcpy(KbdScancode[104][1],"\xB8\x00");
  strcpy(KbdScancode[105][0],"\x00"); //LeftMeta
  strcpy(KbdScancode[105][1],"\x00");
  strcpy(KbdScancode[106][0],"\x1D\x00"); //RightCtrl Mirror Left Ctrl
  strcpy(KbdScancode[106][1],"\x9D\x00");
  strcpy(KbdScancode[107][0],"\x36\x00"); //RightShift
  strcpy(KbdScancode[107][1],"\xB6\x00");
  strcpy(KbdScancode[108][0],"\x38\x00"); //RightAlt/AltGr Mirror Left Alt
  strcpy(KbdScancode[108][1],"\xB8\x00");
  strcpy(KbdScancode[109][0],"\x00"); //RightMeta
  strcpy(KbdScancode[109][1],"\x00");
  strcpy(KbdScancode[110][0],"\x00"); //Reset Ack - Does not apply to this KbdScancode set
  strcpy(KbdScancode[110][1],"\x00");
  strcpy(KbdScancode[111][0],"\x00"); //Keyboard ID - Does not apply to this KbdScancode set
  strcpy(KbdScancode[111][1],"\x00");
  strcpy(KbdScancode[112][0],"\x00"); //Echo - Does not apply to this KbdScancode set
  strcpy(KbdScancode[112][1],"\x00");  
  strcpy(KbdScancode[113][0],"\x00"); //Current KbdScancode Set - Does not apply to this KbdScancode set
  strcpy(KbdScancode[113][1],"\x00");
}
void initScancodeAmiga()
{
  strcpy(KbdScancode[0][0],"\x00"); //No Key
  strcpy(KbdScancode[0][1],"\x00");
  strcpy(KbdScancode[1][0],"\x00"); //Keyboard Error
  strcpy(KbdScancode[1][1],"\x00");
  strcpy(KbdScancode[2][0],"\x00"); //POST Fail
  strcpy(KbdScancode[2][1],"\x00");  
  strcpy(KbdScancode[3][0],"\x00"); //undefined error
  strcpy(KbdScancode[3][1],"\x00");
  strcpy(KbdScancode[4][0],"\x20\x00"); //a
  strcpy(KbdScancode[4][1],"\xA0\x00");
  strcpy(KbdScancode[5][0],"\x35\x00"); //b
  strcpy(KbdScancode[5][1],"\xB5\x00");
  strcpy(KbdScancode[6][0],"\x33\x00"); //c
  strcpy(KbdScancode[6][1],"\xB3\x00");
  strcpy(KbdScancode[7][0],"\x22\x00"); //d
  strcpy(KbdScancode[7][1],"\xA2\x00");
  strcpy(KbdScancode[8][0],"\x12\x00"); //e
  strcpy(KbdScancode[8][1],"\x92\x00");
  strcpy(KbdScancode[9][0],"\x23\x00"); //f
  strcpy(KbdScancode[9][1],"\xA3\x00");
  strcpy(KbdScancode[10][0],"\x24\x00"); //g
  strcpy(KbdScancode[10][1],"\xA4\x00");
  strcpy(KbdScancode[11][0],"\x25\x00"); //h
  strcpy(KbdScancode[11][1],"\xA5\x00");
  strcpy(KbdScancode[12][0],"\x17\x00"); //i
  strcpy(KbdScancode[12][1],"\x97\x00");
  strcpy(KbdScancode[13][0],"\x26\x00"); //j
  strcpy(KbdScancode[13][1],"\xA6\x00");
  strcpy(KbdScancode[14][0],"\x27\x00"); //k
  strcpy(KbdScancode[14][1],"\xA7\x00"); 
  strcpy(KbdScancode[15][0],"\x28\x00"); //l
  strcpy(KbdScancode[15][1],"\xA8\x00");
  strcpy(KbdScancode[16][0],"\x37\x00"); //m
  strcpy(KbdScancode[16][1],"\xB7\x00");
  strcpy(KbdScancode[17][0],"\x36\x00"); //n
  strcpy(KbdScancode[17][1],"\xB6\x00");
  strcpy(KbdScancode[18][0],"\x18\x00"); //o
  strcpy(KbdScancode[18][1],"\x98\x00");
  strcpy(KbdScancode[19][0],"\x19\x00"); //p
  strcpy(KbdScancode[19][1],"\x99\x00");
  strcpy(KbdScancode[20][0],"\x10\x00"); //q
  strcpy(KbdScancode[20][1],"\x90\x00");
  strcpy(KbdScancode[21][0],"\x13\x00"); //r
  strcpy(KbdScancode[21][1],"\x93\x00");
  strcpy(KbdScancode[22][0],"\x21\x00"); //s
  strcpy(KbdScancode[22][1],"\xA1\x00");
  strcpy(KbdScancode[23][0],"\x14\x00"); //t
  strcpy(KbdScancode[23][1],"\x94\x00");
  strcpy(KbdScancode[24][0],"\x16\x00"); //u
  strcpy(KbdScancode[24][1],"\x96\x00");
  strcpy(KbdScancode[25][0],"\x34\x00"); //v
  strcpy(KbdScancode[25][1],"\xB4\x00");
  strcpy(KbdScancode[26][0],"\x11\x00"); //w
  strcpy(KbdScancode[26][1],"\x91\x00");
  strcpy(KbdScancode[27][0],"\x32\x00"); //x
  strcpy(KbdScancode[27][1],"\xB2\x00");
  strcpy(KbdScancode[28][0],"\x15\x00"); //y
  strcpy(KbdScancode[28][1],"\x95\x00");
  strcpy(KbdScancode[29][0],"\x31\x00"); //z
  strcpy(KbdScancode[29][1],"\xB1\x00");
  strcpy(KbdScancode[30][0],"\x01\x00"); //1
  strcpy(KbdScancode[30][1],"\x81\x00");
  strcpy(KbdScancode[31][0],"\x02\x00"); //2
  strcpy(KbdScancode[31][1],"\x82\x00");
  strcpy(KbdScancode[32][0],"\x03\x00"); //3
  strcpy(KbdScancode[32][1],"\x83\x00");
  strcpy(KbdScancode[33][0],"\x04\x00"); //4
  strcpy(KbdScancode[33][1],"\x84\x00");
  strcpy(KbdScancode[34][0],"\x05\x00"); //5
  strcpy(KbdScancode[34][1],"\x85\x00");
  strcpy(KbdScancode[35][0],"\x06\x00"); //6
  strcpy(KbdScancode[35][1],"\x86\x00");
  strcpy(KbdScancode[36][0],"\x07\x00"); //7
  strcpy(KbdScancode[36][1],"\x87\x00");
  strcpy(KbdScancode[37][0],"\x08\x00"); //8
  strcpy(KbdScancode[37][1],"\x88\x00");
  strcpy(KbdScancode[38][0],"\x09\x00"); //9
  strcpy(KbdScancode[38][1],"\x89\x00");
  strcpy(KbdScancode[39][0],"\x0A\x00"); //0
  strcpy(KbdScancode[39][1],"\x8A\x00");
  strcpy(KbdScancode[40][0],"\x44\x00"); //Enter
  strcpy(KbdScancode[40][1],"\xC4\x00");
  strcpy(KbdScancode[41][0],"\x45\x00"); //Esc
  strcpy(KbdScancode[41][1],"\xC5\x00");
  strcpy(KbdScancode[42][0],"\x41\x00"); //Backspace
  strcpy(KbdScancode[42][1],"\xC1\x00");
  strcpy(KbdScancode[43][0],"\x42\x00"); //Tab
  strcpy(KbdScancode[43][1],"\xC2\x00");
  strcpy(KbdScancode[44][0],"\x40\x00"); //Space
  strcpy(KbdScancode[44][1],"\xC0\x00");
  strcpy(KbdScancode[45][0],"\x0B\x00"); //Minus
  strcpy(KbdScancode[45][1],"\x8B\x00");
  strcpy(KbdScancode[46][0],"\x0C\x00"); //Equal
  strcpy(KbdScancode[46][1],"\x8C\x00");
  strcpy(KbdScancode[47][0],"\x1A\x00"); //Left brace
  strcpy(KbdScancode[47][1],"\x9A\x00");
  strcpy(KbdScancode[48][0],"\x1B\x00"); //right brace
  strcpy(KbdScancode[48][1],"\x9B\x00");
  strcpy(KbdScancode[49][0],"\x0D\x00"); //Backslash
  strcpy(KbdScancode[49][1],"\x8D\x00");
  strcpy(KbdScancode[50][0],"\x2B\x00"); //Hash+Tilde for Non-US
  strcpy(KbdScancode[50][1],"\xAB\x00");
  strcpy(KbdScancode[51][0],"\x29\x00"); //Semicolon
  strcpy(KbdScancode[51][1],"\xA9\x00");
  strcpy(KbdScancode[52][0],"\x2A\x00"); //Apostrophe
  strcpy(KbdScancode[52][1],"\xAA\x00");
  strcpy(KbdScancode[53][0],"\x00\x00"); //Grave and Tilde - Special handling required, Make Code 0x00!!!
  strcpy(KbdScancode[53][1],"\x80\x00");
  strcpy(KbdScancode[54][0],"\x38\x00"); //Comma
  strcpy(KbdScancode[54][1],"\xB8\x00");
  strcpy(KbdScancode[55][0],"\x39\x00"); //Dot
  strcpy(KbdScancode[55][1],"\xB9\x00");
  strcpy(KbdScancode[56][0],"\x3A\x00"); //Slash
  strcpy(KbdScancode[56][1],"\xBA\x00");
  strcpy(KbdScancode[57][0],"\x62\x00"); //Capslock
  strcpy(KbdScancode[57][1],"\xE2\x00");
  strcpy(KbdScancode[58][0],"\x50\x00"); //F1
  strcpy(KbdScancode[58][1],"\xD0\x00");
  strcpy(KbdScancode[59][0],"\x51\x00"); //F2
  strcpy(KbdScancode[59][1],"\xD1\x00");
  strcpy(KbdScancode[60][0],"\x52\x00"); //F3
  strcpy(KbdScancode[60][1],"\xD2\x00");
  strcpy(KbdScancode[61][0],"\x53\x00"); //F4
  strcpy(KbdScancode[61][1],"\xD3\x00");
  strcpy(KbdScancode[62][0],"\x54\x00"); //F5
  strcpy(KbdScancode[62][1],"\xD4\x00");
  strcpy(KbdScancode[63][0],"\x55\x00"); //F6
  strcpy(KbdScancode[63][1],"\xD5\x00");
  strcpy(KbdScancode[64][0],"\x56\x00"); //F7
  strcpy(KbdScancode[64][1],"\xD6\x00");
  strcpy(KbdScancode[65][0],"\x57\x00"); //F8
  strcpy(KbdScancode[65][1],"\xD7\x00");
  strcpy(KbdScancode[66][0],"\x58\x00"); //F9
  strcpy(KbdScancode[66][1],"\xD8\x00");
  strcpy(KbdScancode[67][0],"\x59\x00"); //F10
  strcpy(KbdScancode[67][1],"\xD9\x00");
  strcpy(KbdScancode[68][0],"\x00"); //F11
  strcpy(KbdScancode[68][1],"\x00");
  strcpy(KbdScancode[69][0],"\x00"); //F12
  strcpy(KbdScancode[69][1],"\x00");
  strcpy(KbdScancode[70][0],"\x00"); //SysReq/PrintScreen
  strcpy(KbdScancode[70][1],"\x00");
  strcpy(KbdScancode[71][0],"\x00"); //ScrollLock
  strcpy(KbdScancode[71][1],"\x00");
  strcpy(KbdScancode[72][0],"\x5F\x00"); //Pause/Break --> Help
  strcpy(KbdScancode[72][1],"\xDF\x00");
  strcpy(KbdScancode[73][0],"\x0D\x00"); //Insert --> Amiga Backslash/Pipe, which is not available on the keyboard on this position. Inverse T Insert not required on Amiga and closest key position
  strcpy(KbdScancode[73][1],"\x8D\x00");
  strcpy(KbdScancode[74][0],"\x00"); //Home
  strcpy(KbdScancode[74][1],"\x00");
  strcpy(KbdScancode[75][0],"\x5A\x00"); //PgUp -> Maps to KP open bracket as PC keyboards have different layout
  strcpy(KbdScancode[75][1],"\xDA\x00");
  strcpy(KbdScancode[76][0],"\x46\x00"); //Delete
  strcpy(KbdScancode[76][1],"\xC6\x00");
  strcpy(KbdScancode[77][0],"\x00"); //End
  strcpy(KbdScancode[77][1],"\x00");
  strcpy(KbdScancode[78][0],"\x5B\x00"); //PgDn -> Maps to KP closed bracket as PC keyboards have different layout
  strcpy(KbdScancode[78][1],"\xDB\x00");
  strcpy(KbdScancode[79][0],"\x4E\x00"); //Right
  strcpy(KbdScancode[79][1],"\xCE\x00");
  strcpy(KbdScancode[80][0],"\x4F\x00"); //Left
  strcpy(KbdScancode[80][1],"\xCF\x00");
  strcpy(KbdScancode[81][0],"\x4D\x00"); //Down
  strcpy(KbdScancode[81][1],"\xCD\x00");
  strcpy(KbdScancode[82][0],"\x4C\x00"); //Up
  strcpy(KbdScancode[82][1],"\xCC\x00");
  strcpy(KbdScancode[83][0],"\x00"); //Numlock ignored, does not exit on Amiga
  strcpy(KbdScancode[83][1],"\x00");
  strcpy(KbdScancode[84][0],"\x5C\x00"); //Keypad Slash
  strcpy(KbdScancode[84][1],"\xDC\x00");
  strcpy(KbdScancode[85][0],"\x5D\x00"); //Keypad Asterisk
  strcpy(KbdScancode[85][1],"\xDD\x00");
  strcpy(KbdScancode[86][0],"\x4A\x00"); //Keypad Minus
  strcpy(KbdScancode[86][1],"\xCA\x00");
  strcpy(KbdScancode[87][0],"\x5E\x00"); //Keypad Plus
  strcpy(KbdScancode[87][1],"\xDE\x00");
  strcpy(KbdScancode[88][0],"\x43\x00"); //Keypad Enter
  strcpy(KbdScancode[88][1],"\xC3\x00");
  strcpy(KbdScancode[89][0],"\x1D\x00"); //Keypad 1/End
  strcpy(KbdScancode[89][1],"\x9D\x00");
  strcpy(KbdScancode[90][0],"\x1E\x00"); //Keypad 2/Dn
  strcpy(KbdScancode[90][1],"\x9E\x00");
  strcpy(KbdScancode[91][0],"\x1F\x00"); //Keypad 3/PgDn
  strcpy(KbdScancode[91][1],"\x9F\x00");
  strcpy(KbdScancode[92][0],"\x2D\x00"); //Keypad 4/Left
  strcpy(KbdScancode[92][1],"\xAD\x00");
  strcpy(KbdScancode[93][0],"\x2E\x00"); //Keypad 5
  strcpy(KbdScancode[93][1],"\xAE\x00");
  strcpy(KbdScancode[94][0],"\x2F\x00"); //Keypad 6/Right
  strcpy(KbdScancode[94][1],"\xAF\x00");
  strcpy(KbdScancode[95][0],"\x3D\x00"); //Keypad 7/Home
  strcpy(KbdScancode[95][1],"\xBD\x00");
  strcpy(KbdScancode[96][0],"\x3E\x00"); //Keypad 8/Up
  strcpy(KbdScancode[96][1],"\xBE\x00");
  strcpy(KbdScancode[97][0],"\x3F\x00"); //Keypad 9/PgUp
  strcpy(KbdScancode[97][1],"\xBF\x00");
  strcpy(KbdScancode[98][0],"\x0F\x00"); //Keypad 0/Insert
  strcpy(KbdScancode[98][1],"\x8F\x00");
  strcpy(KbdScancode[99][0],"\x3C\x00"); //Keypad ./Delete 
  strcpy(KbdScancode[99][1],"\xBC\x00");
  strcpy(KbdScancode[100][0],"\x30\x00"); //INT 1 a.k.a. 102nd Key Backslash/Pipe Non-US
  strcpy(KbdScancode[100][1],"\xB0\x00"); 
  strcpy(KbdScancode[101][0],"\x67\x00"); //Windows Menu - mirrors Right Amiga, as some keyboards don't have a Right Windows
  strcpy(KbdScancode[101][1],"\xE7\x00"); 
  strcpy(KbdScancode[102][0],"\x63\x00"); //LeftCtrl - From here, misusing of untypical KbdScancodes like F13 onwards for modifier keys starts
  strcpy(KbdScancode[102][1],"\xE3\x00"); 
  strcpy(KbdScancode[103][0],"\x60\x00"); //LeftShift
  strcpy(KbdScancode[103][1],"\xE0\x00");
  strcpy(KbdScancode[104][0],"\x64\x00"); //LeftAlt
  strcpy(KbdScancode[104][1],"\xE4\x00");
  strcpy(KbdScancode[105][0],"\x66\x00"); //LeftMeta -> Left Amiga
  strcpy(KbdScancode[105][1],"\xE6\x00");
  strcpy(KbdScancode[106][0],"\x63\x00"); //RightCtrl - mirrors Left Ctrl as Amiga does not have Right Ctrl
  strcpy(KbdScancode[106][1],"\xE3\x00");
  strcpy(KbdScancode[107][0],"\x61\x00"); //RightShift
  strcpy(KbdScancode[107][1],"\xE1\x00");
  strcpy(KbdScancode[108][0],"\x65\x00"); //RightAlt/AltGr
  strcpy(KbdScancode[108][1],"\xE5\x00");
  strcpy(KbdScancode[109][0],"\x67\x00"); //RightMeta -> Right Amiga
  strcpy(KbdScancode[109][1],"\xE7\x00");
  strcpy(KbdScancode[110][0],"\xFD\x00"); //Reset Ack - Does not apply to this KbdScancode set
  strcpy(KbdScancode[110][1],"\xFE\x00");
  strcpy(KbdScancode[111][0],"\x00"); //Keyboard ID - Does not apply to this KbdScancode set
  strcpy(KbdScancode[111][1],"\x00");
  strcpy(KbdScancode[112][0],"\x00"); //Echo - Does not apply to this KbdScancode set
  strcpy(KbdScancode[112][1],"\x00");  
  strcpy(KbdScancode[113][0],"\x78\x00"); //Reset Warning
  strcpy(KbdScancode[113][1],"\x00");
}

void initScancodeApple()
{
  strcpy(KbdScancode[0][0],"\x00"); //No Key
  strcpy(KbdScancode[0][1],"\x00");
  strcpy(KbdScancode[1][0],"\x00"); //Keyboard Error
  strcpy(KbdScancode[1][1],"\x00");
  strcpy(KbdScancode[2][0],"\x00"); //POST Fail
  strcpy(KbdScancode[2][1],"\x00");  
  strcpy(KbdScancode[3][0],"\x00"); //undefined error
  strcpy(KbdScancode[3][1],"\x00");
  strcpy(KbdScancode[4][0],"\x00\x00"); //a Requires special handling, Scancode 00
  strcpy(KbdScancode[4][1],"\x00");
  strcpy(KbdScancode[5][0],"\x0B\x00"); //b
  strcpy(KbdScancode[5][1],"\x00");
  strcpy(KbdScancode[6][0],"\x08\x00"); //c
  strcpy(KbdScancode[6][1],"\x00");
  strcpy(KbdScancode[7][0],"\x02\x00"); //d
  strcpy(KbdScancode[7][1],"\x00");
  strcpy(KbdScancode[8][0],"\x0E\x00"); //e
  strcpy(KbdScancode[8][1],"\x00");
  strcpy(KbdScancode[9][0],"\x03\x00"); //f
  strcpy(KbdScancode[9][1],"\x00");
  strcpy(KbdScancode[10][0],"\x05\x00"); //g
  strcpy(KbdScancode[10][1],"\x00");
  strcpy(KbdScancode[11][0],"\x04\x00"); //h
  strcpy(KbdScancode[11][1],"\x00");
  strcpy(KbdScancode[12][0],"\x22\x00"); //i
  strcpy(KbdScancode[12][1],"\x00");
  strcpy(KbdScancode[13][0],"\x26\x00"); //j
  strcpy(KbdScancode[13][1],"\x00");
  strcpy(KbdScancode[14][0],"\x28\x00"); //k
  strcpy(KbdScancode[14][1],"\x00"); 
  strcpy(KbdScancode[15][0],"\x25\x00"); //l
  strcpy(KbdScancode[15][1],"\x00");
  strcpy(KbdScancode[16][0],"\x2E\x00"); //m
  strcpy(KbdScancode[16][1],"\x00");
  strcpy(KbdScancode[17][0],"\x2D\x00"); //n
  strcpy(KbdScancode[17][1],"\x00");
  strcpy(KbdScancode[18][0],"\x1F\x00"); //o
  strcpy(KbdScancode[18][1],"\x00");
  strcpy(KbdScancode[19][0],"\x23\x00"); //p
  strcpy(KbdScancode[19][1],"\x00");
  strcpy(KbdScancode[20][0],"\x0C\x00"); //q
  strcpy(KbdScancode[20][1],"\x00");
  strcpy(KbdScancode[21][0],"\x0F\x00"); //r
  strcpy(KbdScancode[21][1],"\x00");
  strcpy(KbdScancode[22][0],"\x01\x00"); //s
  strcpy(KbdScancode[22][1],"\x00");
  strcpy(KbdScancode[23][0],"\x11\x00"); //t
  strcpy(KbdScancode[23][1],"\x00");
  strcpy(KbdScancode[24][0],"\x20\x00"); //u
  strcpy(KbdScancode[24][1],"\x00");
  strcpy(KbdScancode[25][0],"\x09\x00"); //v
  strcpy(KbdScancode[25][1],"\x00");
  strcpy(KbdScancode[26][0],"\x0D\x00"); //w
  strcpy(KbdScancode[26][1],"\x00");
  strcpy(KbdScancode[27][0],"\x07\x00"); //x
  strcpy(KbdScancode[27][1],"\x00");
  strcpy(KbdScancode[28][0],"\x10\x00"); //y
  strcpy(KbdScancode[28][1],"\x00");
  strcpy(KbdScancode[29][0],"\x06\x00"); //z
  strcpy(KbdScancode[29][1],"\x00");
  strcpy(KbdScancode[30][0],"\x12\x00"); //1
  strcpy(KbdScancode[30][1],"\x00");
  strcpy(KbdScancode[31][0],"\x13\x00"); //2
  strcpy(KbdScancode[31][1],"\x00");
  strcpy(KbdScancode[32][0],"\x14\x00"); //3
  strcpy(KbdScancode[32][1],"\x00");
  strcpy(KbdScancode[33][0],"\x15\x00"); //4
  strcpy(KbdScancode[33][1],"\x00");
  strcpy(KbdScancode[34][0],"\x17\x00"); //5
  strcpy(KbdScancode[34][1],"\x00");
  strcpy(KbdScancode[35][0],"\x16\x00"); //6
  strcpy(KbdScancode[35][1],"\x00");
  strcpy(KbdScancode[36][0],"\x1A\x00"); //7
  strcpy(KbdScancode[36][1],"\x00");
  strcpy(KbdScancode[37][0],"\x1C\x00"); //8
  strcpy(KbdScancode[37][1],"\x00");
  strcpy(KbdScancode[38][0],"\x19\x00"); //9
  strcpy(KbdScancode[38][1],"\x00");
  strcpy(KbdScancode[39][0],"\x1D\x00"); //0
  strcpy(KbdScancode[39][1],"\x00");
  strcpy(KbdScancode[40][0],"\x24\x00"); //Enter
  strcpy(KbdScancode[40][1],"\x00");
  strcpy(KbdScancode[41][0],"\x35\x00"); //Esc
  strcpy(KbdScancode[41][1],"\x00");
  strcpy(KbdScancode[42][0],"\x33\x00"); //Backspace
  strcpy(KbdScancode[42][1],"\x00");
  strcpy(KbdScancode[43][0],"\x30\x00"); //Tab
  strcpy(KbdScancode[43][1],"\x00");
  strcpy(KbdScancode[44][0],"\x31\x00"); //Space
  strcpy(KbdScancode[44][1],"\x00");
  strcpy(KbdScancode[45][0],"\x1B\x00"); //Minus
  strcpy(KbdScancode[45][1],"\x00");
  strcpy(KbdScancode[46][0],"\x18\x00"); //Equal
  strcpy(KbdScancode[46][1],"\x00");
  strcpy(KbdScancode[47][0],"\x21\x00"); //Left brace
  strcpy(KbdScancode[47][1],"\x00");
  strcpy(KbdScancode[48][0],"\x1E\x00"); //right brace
  strcpy(KbdScancode[48][1],"\x00");
  strcpy(KbdScancode[49][0],"\x2A\x00"); //Backslash
  strcpy(KbdScancode[49][1],"\x00");
  strcpy(KbdScancode[50][0],"\x2A\x00"); //Hash+Tilde for Non-US
  strcpy(KbdScancode[50][1],"\x00");
  strcpy(KbdScancode[51][0],"\x29\x00"); //Semicolon
  strcpy(KbdScancode[51][1],"\x00");
  strcpy(KbdScancode[52][0],"\x27\x00"); //Apostrophe
  strcpy(KbdScancode[52][1],"\x00");
  strcpy(KbdScancode[53][0],"\x32\x00"); //Grave and Tilde
  strcpy(KbdScancode[53][1],"\x00");
  strcpy(KbdScancode[54][0],"\x2B\x00"); //Comma
  strcpy(KbdScancode[54][1],"\x00");
  strcpy(KbdScancode[55][0],"\x2F\x00"); //Dot
  strcpy(KbdScancode[55][1],"\x00");
  strcpy(KbdScancode[56][0],"\x2C\x00"); //Slash
  strcpy(KbdScancode[56][1],"\x00");
  strcpy(KbdScancode[57][0],"\x39\x00"); //Capslock
  strcpy(KbdScancode[57][1],"\x00");
  strcpy(KbdScancode[58][0],"\x7A\x00"); //F1
  strcpy(KbdScancode[58][1],"\x00");
  strcpy(KbdScancode[59][0],"\x78\x00"); //F2
  strcpy(KbdScancode[59][1],"\x00");
  strcpy(KbdScancode[60][0],"\x63\x00"); //F3
  strcpy(KbdScancode[60][1],"\x00");
  strcpy(KbdScancode[61][0],"\x76\x00"); //F4
  strcpy(KbdScancode[61][1],"\x00");
  strcpy(KbdScancode[62][0],"\x60\x00"); //F5
  strcpy(KbdScancode[62][1],"\x00");
  strcpy(KbdScancode[63][0],"\x61\x00"); //F6
  strcpy(KbdScancode[63][1],"\x00");
  strcpy(KbdScancode[64][0],"\x62\x00"); //F7
  strcpy(KbdScancode[64][1],"\x00");
  strcpy(KbdScancode[65][0],"\x64\x00"); //F8
  strcpy(KbdScancode[65][1],"\x00");
  strcpy(KbdScancode[66][0],"\x65\x00"); //F9
  strcpy(KbdScancode[66][1],"\x00");
  strcpy(KbdScancode[67][0],"\x6D\x00"); //F10
  strcpy(KbdScancode[67][1],"\x00");
  strcpy(KbdScancode[68][0],"\x67\x00"); //F11
  strcpy(KbdScancode[68][1],"\x00");
  strcpy(KbdScancode[69][0],"\x6F\x00"); //F12
  strcpy(KbdScancode[69][1],"\x00");
  strcpy(KbdScancode[70][0],"\x7F\x00"); //SysReq/PrintScreen -> Misused as Power / 0x69 would be PrintScreen/F13
  strcpy(KbdScancode[70][1],"\x00");
  strcpy(KbdScancode[71][0],"\x6B\x00"); //ScrollLock/F14
  strcpy(KbdScancode[71][1],"\x00");
  strcpy(KbdScancode[72][0],"\x71\x00"); //Pause/Break/F15
  strcpy(KbdScancode[72][1],"\x00");
  strcpy(KbdScancode[73][0],"\x72\x00"); //Insert/Help
  strcpy(KbdScancode[73][1],"\x00");
  strcpy(KbdScancode[74][0],"\x73\x00"); //Home
  strcpy(KbdScancode[74][1],"\x00");
  strcpy(KbdScancode[75][0],"\x74\x00"); //PgUp
  strcpy(KbdScancode[75][1],"\x00");
  strcpy(KbdScancode[76][0],"\x75\x00"); //Delete/Forward
  strcpy(KbdScancode[76][1],"\x00");
  strcpy(KbdScancode[77][0],"\x77\x00"); //End
  strcpy(KbdScancode[77][1],"\x00");
  strcpy(KbdScancode[78][0],"\x79\x00"); //PgDn
  strcpy(KbdScancode[78][1],"\x00");
  strcpy(KbdScancode[79][0],"\x3C\x00"); //Right
  strcpy(KbdScancode[79][1],"\x00");
  strcpy(KbdScancode[80][0],"\x3B\x00"); //Left
  strcpy(KbdScancode[80][1],"\x00");
  strcpy(KbdScancode[81][0],"\x3D\x00"); //Down
  strcpy(KbdScancode[81][1],"\x00");
  strcpy(KbdScancode[82][0],"\x3E\x00"); //Up
  strcpy(KbdScancode[82][1],"\x00");
  strcpy(KbdScancode[83][0],"\x47\x00"); //Numlock/Clear
  strcpy(KbdScancode[83][1],"\x00");
  strcpy(KbdScancode[84][0],"\x4B\x00"); //Keypad Slash
  strcpy(KbdScancode[84][1],"\x00");
  strcpy(KbdScancode[85][0],"\x43\x00"); //Keypad Asterisk
  strcpy(KbdScancode[85][1],"\x00");
  strcpy(KbdScancode[86][0],"\x4E\x00"); //Keypad Minus
  strcpy(KbdScancode[86][1],"\x00");
  strcpy(KbdScancode[87][0],"\x45\x00"); //Keypad Plus
  strcpy(KbdScancode[87][1],"\x00");
  strcpy(KbdScancode[88][0],"\x4C\x00"); //Keypad Enter
  strcpy(KbdScancode[88][1],"\x00");
  strcpy(KbdScancode[89][0],"\x53\x00"); //Keypad 1/End
  strcpy(KbdScancode[89][1],"\x00");
  strcpy(KbdScancode[90][0],"\x54\x00"); //Keypad 2/Dn
  strcpy(KbdScancode[90][1],"\x00");
  strcpy(KbdScancode[91][0],"\x55\x00"); //Keypad 3/PgDn
  strcpy(KbdScancode[91][1],"\x00");
  strcpy(KbdScancode[92][0],"\x56\x00"); //Keypad 4/Left
  strcpy(KbdScancode[92][1],"\x00");
  strcpy(KbdScancode[93][0],"\x57\x00"); //Keypad 5
  strcpy(KbdScancode[93][1],"\x00");
  strcpy(KbdScancode[94][0],"\x58\x00"); //Keypad 6/Right
  strcpy(KbdScancode[94][1],"\x00");
  strcpy(KbdScancode[95][0],"\x59\x00"); //Keypad 7/Home
  strcpy(KbdScancode[95][1],"\x00");
  strcpy(KbdScancode[96][0],"\x5B\x00"); //Keypad 8/Up
  strcpy(KbdScancode[96][1],"\x00");
  strcpy(KbdScancode[97][0],"\x5C\x00"); //Keypad 9/PgUp
  strcpy(KbdScancode[97][1],"\x00");
  strcpy(KbdScancode[98][0],"\x52\x00"); //Keypad 0/Insert
  strcpy(KbdScancode[98][1],"\x00");
  strcpy(KbdScancode[99][0],"\x41\x00"); //Keypad ./Delete 
  strcpy(KbdScancode[99][1],"\x00");
  strcpy(KbdScancode[100][0],"\x0A\x00"); //INT 1 a.k.a. 102nd Key Backslash/Pipe Non-US
  strcpy(KbdScancode[100][1],"\x00"); 
  strcpy(KbdScancode[101][0],"\0x51\x00"); //Windows Menu -> Maps to Keypad = which is not available on PC keyboards. No need to mirror the command key
  strcpy(KbdScancode[101][1],"\x00"); 
  strcpy(KbdScancode[102][0],"\x36\x00"); //LeftCtrl - From here, misusing of untypical KbdScancodes like F13 onwards for modifier keys starts
  strcpy(KbdScancode[102][1],"\x00"); 
  strcpy(KbdScancode[103][0],"\x38\x00"); //LeftShift
  strcpy(KbdScancode[103][1],"\x00");
  strcpy(KbdScancode[104][0],"\x3A\x00"); //LeftAlt/LeftOption
  strcpy(KbdScancode[104][1],"\x00");
  strcpy(KbdScancode[105][0],"\x37\x00"); //LeftMeta -> Command
  strcpy(KbdScancode[105][1],"\x00");
  strcpy(KbdScancode[106][0],"\x7D\x00"); //RightCtrl
  strcpy(KbdScancode[106][1],"\x00");
  strcpy(KbdScancode[107][0],"\x7B\x00"); //RightShift
  strcpy(KbdScancode[107][1],"\x00");
  strcpy(KbdScancode[108][0],"\x7C\x00"); //RightAlt/AltGr/RightOption
  strcpy(KbdScancode[108][1],"\x00");
  strcpy(KbdScancode[109][0],"\x37\x00"); //RightMeta -> Command (mirrored, as on Apple Keyboard)
  strcpy(KbdScancode[109][1],"\x00");
  strcpy(KbdScancode[110][0],"\x00"); //Reset Ack - Does not apply to this KbdScancode set
  strcpy(KbdScancode[110][1],"\x00");
  strcpy(KbdScancode[111][0],"\x00"); //Keyboard ID - Does not apply to this KbdScancode set
  strcpy(KbdScancode[111][1],"\x00");
  strcpy(KbdScancode[112][0],"\x00"); //Echo - Does not apply to this KbdScancode set
  strcpy(KbdScancode[112][1],"\x00");  
  strcpy(KbdScancode[113][0],"\x00"); //Current KbdScancode Set - Does not apply to this KbdScancode set
  strcpy(KbdScancode[113][1],"\x00");
}

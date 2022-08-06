#include "debugmsg.h"
#include <Arduino.h>

int debugMessage=1;

void debugSetup()
{
  if (debugMessage) {
    Serial.begin( 115200 );
    while (!Serial); 
    Serial.println("Start");    
  }
}

/*
  LCDdisplay.h - Library for display things.
  Created by Maxime MERKLEN, April 20 2021.
*/

#ifndef LCDdisplay_h
#define LCDdisplay_h

#include "Arduino.h"
//#include "string.h"


class LCDdisplay
{
  public:
    LCDdisplay();
    void displayTemp(float t, float h);
    void displayERROR(String error);
  private:
};

#endif

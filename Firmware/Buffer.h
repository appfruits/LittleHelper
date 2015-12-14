/*
 * Little Helper -- your best friend in your lab
 * http://www.appfruits.com/littlehelper
 *
 * This software is part of the firmware running Little Helper. You may use, copy, 
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software 
 * but you must include this copyright notice and this permission in all copies or 
 * substantial portions of the Software.
 *
 * Appfruits invests time and resources to make this open source. Please support us
 * and the open-source hardware initiative.
 * 
 * Copyright 2014-2015 Phillip Schuster (@appfruits)
 * http://www.appfruits.com
 * 
 * MIT-License
 */

#ifndef _BUFFER_H_
#define _BUFFER_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Wire.h>

struct Line {
public:
  char buffer[22];
  
  Line()
  {
    memset(buffer,0,sizeof(buffer)); 
  }
  
  Line(const char* line) 
  {
    strcpy(buffer,line);
  }
};

class History
{
public:
  History();
  void addLine(const char* line);
  uint16_t numberOfLines();
  const char* getLine(uint16_t index);
  
private:
  Line _lines[500];
  uint16_t _currentLine;
  uint16_t _numberOfLines;
};

#endif


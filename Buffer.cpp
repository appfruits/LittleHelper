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

#include "Buffer.h"

History::History()
{
  _currentLine = 0;
  _numberOfLines = 0;
}

void History::addLine(const char* message)
{
  uint16_t len = strlen(message);
  uint16_t numberOfLines = (uint16_t)len/21;
  for (uint16_t i=0;i<=numberOfLines;i++)
  {
    Line* line = &_lines[_currentLine];
    memset(line->buffer,0,sizeof(line->buffer));
    
    const char* start = message+(i*sizeof(char)*21);
    const char* end = start + (sizeof(char)*21);
    uint16_t length = (int)end - (int)start;
    if (((int)end-(int)message) > len)
    {
       length = ((int)end-(int)message) - len;
    }
    
    memcpy(line->buffer,start,length);
    
    _currentLine++;
    if (_currentLine > 499)
    {
      _currentLine = 0;
    }
    else
    {
       _numberOfLines++; 
    }
  }
}

uint16_t History::numberOfLines()
{
   return _numberOfLines; 
}

const char* History::getLine(uint16_t index)
{
  if (index > _numberOfLines) return "";
  return _lines[index].buffer;
}

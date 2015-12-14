//
// Created by Phillip Schuster on 27.03.15.
//

#ifndef _TEENSYCMAKE_DEBUG_H_
#define _TEENSYCMAKE_DEBUG_H_

#include "Arduino.h"
#include <usb_serial.h>

class Appfruits_Debug: public usb_serial_class
{

};

extern Appfruits_Debug Debug;


#endif //_TEENSYCMAKE_DEBUG_H_

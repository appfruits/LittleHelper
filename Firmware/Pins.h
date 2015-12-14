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

#ifndef TEENSYCMAKE_PINS_H
#define TEENSYCMAKE_PINS_H

#include <stdint-gcc.h>
#include "Arduino.h"

#define EXT_PIN_3 3
#define EXT_PIN_2 24
#define EXT_PIN_1 A14
#define EXT_PIN_DAC A14

#define PIN_3V3 4
#define PIN_DAC 3
#define PIN_GND 0

class Pin
{
public:
	Pin(String name, uint16_t color, uint8_t hardwareId) {
		this->_name = name;
		this->_color = color;
		this->_hardwareId = hardwareId;
		this->_active = false;
	}

	bool isActive();
	void setActive(bool active);
	void setName(String name);
	String getName();
	uint8_t getHardwareId();
	uint16_t getColor();

	void setPinMode(uint8_t thePinMode);
	int analogRead();

private:
	String _name;
	uint16_t _color;
	uint8_t _hardwareId;
	bool _active;
};


class PinsClass
{
public:
	PinsClass();

	Pin* getPin(int8_t pos);
	void setPinName(int8_t pos, String name);
	void activatePin(int8_t pos, String name);
	void setPinActive(int8_t pos, bool active);
	bool isPinActive(int8_t pos);
	uint8_t getPinId(int8_t pos);
	void resetPins();

private:
	Pin _pins[5];
};

extern PinsClass Pins;


#endif //TEENSYCMAKE_PINS_H

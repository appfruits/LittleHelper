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

#include "Pins.h"
#include "Application.h"

PinsClass Pins;

bool Pin::isActive()
{
    return _active;
}

void Pin::setActive(bool active)
{
    if (_active == active) return;
    _active = active;

    Application.onPinChanged();
}

String Pin::getName()
{
    return _name;
}

void Pin::setName(String name)
{
    _name = name;
    Application.onPinChanged();
}

uint8_t Pin::getHardwareId()
{
    return _hardwareId;
}

uint16_t Pin::getColor()
{
    return _color;
}

void Pin::setPinMode(uint8_t thePinMode)
{
    pinMode(this->getHardwareId(),thePinMode);
}

int Pin::analogRead()
{
    return ::analogRead(this->getHardwareId());
}

PinsClass::PinsClass():
    _pins({
          Pin("GND",RGB565(0,0,0),0),
          Pin("",Application.getTheme()->getComplementColor(ColorTheme::Shade::Darker),A14),
          Pin("",Application.getTheme()->getSecondaryColor2(ColorTheme::Shade::Darker),24),
          Pin("",Application.getTheme()->getSecondaryColor1(ColorTheme::Shade::Darker),3),
          Pin("3V3",RGB565(255,0,0),0)
    })
{
}

Pin* PinsClass::getPin(int8_t pos)
{
    if (pos < 0) pos = 0;
    if (pos > 4) pos = 4;

    return &_pins[pos];
}

void PinsClass::activatePin(int8_t pos, String name)
{
    Pin* pin = this->getPin(pos);
    pin->setActive(true);
    pin->setName(name);
}

void PinsClass::setPinActive(int8_t pos, bool active)
{
    Pin* pin = this->getPin(pos);
    pin->setActive(active);
}

void PinsClass::setPinName(int8_t pos, String name)
{
    Pin* pin = this->getPin(pos);
    pin->setName(name);
}

bool PinsClass::isPinActive(int8_t pos)
{
    Pin* pin = this->getPin(pos);
    return pin->isActive();
}

uint8_t PinsClass::getPinId(int8_t pos)
{
    return this->getPin(pos)->getHardwareId();
}

void PinsClass::resetPins()
{
    for (uint8_t i=0;i<5;i++)
    {
        _pins[i].setActive(false);
    }
}
//
// Created by Phillip Schuster on 26.03.15.
//

#ifndef _TEENSYCMAKE_BUTTON_H_
#define _TEENSYCMAKE_BUTTON_H_

#include "Arduino.h"

class Appfruits_Button
{
public:
    Appfruits_Button(uint8_t pin);

    bool buttonPressed();
    bool buttonUp();
    bool buttonClicked();
    uint32_t getClickLength();     //TODO: uint32_t is a bit oversized
    uint32_t getButtonDownTime();
    void begin();

    void update();

private:
    uint32_t _buttonDownTime;
    uint8_t _pin;
    bool _clicked;
    bool _lastState;
    uint32_t _clickLength;
};


#endif //_TEENSYCMAKE_BUTTON_H_

//
// Created by Phillip Schuster on 26.03.15.
//

#include "Appfruits_Button.h"
#include "Application.h"

Appfruits_Button::Appfruits_Button(uint8_t pin)
{
    _pin = pin;
}

void Appfruits_Button::begin()
{
    pinMode(_pin,INPUT);
}

void Appfruits_Button::update()
{
    _clicked = false;
    _lastState = digitalRead(_pin);

    if (_lastState == LOW)
    {
        if (_buttonDownTime == 0)
        {
            _buttonDownTime = millis();
        }
    }
    else
    {
        if (_buttonDownTime > 0)
        {
            LOG("Button clicked");
            _clicked = true;
            _clickLength = millis() - _buttonDownTime;
        }

        _buttonDownTime = 0;
    }
}

bool Appfruits_Button::buttonClicked()
{
    return _clicked;
}

bool Appfruits_Button::buttonPressed()
{
    return (_lastState == LOW);
}

bool Appfruits_Button::buttonUp()
{
    return (_lastState == HIGH);
}

uint32_t Appfruits_Button::getClickLength()
{
    return _clickLength;
}

uint32_t Appfruits_Button::getButtonDownTime()
{
    if (_buttonDownTime == 0) return 0;
    return millis() - _buttonDownTime;
}
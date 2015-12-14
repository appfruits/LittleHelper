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

#include "TouchWheel.h"
#include "Application.h"

TouchWheel::TouchWheel(Appfruits_QTouch* driver)
{
	this->_driver = driver;
	this->_driver->setDelegate(this);
	this->resetStates();
}

void TouchWheel::begin()
{
	this->_driver->begin();
	this->_driver->enableWheel();
	this->_driver->setDetectThreshold(0,41);
	this->_driver->setDetectThreshold(1,41);
	this->_driver->setDetectThreshold(2,41);
	this->_driver->setDetectionIntegrator(3);
}

void TouchWheel::update()
{
	this->resetStates();

	if (this->_driver->eventAvailable())
	{
		if (this->_driver->wheelDetected())
		{
			this->_sliderDelta = this->_driver->sliderDelta();
		}
	}
}

void TouchWheel::resetStates()
{
	for (int i=0;i<4;i++)
	{
		this->_button[i] = 0;
	}

	this->_sliderDelta = 0;
	this->_sliderPos = 0;
}

bool TouchWheel::isButtonReleased(Direction direction)
{
	return (this->_button[direction] > 0);
}

bool TouchWheel::isSliding()
{
	return this->_sliding;
}

int8_t TouchWheel::getSliderDelta()
{
	return this->_sliderDelta;
}

uint8_t TouchWheel::getSliderPosition()
{
	return this->_sliderPos;
}

void TouchWheel::onTouchLeftButtonPressed(uint32_t duration)
{
	_button[Direction::Left] = duration;
}

void TouchWheel::onTouchTopButtonPressed(uint32_t duration)
{
	_button[Direction::Top] = duration;
}

void TouchWheel::onTouchRightButtonPressed(uint32_t duration)
{
	_button[Direction::Right] = duration;
}

void TouchWheel::onTouchBottomButtonPressed(uint32_t duration)
{
	_button[Direction::Bottom] = duration;
}

void TouchWheel::onSlider(uint8_t sliderPos, int8_t sliderDelta)
{
	//LOG_VALUE("Slider detected",sliderDelta);
	this->_sliderPos = sliderPos;
	this->_sliderDelta = sliderDelta;

	this->_sliding = true;
}

void TouchWheel::onTouchDown()
{
	this->_touching = true;
}

void TouchWheel::onTouchUp(uint32_t duration)
{
	this->_touching = false;
}

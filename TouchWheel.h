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

#ifndef _TEENSYCMAKE_TOUCHWHEEL_H_
#define _TEENSYCMAKE_TOUCHWHEEL_H_

#include <Arduino.h>
#include <stdint-gcc.h>
#include "Appfruits_QTouch.h"

class TouchWheel: public Appfruits_QTouch_Delegate
{
public:
	typedef enum Direction {
		Left = 0,
		Top = 1,
		Right = 2,
		Bottom = 3
	} Direction;

	TouchWheel(Appfruits_QTouch* driver);

	void begin();
	void update();
	bool isButtonReleased(Direction direction);
	bool isSliding();
	int8_t getSliderDelta();
	uint8_t getSliderPosition();

private:
	bool _sliding;
	bool _touching;
	uint8_t _sliderDelta;
	uint8_t _sliderPos;
	Appfruits_QTouch* _driver;

	void resetStates();

	uint32_t _button[4];
	uint32_t _touchStart;

	virtual void onTouchLeftButtonPressed(uint32_t duration) override;
	virtual void onTouchTopButtonPressed(uint32_t duration) override;
	virtual void onTouchRightButtonPressed(uint32_t duration) override;
	virtual void onTouchBottomButtonPressed(uint32_t duration) override;
	virtual void onSlider(uint8_t sliderPos, int8_t sliderDelta) override;
	virtual void onTouchDown() override;
	virtual void onTouchUp(uint32_t duration) override;
};


#endif //_TEENSYCMAKE_TOUCHWHEEL_H_

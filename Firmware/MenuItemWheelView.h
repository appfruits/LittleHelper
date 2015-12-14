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

#ifndef _TEENSYCMAKE_MENUITEMWHEELVIEW_H_
#define _TEENSYCMAKE_MENUITEMWHEELVIEW_H_

#include "MenuItemView.h"

class MenuItemWheelView: public MenuItemView
{
public:
	MenuItemWheelView(String title, MenuItemViewDelegate* delegate);
	MenuItemWheelView(String title, MenuItemViewDelegate* delegate, void* object);

	virtual void handleEvents() override;

	void setMinValue(float minValue);
	void setMaxValue(float maxValue);
	void setScale(float scale);
	void setLimits(float minValue, float maxValue);
	float getValue();
	void setValue(float value);
	void setTitle(String title);

private:
	float _touchWheelOffset;
	bool _lastButtonState;
	float _minValue;
	float _maxValue;
	float _scale;
	float _value;

public:
	virtual void draw() override;

	virtual bool needsFocus() override;

	virtual void onClicked() override;

public:
	virtual String getDescription() override;
};


#endif //_TEENSYCMAKE_MENUITEMWHEELVIEW_H_

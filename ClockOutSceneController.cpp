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

#include "ClockOutSceneController.h"
#include "MenuItemWheelView.h"
#include "MenuItemEnumView.h"

ClockOutSceneController::ClockOutSceneController():
		SceneController(),
		_menuView("Options",MINX,MAXY-60,MAXW,58),
		_pwmPreviewView(MINX,MINY,MAXW,55)
{
	MenuItemEnumView* frequencyControl = new MenuItemEnumView("Frequency", this);
	frequencyControl->addItem(488,"488 Hz");
	frequencyControl->addItem(1000,"1 KHz");
	frequencyControl->addItem(1000000,"1 MHz");
	frequencyControl->addItem(2000000,"2 MHz");
	frequencyControl->addItem(4000000,"4 MHz");
	frequencyControl->addItem(8000000,"8 MHz");
	frequencyControl->addItem(12000000,"12 MHz");

	_duty = 0.5f;
	MenuItemWheelView* dutyControl = new MenuItemWheelView("Duty", this);
	dutyControl->setLimits(0,1);
	dutyControl->setScale(0.1f);
	dutyControl->setValue(_duty);

	_menuView.addMenuItem(frequencyControl);
	_menuView.addMenuItem(dutyControl);
	_menuView.setVisible(true);
	_menuView.setSelectedItemIndex(1);

	_pwmPreviewView.setFrequency(2);
	_pwmPreviewView.setDuty(_duty);

	_firstUpdate = true;
}

void ClockOutSceneController::onWillAppear()
{
	SceneController::onWillAppear();

	_menuView.setFocus();
	Application.getStatusBar()->setCaption("PWM");
	_pwmPreviewView.setNeedsDisplay();

	//Activate pin
	pinMode(EXT_PIN_3, OUTPUT);
	analogWrite(EXT_PIN_3, _duty * 255);

	Pins.activatePin(1,true);
}

void ClockOutSceneController::loop()
{
	SceneController::loop();

	_pwmPreviewView.update();
	_menuView.update();
}

void ClockOutSceneController::menuItemViewValueChanged(MenuItemView *menuItemView, float value)
{
	if (menuItemView->getTitle() == "Frequency")
	{
		_pwmPreviewView.setFrequency(value);
		analogWriteFrequency(EXT_PIN_3,value);
		analogWrite(EXT_PIN_3,_duty*255);
		_frequency = value;
	}
	else if (menuItemView->getTitle() == "Duty")
	{
		_pwmPreviewView.setDuty(value);
		analogWrite(EXT_PIN_3,value*255);
		_duty = value;
	}
}

String ClockOutSceneController::getName()
{
	return "Clock-Out";
}

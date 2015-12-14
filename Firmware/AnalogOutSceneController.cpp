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

#include "AnalogOutSceneController.h"
#include "MenuItemEnumView.h"
#include "MenuItemWheelView.h"

AnalogOutSceneController::AnalogOutSceneController():
		SceneController(),
		_waveformView(MINX,MINY,MAXW,55),
		_menuView("Options",MINX,MAXY-60,MAXW,58)
{
	MenuItemEnumView* frequencyControl = new MenuItemEnumView("Waveform", this);
	frequencyControl->addItem(0,"Steady");
	frequencyControl->addItem(1,"Sinus");
	frequencyControl->addItem(2,"Cosinus");
	frequencyControl->addItem(3,"Square");

	MenuItemWheelView* dutyControl = new MenuItemWheelView("Frequency", this);
	dutyControl->setLimits(0,1000);
	dutyControl->setScale(0.1f);
	dutyControl->setValue(1);

	_menuView.addMenuItem(frequencyControl);
	_menuView.addMenuItem(dutyControl);
	_menuView.setVisible(true);
	_menuView.setSelectedItemIndex(1);
}

void AnalogOutSceneController::onWillAppear()
{
	SceneController::onWillAppear();

	_menuView.setFocus();
	Application.getStatusBar()->setCaption("Analog Out");
	_waveformView.setNeedsDisplay();

	//Activate pin
//	pinMode(EXT_PIN_DAC, OUTPUT);
//	analogWrite(EXT_PIN_DAC, _duty * 255);

	Pins.activatePin(PIN_DAC,true);
}

void AnalogOutSceneController::loop()
{
	SceneController::loop();

	_waveformView.update();
	_menuView.update();
}

String AnalogOutSceneController::getName()
{
	return "Analog-Out";
}

void AnalogOutSceneController::menuItemViewValueChanged(MenuItemView *menuItemView, float value)
{
	if (menuItemView->getTitle() == "Frequency")
	{
		_waveformView.setXScale(value);
	}
}
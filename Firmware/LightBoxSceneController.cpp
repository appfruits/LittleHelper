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

#include "LightBoxSceneController.h"
#include "MenuItemWheelView.h"

LightBoxSceneController::LightBoxSceneController():
		_pinDescriptionView(MINX,MINY,MAXW,MAXH-40),
		_menuView("Options",MINX,MAXY-26,MAXW,26),
		_intro(true),
		_settingsMenuView("Settings",MINX,MINY,MAXW,MAXY-35),
		_button("Let's go",this),
		_i2c(24,3)
{
	LOG("LightBoxSceneController Constructor");
	_menuView.addMenuItem(&_button);

	_settings.r = _settings.b = _settings.g = 128;
	_settings.currentSlot = 10;
	_settings.scale = 0.1f;

	MenuItemWheelView* currentSlot = new MenuItemWheelView("Slot", this);
	currentSlot->setLimits(0,31);
	currentSlot->setScale(0.1f);

	_currentSlotMenuItem = new MenuItemWheelView("Slot",this);
	_currentSlotMenuItem->setLimits(0,31);
	_currentSlotMenuItem->setScale(1);
	_settingsMenuView.addMenuItem(_currentSlotMenuItem);

	_rMenuItem = new MenuItemWheelView("Red",this);
	_rMenuItem->setLimits(0,255);
	_rMenuItem->setScale(1);
	_settingsMenuView.addMenuItem(_rMenuItem);

	_gMenuItem = new MenuItemWheelView("Green",this);
	_gMenuItem->setLimits(0,255);
	_gMenuItem->setScale(1);
	_settingsMenuView.addMenuItem(_gMenuItem);

	_bMenuItem = new MenuItemWheelView("Blue",this);
	_bMenuItem->setLimits(0,255);
	_bMenuItem->setScale(1);
	_settingsMenuView.addMenuItem(_bMenuItem);

	_scaleMenuItem = new MenuItemWheelView("Scale",this);
	_scaleMenuItem->setLimits(0,10);
	_scaleMenuItem->setScale(0.1);
	_settingsMenuView.addMenuItem(_scaleMenuItem);

	//Setup Pins
	Pins.activatePin(PIN_GND,"GND");
	Pins.activatePin(3,"A4 (SDA)");
	Pins.activatePin(2,"A5 (SCL)");

	//_i2c.setPins(Pins.getPin(3)->getHardwareId(),Pins.getPin(2)->getHardwareId());

	updateUI();
}

LightBoxSceneController::~LightBoxSceneController()
{
}

void LightBoxSceneController::loop()
{
	SceneController::loop();

	_pinDescriptionView.update();
	_menuView.update();
	_settingsMenuView.update();
}

void LightBoxSceneController::updateUI()
{
	if (_intro)
	{
		_pinDescriptionView.setVisible(true);
		_settingsMenuView.setVisible(false);
		_menuView.setVisible(true);

		_menuView.setFocus();
	}
	else
	{
		_currentSlotMenuItem->setValue(_settings.currentSlot);
		_rMenuItem->setValue(_settings.r);
		_gMenuItem->setValue(_settings.g);
		_bMenuItem->setValue(_settings.b);
		_scaleMenuItem->setValue(_settings.scale);

		_pinDescriptionView.setVisible(false);
		_settingsMenuView.setVisible(true);
		_menuView.setVisible(false);

		_settingsMenuView.setFocus();
	}
}

void LightBoxSceneController::onWillAppear()
{
	SceneController::onWillAppear();

	Application.getStatusBar()->setCaption("Lightbox");
	this->updateUI();
}

String LightBoxSceneController::getName()
{
	return "Lightbox";
}

void LightBoxSceneController::menuItemViewTriggered(MenuItemView *menuItemView)
{
	if (_intro)
	{
		_intro = false;
		updateUI();
	}
	else
	{

	}
}

void LightBoxSceneController::sendData()
{
	LOG("Sending data");
	LOG_VALUE("Current-Slot",_settings.currentSlot);
	_i2c.beginTransmission(4);
	_i2c.write((uint8_t*)&_settings,sizeof(LightboxSettings));
	_i2c.endTransmission();

/*	pinMode(3,OUTPUT);
	for (int i=0;i<100;i++)
	{
		digitalWrite(3,HIGH);
		delay(1);
		digitalWrite(3,LOW);
		delay(3);
	}*/
}

void LightBoxSceneController::menuItemViewValueChanged(MenuItemView *menuItemView, float value)
{
	if (menuItemView == _currentSlotMenuItem)
	{
		_settings.currentSlot = value;
	}
	else if (menuItemView == _rMenuItem)
	{
		_settings.r = value;
	}
	else if (menuItemView == _gMenuItem)
	{
		_settings.g = value;
	}
	else if (menuItemView == _bMenuItem)
	{
		_settings.b = value;
	}
	else if (menuItemView == _scaleMenuItem)
	{
		_settings.scale = value;
	}

	sendData();
}

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

#include "I2CScannerSceneController.h"
#include "MenuItemButtonView.h"
#include "LabelView.h"

#define PIN_INFO 0
#define SCANNING 1
#define SHOWRESULTS 2

I2CScannerSceneController::I2CScannerSceneController():
	_progressBar(MINX+20,MINY+25,MAXW-40,10),
	_scanningLabel("Scanning",MINX,MINY+10,MAXW,10),
	_pinDescriptionView(MINX,MINY,MAXW,MAXH-40),
	_menuView("Options",MINX,MAXY-26,MAXW,26),
	_button("Let's go",this),
	_state(State::PinInfo),
	_devicesFoundLabel("0",MINX+20,MINY+40,MAXW-40,20),
	_resultList("Results",MINX,MINY,MAXW,MAXH)
{
	_scanningLabel.setTextAlign(TEXTALIGN_CENTERED);
	_devicesFoundLabel.setTextAlign(TEXTALIGN_CENTERED);
	_devicesFoundLabel.setFont(ARIAL_16);

	_progressBar.setValue(0.3);

	_menuView.addMenuItem(&_button);

	//Setup Pins
	Pins.activatePin(PIN_GND,"GND");
	Pins.activatePin(1,"SCL");
	Pins.activatePin(2,"SDA");

	setState(State::PinInfo);
}

I2CScannerSceneController::~I2CScannerSceneController()
{
	leds.setPixelColor(1,80,80,0);
	leds.show();

}

bool I2CScannerSceneController::scanAddress(uint8_t address)
{
	Wire.beginTransmission(address);
	byte error = Wire.endTransmission();

	//TODO: Handle I2C error
	if (error == 0 || error == 4)
	{
		_devicesFound[_numDevicesFound] = address;
		_numDevicesFound++;
	}

	return true;
}

void I2CScannerSceneController::loop()
{
	SceneController::loop();

	if (_state == State::Scanning)
	{
		_progressBar.setValue((float)_currentAddress/127.0f);

		if (scanAddress(_currentAddress))
		{
			_devicesFoundLabel.setText(_numDevicesFound);
		}

		_currentAddress++;
		if (_currentAddress > 127)
		{
			endScan();
		}
	}

	_progressBar.update();
	_scanningLabel.update();
	_devicesFoundLabel.update();

	_pinDescriptionView.update();
	_menuView.update();

	_resultList.update();
}

void I2CScannerSceneController::updateUI()
{
	if (_state == I2CScannerSceneController::State::PinInfo)
	{
		_pinDescriptionView.setVisible(true);
		_resultList.setVisible(false);

		_progressBar.setVisible(false);
		_scanningLabel.setVisible(false);
		_devicesFoundLabel.setVisible(false);

		_button.setTitle("Let's start");

		_menuView.setVisible(true);
		_menuView.setFocus();
	}
	else if (_state == I2CScannerSceneController::State::Scanning)
	{
		_pinDescriptionView.setVisible(false);
		_resultList.setVisible(false);

		_progressBar.setVisible(true);
		_scanningLabel.setVisible(true);
		_devicesFoundLabel.setVisible(true);

		_button.setTitle("Cancel");

		_menuView.setVisible(true);
		_menuView.setFocus();

		_progressBar.setValue(0);
	}
	else if (_state == I2CScannerSceneController::State::Results)
	{
		_pinDescriptionView.setVisible(false);
		_resultList.setVisible(true);

		_progressBar.setVisible(false);
		_scanningLabel.setVisible(false);
		_devicesFoundLabel.setVisible(false);

		_menuView.setVisible(false);

		_resultList.setFocus();
	}
}

void I2CScannerSceneController::setState(I2CScannerSceneController::State state)
{
	_state = state;

	updateUI();
}

void I2CScannerSceneController::onWillAppear()
{
	SceneController::onWillAppear();

	Application.getStatusBar()->setCaption("I2C Scan");
	setState(State::PinInfo);
}

String I2CScannerSceneController::getName()
{
	return "I2CScanner";
}

void I2CScannerSceneController::startScan()
{
	_button.setTitle("Cancel");

	setState(I2CScannerSceneController::State::Scanning);
	_currentAddress = 1;
	_numDevicesFound = 0;
}

void I2CScannerSceneController::endScan()
{
	for (int i=0;i<_numDevicesFound;i++)
	{
		String itemText = String("0x") + String(_devicesFound[i],HEX) + String(" (") + _devicesFound[i] + String(")");
		MenuItemButtonView* listItem = new MenuItemButtonView(itemText,this);
		listItem->setTag(_devicesFound[i]);

		_resultList.addMenuItem(listItem);
	}

	setState(State::Results);
}

void I2CScannerSceneController::menuItemViewTriggered(MenuItemView *menuItemView)
{
	if (_state == State::PinInfo)
	{
		startScan();
	}
	else if (_state == State::Scanning)
	{
		setState(State::PinInfo);
	}
	else if (_state == State::Results)
	{
		setState(State::PinInfo);
	}
}

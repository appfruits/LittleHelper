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

#ifndef TEENSYCMAKE_I2CSCANNER_H
#define TEENSYCMAKE_I2CSCANNER_H

#include "SceneController.h"
#include "ProgressBar.h"
#include "PinDescriptionView.h"
#include "MenuView.h"
#include "MenuItemView.h"
#include "LabelView.h"
#include "MenuItemButtonView.h"

class I2CScannerSceneController: public SceneController, MenuItemViewDelegate
{
public:
	I2CScannerSceneController();
	~I2CScannerSceneController();

	virtual void loop() override;

public:
	virtual void onWillAppear() override;
	virtual String getName() override;

private:
	typedef enum State {
		PinInfo = 0,
		Scanning = 1,
		Results = 2
	} State;

	ProgressBar _progressBar;
	PinDescriptionView _pinDescriptionView;
	MenuView _menuView;
	LabelView _scanningLabel;
	MenuItemButtonView _button;
	uint8_t _currentAddress;
	LabelView _devicesFoundLabel;
	uint8_t _devicesFound[8];
	uint8_t _numDevicesFound;
	MenuView _resultList;
	I2CScannerSceneController::State _state;

	virtual void menuItemViewTriggered(MenuItemView *menuItemView) override;
	void startScan();
	void endScan();
	bool scanAddress(uint8_t address);
	void setState(I2CScannerSceneController::State state);

	void updateUI();
};


#endif //TEENSYCMAKE_I2CSCANNER_H

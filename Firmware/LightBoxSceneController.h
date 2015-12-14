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

#ifndef TEENSYCMAKE_LIGHTBOXSCENECONTROLLER_H
#define TEENSYCMAKE_LIGHTBOXSCENECONTROLLER_H

#include "SceneController.h"
#include "MenuItemView.h"
#include "PinDescriptionView.h"
#include "MenuItemButtonView.h"
#include "MenuItemWheelView.h"
#include "SoftI2CMaster.h"

class LightBoxSceneController : public SceneController, MenuItemViewDelegate
{
	typedef struct LightboxSettings {
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t currentSlot;
		float scale;
	} LightboxSettings;

public:
	LightBoxSceneController();
	~LightBoxSceneController();

	virtual void loop() override;

public:
	virtual void onWillAppear() override;
	virtual String getName() override;

private:
	PinDescriptionView _pinDescriptionView;
	MenuView _menuView;
	bool _intro;
	MenuView _settingsMenuView;
	MenuItemButtonView _button;
	LightboxSettings _settings;
	MenuItemWheelView* _scaleMenuItem;
	MenuItemWheelView* _rMenuItem;
	MenuItemWheelView* _gMenuItem;
	MenuItemWheelView* _bMenuItem;
	MenuItemWheelView* _currentSlotMenuItem;
	SoftI2CMaster _i2c;

	virtual void menuItemViewTriggered(MenuItemView *menuItemView) override;

	void updateUI();
	void sendData();

	virtual void menuItemViewValueChanged(MenuItemView *menuItemView, float value) override;
};


#endif //TEENSYCMAKE_LIGHTBOXSCENECONTROLLER_H

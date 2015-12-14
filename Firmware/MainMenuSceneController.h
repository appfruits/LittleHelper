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

#ifndef _TEENSYCMAKE_MAINMENUSCENECONTROLLER_H_
#define _TEENSYCMAKE_MAINMENUSCENECONTROLLER_H_

#include "SceneController.h"
#include "StatusBarView.h"
#include "MenuView.h"
#include "AnalogOutSceneController.h"
#include "ClockOutSceneController.h"
#include "I2CScannerSceneController.h"
#include "ScopeSceneController.h"
#include "LightBoxSceneController.h"

class MenuAction
{
public:
	MenuAction(MenuView* nextMenu, bool forward)
	{
		_nextMenu = nextMenu;
		_forward = forward;
	}

	MenuAction(SceneController* nexScene)
	{
		_nextScene = _nextScene;
		_nextMenu = NULL;
	}

	MenuView* getNextMenu() { return _nextMenu; };
	bool isForward() { return _forward; };
	SceneController* getNextScene() { return _nextScene; };

private:
	MenuView* _nextMenu;
	bool _forward;
	SceneController* _nextScene;
};

class MainMenuSceneController : public SceneController, MenuItemViewDelegate
{
public:
	MainMenuSceneController();
	virtual void loop();

private:
	void setCurrentMenuView(MenuView* menuView, bool forward);
	MenuView* getCurrentMenuView();

private:
	MenuView _mainMenuView;
	MenuView _settingsMenuView;
	MenuView* _currentMenuView;
	View _menuBackgroundView;
	float _selectedItem;
	AnalogOutSceneController* _analogOutputSceneController;
	ClockOutSceneController* _clockOutSceneController;
	I2CScannerSceneController* _i2cScannerSceneController;
	ScopeSceneController* _scopeSceneController;
	LightBoxSceneController* _lightboxSceneController;

	virtual void menuItemViewTriggered(MenuItemView *menuItemView);

public:
	virtual void onWillAppear() override;

	virtual String getName() override;

private:
	virtual void menuItemViewValueChanged(MenuItemView *menuItemView, float value) override;
};


#endif //_TEENSYCMAKE_MAINMENUSCENECONTROLLER_H_

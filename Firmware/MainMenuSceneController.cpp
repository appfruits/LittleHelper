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

#include "MainMenuSceneController.h"
#include "MenuItemButtonView.h"
#include "MenuItemWheelView.h"

MainMenuSceneController::MainMenuSceneController() :
		SceneController(),
		_currentMenuView(NULL),
		_mainMenuView("Home",MINX,MINY,MAXW,MAXY-35),
		_settingsMenuView("Settings",MAXX,MINY,MAXW,MAXY-35),
		_menuBackgroundView(MINX,MINY,MAXW,MAXY-35)
{
	_mainMenuView.addMenuItem(new MenuItemButtonView("Settings", this, new MenuAction(&_settingsMenuView, true)));
	_mainMenuView.addMenuItem(new MenuItemButtonView("Analog Out", this));
	_mainMenuView.addMenuItem(new MenuItemButtonView("Clock Out", this));
	_mainMenuView.addMenuItem(new MenuItemButtonView("I2C-Scanner", this));
	_mainMenuView.addMenuItem(new MenuItemButtonView("Scope", this));
	_mainMenuView.addMenuItem(new MenuItemButtonView("LightBox", this));
	_mainMenuView.setVisible(true);

	//Touch-Wheel
	MenuItemWheelView* twThreshold = new MenuItemWheelView("Threshold",this);
	twThreshold->setLimits(0,127);
	twThreshold->setValue(qtouch.getDetectThreshold(0));
	MenuItemWheelView* twIntegrator = new MenuItemWheelView("Integrator",this);
	twIntegrator->setLimits(0,127);
	twIntegrator->setValue(qtouch.getDetectionIntegrator());

	_settingsMenuView.addMenuItem(new MenuItemButtonView("<- Back to Home", this, new MenuAction(&_mainMenuView, false)));
	_settingsMenuView.addMenuItem(new MenuItemButtonView("Brightness", this));
	_settingsMenuView.addMenuItem(new MenuItemButtonView("Speed", this));
	_settingsMenuView.addMenuItem(twThreshold);
	_settingsMenuView.addMenuItem(twIntegrator);
	_settingsMenuView.setVisible(true);

	//Create a background view that fixes animation bugs as we move the whole menu without erasing the background beneath it
	_menuBackgroundView.setBackgroundColor(ST7735_BLACK);
	_menuBackgroundView.setOpaque(true);

	_selectedItem = 0.0f;

	setCurrentMenuView(&_mainMenuView, true);
}


void MainMenuSceneController::onWillAppear()
{
	SceneController::onWillAppear();

	_currentMenuView->setFocus();
}

void MainMenuSceneController::setCurrentMenuView(MenuView *menuView, bool forward)
{
	if (_currentMenuView == menuView) return;

	//Move old view to left
	if (_currentMenuView != NULL)
	{
		if (forward) _currentMenuView->popLeft(true); else _currentMenuView->popRight(true);
	}

	//Activate new view, push to left and set status bar caption
	_currentMenuView = menuView;
	Application.getStatusBar()->setCaption(menuView->getName());
	_currentMenuView->setSelectedItemIndex(0);
	_selectedItem = 0.0f;
	_currentMenuView->setVisible(true);
	_currentMenuView->setFocus();
	if (forward) _currentMenuView->pushLeft(true); else _currentMenuView->pushRight(true);
}

MenuView* MainMenuSceneController::getCurrentMenuView()
{
	return _currentMenuView;
}

void MainMenuSceneController::loop()
{
	_menuBackgroundView.update();
	_mainMenuView.update();
	_settingsMenuView.update();
}

void MainMenuSceneController::menuItemViewTriggered(MenuItemView *menuItemView)
{
	MenuAction* menuAction = (MenuAction*)menuItemView->getObject();
	if (menuAction != NULL)
	{
		MenuView* nextMenuView = menuAction->getNextMenu();
		bool forward = menuAction->isForward();

		if (nextMenuView != NULL)
		{
			setCurrentMenuView(nextMenuView, forward);
			return;
		}
	}
	else if (menuItemView->getTitle() == "Analog Out")
	{
		_analogOutputSceneController = new AnalogOutSceneController();
		Application.pushScene(_analogOutputSceneController);
	}
	else if (menuItemView->getTitle() == "Clock Out")
	{
		_clockOutSceneController = new ClockOutSceneController();
		Application.pushScene(_clockOutSceneController);
	}
	else if (menuItemView->getTitle() == "I2C-Scanner")
	{
		_i2cScannerSceneController = new I2CScannerSceneController();
		Application.pushScene(_i2cScannerSceneController);
	}
	else if (menuItemView->getTitle() == "Scope")
	{
		_scopeSceneController = new ScopeSceneController();
		Application.pushScene(_scopeSceneController);
	}
	else if (menuItemView->getTitle() == "LightBox")
	{
		_lightboxSceneController = new LightBoxSceneController();
		Application.pushScene(_lightboxSceneController);
	}
}


void MainMenuSceneController::menuItemViewValueChanged(MenuItemView *menuItemView, float value)
{
	if (menuItemView->getTitle() == "Threshold")
	{
		for (int i=0;i<3;i++)
		{
			qtouch.setDetectThreshold(i,(int)value);
		}
		LOG_VALUE("Touch-Wheel detection threshold",(int)value);
	}
	else if (menuItemView->getTitle() == "Integrator")
	{
		qtouch.setDetectionIntegrator((int)value);
		LOG_VALUE("Touch-Wheel integrator",(int)value);
	}
}

String MainMenuSceneController::getName()
{
	return "Main-Menu";
}

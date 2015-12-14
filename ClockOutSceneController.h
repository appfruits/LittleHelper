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

#ifndef _TEENSYCMAKE_CLOCKOUTSCENECONTROLLER_H_
#define _TEENSYCMAKE_CLOCKOUTSCENECONTROLLER_H_

#include "SceneController.h"
#include "StatusBarView.h"
#include "MenuView.h"
#include "MenuItemView.h"
#include "PWMPreviewView.h"

class ClockOutSceneController: public SceneController, MenuItemViewDelegate
{
public:
	ClockOutSceneController();

private:
	MenuView _menuView;
	PWMPreviewView _pwmPreviewView;
	bool _firstUpdate;
	float _duty;
	uint32_t _frequency;

	virtual void loop() override;

	virtual void menuItemViewValueChanged(MenuItemView *menuItemView, float value) override;

public:
	virtual void onWillAppear() override;

	virtual String getName() override;
};


#endif //_TEENSYCMAKE_CLOCKOUTSCENECONTROLLER_H_

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

#ifndef TEENSYCMAKE_SCOPESCENECONTROLLER_H
#define TEENSYCMAKE_SCOPESCENECONTROLLER_H

#include "SceneController.h"
#include "ScopeView.h"
#include "LabelView.h"
#include "MenuView.h"
#include "MenuItemWheelView.h"
#include "MenuItemEnumView.h"

#define MAX_SAMPLES 1000

class ScopeSceneController: public SceneController, ScopeViewDelegate, MenuItemViewDelegate
{
public:
	ScopeSceneController();

	typedef enum Slope {
		Raising = 0,
		Falling = 1,
		Both = 2,
		Off = 3
	} Slope;

private:
	ScopeView _scopeView;
	MenuView _menuView;
	MenuItemWheelView* _xScaleItemView;
	MenuItemWheelView* _xPosItemView;
	MenuItemEnumView* _triggerItemView;
	int _samples[MAX_SAMPLES];
	uint16_t _numSamples;
	bool _paused;
	IntervalTimer _timer;
	float _samplesPerSecond;
	uint32_t _lastTick;
	Record _record;
	LabelView _labelView;
	int _numTriggers;
	int _triggerSlot;
	int _lastTriggerSlot;
	bool _triggered;
	int _samplesInTrigger;
	int _currentTriggerSlot;
	int _triggers[100];
	int _previousSample;
	float _xScale;
	float _xPos;
	uint8_t _triggerSlope;

public:
	virtual void loop() override;
	virtual String getName() override;
	virtual void onWillAppear() override;
	virtual void onWillDisappear() override;
	void copySamples(int start, int end, Record* record);
	bool isPaused();

	void addSample(int value);

private:
	virtual void onPause(ScopeView *scopeView);

	virtual uint16_t getNumberOfSamples();

	virtual int getSampleAtIndex(uint16_t index);

	virtual bool copySamples(uint16_t start, uint16_t length, int *buffer);

	virtual float getSamplesPerSecond();

	virtual void xSystemChanged();

	virtual Record *getRecord();

	virtual void menuItemViewTriggered(MenuItemView *menuItemView) override;

	virtual void menuItemViewValueChanged(MenuItemView *menuItemView, float value) override;
};


#endif //TEENSYCMAKE_SCOPESCENECONTROLLER_H

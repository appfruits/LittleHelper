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

#include "ScopeSceneController.h"

static ScopeSceneController* _currentScopeSceneController = NULL;
static bool inInterrupt = false;

void onScopeTimerTick(void)
{
	if (_currentScopeSceneController != NULL)
	{
		int sample = Pins.getPin(1)->analogRead();
		_currentScopeSceneController->addSample(sample);
	}
}

ScopeSceneController::ScopeSceneController():
	_scopeView(this,MINX,MINY,MAXW,MAXH-20),
	_menuView("Controls",MINX,MINY+MAXH-20,MAXW,20,false),
	_numSamples(0),
	_paused(false),
	_labelView("Hallo",MINX,MINY+40,MAXW,15)
{
	_scopeView.setDelegate(this);
	_scopeView._currentRecord = &_record;
	_numTriggers = 0;
	_triggerSlot = 0;
	_triggered = false;
	_previousSample = 0;
	_triggerSlope = Slope::Raising;

	_xScaleItemView = new MenuItemWheelView("xS",this);
	//_xScaleItemView->setTitle("<*>");
	_xScaleItemView->setLimits(0.1f,10.0f);

	_xPosItemView = new MenuItemWheelView("xP",this);
	//_xPosItemView->setTitle("<+>");
	_xPosItemView->setLimits(-64,64);

	_triggerItemView = new MenuItemEnumView("T",this);
	_triggerItemView->addItem(0,"Raise");
	_triggerItemView->addItem(1,"Fall");
	_triggerItemView->addItem(2,"Both");
	_triggerItemView->addItem(3,"Off");

	_menuView.addMenuItem(_xScaleItemView);
	_menuView.addMenuItem(_xPosItemView);
	_menuView.addMenuItem(_triggerItemView);
}


String ScopeSceneController::getName()
{
	return "ScopeSceneController";
}

bool ScopeSceneController::isPaused()
{
	return _paused;
}

void ScopeSceneController::onWillAppear()
{
	SceneController::onWillAppear();

	Pins.activatePin(1,"Channel 1");
	//Pins.activatePin(2,"Channel 2");
	Pins.activatePin(PIN_GND,"GND");

	Pins.getPin(1)->setPinMode(INPUT);
	//Pins.getPin(2)->setPinMode(INPUT);

	Application.getStatusBar()->setCaption("Scope");

	_menuView.setFocus();

	_currentScopeSceneController = this;

	_timer.begin(onScopeTimerTick,500);
}

void ScopeSceneController::onWillDisappear()
{
	SceneController::onWillDisappear();

	_timer.end();
	_currentScopeSceneController = NULL;
}

/*
 *
 * 	display.println(length+start);
		this->_delegate->copySamples(numSamples+start,abs(start),&_samples[0]);
		this->_delegate->copySamples(0,length + start,&_samples[abs(start)]);
	}
	else
	{
		if (end < numSamples)
		{
			display.print("S-Start:");
			display.println(start);
			display.print("S-Length:");
			display.println(length);
			display.println(length+start);

			this->_delegate->copySamples(start,length,&_samples[0]);
		}
		else
		{
			display.print("S1-Start:");
			display.println(start);
			display.print("S2-Length:");
			display.println(numSamples-start);
			display.print("S2-Start:");
			display.println(0);
			display.print("S2-Length");
			display.println(end-numSamples);

			this->_delegate->copySamples(start,numSamples-start,&_samples[0]);
			this->_delegate->copySamples(0,end-numSamples,&_samples[numSamples-start]);
		}
	}
 */

void ScopeSceneController::copySamples(int start, int end, Record *record)
{
	int s = start;
	int l = end - start;
	if (start < 0)
	{
		s = MAX_SAMPLES + start;
		l = abs(start);

		memcpy(&record->samples[0],&_samples[s],sizeof(int)*l);
		memcpy(&record->samples[l],&_samples[0],sizeof(int)*end);
	}
	else
	{
		if (end < MAX_SAMPLES)
		{
			memcpy(&record->samples[0],&_samples[s],sizeof(int)*l);
		}
		else
		{
			l = MAX_SAMPLES - start;
			memcpy(&record->samples[0],&_samples[start],sizeof(int)*l);
			memcpy(&record->samples[l],&_samples[0],sizeof(int)*(end-MAX_SAMPLES));
		}
	}
}

void ScopeSceneController::addSample(int value)
{
	if (inInterrupt) return;
	inInterrupt = true;
	if (_paused) return;

	_samples[_numSamples] = value;

	if (_triggered == false)
	{
		//Check triggers
		bool triggered = false;
		if (_triggerSlope == Slope::Falling && (_previousSample-value > 500))
		{
			triggered = true;
		}
		if (_triggerSlope == Slope::Raising && (value - _previousSample > 500))
		{
			triggered = true;
		}
		if (_triggerSlope == Slope::Both && (abs(_previousSample-value) > 500))
		{
			triggered = true;
		}

		if (triggered)
		{
			{
				_samplesInTrigger = 0;
				_currentTriggerSlot = _numSamples;
				_triggered = true;
				_numTriggers++;
			}
		}
	}
	else
	{
		_samplesInTrigger++;
		if (_samplesInTrigger > 64)
		{
			_triggered = false;
			_triggerSlot = _currentTriggerSlot;
			_triggers[_numTriggers] = _triggerSlot;
		}
	}

	//Advance memory position
	_numSamples++;
	if (_numSamples >= MAX_SAMPLES)
	{
		_numSamples = 0;

/*		_paused = true;

		Serial.println("Samples");
		for (int i=0;i<MAX_SAMPLES;i++)
		{
			Serial.print(i);
			Serial.print(";");
			Serial.println(_samples[i]);
		}
		Serial.println("Triggers");
		for (int i=0;i<_numTriggers;i++)
		{
			Serial.print(i);
			Serial.print(";");
			Serial.println(_triggers[i]);
		}*/
	}

	_samplesPerSecond= 1000000 / (micros() - _lastTick);
	_lastTick = micros();

	//Save value to compare in next sample
	_previousSample = value;

	inInterrupt = false;
}

void ScopeSceneController::loop()
{
	SceneController::loop();

	if (!_paused)
	{
		int lastTriggerSlot;
		int triggerSlot;

		noInterrupts();
		lastTriggerSlot = _lastTriggerSlot;
		triggerSlot = _triggerSlot;
		interrupts();

		if (lastTriggerSlot != triggerSlot)
		{
			_record.reset();
			_record.startPos = triggerSlot - 64;
			_record.endPos = triggerSlot + 64;

			copySamples(_record.startPos,_record.endPos,&_record);
			_scopeView.setNeedsDisplay();

			noInterrupts();
			this->_lastTriggerSlot = this->_triggerSlot;
			interrupts();
		}
		else if (_triggerSlope == Slope::Off)
		{
			_record.reset();
			noInterrupts();
			int numSamples = _numSamples;
			interrupts();
			_record.startPos = numSamples - 1 - 128;
			_record.endPos = numSamples - 1;

			copySamples(_record.startPos,_record.endPos,&_record);
			_scopeView.setNeedsDisplay();
		}
	}

	if (_paused)
	{
		//_scopeView.update();
	}
	else
	{
/*		int sample = Pins.getPin(1)->analogRead();
		//sample = random(-127,127);

		_samples[_numSamples] = sample;
		_numSamples++;
		if (_numSamples >= MAX_SAMPLES)
		{
			_numSamples = 0;
			_scopeView.setCursor(0);
		}

		_scopeView.setCursor(_scopeView.getCursor()+1);*/

		//_scopeView.setNeedsDisplay();
		//_scopeView.update();
	}

	_scopeView.update();
	_labelView.update();
	_menuView.update();
}

void ScopeSceneController::onPause(ScopeView *scopeView)
{
	_paused = !_paused;

	if (_paused) {
		_timer.end();
		leds.setPixelColor(0,128,0,0);
		leds.show();
	}
	else
	{
		_timer.begin(onScopeTimerTick,250);
		leds.setPixelColor(0,0,128,0);
		leds.show();
	}
}

uint16_t ScopeSceneController::getNumberOfSamples()
{
	return MAX_SAMPLES;
}

int ScopeSceneController::getSampleAtIndex(uint16_t index)
{
	noInterrupts();
	int sample = _samples[index];
	interrupts();
	return sample;
}

bool ScopeSceneController::copySamples(uint16_t start, uint16_t length, int *buffer)
{
	if (start+length >= MAX_SAMPLES-1) return false;
	if (start < 0) return false;

	noInterrupts();
	memcpy(buffer,&_samples[start],length*sizeof(int));
	interrupts();
	return true;
}

float ScopeSceneController::getSamplesPerSecond()
{
	noInterrupts();
	float sps = _samplesPerSecond;
	interrupts();
	return sps;
}

void ScopeSceneController::xSystemChanged()
{
	int interval = _xScale * 1000;
	_timer.end();
	_record.reset();
	_timer.begin(onScopeTimerTick,interval);

	_scopeView.setNeedsDisplay();
}

Record *ScopeSceneController::getRecord()
{
	return &_record;
}

void ScopeSceneController::menuItemViewTriggered(MenuItemView *menuItemView)
{

}

void ScopeSceneController::menuItemViewValueChanged(MenuItemView *menuItemView, float value)
{
	if (menuItemView == _xScaleItemView)
	{
		_xScale = value;

		xSystemChanged();
	}
	else if (menuItemView == _xPosItemView)
	{
		_xPos = value;

		xSystemChanged();
	}
	else if (menuItemView == _triggerItemView)
	{
		_triggerSlope = value;
	}
}

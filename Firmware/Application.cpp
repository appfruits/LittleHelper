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

#include "Application.h"
#include "SceneController.h"
#include "Animator.h"

ApplicationClass Application;

ApplicationClass::ApplicationClass()
{
	_firstSceneLoop = true;
	_focusedView = NULL;
	_buttonDownStartTime = 0;
	_currentLed = 0;
}

ApplicationClass::~ApplicationClass()
{

}

void ApplicationClass::sendScreenshot()
{
	leds.setPixelColor(0,128,128,128);
	leds.setPixelColor(1,128,128,128);
	leds.setPixelColor(2,128,128,128);
	leds.show();

	Serial.println("<screenshot>");
	for (int y=0;y<160;y++)
	{
		for (int x=0;x<128;x++)
		{
			uint16_t color = display.backbuffer[x][y];
			int r = ((((color >> 11) & 0x1F) * 527) + 23) >> 6;
			int g = ((((color >> 5) & 0x3F) * 259) + 33) >> 6;
			int b = (((color & 0x1F) * 527) + 23) >> 6;

			Serial.print(r);
			Serial.print(",");
			Serial.print(g);
			Serial.print(",");
			Serial.println(b);
		}
	}
	Serial.println("</screenshot>");

	leds.setPixelColor(0,0,0,0);
	leds.setPixelColor(1,0,0,0);
	leds.setPixelColor(2,0,0,0);
	leds.show();

}

void ApplicationClass::loop()
{
	//Run Animations
	Animator.update();

	//Update button state for next run loop
	button.update();

	//Gather touch wheel events
	touchWheel.update();

	if (button.getButtonDownTime() > 1000)
	{
		leds.setPixelColor(2,80,0,0);
		leds.show();
	}

	if (button.getButtonDownTime() > 1300)
	{
		leds.setPixelColor(1,80,0,0);
		leds.show();
	}

	if (button.getButtonDownTime() > 1600)
	{
		leds.setPixelColor(0,80,0,0);
		leds.show();

		digitalWrite(killPin,LOW);
		while (true) { delay(100); };
	}

	//Move up in controller hierarchy
	if (touchWheel.isButtonReleased(TouchWheel::Direction::Top))
	{
		Application.dismissScene();
	}

	if (touchWheel.isButtonReleased(TouchWheel::Direction::Bottom))
	{
		this->sendScreenshot();
	}

	//Handle Events of focused View
	if (Application.getFocusedView() != NULL)
	{
		Application.getFocusedView()->handleEvents();
	}

	//Run current controller
	if (_scenes.count() > 0)
	{
		SceneController* sceneController = _scenes.peek();

		//Call onWillAppear event handler if this is the first time the loop function is called by the scene
		//The default implementation will clear the display!
		if (_firstSceneLoop)
		{
			sceneController->onWillAppear();
			_statusBarView.setNeedsDisplay();
			_firstSceneLoop = false;
		}

		//Run the scenes loop function
		sceneController->loop();

		//Update Statusbar
		if (sceneController->statusBarVisible())
		{
			_statusBarView.update();
		}

		digitalWrite(ledPin,!digitalRead(ledPin));
		//delay(10);
	}
	else
	{
		digitalWrite(ledPin,!digitalRead(ledPin));
		delay(50);
	}

/*	leds.setPixelColor(0,0,0,0);
	leds.setPixelColor(1,0,0,0);
	leds.setPixelColor(2,0,0,0);
	leds.setPixelColor(_currentLed,80,80,0);
	leds.show();*/

	_currentLed++;
	if (_currentLed > 2)
	{
		_currentLed = 0;
	}

	//Update display
	display.display();
	//sendScreenshot();
}

void ApplicationClass::pushScene(SceneController *scene)
{
	LOG_VALUE("Pushing scene",scene->getName());

	_firstSceneLoop = true;
	_scenes.push(scene);

	_statusBarView.setNeedsDisplay();
}

void ApplicationClass::dismissScene()
{
	if (_scenes.count() <= 1) return;
	LOG_VALUE("Dismissing scene", _scenes.peek()->getName());

	SceneController* sceneController = _scenes.pop();
	sceneController->onWillDisappear();

	_statusBarView.setNeedsDisplay();

	leds.setPixelColor(0,80,80,0);
	leds.show();

	leds.setPixelColor(2,80,80,0);
	leds.show();

	_firstSceneLoop = true;


}

void ApplicationClass::setFocusedView(View *focusView)
{
	LOG_VALUE("Setting focus to view",focusView->getDescription());
	_focusedView = focusView;
}

View* ApplicationClass::getFocusedView()
{
	return _focusedView;
}

void ApplicationClass::resetFocus()
{
	_focusedView = NULL;
}

StatusBarView *ApplicationClass::getStatusBar()
{
	return &_statusBarView;
}

void ApplicationClass::onPinChanged()
{
	_statusBarView.setNeedsDisplay();
}

ColorTheme* ApplicationClass::getTheme()
{
	return &_theme;
}
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

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "Appfruits_ST7735.h"
#include "Appfruits_QTouch.h"
#include "StackArray.h"
#include "SceneController.h"
#include "Appfruits_Button.h"
#include "Appfruits_Debug.h"
#include <MAX1704.h>
#include "StatusBarView.h"
#include "Pins.h"
#include "ColorTheme.h"
#include "TouchWheel.h"
#include "Icon.h"

// If using software SPI (the default case):
#define sclk 13  // SCLK can also use pin 14
#define mosi 11  // MOSI can also use pin 7
#define cs   10  // CS & DC can use pins 2, 6, 9, 10, 15, 20, 21, 22, 23
#define dc   21  //  but certain pairs must NOT be used: 2+10, 6+9, 20+23, 21+22
#define rst  9   // RST can use any pin
#define sdcs 4   // CS for SD card, can use any pin

#define buttonPin 1
#define neoPixelPin 22
#define numPixels 3

#define ledPin 28

#define killPin 31
#define lcdBacklightPin 6

#define chargeAlertPin 2

#define EXT_PIN_3 3
#define EXT_PIN_2 24
#define EXT_PIN_1 A14
#define EXT_PIN_DAC A14

#define LOG(m) if (Serial.available()) {Serial.println(m);}
#define LOG_VALUE(m,v) if (Serial.available()) {Serial.print(m);Serial.print(": ");Serial.println(v);}

class SceneController;
class View;

class ApplicationClass
{
public:
	ApplicationClass();
	~ApplicationClass();

	void loop();
	void pushScene(SceneController* scene);
	void dismissScene();

	StatusBarView* getStatusBar();

	void setFocusedView(View* focusView);
	View* getFocusedView();
	void resetFocus();

	void onPinChanged();

	void sendScreenshot();

	ColorTheme* getTheme();

private:
	StackArray<SceneController*> _scenes;
	bool _firstSceneLoop;
	View* _focusedView;
	StatusBarView _statusBarView;
	uint32_t _buttonDownStartTime;
	ColorTheme _theme;
	uint8_t _currentLed;
};

extern ApplicationClass Application;
extern Appfruits_ST7735 display;
extern TouchWheel touchWheel;
extern Adafruit_NeoPixel leds;
extern Appfruits_Button button;
extern MAX1704 battery;
extern Appfruits_QTouch qtouch;

#endif //_APPLICATION_H_

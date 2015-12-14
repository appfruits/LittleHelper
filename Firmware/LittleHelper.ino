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
#include "MainMenuSceneController.h"

Appfruits_ST7735 display = Appfruits_ST7735(cs, dc, rst);
Appfruits_QTouch qtouch = Appfruits_QTouch(14);
TouchWheel touchWheel(&qtouch);
Adafruit_NeoPixel leds = Adafruit_NeoPixel(numPixels, neoPixelPin, NEO_GRB + NEO_KHZ800);
Appfruits_Button button = Appfruits_Button(buttonPin);
MAX1704 battery = MAX1704();

MainMenuSceneController* mainMenu;

void selfCheck()
{
	byte error, address;
	int nDevices;

	Serial.println("Scanning...");

	nDevices = 0;
	for(address = 1; address < 127; address++ )
	{
		// The i2c_scanner uses the return value of
		// the Write.endTransmisstion to see if
		// a device did acknowledge to the address.
		Wire.beginTransmission(address);
		error = Wire.endTransmission();

		if (error == 0)
		{
			Serial.print("I2C device found at address 0x");
			if (address<16)
				Serial.print("0");
			Serial.print(address,HEX);
			Serial.println("  !");

			nDevices++;
		}
		else if (error==4)
		{
			Serial.print("Unknow error at address 0x");
			if (address<16)
				Serial.print("0");
			Serial.println(address,HEX);
		}
	}
	if (nDevices == 0)
		Serial.println("No I2C devices found\n");
	else
		Serial.println("done\n");
}

void setup()
{
	//Neopixels
	LOG("Initializing pixels");
	leds.begin();
	leds.setBrightness(40);
	leds.setPixelColor(0,0);
	leds.setPixelColor(1,255,255,255);
	leds.setPixelColor(2,0);
	leds.show();

	//Initialize Serial
	Serial.begin(230400);

	//Initialize I2C
	Wire.begin();

	//Display on
	LOG("Activating LCD-Backlight");
	pinMode(lcdBacklightPin,OUTPUT);
	digitalWrite(lcdBacklightPin,HIGH);

	//Turn device on
	LOG("Setting Kill pin");
	pinMode(killPin,OUTPUT);
	digitalWrite(killPin,HIGH);

	leds.setPixelColor(1,0);
	leds.show();

	//LED
	LOG("Configuring built in LED");
	pinMode(ledPin,OUTPUT);

	//Init display
	LOG("Initializing display");
	display.initR(INITR_BLACKTAB);
	display.setRotation(2);
	display.clear(ST7735_BLACK);

	//Setup chargealert
	//pinMode(chargeAlertPin,INPUT_PULLUP);

	//Setup button
	LOG("Initializing Wheel-Button");
	button.begin();

	//Init touch
	LOG("Initializing touch wheel");
	touchWheel.begin();

	LOG("Starting MainMenu");
	mainMenu = new MainMenuSceneController();
	Application.pushScene(mainMenu);
}

void loop()
{
	Application.loop();
}
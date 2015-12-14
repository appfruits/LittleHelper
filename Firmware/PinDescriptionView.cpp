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

#include "PinDescriptionView.h"
#include "Application.h"

PinDescriptionView::PinDescriptionView():
	View(MINX,MINY,MAXW,MAXH)
{
	
}

PinDescriptionView::PinDescriptionView(uint16_t x, uint16_t y, uint16_t width, uint16_t height): View (x,y,width,height)
{

}

void PinDescriptionView::draw()
{
	const int segmentWidth = 20;
	const int segmentHeight = 10;
	const int gap = 1;
	const int numPins = 5;
	const int pinHeight = 20;

	//Draw Intro Text
	display.setCursor(0,_frame.y);
	display.setFont(ARIAL_8);
	display.setTextColor(RGB565(255,255,255));
	display.setTextWrap(true);
	display.print(_text);

	int x = (MAXW - ((segmentWidth * numPins) + (gap * (numPins-1)))) / 2;

	for (uint8_t i=0;i<5;i++)
	{
		Pin* pin = Pins.getPin(i);
		if (pin->getColor() == 0)
		{
			display.drawRoundRect(x,_frame.bottom()-segmentHeight,segmentWidth,segmentHeight,1,RGB565(255,255,255));
		}
		else
		{
			display.fillRoundRect(x,_frame.bottom()-segmentHeight,segmentWidth,segmentHeight,1,pin->getColor());
		}

		display.drawFastVLine(x+(segmentWidth/2),_frame.bottom()-segmentHeight-pinHeight,pinHeight,RGB565(249,209,106));

		x += segmentWidth + gap;
	}

	//In Landscape X = Y and Y = X, therefore X-coords from before are now the Y coords
	display.setOrientation(LANDSCAPE_LEFT);
	display.setFont(ARIAL_8);
	x = (MAXH-_frame.height)+(segmentHeight + pinHeight + 5);
	int y = (MAXW - ((segmentWidth * numPins) + (gap * (numPins-1)))) / 2;
	y += 6; //Text height
	for (uint8_t i=0;i<5;i++)
	{
		Pin* pin = Pins.getPin(i);
		if (pin->isActive())
		{
			display.setCursor(x,y);
			display.print(pin->getName());
		}

		y += segmentWidth + gap;
	}
	display.setOrientation(PORTRAIT);
}

void PinDescriptionView::setText(String text)
{
	_text = text;
	setNeedsDisplay();
}
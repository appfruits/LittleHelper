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

#include "StatusBarView.h"
#include "Application.h"
#include "Timer.h"

StatusBarView::StatusBarView() : View(MINX,0,MAXW,25), _timeOut(1000)
{
	_charge = 0;
}

void StatusBarView::setCaption(String caption)
{
	_caption = caption;
	setNeedsDisplay();
}

void StatusBarView::draw()
{
	float chargeLevel = battery.stateOfCharge();
	LOG_VALUE("Battery charge level",chargeLevel);

	_charge = 15;

	display.fillRect(_frame.x,_frame.y,_frame.width,_frame.height,ST7735_BLACK);
	//display.drawRect(_frame.x + _frame.width - 30 - 2,_frame.y + 2,_frame.x + _frame.width - 2 - 2,_frame.y + _frame.height - 2, ST7735_WHITE);
	display.drawRect(104,1,21,8,ST7735_WHITE);
	display.drawRect(125,3,1,3,ST7735_WHITE);
	display.fillRect(105,2,_charge,6,ST7735_WHITE);

	display.setFont(ARIAL_16);
	display.setTextSize(1);
	display.setTextColor(ST7735_WHITE);
	display.setCursor(2,2);
	display.print(_caption);

	int width = 10;
	int begin = 64 - (width * 1.5);

	Rect pinMarkFrame = Rect(begin,0,width-1,2);
	for (int i=0;i<3;i++)
	{
		Pin* pin = Pins.getPin(i+1);
		if (pin->isActive())
		{
			display.fillRect(pinMarkFrame,pin->getColor());
		}
		pinMarkFrame.x += width;
	}
}


void StatusBarView::update()
{
/*	if (_timeOut.isTimedOut())
	{
		setNeedsDisplay();
		_timeOut.reset();
	}*/

	View::update();
}

String StatusBarView::getDescription()
{
	return "StatusBarView";
}

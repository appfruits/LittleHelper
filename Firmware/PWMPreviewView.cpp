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

#include "PWMPreviewView.h"
#include "Application.h"

#define paddingLeft 5
#define paddingRight 5
#define waveformColor RGB565(24,122,189)

PWMPreviewView::PWMPreviewView(uint16_t x, uint16_t y, uint16_t width, uint16_t height): View(x,y,width,height)
{
	_frequency = 4.0f;
	_duty = 0.5f;
	_needsDisplay = true;
}

void PWMPreviewView::draw()
{
	LOG("Drawing PWM View");

	display.fillRect(_frame.x,_frame.y,_frame.width,_frame.height,Application.getTheme()->getBackgroundColor());

	//display.drawFastHLine(_frame.x,_frame.bottom(),_frame.width,ST7735_CYAN);

	uint16_t lineColor = Application.getTheme()->getSecondaryColor2();

	if (_duty <= 0.0f)
	{
		display.drawFastHLine(_frame.x+paddingLeft,_frame.bottom()-1,_frame.width-paddingLeft-paddingRight,lineColor);
	}
	else if (_duty >= 1.0f)
	{
		display.drawFastVLine(_frame.x+paddingLeft,_frame.y,_frame.height-1,lineColor);
		display.drawFastHLine(_frame.x+paddingLeft,_frame.y,_frame.width-paddingLeft-paddingRight,lineColor);
		display.drawFastVLine(_frame.x+_frame.width-paddingRight,_frame.y,_frame.height-1,lineColor);
	}
	else
	{
		float segmentWidth = (float)(_frame.width-paddingLeft-paddingRight)/_frequency;
		for (float i=0;i<_frequency;i++)
		{
			int x = _frame.x + paddingLeft + (i*segmentWidth);
			int x1 = _frame.x + paddingLeft + (i*segmentWidth) + (segmentWidth*_duty);
			int x2 = x + segmentWidth;

			display.drawFastVLine(x,_frame.y,_frame.height-1,lineColor);
			display.drawFastHLine(x,_frame.y,x1-x,lineColor);
			if (x1 != x)
			{
				display.drawFastVLine(x1,_frame.y,_frame.height,lineColor);
			}
			display.drawFastHLine(x1,_frame.bottom()-1,x2-x1,lineColor);
		}
	}
}

void PWMPreviewView::setFrequency(float frequency)
{
	if (_frequency == frequency) return;

	//_frequency = frequency;
	setNeedsDisplay();
}

void PWMPreviewView::setDuty(float duty)
{
	if (duty == _duty) return;

	_duty = duty;
	setNeedsDisplay();
}

String PWMPreviewView::getDescription()
{
	return "PWMPreviewView";
}

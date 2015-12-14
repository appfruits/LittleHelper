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

#include "WaveformView.h"
#include "Application.h"

WaveformView::WaveformView(uint16_t x, uint16_t y, uint16_t width, uint16_t height): View(x,y,width,height)
{
	_xScale = 0.1f;
}

void WaveformView::draw()
{
//	uint16_t color = RGB565(12,61,94);
//	if (_selected) color = RGB565(24,122,189);
	display.fillRect(_frame.x,_frame.y,_frame.width,_frame.height,Application.getTheme()->getBackgroundColor());

	int lx,ly;
	for (int x=0;x<128;x++)
	{
		int y = sin((x+64)*_xScale) * 20;
		if (x == 0)
		{
			lx = x;
			ly = y;
		}

		display.drawLine(_frame.x + lx,_frame.y + ly + 20,_frame.x + x,_frame.y + y + 20,Application.getTheme()->getSecondaryColor1());

		lx = x;
		ly = y;
	}
}

String WaveformView::getDescription()
{
	return "WaveformView";
}

void WaveformView::setXScale(float xScale)
{
	if (_xScale == xScale) return;
	_xScale = xScale;
	setNeedsDisplay();
}
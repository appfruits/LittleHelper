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

#include "ScopeView.h"
#include "Application.h"

ScopeView::ScopeView(ScopeViewDelegate* delegate, uint16_t x, uint16_t y, uint16_t width, uint16_t height):
	View(x,y,width,height),
	_yScale(0.085f),
	_cursor(0),
	_delegate(delegate)
{

}

void ScopeView::setCursor(uint16_t cursor)
{
	if (_cursor == cursor) return;
	_cursor = cursor;

	setNeedsDisplay();
}

uint16_t ScopeView::getCursor()
{
	return _cursor;
}

void ScopeView::draw()
{
	View::draw();

	Record* record = this->_delegate->getRecord();

	display.fillRect(_frame.x,_frame.y,_frame.width,_frame.height,Application.getTheme()->getBackgroundColor());

	int yPos = _frame.bottom();
	for (int s=0;s<=4;s++)
	{
		int y = (1023.0f/3.3f) * s * _yScale;
		display.drawFastHLine(_frame.x,yPos - y,_frame.width,Application.getTheme()->getSecondaryColor1());
	}
	display.drawFastHLine(_frame.x,yPos+1,_frame.width,Application.getTheme()->getSecondaryColor1());

	int x;
	int y;
	int lastY;
	int lastX;
	for (int i=0;i<128;i++)
	{
		x = i;
		y = record->samples[i] * _yScale;

		if (i > 0)
		{
			display.drawLine(lastX,yPos-lastY,x,yPos-y,Application.getTheme()->getPrimaryColor());
		}

		lastY = y;
		lastX = x;
	}

	display.setFont(ARIAL_8);
	display.setCursor(0,MINY);
	display.print("Start:");
	display.println(record->startPos);
	display.print("End:");
	display.println(record->endPos);

	display.drawIcon(&SlopeFalling,40,40,ST7735_WHITE);
}

String ScopeView::getDescription()
{
	return "ScopeView";
}

void ScopeView::setDelegate(ScopeViewDelegate *delegate)
{
	_delegate = delegate;
}

void ScopeView::setRecord(Record record)
{
	_record = record;
	setNeedsDisplay();
}

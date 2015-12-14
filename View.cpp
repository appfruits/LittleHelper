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

#include "View.h"
#include "Application.h"

View::View()
{
	_opaque = false;
	_needsDisplay = true;
}

View::~View()
{
}

View::View(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	_frame = Rect(x,y,width,height);
	_opaque = false;
	_needsDisplay = true;
	_visible = true;
}

View::View(Rect frame)
{
	_frame = frame;
}

Rect& View::getFrame()
{
	return _frame;
}

void View::setFrame(Rect frame)
{
	_frame = frame;
	layout();
}

void View::setFrame(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	_frame = Rect(x,y,width,height);
}

void View::draw()
{
	//LOG_VALUE("Draw",this->getDescription());

	if (_needsDisplay && _opaque)
	{
		display.fillRect(_frame.x,_frame.y,_frame.width,_frame.height,_backgroundColor);
	}
}

void View::update()
{
	if (isVisible())
	{
		if (this->_needsDisplay)
		{
			//LOG_VALUE("Draw",this->getDescription());
			draw();
		}
	}
	else
	{
		//LOG_VALUE("Draw skipped, invisible",this->getDescription());
	}

	didDraw();
}

bool View::isVisible()
{
	return _visible;
}

void View::setVisible(bool visible)
{
	if (_visible == visible) return;
	_visible = visible;

	//Check Focus
	if (this->hasFocus())
	{
		Application.resetFocus();
	}

	if (!visible)
	{
		display.fillRect(_frame,Application.getTheme()->getBackgroundColor());
	}

	setNeedsDisplay();
}

void View::handleEvents()
{
}

void View::animationUpdated(Animation *animation, float currentValue, float timeLeft)
{
	if (animation->getKey() == "frame.x")
	{
		display.fillRect(_frame,Application.getTheme()->getBackgroundColor());
		_frame.x = currentValue;
		layout();
	}
}

void View::layout()
{
	setNeedsDisplay();
}

void View::didDraw()
{
	if (this->_needsDisplay == false) return;

	//LOG_VALUE("Did draw",this->getDescription());

	this->_needsDisplay = false;
}

void View::setBackgroundColor(uint16_t backgroundColor)
{
	_backgroundColor = backgroundColor;
}

void View::setOpaque(bool opaque)
{
	_opaque = opaque;
}

void View::setFocus()
{
	View* currentFocusView = Application.getFocusedView();

	Application.setFocusedView(this);
	setNeedsDisplay();

	if (currentFocusView != NULL)
	{
		currentFocusView->setNeedsDisplay();
	}
}

bool View::hasFocus()
{
	return (this == Application.getFocusedView());
}

void View::setNeedsDisplay()
{
	//LOG_VALUE("Needs display",this->getDescription());
	this->_needsDisplay = true;
}

String View::getDescription()
{
	return "View";
}

void View::onTouchWheelLeftClicked(uint32_t duration)
{

}

void View::onTouchWheelTopClicked(uint32_t duration)
{
	Application.dismissScene();
}

void View::onTouchWheelRightClicked(uint32_t duration)
{

}

void View::onTouchWheelBottomClicked(uint32_t duration)
{

}

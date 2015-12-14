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

#include "MenuItemWheelView.h"
#include "Application.h"

MenuItemWheelView::MenuItemWheelView(String title, MenuItemViewDelegate* delegate):
		MenuItemView(title)
{
	_title = title;
	_delegate = delegate;
	_touchWheelOffset = 0.0f;

	_minValue = 0;
	_maxValue = 100;
	_value = _minValue;
	_scale = 1.0f;
};

MenuItemWheelView::MenuItemWheelView(String title, MenuItemViewDelegate* delegate, void *object):
		MenuItemWheelView(title, delegate)
{
	_object = object;
	_touchWheelOffset = 0.0f;
}

void MenuItemWheelView::handleEvents()
{
	View::handleEvents();

	if (hasFocus())
	{
		if (button.buttonClicked())
		{
			_menuView->setFocus();
			return;
		}

		if (touchWheel.isSliding())
		{
			float oldValue = _value;
			float oldTouchWheelOffset = _touchWheelOffset;
			_touchWheelOffset += ((float)touchWheel.getSliderDelta() * 0.1f);
			_value = _touchWheelOffset * _scale;
			if (_value < _minValue)
			{
				_value = _minValue;
				_touchWheelOffset = oldTouchWheelOffset;
			}
			if (_value > _maxValue)
			{
				_value = _maxValue;
				_touchWheelOffset = oldTouchWheelOffset;
			}

			if (_delegate)
			{
				if (_value != oldValue)
				{
					_delegate->menuItemViewValueChanged(this,getValue());
				}
			}

			setNeedsDisplay();
		}
	}
}

void MenuItemWheelView::draw()
{
	uint16_t color = Application.getTheme()->getPrimaryColor(ColorTheme::Shade::Lighter);
	display.setTextColor(Application.getTheme()->getTextColor(ColorTheme::Shade::Dark));

	if (isSelected())
	{
		color = Application.getTheme()->getPrimaryColor();
		display.setTextColor(Application.getTheme()->getTextColor());
	}

	display.fillRect(_frame.x,_frame.y,_frame.width,_frame.height,color);
	if (hasFocus())
	{
		display.drawRect(_frame.x,_frame.y,_frame.width,_frame.height,Application.getTheme()->getPrimaryColor(ColorTheme::Shade::Light));
	}

	display.setFont(ARIAL_8);
	display.setTextSize(1);
	display.setCursor(_frame.x + 4,_frame.y+((_frame.height-8)/2));
	display.setTextWrap(false);
	display.print(_title);

	int textWidth = display.calcTextWidth(_touchWheelOffset,ARIAL_8);
	display.setCursor(_frame.x + _frame.width - 4 - 4 - textWidth, _frame.y+((_frame.height-8)/2));
	display.print(getValue());
}

void MenuItemWheelView::setMinValue(float minValue)
{
	_minValue = minValue;
}

void MenuItemWheelView::setMaxValue(float maxValue)
{
	_maxValue = maxValue;
}

void MenuItemWheelView::setScale(float scale)
{
	if (scale <= 0) scale = 0.01f;
	_scale = scale;
}

float MenuItemWheelView::getValue()
{
	return _value;
}

void MenuItemWheelView::setValue(float value)
{
	if (this->_value == value) return;

	this->_value = value;
	this->_touchWheelOffset = this->_value / this->_scale;

	setNeedsDisplay();
}

void MenuItemWheelView::setLimits(float minValue, float maxValue)
{
	setMinValue(minValue);
	setMaxValue(maxValue);
}


bool MenuItemWheelView::needsFocus()
{
	return true;
}

void MenuItemWheelView::onClicked()
{
	if (hasFocus())
	{
		_menuView->setFocus();
	}
	else
	{
		this->setFocus();
	}
}


String MenuItemWheelView::getDescription()
{
	return "MenuItemWheelView";
}

void MenuItemWheelView::setTitle(String title)
{
	_title = title;
	setNeedsDisplay();
}
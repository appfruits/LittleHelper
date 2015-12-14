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

#include "MenuItemEnumView.h"
#include "Application.h"

MenuItemEnumView::MenuItemEnumView(String title, MenuItemViewDelegate* delegate):
		MenuItemView(title)
{
	_title = title;
	_delegate = delegate;
	_touchWheelOffset = 0.0f;
	_selectedItemIndex = 0;
};

MenuItemEnumView::MenuItemEnumView(String title, MenuItemViewDelegate* delegate, void *object):
		MenuItemEnumView(title, delegate)
{
	_object = object;
	_touchWheelOffset = 0.0f;
}

void MenuItemEnumView::handleEvents()
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
			_touchWheelOffset += ((float)touchWheel.getSliderDelta() * 0.1f);
			if (_touchWheelOffset < 0) _touchWheelOffset = 0;
			if (_touchWheelOffset > _items.count()-1) _touchWheelOffset = _items.count()-1;
			setSelectedItemIndex(_touchWheelOffset);

			if (_delegate)
			{
				_delegate->menuItemViewValueChanged(this,getValue());
			}

			setNeedsDisplay();
		}
	}
}

void MenuItemEnumView::draw()
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

	if (_items.count() > 0)
	{
		String caption = _items.at(_selectedItemIndex)->caption;
		int textWidth = display.calcTextWidth(caption,ARIAL_8);
		display.setCursor(_frame.x + _frame.width - 4 - 4 - textWidth, _frame.y+((_frame.height-8)/2));
		display.print(caption);
	}
}

int32_t MenuItemEnumView::getValue()
{
	if (_items.count() <= 0) return 0;
	return _items.at(_selectedItemIndex)->value;
}

void MenuItemEnumView::setValue(int32_t value)
{
	for (int i=0;i<_items.count();i++)
	{
		EnumViewItem* item = _items.at(i);
		if (item->value == value)
		{
			setSelectedItemIndex(i);
			return;
		}
	}
}

bool MenuItemEnumView::needsFocus()
{
	return true;
}

void MenuItemEnumView::onClicked()
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


String MenuItemEnumView::getDescription()
{
	return "MenuItemEnumView";
}

void MenuItemEnumView::addItem(int32_t value, String caption)
{
	_items.push(new EnumViewItem(value,caption));
}

void MenuItemEnumView::setSelectedItemIndex(uint8_t selectedItemIndex)
{
	if (_selectedItemIndex == selectedItemIndex) return;
	_selectedItemIndex = selectedItemIndex;

	setNeedsDisplay();
}

uint8_t MenuItemEnumView::getSelectedItemIndex()
{
	return _selectedItemIndex;
}
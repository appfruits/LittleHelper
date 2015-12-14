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
 
#include <stdint-gcc.h>
#include "MenuItemView.h"
#include "Animator.h"
#include "MenuView.h"
#include "Application.h"

MenuItemView::MenuItemView()
{
	_delegate = NULL;
	_tag = 0;
	_object = NULL;
	_title = "";
	_menuView = NULL;
}

MenuItemView::MenuItemView(String title):
		_title(title)
{
	_delegate = NULL;
	_tag = 0;
	_object = NULL;
	_menuView = NULL;
}

void MenuItemView::draw()
{
	uint16_t color = Application.getTheme()->getPrimaryColor(ColorTheme::Shade::Lighter);
	display.setTextColor(Application.getTheme()->getTextColor(ColorTheme::Shade::Dark));

	if (isSelected())
	{
		color = Application.getTheme()->getPrimaryColor();
		display.setTextColor(Application.getTheme()->getTextColor());
	}
	display.fillRect(_frame.x,_frame.y,_frame.width,_frame.height,color);
	display.setFont(ARIAL_8);
	display.setTextSize(1);

	display.setCursor(_frame.x + 4,_frame.y+((_frame.height-8)/2));
	display.setTextWrap(false);
	display.print(_title);
}

void MenuItemView::popLeft(bool animated)
{
	Animation* animation = Animator.getAnimationSlot();
	if (!animation || !animated)
	{
		_frame.x = -MAXX;
		return;
	}

	float delay = 0 ;
	if (isSelected()) delay = 0.1;
	animation->init("frame.x",_frame.x,-MAXX,1,delay);
	addAnimation(animation);
}

void MenuItemView::pushLeft(bool animated)
{
	_frame.x = MAXX;
	Animation* animation = Animator.getAnimationSlot();
	if (!animation || !animated)
	{
		_frame.x = MINX;
		return;
	}

	animation->init("frame.x",_frame.x,-MINX,1,0.2);
	addAnimation(animation);
}

String MenuItemView::getTitle()
{
	return _title;
}

void MenuItemView::setTitle(String title)
{
	_title = title;
	setNeedsDisplay();
}

MenuItemViewDelegate* MenuItemView::getDelegate()
{
	return _delegate;
}

void MenuItemView::setDelegate(MenuItemViewDelegate *delegate)
{
	_delegate = delegate;
}

uint8_t MenuItemView::getTag()
{
	return _tag;
}

void MenuItemView::setTag(uint8_t tag)
{
	_tag = tag;
}

void *MenuItemView::getObject()
{
	return _object;
}

void MenuItemView::setObject(void *object)
{
	_object = object;
}

void MenuItemView::setSelected(bool selected)
{
	_selected = selected;
}

bool MenuItemView::isSelected()
{
	return _selected;
}

void MenuItemView::setMenuView(MenuView *menuView)
{
	_menuView = menuView;
}

MenuView* MenuItemView::getMenuView()
{
	return _menuView;
}

bool MenuItemView::needsFocus()
{
	return false;
}

void MenuItemView::onClicked()
{
}

String MenuItemView::getDescription()
{
	return "MenuItemView";
}

void MenuItemView::setNeedsDisplay()
{
	View::setNeedsDisplay();

	if (_menuView != NULL)
	{
		_menuView->setNeedsDisplay();
	}
}

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

#include "MenuItemButtonView.h"
#include "Application.h"

MenuItemButtonView::MenuItemButtonView(String title, MenuItemViewDelegate* delegate):
	MenuItemView(title)
{
	_title = title;
	_delegate = delegate;
};

MenuItemButtonView::MenuItemButtonView(String title, MenuItemViewDelegate* delegate, void *object):
		MenuItemButtonView(title, delegate)
{
	_object = object;
}

void MenuItemButtonView::onClicked()
{
	if (_delegate != NULL)
	{
		_delegate->menuItemViewTriggered(this);
	}
}

String MenuItemButtonView::getDescription()
{
	return "MenuItemButtonView";
}

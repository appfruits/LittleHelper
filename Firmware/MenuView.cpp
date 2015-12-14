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

#include "MenuView.h"
#include "Animator.h"
#include "MenuItemView.h"
#include "Application.h"

MenuView::MenuView()
{
	_scrollOffset = 0;
	_selectedItemIndex = 0;
	_delegate = NULL;
}

MenuView::MenuView(String name, uint16_t x, uint16_t y, uint16_t width, uint16_t height, bool vertical) : View(x,y,width,height)
{
	_selectedItemIndex = 0;
	setName(name);
	_touchWheelOffset = 0.0f;
	_delegate = NULL;
	_vertical = vertical;
	_scrollOffset = 0;
}

MenuView::~MenuView()
{
	while (!_menuItems.isEmpty())
	{
		MenuItemView* itemView = _menuItems.pop();
		delete itemView;
	}
}

void MenuView::draw()
{
	display.setClipRect(getFrame());
	display.fillRect(_frame.x,_frame.y,_frame.width,_frame.height, ST7735_BLACK);
	for (uint16_t i=0;i<_menuItems.count();i++)
	{
		MenuItemView* itemView = _menuItems.at(i);
		itemView->setSelected((_selectedItemIndex == i));
		itemView->draw();
	}
	display.resetClipRect();
}


Rect MenuView::itemViewRect(int itemIndex)
{
	return Rect(_frame.x,_frame.y + (28*itemIndex),128,26);
}

void MenuView::layout()
{
	View::layout();

	if (_vertical)
	{
		Rect frame = Rect(_frame.x,_frame.y-_scrollOffset,128,26);
		for (uint16_t i=0;i<_menuItems.count();i++)
		{
			MenuItemView* itemView = _menuItems.at(i);
			if (itemView)
			{
				itemView->setFrame(frame);
				frame.y += 28;
			}
		}
	}
	else
	{
		int gap = 1;
		int itemWidth = (_frame.width - ((_menuItems.count()-1) * gap)) / _menuItems.count();
		Rect frame = Rect(_frame.x,_frame.y,itemWidth,_frame.height);
		for (uint16_t i=0;i<_menuItems.count();i++)
		{
			MenuItemView* itemView = _menuItems.at(i);
			if (itemView)
			{
				itemView->setFrame(frame);
				frame.x += itemWidth + gap;
			}
		}
	}
}

void MenuView::addMenuItem(MenuItemView *view)
{
	_menuItems.push(view);
	view->setMenuView(this);
	layout();
}

uint8_t MenuView::getSelectedItemIndex()
{
	return _selectedItemIndex;
}


void MenuView::setScrollOffset(int32_t offset, bool animated)
{
	LOG_VALUE("Scroll-Offset",offset);

	Animation* animation = Animator.getAnimationSlot();
	if (!animation || !animated)
	{
		_scrollOffset = offset;
		layout();
		return;
	}

	animation->init("scrollOffset",_scrollOffset,offset,0.1);
	addAnimation(animation);

	layout();
}

void MenuView::setSelectedItemIndex(uint8_t selectedItemIndex)
{
	if (_selectedItemIndex == selectedItemIndex) return;

	_selectedItemIndex = selectedItemIndex;

	LOG_VALUE("Setting selected index",selectedItemIndex);

	//Check scrollOffset
	MenuItemView* itemView = _menuItems.at(_selectedItemIndex);
	if (itemView)
	{
		Rect itemRect = itemViewRect(_selectedItemIndex);
		if (itemView->getFrame().bottom() > _frame.bottom())
		{
			setScrollOffset(itemRect.bottom() - _frame.bottom(), true);
		}
		else if (itemView->getFrame().top() < _frame.top())
		{
			setScrollOffset(itemRect.top()-_frame.top(),true);
		}
	}

	setNeedsDisplay();
}

void MenuView::popLeft(bool animated)
{
	Animation* animation = Animator.getAnimationSlot();
	if (!animation || !animated)
	{
		_frame.x = -MAXX;
		layout();
		return;
	}

	animation->init("frame.x",_frame.x,-MAXX,0.3);
	addAnimation(animation);
}

void MenuView::pushLeft(bool animated)
{
	//_frame.x = MAXX-30;
	Animation* animation = Animator.getAnimationSlot();
	if (!animation || !animated)
	{
		_frame.x = MINX;
		layout();
		return;
	}

	animation->init("frame.x",_frame.x,MINX,0.3,0.2);
	addAnimation(animation);
}

void MenuView::popRight(bool animated)
{
	Animation* animation = Animator.getAnimationSlot();
	if (!animation || !animated)
	{
		_frame.x = MAXX;
		layout();
		return;
	}

	animation->init("frame.x",_frame.x,MAXX,0.3);
	addAnimation(animation);
}

void MenuView::pushRight(bool animated)
{
	_frame.x = -MAXX;
	Animation* animation = Animator.getAnimationSlot();
	if (!animation || !animated)
	{
		_frame.x = MINX;
		layout();
		return;
	}

	animation->init("frame.x",_frame.x,MINX,0.3,0.2);
	addAnimation(animation);
}


void MenuView::animationUpdated(Animation *animation, float currentValue, float timeLeft)
{
	View::animationUpdated(animation, currentValue, timeLeft);

	if (animation->getKey() == "scrollOffset")
	{
		_scrollOffset = currentValue;
		layout();
	}
}

void MenuView::setName(String name)
{
	_name = name;
}

String MenuView::getName()
{
	return _name;
}

int MenuView::getNumberOfItems()
{
	return _menuItems.count();
}

void MenuView::handleEvents()
{
	View::handleEvents();

	if (touchWheel.isSliding())
	{
		_touchWheelOffset += ((float)touchWheel.getSliderDelta() * 0.05f);
		if (_touchWheelOffset < 0) _touchWheelOffset = 0;
		if (_touchWheelOffset > _menuItems.count()-1) _touchWheelOffset = _menuItems.count()-1;
		setSelectedItemIndex(_touchWheelOffset);
	}

	if (button.buttonClicked())
	{
		MenuItemView* selectedItemView = _menuItems.at(_selectedItemIndex);
		if (selectedItemView)
		{
			selectedItemView->onClicked();
		}
	}
}

MenuViewDelegate* MenuView::getDelegate()
{
	return _delegate;
}

void MenuView::setDelegate(MenuViewDelegate *delegate)
{
	_delegate = delegate;
}

String MenuView::getDescription()
{
	return "MenuView";
}

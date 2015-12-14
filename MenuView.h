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

#ifndef _TEENSYCMAKE_MENUVIEW_H_
#define _TEENSYCMAKE_MENUVIEW_H_

#include <stdint-gcc.h>
#include "View.h"
#include "StackArray.h"

class MenuItemView;

class MenuViewDelegate
{
public:
	virtual void menuViewItemClicked(MenuItemView* menuItemView) = 0;
};

class MenuView: public View
{
public:
	MenuView();
	MenuView(String name, uint16_t x, uint16_t y, uint16_t width, uint16_t height, bool vertical=true);
	~MenuView();
	virtual void draw();
	void layout();

	virtual void handleEvents() override;

	void addMenuItem(MenuItemView* view);
	void setSelectedItemIndex(uint8_t selectedItemIndex);
	uint8_t getSelectedItemIndex();

	String getName();
	void setName(String name);

	void popLeft(bool animated);
	void pushLeft(bool animated);
	void popRight(bool animated);
	void pushRight(bool animated);

	int getNumberOfItems();

	void setDelegate(MenuViewDelegate* delegate);
	MenuViewDelegate* getDelegate();

private:
	StackArray<MenuItemView*> _menuItems;
	int32_t _scrollOffset;
	uint8_t _selectedItemIndex;
	String _name;
	float _touchWheelOffset;
	MenuViewDelegate* _delegate;
	bool _vertical;

public:
	virtual String getDescription() override;

protected:
	virtual void animationUpdated(Animation *animation, float currentValue, float timeLeft) override;
	virtual void setScrollOffset(int32_t offset, bool animated=true);
	virtual Rect itemViewRect(int itemIndex);
};


#endif //_TEENSYCMAKE_MENUVIEW_H_

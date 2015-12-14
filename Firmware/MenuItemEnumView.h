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

#ifndef _TEENSYCMAKE_MENUITEMENUMVIEW_H_
#define _TEENSYCMAKE_MENUITEMENUMVIEW_H_

#include "MenuItemView.h"

class Enumerable
{
	virtual uint32_t getValue() = 0;
	virtual String getTitle() = 0;
};

struct EnumViewItem
{
	EnumViewItem(int32_t value, String caption) { this->value = value; this->caption = caption; };
	int32_t value;
	String caption;
};

class MenuItemEnumView: public MenuItemView
{
public:
	MenuItemEnumView(String title, MenuItemViewDelegate* delegate);
	MenuItemEnumView(String title, MenuItemViewDelegate* delegate, void* object);

	virtual void handleEvents() override;

	int32_t getValue();
	void setValue(int32_t value);
	uint8_t getSelectedItemIndex();
	void setSelectedItemIndex(uint8_t selectedItemIndex);

	void addItem(int32_t value, String caption);

private:
	float _touchWheelOffset;
	StackArray<EnumViewItem*> _items;
	uint8_t _selectedItemIndex;

public:
	virtual void draw() override;
	virtual bool needsFocus() override;
	virtual void onClicked() override;

public:
	virtual String getDescription() override;
};


#endif //_TEENSYCMAKE_MENUITEMENUMVIEW_H_

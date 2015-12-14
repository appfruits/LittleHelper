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

#ifndef _TEENSYCMAKE_MENUITEMVIEW_H_
#define _TEENSYCMAKE_MENUITEMVIEW_H_

#include "View.h"
#include "Animation.h"
#include "MenuView.h"

class MenuItemView;

class MenuItemViewDelegate
{
public:
	virtual void menuItemViewTriggered(MenuItemView* menuItemView) {};

	virtual void menuItemViewValueChanged(MenuItemView* menuItemView, float value) {};
};

class MenuItemView: public View
{
public:
	MenuItemView();
	MenuItemView(String title);
	~MenuItemView() {};

	virtual void draw();
	void popLeft(bool animated);
	void pushLeft(bool animated);
	String getTitle();
	void setTitle(String title);

	uint8_t getTag();
	void setTag(uint8_t tag);
	void* getObject();
	void setObject(void* object);

	void setSelected(bool selected);
	bool isSelected();

	virtual bool needsFocus();
	virtual void onClicked();

	void setMenuView(MenuView* menuView);
	MenuView* getMenuView();

	MenuItemViewDelegate* getDelegate();
	void setDelegate(MenuItemViewDelegate* delegate);

protected:
	MenuItemViewDelegate* _delegate;
	String _title;
	void* _object;
	int _tag;
	bool _selected;
	MenuView* _menuView;

public:
	virtual String getDescription() override;

	virtual void setNeedsDisplay() override;
};


#endif //_TEENSYCMAKE_MENUITEMVIEW_H_

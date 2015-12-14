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

#ifndef _VIEW_H_
#define _VIEW_H_

#include "Arduino.h"
#include "Animation.h"
#include "Object.h"

struct Rect
{
public:
	Rect() {};
	Rect(int x, int y, int w, int h) { this->x=x; this->y=y; this->width=w; this->height=h;};

	int midY() { return (y + height)/2; };
	int midX() { return (x + width)/2; };
	int right() { return (x + width); };
	int bottom() { return (y + height); };
	int top() { return (y); };

	int x;
	int y;
	int width;
	int height;
};

#define MINX 0
#define MAXX 128
#define MINY 25
#define MAXY 160
#define MAXH (MAXY-MINY)
#define MAXW (MAXX-MINX)

class View: public AnimatableObject, Object
{
public:
	View();
	~View();
	View(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
	View(Rect frame);

	//Dimensions
	void setFrame(Rect frame);
	void setFrame(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
	Rect& getFrame();
	Rect getScreenFrame();

	//Display
	virtual void draw();
	virtual void update();
	virtual void layout();
	void setBackgroundColor(uint16_t backgroundColor);
	void setOpaque(bool opaque);

	virtual void setNeedsDisplay();
	void didDraw();

	//Visibility
	bool isVisible();
	void setVisible(bool visible=true);

	//Event handling
	void setFocus();
	bool hasFocus();
	virtual void handleEvents();

	virtual void onTouchWheelLeftClicked(uint32_t duration);
	virtual void onTouchWheelTopClicked(uint32_t duration);
	virtual void onTouchWheelRightClicked(uint32_t duration);
	virtual void onTouchWheelBottomClicked(uint32_t duration);

protected:
	virtual void animationUpdated(Animation *animation, float currentValue, float timeLeft) override;

protected:
	Rect _frame;
	bool _visible;
	bool _opaque;
	uint16_t _backgroundColor;
	bool _needsDisplay;

public:
	virtual String getDescription() override;
};

#endif

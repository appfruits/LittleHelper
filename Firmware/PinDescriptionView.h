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

#ifndef TEENSYCMAKE_PINDESCRIPTIONVIEW_H
#define TEENSYCMAKE_PINDESCRIPTIONVIEW_H

#include "View.h"

class PinDescriptionView: public View
{
public:
	PinDescriptionView();
	PinDescriptionView(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

	void setText(String text);

	virtual void draw() override;

private:
	String _text;
};


#endif //TEENSYCMAKE_PINDESCRIPTIONVIEW_H

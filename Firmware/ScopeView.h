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

#ifndef TEENSYCMAKE_SCOPEVIEW_H
#define TEENSYCMAKE_SCOPEVIEW_H

#include "View.h"

//TODO: 16-bit might be too less for larger memories (numSamples, cursor)

class Record
{
public:
	Record() {
		memset(samples,0,sizeof(int)*128);
		state = 0;
	}

	void reset() { endPos = 0; startPos = 0; triggerPos = 0; state = 0; todo = 0;};

	int samples[128];
	int startPos;
	int triggerPos;
	int endPos;
	int todo;
	int state;
};

class ScopeView;

class ScopeViewDelegate
{
public:
	virtual void onPause(ScopeView* scopeView) = 0;
	virtual uint16_t getNumberOfSamples() = 0;
	virtual int getSampleAtIndex(uint16_t index) = 0;
	virtual bool copySamples(uint16_t start, uint16_t length, int* buffer) = 0;
	virtual float getSamplesPerSecond() = 0;
	virtual Record* getRecord() = 0;
};

class ScopeView: public View
{
public:
	ScopeView(ScopeViewDelegate* delegate, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

	void setCursor(uint16_t cursor);
	uint16_t getCursor();

	void setDelegate(ScopeViewDelegate* delegate);
	void setRecord(Record record);

private:
	uint16_t _cursor;
	float _yScale;
	ScopeViewDelegate* _delegate;
	int _samples[200];
	Record _record;

public:
	Record* _currentRecord;

public:
	virtual void draw() override;
	virtual String getDescription() override;
};


#endif //TEENSYCMAKE_SCOPEVIEW_H

/*
 * This is a library for the Atmel QTouch AT42QT2120
 * But it should work with other QTouch Devices as well
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

#ifndef _APPFRUITS_QTOUCH_
#define _APPFRUITS_QTOUCH_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Wire.h>

#define QT2120_I2C_ADDRESS 0x1C
#define QT2120_DETECTION_STATUS 2
#define QT2120_KEYSTATUS_1 3 
#define QT2120_KEYSTATUS_2 4 
#define QT2120_SLIDERPOS 5
#define QT2120_SLIDER_OPTIONS 14
#define QT2120_DETECT_THRESHOLD 16
#define QT2120_DETECTION_INTEGRATOR 11

#define QT2120_NUMBER_OF_SAMPLES 1

class Appfruits_QTouch_Delegate
{
public:
  virtual void onTouchLeftButtonPressed(uint32_t duration) {};
  virtual void onTouchTopButtonPressed(uint32_t duration) {};
  virtual void onTouchRightButtonPressed(uint32_t duration) {};
  virtual void onTouchBottomButtonPressed(uint32_t duration) {};

  virtual void onSlider(uint8_t sliderPos, int8_t sliderDelta) {};
  virtual void onTouchDown() {};
  virtual void onTouchUp(uint32_t duration) {};
};

class Appfruits_QTouch
{
public:
  Appfruits_QTouch(uint8_t changePin);
  void begin();

  void enableSlider(void);
  void enableWheel(void);

  bool touchDetected();
  bool sliderDetected();
  bool wheelDetected();
  uint8_t sliderPosition();
  int8_t sliderDelta();
  uint8_t wheelPosition();
  int8_t wheelDelta();
  bool isKeyPressed(uint8_t index);
  void setDetectThreshold(uint8_t index, uint8_t value);
  void setDetectionIntegrator(uint8_t value);
  uint8_t getDetectThreshold(uint8_t index);
  uint8_t getDetectionIntegrator();
  void setDragging(bool dragging);
  bool isDragging();
  uint8_t getLastSliderPos();

  bool eventAvailable();
  void setDelegate(Appfruits_QTouch_Delegate* delegate);

private:
  Appfruits_QTouch_Delegate* _delegate;
  uint8_t _lastSliderPos;
  bool _dragging;
  uint32_t _dragStartTime;
  uint8_t _maxDelta;
  uint8_t _changePin;
  float _deltas[QT2120_NUMBER_OF_SAMPLES];
  uint8_t _currentDelta;

  bool isBitSet(uint8_t b, uint8_t n);
  void writeRegister(uint8_t reg, uint8_t value);
  uint16_t readRegister16(uint8_t reg);
  uint8_t readRegister8(uint8_t reg);

};

#endif
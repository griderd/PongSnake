// SevenSegment.h

#ifndef _SEVENSEGMENT_h
#define _SEVENSEGMENT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class SevenSegment
{
public:
	SevenSegment(int dataPin, int latchPin, int clockPin, int selectDataPin, int selectClockPin);
	void displayChar(unsigned char charIndex, int digitIndex);
	void display(char* str, int len);
	void setDot(int index, bool value);
	void setDigits(unsigned char hex);
	void setChar(unsigned char ch);

private:
	int _dataPin;
	int _latchPin;
	int _clockPin;
	int _selectDataPin;
	int _selectClockPin;
	bool dot[4];
};

#endif


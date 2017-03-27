#ifndef CUSTOM8x8_H
#define CUSTOM8x8_H

#include "Arduino.h"

class Custom8x8
{
public:
	Custom8x8(int, int, int);
	void clearPixels();
	void setPixel(int, int, bool);
	void updateDisplay();

private:
	byte rows;
	byte columns;

	int _rowPin;
	int _columnPin;
	int _clockPin;
};

#endif

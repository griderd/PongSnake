#include "Arduino.h"
#include "Custom8x8.h"

Custom8x8::Custom8x8(int rowPin, int columnPin, int clockPin)
{
	_rowPin = rowPin;
	_columnPin = columnPin;
	_clockPin = clockPin;

	pinMode(_rowPin, OUTPUT);
	pinMode(_columnPin, OUTPUT);
	pinMode(_clockPin, OUTPUT);
}

void Custom8x8::clearPixels()
{
	rows = 0;
	columns = 0;
}

void Custom8x8::setPixel(int x, int y, bool value)
{
	byte bitValue = value ? 1 : 0;

	rows ^= (-bitValue ^ rows) & (1 << y);
	columns ^= (-bitValue ^ columns) & (1 << x);
}

void Custom8x8::updateDisplay()
{
	int rowBit;
	int columnBit;

	for (int i = 0; i < 8; i++)
	{
		rowBit = ((rows >> i) & 1) != 0 ? HIGH : LOW;
		columnBit = ((columns >> i) & 1) != 0 ? LOW : HIGH;

		digitalWrite(_rowPin, rowBit);
		digitalWrite(_columnPin, columnBit);
		digitalWrite(_clockPin, HIGH);
		digitalWrite(_clockPin, LOW);
	}
}
#include "SevenSegment.h"
#include "Arduino.h"

// Chars: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, P, ' '
unsigned char chars[] = {
	/* ' ' through '/' */
	0x00,0x00,0x22,0x00,0x00,0x00,0x00,0x02,0x39,0x0F,0x00,0x00,0x10,0x40,0x80,0x00,
	/* 0 - 9 */
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
	/* ':' - '@' */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	/* A - Z */
	0x77,0x7c,0x58,0x5e,0x79,0x71,0x7D,0x76,0x06,0x0E,0x00,0x38,0x00,
	0x54,0x5c,0x73,0x00,0x50,0x6D,0x00,0x1c,0x3e,0x00,0x00,0x66,0x5b };

// Digits: Left, center-left, center-right, right
unsigned char digits[] = { 14, 13, 11, 7 };

SevenSegment::SevenSegment(int dataPin, int latchPin, int clockPin, int selectDataPin, int selectClockPin)
{
	_dataPin = dataPin;
	_latchPin = latchPin;
	_clockPin = clockPin;
	_selectDataPin = selectDataPin;
	_selectClockPin = selectClockPin;

	pinMode(_dataPin, OUTPUT);
	pinMode(_latchPin, OUTPUT);
	pinMode(_clockPin, OUTPUT);
	pinMode(_selectDataPin, OUTPUT);
	pinMode(_selectClockPin, OUTPUT);
}

void SevenSegment::displayChar(unsigned char charIndex, int digitIndex)
{
	unsigned char c = chars[charIndex];
	if (dot[digitIndex])
		c = c + 128;

	digitalWrite(_latchPin, LOW);
	shiftOut(_dataPin, _clockPin, MSBFIRST, c);
	digitalWrite(_latchPin, HIGH);

	bool bit;

	//shiftOut(_selectDataPin, _selectClockPin, MSBFIRST, digits[digitIndex]);
	for (int i = 3; i >= 0; i--)
	{
		bit = ((digits[digitIndex] >> i) & 1) != 0 ? HIGH : LOW;
		digitalWrite(_selectDataPin, bit);
		digitalWrite(_selectClockPin, HIGH);
		digitalWrite(_selectClockPin, LOW);
	}
}

void SevenSegment::display(char str[], int len)
{
	int max = len;
	if (max > 4)
		max = 4;

	for (int i = 0; i < max; i++)
	{
		unsigned char index = 0;
		unsigned char c = str[i];
		if ((c >= 'a') && (c <= 'z'))
			c = c - 32;		// Take lowercase letters and make them uppercase.

		if ((c >= ' ') && (c <= 'Z'))
		{
			index = c - ' ';
		}
		else
			index = 0;

		displayChar(index, i);
		delay(5);
	}
}

// Forces the digits specified by the hex value to display. Expects a value between 0 and 0xF
void SevenSegment::setDigits(unsigned char hex)
{
	shiftOut(_selectDataPin, _selectClockPin, MSBFIRST, hex);
}

void SevenSegment::setChar(unsigned char ch)
{
	unsigned char index = 0;
	unsigned char c = ch;
	if ((c >= 'a') && (c <= 'z'))
		c = c - 32;		// Take lowercase letters and make them uppercase.

	if ((c >= ' ') && (c <= 'Z'))
		index = c - ' ';
	else
		index = 0;

	digitalWrite(_latchPin, LOW);
	shiftOut(_dataPin, _clockPin, MSBFIRST, chars[index]);
	digitalWrite(_latchPin, HIGH);
}

void SevenSegment::setDot(int index, bool value)
{
	dot[index] = value;
}
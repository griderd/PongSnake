// Joystick.h

#ifndef _JOYSTICK_h
#define _JOYSTICK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Joystick
{
 protected:


 public:
	 Joystick(int xPin, int yPin, int buttonPin, int deadZoneX, int deadZoneY);
	 void SetCenter();
	 void GetPosition(int* x, int* y);
	 bool GetButton();

private:
	int deadzoneX;
	int deadzoneY;
	int centerX;
	int centerY;

	int x;
	int y;
	int button;
};


#endif


#include "Joystick.h"

Joystick::Joystick(int xPin, int yPin, int buttonPin, int deadZoneX, int deadZoneY)
{
	x = xPin;
	y = yPin;
	button = buttonPin;

	deadzoneX = deadZoneX;
	deadzoneY = deadZoneY;

	pinMode(button, INPUT);
}

void Joystick::SetCenter()
{
	centerX = analogRead(x);
	centerY = analogRead(y);
}

void Joystick::GetPosition(int *outx, int *outy)
{
	int xPos = analogRead(x);
	int yPos = analogRead(y);

	if (abs(xPos - centerX) > (deadzoneX / 2))
	{
		if (xPos > centerX)
			*outx = xPos - centerX;
		else
			*outx = centerX - xPos;
	}
	
	if (abs(yPos - centerY) > (deadzoneY / 2))
	{
		if (yPos > centerY)
			*outy = yPos - centerY;
		else
			*outy = centerY - yPos;
	}
}

bool Joystick::GetButton()
{
	int btnState = digitalRead(button);
	Serial.println(btnState);
	return btnState;
}
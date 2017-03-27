#include "PassiveBuzzer.h"

PassiveBuzzer::PassiveBuzzer(int signal)
{
	signalPin = signal;
	pinMode(signalPin, OUTPUT);
}

void PassiveBuzzer::Signal(int frequency, int length)
{
	tone(signalPin, frequency, length);
}

void PassiveBuzzer::Signal(int frequency)
{
	tone(signalPin, frequency);
}

void PassiveBuzzer::EndSignal()
{
	noTone(signalPin);
}


// PassiveBuzzer.h

#ifndef _PASSIVEBUZZER_h
#define _PASSIVEBUZZER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class PassiveBuzzer
{
 public:
	 PassiveBuzzer(int signal);
	 void Signal(int frequency, int length);
	 void Signal(int frequency);
	 void EndSignal();

private:
	int signalPin;
};

#endif


#include "Custom8x8.h"
#include "SevenSegment.h"
#include <SevenSegment.h>
#include <Custom8x8.h>
#include "GameState.h"
#include "PassiveBuzzer.h"
#include "Joystick.h"

#define GAMEMODE_PONG 0
#define GAMEMODE_SNAKE 1

#define PIN_ROW 2
#define PIN_COLUMN 3
#define PIN_ARRAYCLOCK 4
#define PIN_GAME 5
#define PIN_P1BTN 6
#define PIN_P2BTN 7
#define PIN_7SDATA 8
#define PIN_7SLATCH 9
#define PIN_7SCLOCK 10
#define PIN_BUZZER 11
#define PIN_7SSELDATA 12
#define PIN_7SSELCLOCK 13

#define APIN_P1JOYX 0
#define APIN_P1JOYY 1
#define APIN_P2JOYX 2
#define APIN_P2JOYY 3

int gameMode = GAMEMODE_PONG;

bool p1Ready = false;
bool p2Ready = false;

Joystick player1(APIN_P1JOYX, APIN_P1JOYY, PIN_P1BTN, 10, 10);
Joystick player2(APIN_P2JOYX, APIN_P2JOYY, PIN_P2BTN, 10, 10);

PassiveBuzzer buzzer(PIN_BUZZER);

Custom8x8 led(PIN_ROW, PIN_COLUMN, PIN_ARRAYCLOCK);
SevenSegment score(PIN_7SDATA, PIN_7SLATCH, PIN_7SCLOCK, PIN_7SSELDATA, PIN_7SSELCLOCK);
GameState state(&score, &led, &player1, &player2, &buzzer);

int delayTime = 5;

void setup() 
{
  // put your setup code here, to run once:

	Serial.begin(921600);

	pinMode(PIN_GAME, INPUT);
	led.clearPixels();
	led.updateDisplay();
	state.SetState(Init);
}

void loop() 
{
  // put your main code here, to run repeatedly:

	gameMode = digitalRead(PIN_GAME);
	
	state.Execute();
}



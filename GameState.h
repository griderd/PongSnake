// GameState.h

#ifndef _GAMESTATE_h
#define _GAMESTATE_h

#include <SevenSegment.h>
#include <Custom8x8.h>
#include "Joystick.h"
#include "PassiveBuzzer.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum GameStates
{
	Init,
	GetPlayerCount,
	WaitPlayer1,
	WaitPlayer2,
	PlayGame
};

class GameState
{
 protected:


 public:
	 // Creates an instance of the GameState object.
	 GameState(SevenSegment* seg, Custom8x8* led, Joystick* p1, Joystick* p2, PassiveBuzzer* buzzer);

	 // Executes the code associated with the current state;
	 void Execute();

	 // Forces the game into a particular state.
	 void SetState(GameStates state);

private:
	void init();
	void getPlayerCount();
	void waitPlayer1();
	void waitPlayer2();
	void playGame();

	int state;
	int playerCount;
	Joystick* player1;
	Joystick* player2;
	SevenSegment* display;
	Custom8x8* grid;
	PassiveBuzzer* _buzzer;
};

#endif


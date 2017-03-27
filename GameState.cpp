#include <SevenSegment.h>
#include <Custom8x8.h>
#include "GameState.h"
#include "PassiveBuzzer.h"

GameState::GameState(SevenSegment* seg, Custom8x8* led, Joystick* p1, Joystick* p2, PassiveBuzzer* buzzer)
{
	display = seg;
	grid = led;
	player1 = p1;
	player2 = p2;
	_buzzer = buzzer;
}

void GameState::Execute()
{
	switch (state)
	{
	case Init:
		init(); break;

	case GetPlayerCount:
		getPlayerCount(); break;

	case WaitPlayer1:
		waitPlayer1(); break;

	case WaitPlayer2:
		waitPlayer2(); break;

	case PlayGame:
		playGame(); break;

	default:
		break;
	}
}

void GameState::SetState(GameStates state)
{
	this->state = state;
}

void GameState::init()
{
	_buzzer->Signal(500);

	display->setDot(0, true);
	display->setDot(1, true);
	display->setDot(2, true);
	display->setDot(3, true);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			grid->setPixel(i, j, true);
		}
	}
	grid->updateDisplay();

	for (int i = 0; i < 200; i++)
	{
		display->display("8888", 4);
		delay(1);
	}

	display->setDot(0, false);
	display->setDot(1, false);
	display->setDot(2, false);
	display->setDot(3, false);

	state = GetPlayerCount;

	_buzzer->EndSignal();
}

void GameState::getPlayerCount()
{
	int count = 0;
	while (!count)
	{
		display->display("1or2", 4);
		grid->clearPixels();
		grid->updateDisplay();
		delay(1);
		
		Serial.print("Joystick 1: ");
		int btn1 = player1->GetButton();
		Serial.print("Joystick 2: ");
		int btn2 = player2->GetButton();

		if (player1->GetButton())
			count = 1;
		else if (player2->GetButton())
			count = 2;
	}

	playerCount = count;
	state = WaitPlayer1;
}

void GameState::waitPlayer1()
{
	bool ready = false;

	while (!ready)
	{
		display->display("P1  ", 4);

		if (player1->GetButton())
			ready = true;
	}

	if (playerCount == 2)
		state = WaitPlayer2;
	else
		state = PlayGame;
}

void GameState::waitPlayer2()
{
	bool ready = false;

	while (!ready)
	{
		display->display("P2  ", 4);
		if (player2->GetButton())
			ready = true;
	}

	state = PlayGame;
}

void GameState::playGame()
{
	display->setDot(1, true);
	display->display("0000", 4);
}
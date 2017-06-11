#pragma once
#include "GameState.h"

class Action
{
public:
	Action() {};
	virtual ~Action() {};

	virtual void executeAction(GameState& game, bool isPlayer1) = 0;
};


#pragma once
#include "Action.h"
#include "AllowedMovement.h"

class Move :
	public Action
{
	AllowedMovement _move;

	Orientation getOrientation(Orientation orientation, bool left);
	Orientation newOrientation(Orientation orientation);
	int steps();

public:
	Move(AllowedMovement allowedMove);
	~Move();

	void executeAction(GameState& game, bool isPlayer1) override;
};


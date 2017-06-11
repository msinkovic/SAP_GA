#pragma once
#include "Action.h"
class Rotate :
	public Action
{
	Orientation _newOrientation;
public:
	Rotate(Orientation newOrientation);
	~Rotate();

	void executeAction(GameState& game, bool isPlayer1) override;
};


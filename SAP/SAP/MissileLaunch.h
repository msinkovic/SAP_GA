#pragma once
#include "Action.h"
class MissileLaunch :
	public Action
{
	Orientation _direction;

	bool checkMissileCollisions(MovableObject newMissile, GameState game);

public:
	MissileLaunch(Orientation direction);
	~MissileLaunch();

	void executeAction(GameState& game, bool isPlayer1) override;
};


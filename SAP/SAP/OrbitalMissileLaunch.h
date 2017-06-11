#pragma once
#include "Action.h"
class OrbitalMissileLaunch :
	public Action
{
	Point2D _location;
public:
	OrbitalMissileLaunch(Point2D location);
	~OrbitalMissileLaunch();

	void executeAction(GameState& game, bool isPlayer1) override;
};


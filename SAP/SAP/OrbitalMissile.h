#pragma once
#include "Point2D.h"
#include "PlayerAgent.h"

class OrbitalMissile
{
	Point2D _target;
	unsigned int _radius;
	unsigned int _turnsToTarget;

public:
	explicit OrbitalMissile(const Point2D target, const unsigned int radius, const unsigned int turns);
	explicit OrbitalMissile(const int x, const int y, const unsigned int radius, const unsigned int turns);

	bool turnEnded();	// returns true if missile is going to hit targeted location at the end of this turn
	bool didHit(PlayerAgent player) const;	// returns true if player was hit

	Point2D getTarget() const;

	~OrbitalMissile();
};


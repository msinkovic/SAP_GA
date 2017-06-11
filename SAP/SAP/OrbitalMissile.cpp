#include "OrbitalMissile.h"



OrbitalMissile::OrbitalMissile(const Point2D target, const unsigned int radius, const unsigned int turnsUntilReachingTarget)
{
	_target = target;
	_radius = radius;
	_turnsToTarget = turnsUntilReachingTarget;
}


OrbitalMissile::OrbitalMissile(const int x, const int y, const unsigned int radius, const unsigned int turnsUntilReachingTarget)
{
	_target = Point2D(x, y);
	_radius = radius;
	_turnsToTarget = turnsUntilReachingTarget;
}


OrbitalMissile::~OrbitalMissile()
{
}


bool OrbitalMissile::turnEnded()	//	returns true if missile is going to hit targeted location at the end of this turn
{
	_turnsToTarget -= 1;
	return _turnsToTarget == 0 ? true : false;
}


bool OrbitalMissile::didHit(PlayerAgent player) const	//	returns true if player was hit
{
	if (_target.distanceToPoint(player.getLocation()) - player.getRadius() < _radius) {
		return true;
	}
	else {
		return false;
	}
}


Point2D OrbitalMissile::getTarget() const
{
	return _target;
}
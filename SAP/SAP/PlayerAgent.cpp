#include "PlayerAgent.h"


PlayerAgent::PlayerAgent()
{

}


PlayerAgent::PlayerAgent(const int x, const int y, const Orientation orientation, const unsigned int radius, 
	const unsigned int movePoints, const unsigned int healthPoints, const WeaponIndentifier weapon)
{
	_objectRadius = radius;

	_point = Point2D(x, y);
	_orientation = orientation;

	_healthPoints = healthPoints;
	_weapon = weapon;

	movementPoints = movePoints;
}


PlayerAgent::PlayerAgent(const Point2D point, const Orientation orientation, const unsigned int radius, 
	const unsigned int movePoints, const unsigned int healthPoints, const WeaponIndentifier weapon)
{
	_objectRadius = radius;

	_point = point;
	_orientation = orientation;

	_healthPoints = healthPoints;
	_weapon = weapon;

	movementPoints = movePoints;
}


PlayerAgent::~PlayerAgent()
{
}


void PlayerAgent::commitedSuicide()
{
	_healthPoints = 0;
}


bool PlayerAgent::inflictDamage()	//	bool - returns if agent is destroyed
{
	if (_healthPoints > 0) {
		_healthPoints -= 1;
	}

	return _healthPoints == 0 ? true : false;  //	returns true if it is destroyed
}


bool PlayerAgent::isAlive() const
{
	return _healthPoints > 0;
}


bool PlayerAgent::isAbleToMove(const unsigned int cost) const
{
	if (movementPoints >= cost) {
		return true;
	}
	else
	{
		return false;
	}
}

void PlayerAgent::setOrientation(Orientation newOrientation)
{
	this->_orientation = newOrientation;
}


void PlayerAgent::setWeapon(const WeaponIndentifier newWeapon)
{
	_weapon = newWeapon;
}


WeaponIndentifier PlayerAgent::weapon() const
{
	return _weapon;
}


unsigned int PlayerAgent::health() const
{
	return _healthPoints;
}


std::ostream& operator<<(std::ostream& out, PlayerAgent& player)
{
	out << "Location: " << player.getLocation() << "\n";
	out << "Orientation: " << player.getOrientation() << "\n";
	out << "Health: " << player.health() << "\n";
	out << "MovePts: " << player.movementPoints << "\n";
	out << "Weapon: " << player.weapon() << "\n";
	
	return out;
}
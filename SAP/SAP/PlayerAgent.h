#pragma once
#include "MovableObject.h"
#include "WeaponIndentifier.h"

class PlayerAgent :
	public MovableObject
{
	unsigned int _healthPoints;
	WeaponIndentifier _weapon;

public:

	explicit PlayerAgent();
	explicit PlayerAgent(const int x, const int y, const Orientation orientation, const unsigned int radius, 
		const unsigned int movePoints, const unsigned int healthPoints, const WeaponIndentifier weapon);
	explicit PlayerAgent(const Point2D point, const Orientation orientation, const unsigned int radius,const unsigned int movePoints, const unsigned int healthPoints, const WeaponIndentifier weapon);
	~PlayerAgent();

	void commitedSuicide();
	bool inflictDamage();
	bool isAlive() const;
	bool isAbleToMove(const unsigned int cost) const;

	void setOrientation(Orientation newOrientation);
	void setWeapon(const WeaponIndentifier newWeapon);

	WeaponIndentifier weapon() const;
	unsigned int health() const;

	//	var
	unsigned int movementPoints;
};

std::ostream& operator<<(std::ostream& out, PlayerAgent& player);
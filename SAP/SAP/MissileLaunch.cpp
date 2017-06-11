#include "MissileLaunch.h"



MissileLaunch::MissileLaunch(Orientation direction)
{
	this->_direction = direction;
}


MissileLaunch::~MissileLaunch()
{
}


bool MissileLaunch::checkMissileCollisions(MovableObject newMissile, GameState game)
{
	bool isDestroyed = false;
	for (auto it = game.MissileList.begin(); it != game.MissileList.end();)
	{
		if (newMissile.collision(&(*it))) {
			it = game.MissileList.erase(it);
			isDestroyed = true;
		}
		else
		{
			it++;
		}
	}
	return isDestroyed;
}


void MissileLaunch::executeAction(GameState& game, bool isPlayer1)
{
	if (isPlayer1)
	{
		if (game.Player1.weapon() == WeaponIndentifier::Missile)
		{
			Point2D offset = Point2D::orientationToPoint(this->_direction) * (game.Player1.getRadius() + game.config_ptr->Missile_Radius);
			Point2D spawnLocation = Point2D(game.Player1.getLocation() + offset);

			MovableObject newMissile = MovableObject(spawnLocation, _direction, game.config_ptr->Missile_Radius);
			game.Player1.setWeapon(WeaponIndentifier::None);

			bool isDestroyed = this->checkMissileCollisions(newMissile, game);

			if (newMissile.collision(&(game.Player2))) {
				game.Player2.inflictDamage();
				std::cout << " -- Player2 got hit by missile. Health:" << game.Player2.health() << std::endl;
				isDestroyed = true;
			}

			if (!isDestroyed) {
				game.MissileList.push_back(newMissile);
			}
		}
	}
	else
	{
		if (game.Player2.weapon() == WeaponIndentifier::Missile)
		{
			Point2D offset = Point2D::orientationToPoint(this->_direction) * (game.Player2.getRadius() + game.config_ptr->Missile_Radius);
			Point2D spawnLocation = Point2D(game.Player2.getLocation() + offset);

			MovableObject newMissile = MovableObject(spawnLocation, _direction, game.config_ptr->Missile_Radius);
			game.Player2.setWeapon(WeaponIndentifier::None);

			bool isDestroyed = this->checkMissileCollisions(newMissile, game);

			if (newMissile.collision(&(game.Player1))) {
				game.Player1.inflictDamage();
				std::cout << " -- Player1 got hit by missile. Health:" << game.Player1.health() << std::endl;
				isDestroyed = true;
			}

			if (!isDestroyed) {
				game.MissileList.push_back(newMissile);
			}
		}
	}
}

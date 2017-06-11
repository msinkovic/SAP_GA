#include "OrbitalMissileLaunch.h"



OrbitalMissileLaunch::OrbitalMissileLaunch(Point2D location)
{
	this->_location = location;
}


OrbitalMissileLaunch::~OrbitalMissileLaunch()
{
}


void OrbitalMissileLaunch::executeAction(GameState& game, bool isPlayer1)
{
	if (isPlayer1) {
		if (game.Player1.weapon() == WeaponIndentifier::OrbitalMissile) {
			OrbitalMissile newOrbitalMissile = OrbitalMissile(this->_location, game.config_ptr->OrbitalMissile_Radius, game.config_ptr->OrbitalMissile_TurnsToTarget);
			game.OrbitalMissileList.push_back(newOrbitalMissile);
			game.Player1.setWeapon(WeaponIndentifier::None);
		}
	}
	else
	{
		if (game.Player2.weapon() == WeaponIndentifier::OrbitalMissile) {
			OrbitalMissile newOrbitalMissile = OrbitalMissile(this->_location, game.config_ptr->OrbitalMissile_Radius, game.config_ptr->OrbitalMissile_TurnsToTarget);
			game.OrbitalMissileList.push_back(newOrbitalMissile);
			game.Player2.setWeapon(WeaponIndentifier::None);
		}
	}
}
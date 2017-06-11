#pragma once
#include <iostream>
enum class WeaponIndentifier
{
	Missile,
	OrbitalMissile,
	None
};

std::ostream& operator<<(std::ostream& out, const WeaponIndentifier& weapon);
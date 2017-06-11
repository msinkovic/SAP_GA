#include "WeaponIndentifier.h"


std::ostream& operator<<(std::ostream& out, const WeaponIndentifier& weapon)
{
	switch (weapon)
	{
	case WeaponIndentifier::Missile:
		return out << "Missile";
	case WeaponIndentifier::OrbitalMissile:
		return out << "OrbitalMissile";
	case WeaponIndentifier::None:
		return out << "None";
	}
}
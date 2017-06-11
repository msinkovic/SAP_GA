#include "Orientation.h"

std::ostream& operator<<(std::ostream& out, const Orientation& orientation)
{
	switch (orientation)
	{
	case Orientation::N:
		return out << "N";
	case Orientation::NE:
		return out << "NE";
	case Orientation::NW:
		return out << "NW";
	case Orientation::S:
		return out << "S";
	case Orientation::SE:
		return out << "SE";
	case Orientation::SW:
		return out << "SW";
	case Orientation::E:
		return out << "E";
	case Orientation::W:
		return out << "W";
	default:
		return out << "Error - orientation";
	}
}
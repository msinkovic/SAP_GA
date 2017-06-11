#pragma once
#include <iostream>

enum class Orientation
{
	N,	// north 
	NE,	// northeast
	E,	// east
	SE,	// southeast
	S,	// south
	SW,	// southwest
	W,	// west
	NW	// northwest
};

std::ostream& operator<<(std::ostream& out, const Orientation& orientation);
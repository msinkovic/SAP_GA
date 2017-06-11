#include "Rotate.h"



Rotate::Rotate(Orientation newOrientation)
{
	this->_newOrientation = newOrientation;
}


Rotate::~Rotate()
{
}


void Rotate::executeAction(GameState& game, bool isPlayer1)
{
	if (isPlayer1) {
		game.Player1.setOrientation(_newOrientation);
		game.Player1.movementPoints++;
	}
	else
	{
		game.Player2.setOrientation(_newOrientation);
		game.Player2.movementPoints++;
	}
}
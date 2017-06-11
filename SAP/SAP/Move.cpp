#include "Move.h"



Move::Move(AllowedMovement allowedMove)
{
	this->_move = allowedMove;
}


Move::~Move()
{
}


Orientation Move::getOrientation(Orientation orientation, bool left)
{
	int value = static_cast<int> (orientation);
	
	value = value + (left ? -1 : 1);
	if (value < 0) {
		return Orientation::NW;
	}
	else if(value > 7) {
		return Orientation::N;
	}
	else
	{
		return static_cast<Orientation> (value);
	}
}


Orientation Move::newOrientation(Orientation orientation)
{
	Orientation newOrientation = orientation;

	if (this->_move == AllowedMovement::Diagonal_Left_By1 || this->_move == AllowedMovement::Diagonal_Left_By2 || this->_move == AllowedMovement::Left_By1) {
		newOrientation = getOrientation(newOrientation, true);
	}
	if (this->_move == AllowedMovement::Left_By1) {
		newOrientation = getOrientation(newOrientation, true);
	}

	if (this->_move == AllowedMovement::Diagonal_Right_By1 || this->_move == AllowedMovement::Diagonal_Right_By2 || this->_move == AllowedMovement::Right_By1) {
		newOrientation = getOrientation(newOrientation, false);
	}
	if (this->_move == AllowedMovement::Right_By1) {
		newOrientation = getOrientation(newOrientation, false);
	}

	return newOrientation;
}


int Move::steps()
{
	if (this->_move == AllowedMovement::Diagonal_Left_By2 || this->_move == AllowedMovement::Diagonal_Right_By2 || this->_move == AllowedMovement::Forward_By2) {
		return 2;
	}
	else if (this->_move == AllowedMovement::Forward_By3) {
		return 3;
	}
	return 1;
}


void Move::executeAction(GameState& game, bool isPlayer1)
{
	int steps = this->steps();

	if (isPlayer1)
	{
		if (game.Player1.isAbleToMove(steps))
		{
			Orientation newOrientation = this->newOrientation(game.Player1.getOrientation());
			game.Player1.setOrientation(newOrientation);
			
			for (int i = 0; i < steps && game.Player1.isAlive() ; i++)
			{
				game.movePlayer1();	

				if (game.Player1.getLocation().distanceToPoint(Point2D()) > game.Radius) {
					game.Player1.commitedSuicide();
					//std::cout << " -- Player1 dies outside play area." << std::endl;
				}
				using namespace std::chrono_literals;
			}
		}
	}
	else
	{
		if (game.Player2.isAbleToMove(steps))
		{
			Orientation newOrientation = this->newOrientation(game.Player2.getOrientation());
			game.Player2.setOrientation(newOrientation);

			for (int i = 0; i < steps && game.Player2.isAlive(); i++)
			{
				game.movePlayer2();

				if (game.Player2.getLocation().distanceToPoint(Point2D()) > game.Radius) {
					game.Player2.commitedSuicide();
					//std::cout << " -- Player2 dies outside play area." << std::endl;
				}
				using namespace std::chrono_literals;
			}
		}
	}
}
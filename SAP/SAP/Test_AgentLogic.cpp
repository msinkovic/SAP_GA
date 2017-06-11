#include "Test_AgentLogic.h"



Test_AgentLogic::Test_AgentLogic()
{
	nextLocation = Point2D(100, 100);
}


Test_AgentLogic::~Test_AgentLogic()
{
}


Action* Test_AgentLogic::getAction()
{
	PlayerAgent player = _game.getPlayer1();

	if (player.getLocation() == nextLocation || nextLocation == Point2D(100,100)) {
		setNextLocation();
	}

	if (player.weapon() == WeaponIndentifier::Missile) {
			// std::cout << "Missile\n";
			return new MissileLaunch(getOrientationToPoint(player.getLocation(), _game.getPlayer2().getLocation()));
	}
	else if(player.weapon() == WeaponIndentifier::OrbitalMissile){
			PlayerAgent player2 = _game.getPlayer2();
			// std::cout << "Orbital\n";
			return new OrbitalMissileLaunch(player2.getLocation() + Point2D::orientationToPoint(player2.getOrientation()) * 3);
	}
	else
	{
		Orientation toTarget = getOrientationToPoint(player.getLocation(), nextLocation);
		Orientation playerOrientation = player.getOrientation();

		if (needsToRotate(playerOrientation, toTarget) || player.movementPoints == 0)
		{
			// std::cout << "Rotate\n";
			return new Rotate(toTarget);
		}
		else {
			int aInt = static_cast<int>(playerOrientation);
			int bInt = static_cast<int>(toTarget);

			int diff = abs(bInt - aInt);
			double dist = player.getLocation().distanceToPoint(nextLocation);

			if (diff == 1 || diff == -7) {
				if (dist <= 1 || player.movementPoints == 1) {
					// std::cout << "DR1\n";
					return new Move(AllowedMovement::Diagonal_Right_By1);
				}
				// std::cout << "DR2\n";
				return new Move(AllowedMovement::Diagonal_Right_By2);
			}
			if (diff == -1 || diff == 7) {
				if (dist <= 1 || player.movementPoints == 1) {
					// std::cout << "DL1\n";
					return new Move(AllowedMovement::Diagonal_Left_By1);
				}
				// std::cout << "DL2\n";
				return new Move(AllowedMovement::Diagonal_Left_By2);
			}
			if (diff == 2 || diff == -6) {
				// std::cout << "R1\n";
				return new Move(AllowedMovement::Right_By1);
			}
			if (diff == -2 || diff == 6) {
				// std::cout << "L1\n";
				return new Move(AllowedMovement::Left_By1);
			}
			if (diff == 0) {
				if (dist >= 3 && player.movementPoints >= 3) {
					// std::cout << "F3\n";
					return new Move(AllowedMovement::Forward_By3);
				}
				else if (dist >= 2 && player.movementPoints >= 2) {
					// std::cout << "F2\n";
					return new Move(AllowedMovement::Forward_By2);
				}
				else {
					// std::cout << "F1\n";
					return new Move(AllowedMovement::Forward_By1);
				}
			}
		}
		
	}
	return new Rotate(player.getOrientation());
}


Orientation Test_AgentLogic::getOrientationToPoint(Point2D from, Point2D to)
{
	Point2D diffInLocation = to - from;

	if(diffInLocation.X < 0)
	{
		if (diffInLocation.Y < 0) {
			return Orientation::SW;
		}
		else if (diffInLocation.Y == 0) {
			return Orientation::W;
		}
		else {
			return Orientation::NW;
		}
	}
	else if (diffInLocation.X > 0)
	{
		if (diffInLocation.Y < 0) {
			return Orientation::SE;
		}
		else if (diffInLocation.Y == 0) {
			return Orientation::E;
		}
		else {
			return Orientation::NE;
		}
	}
	else
	{
		if (diffInLocation.Y < 0) {
			return Orientation::S;
		}
		else {
			return Orientation::N;
		}
	}
}


void Test_AgentLogic::setNextLocation()
{
	Point2D next = Point2D(100, 100);
	Point2D playerLoc = _game.getPlayer1().getLocation();
	
	double min = playerLoc.distanceToPoint(next);
	double radius = _game.getGameState().Radius - _game.getGameState().config_ptr->World_RadiusDecrease;

	for (auto x : _game.getResourceMap())
	{
		double distFromCenter = x.first.distanceToPoint(Point2D());
		if (distFromCenter <=  radius) {
			double delta = x.first.distanceToPoint(playerLoc);
			if (delta < min) {
				min = delta;
				next = x.first;
			}
		}
	}

	nextLocation = next;
	if (nextLocation.distanceToPoint(Point2D()) > _game.getGameState().Radius)
	{
		nextLocation = Point2D();
	}
}


bool Test_AgentLogic::needsToRotate(Orientation a, Orientation b)
{
	int aInt = static_cast<int>(a);
	int bInt = static_cast<int>(b);

	int diff = std::abs(aInt - bInt);
	
	if (diff <= 2 || diff >= 6) {
		return false;
	}
	return true;
}
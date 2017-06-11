#include "GameState.h"



GameState::GameState()
{
}


GameState::~GameState()
{
}


void GameState::advanceOrbitalMissiles()
{
	for (auto it = OrbitalMissileList.begin(); it != OrbitalMissileList.end();)
	{
		if (it->turnEnded()) {
			if (it->didHit(Player1) && Player1.isAlive()) {
				Player1.inflictDamage();
				std::cout << " -- Player1 got hit by orbital missile. Health:" << Player1.health() << std::endl;
			}
			if (it->didHit(Player2) && Player1.isAlive()) {
				Player2.inflictDamage();
				std::cout << " -- Player2 got hit by orbital missile. Health:" << Player2.health() << std::endl;
			}
			it = OrbitalMissileList.erase(it);
		}
		else {
			it++;
		}
	}
}


//	move all missiles step by step, with each step do collsion check
void GameState::moveMissiles()
{
	unsigned int missileSpeed = config_ptr->Missile_Speed;
	for (unsigned int i = 0; i < missileSpeed; i++)
	{
		for (auto& missile : MissileList)
		{
			missile.move();
		}

		bool didHit = false;
		auto it = MissileList.begin();

		while (it != MissileList.end())
		{
			didHit = false;

			auto it_collision = next(it);
			while (it_collision != MissileList.end())
			{
				if (it->collision(&(*it_collision)))
				{
					if (it_collision->collision(&Player1) && Player1.isAlive()) {
						Player1.inflictDamage();
						std::cout << " -- Player1 got hit by missile. Health:" << Player1.health() << std::endl;
					}
					if (it_collision->collision(&Player2) && Player1.isAlive()) {
						Player2.inflictDamage();
						std::cout << " -- Player2 got hit by missile. Health:" << Player2.health() << std::endl;
					}

					it_collision = MissileList.erase(it_collision);
				}
				else {
					it_collision++;
				}
			}

			if (it->collision(&Player1) && Player1.isAlive()) {
				Player1.inflictDamage();
				didHit = true;

				std::cout << " -- Player1 got hit by missile. Health:" << Player1.health() << std::endl;
			}
			if (it->collision(&Player2) && Player1.isAlive()) {
				Player2.inflictDamage();
				didHit = true;

				std::cout << " -- Player2 got hit by missile. Health:" << Player2.health() << std::endl;
			}

			if (it->getLocation().distanceToPoint(Point2D()) > Radius) {
				didHit = true;
			}

			if (didHit) {
				it = MissileList.erase(it);
			}
			else {
				it++;
			}
		}
		using namespace std::chrono_literals;
	}
}


void GameState::movePlayer1()
{
	movePlayer(Player1, 1);
}


void GameState::movePlayer2()
{
	movePlayer(Player2, 2);
}


void GameState::movePlayer(PlayerAgent& player, int playerIndentifier)
{
	player.move();
	player.movementPoints--;

	for (auto it = MissileList.begin(); it != MissileList.end();)
	{
		if (player.collision(&(*it))) {
			it = MissileList.erase(it);
			player.inflictDamage();
			std::cout << " -- Player" << playerIndentifier << " got hit by missile. Health:" << player.health() << std::endl;
		}
		else {
			it++;
		}
	}

	if (Player1.collision(&Player2)) {
		Player1.commitedSuicide();
		Player2.commitedSuicide();
		if (playerIndentifier == 1) {
			std::cout << " -- Player1 crashed into Player2. Both died." << std::endl;
		}
		else {
			std::cout << " -- Player2 crashed into Player1. Both died." << std::endl;
		}
	}
}


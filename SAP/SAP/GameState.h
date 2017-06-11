#pragma once
#include <map>
#include <list>
#include "ResourceIndentifier.h"
#include "OrbitalMissile.h"
#include "ConfigurableParameters.h"

struct GameState
{
	GameState();
	~GameState(); 

	void advanceOrbitalMissiles();
	void moveMissiles();
	void movePlayer1();
	void movePlayer2();

	PlayerAgent Player1;
	PlayerAgent Player2;

	std::map<Point2D, ResourceIndentifier> ResourceMap;
	std::list<MovableObject> MissileList;
	std::list<OrbitalMissile> OrbitalMissileList;

	bool IsDone;
	unsigned int Turn;
	unsigned int Radius;
	
	const ConfigurableParameters* config_ptr;

private:
	void movePlayer(PlayerAgent& player, int playerIndentifier);
};


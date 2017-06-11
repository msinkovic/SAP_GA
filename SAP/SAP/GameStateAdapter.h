#pragma once
#include "GameState.h"

class GameStateAdapter
{
	PlayerAgent* _player1;
	PlayerAgent* _player2;

	std::map<Point2D, ResourceIndentifier>* _resourceMap;
	std::list<MovableObject>* _missileList;
	std::list<OrbitalMissile>* _orbitalMissileList;

	unsigned int *_turn;
	unsigned int *_radius;

	const ConfigurableParameters* _config_ptr;

public:
	explicit GameStateAdapter();
	~GameStateAdapter();

	void bind(GameState &game, bool player2);

	GameState getGameState() const;
	PlayerAgent getPlayer1() const;
	PlayerAgent getPlayer2() const;
	std::map<Point2D, ResourceIndentifier> getResourceMap() const;
	std::list<MovableObject> getMissileList() const;
	std::list<OrbitalMissile> getOrbitalMissileList() const;
};


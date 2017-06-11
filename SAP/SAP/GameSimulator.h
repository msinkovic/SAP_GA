#pragma once
#include <random>
#include "GameState.h"
#include "ConfigurableParameters.h"
#include "AgentController.h"

class GameSimulator
{
	AgentController* _player1Controller;
	AgentController* _player2Controller;

	GameState _game;
	ConfigurableParameters _parameters;

	mutable std::mt19937 _randomNumberEngine;
	std::discrete_distribution<int> _resourceGenerator;

	Point2D randomLocation(unsigned int minDistanceFromCenter, unsigned int maxDistanceFromCenter) const;
	ResourceIndentifier generateNewResource() const;

	void generatePlayers();
	void generateStartingResources();
	void generateResources(unsigned int count);

	void startTurn();
	void collectResources();

	void simulateTurn();

public:
	explicit GameSimulator(const ConfigurableParameters config, AgentController* player1, AgentController* player2);
	~GameSimulator();

	void play();
	GameState* getGameState();
};


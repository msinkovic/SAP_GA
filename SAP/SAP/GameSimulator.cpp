#include "GameSimulator.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <thread>


GameSimulator::GameSimulator(const ConfigurableParameters config, AgentController* player1, AgentController* player2)
{
	_parameters = config;

	_player1Controller = player1;
	_player2Controller = player2;
	
	//	Generating starting world
	std::cout << "Creating new game world..." << std::endl;

	std::random_device rd;
	_randomNumberEngine = std::mt19937(rd());
	
	double gasSpawnChance = static_cast<double>(_parameters.World_GasSpawnChance);
	double missileSpawnChance = static_cast<double>(_parameters.World_MissileSpawnChance);
	double orbitalMissileSpawnChance = static_cast<double>(_parameters.World_OrbitalMissileSpawnChance);

	_resourceGenerator = std::discrete_distribution<int>({ gasSpawnChance, missileSpawnChance, orbitalMissileSpawnChance });

	_game.IsDone = false;
	_game.Turn = 0; 
	_game.Radius = _parameters.World_Radius;
	_game.config_ptr = &_parameters;

	std::cout << "Generating new players..." << std::endl;
	this->generatePlayers();
	std::cout << "Generating resources..." << std::endl;
	this->generateStartingResources();

	//	bind controllers to current GameState 
	GameStateAdapter gsAdapter;
	gsAdapter.bind(this->_game, false);
	//		Player1 
	_player1Controller->bindToGSAdapter(gsAdapter);
	//		Player2	
	gsAdapter.bind(this->_game, true);
	_player2Controller->bindToGSAdapter(gsAdapter);

	std::cout << "New game world has been created." << std::endl;
}


GameSimulator::~GameSimulator()
{
}


Point2D GameSimulator::randomLocation(unsigned int minDistance, unsigned int maxDistance) const
{
	if (minDistance > maxDistance) {
		std::swap(minDistance, maxDistance);
	}

	std::uniform_int_distribution<int> uniformPRandomNumberGenerator_X(0, maxDistance);
	int x = uniformPRandomNumberGenerator_X(_randomNumberEngine) * -1;
	
	double result = static_cast<double> (minDistance * minDistance) - static_cast<double> (x * x);
	int minY = result < 0 ? 0 : static_cast<int> (std::ceil(std::sqrt(result)));

	result = static_cast<double> (maxDistance * maxDistance) - static_cast<double> (x * x);
	int maxY = static_cast<int> (std::floor(std::sqrt(result)));

	if (minY < maxY)
	{
		std::uniform_int_distribution<int> uniformPRandomNumberGenerator_Y(minY, maxY);
		std::bernoulli_distribution yIsPositiveGenerator(0.5);
		
		int y = uniformPRandomNumberGenerator_Y(_randomNumberEngine);		
		if (yIsPositiveGenerator(_randomNumberEngine)) {
			y *= -1;
		}

		return Point2D(x, y);
	}
	else
	{
		return Point2D(x, 0);
	}
}


ResourceIndentifier GameSimulator::generateNewResource() const
{
	switch (_resourceGenerator(_randomNumberEngine))
	{
	case 0:
		return ResourceIndentifier::Gas;
	case 1:
		return ResourceIndentifier::Missile;
	case 2:
		return ResourceIndentifier::OrbitalMissile;
	default:
		std::cout << "Error occured while generating resource! Returning default value." << std::endl;
		return ResourceIndentifier::Gas;
	} 
}


void GameSimulator::generatePlayers()
{
	//
	//	Generate Player1
	//
	Point2D p1_Spawn = this->randomLocation(_parameters.World_PlayerSpawn_MinDistanceToCenter, _parameters.World_PlayerSpawn_MaxDistanceToCenter);
	Orientation p1_Orientation = Orientation::E;
	unsigned int p1_Radius = _parameters.PlayerAgent_Radius;
	unsigned int p1_HealthPoints = _parameters.PlayerAgent_HealthPoints;
	unsigned int p1_MovementPoints = _parameters.PlayerAgent_MovementaPoints;
	WeaponIndentifier p1_Weapon = _parameters.PlayerAgent_Weapon;

	_game.Player1 = PlayerAgent(p1_Spawn, p1_Orientation, p1_Radius, p1_MovementPoints, p1_HealthPoints, p1_Weapon);

	std::cout << "Player1 created." << std::endl;

	//
	//	Generate Player2
	//
	Point2D p2_Spawn = p1_Spawn * Point2D(-1, -1);
	Orientation p2_Orientation = Orientation::W;
	unsigned int p2_Radius = _parameters.PlayerAgent_Radius;
	unsigned int p2_HealthPoints = _parameters.PlayerAgent_HealthPoints;
	unsigned int p2_MovementPoints = _parameters.PlayerAgent_MovementaPoints;
	WeaponIndentifier p2_Weapon = _parameters.PlayerAgent_Weapon;

	_game.Player2 = PlayerAgent(p2_Spawn, p2_Orientation, p2_Radius, p2_MovementPoints, p2_HealthPoints, p2_Weapon);

	std::cout << "Player2 created." << std::endl;
}


void GameSimulator::generateStartingResources()
{
	unsigned int gasCount, missileCount, orbitalMissileCount;
	gasCount = missileCount = orbitalMissileCount = 0;

	if (_parameters.World_GenerateResourcesAtStart % 2 == 1) {
		Point2D newPoint = Point2D();
		ResourceIndentifier newResource = this->generateNewResource();
		
		switch (newResource)
		{
		case ResourceIndentifier::Gas:
			gasCount++;
			break;
		case ResourceIndentifier::Missile:
			missileCount++;
			break;
		case ResourceIndentifier::OrbitalMissile:
			orbitalMissileCount++;
			break;
		}

		_game.ResourceMap[newPoint] = newResource;
	}
	while (_game.ResourceMap.size() < _parameters.World_GenerateResourcesAtStart)
	{
		Point2D newPoint = this->randomLocation(1, _game.Radius);
		
		while (_game.ResourceMap.find(newPoint) != _game.ResourceMap.end()) {
			newPoint = this->randomLocation(1, _game.Radius);
		}
		
		if (newPoint != _game.Player1.getLocation()) {
			Point2D newMirrorPoint = newPoint * Point2D(-1, -1);
			
			ResourceIndentifier newResource = this->generateNewResource();

			switch (newResource)
			{
			case ResourceIndentifier::Gas:
				gasCount += 2;
				break;
			case ResourceIndentifier::Missile:
				missileCount += 2;
				break;
			case ResourceIndentifier::OrbitalMissile:
				orbitalMissileCount += 2;
				break;
			}
			
			_game.ResourceMap[newPoint] = newResource;
			_game.ResourceMap[newMirrorPoint] = newResource;
		}
	}

	std::cout << "Generated " << _game.ResourceMap.size() << " resources.\n\tGas " << gasCount
		<< " , missile " << missileCount << " and orbital missile " << orbitalMissileCount << "." << std::endl;
}


void GameSimulator::generateResources(unsigned int count)
{
	std::bernoulli_distribution xIsPositiveGenerator(0.5);

	for (unsigned int created = 0; created < count; )
	{
		Point2D newPoint = this->randomLocation(0, _game.Radius);
		
		if (xIsPositiveGenerator(_randomNumberEngine)) {
			newPoint.X *= -1;
		}

		if (newPoint != _game.Player1.getLocation() && newPoint != _game.Player2.getLocation())
		{
			_game.ResourceMap[newPoint] = this->generateNewResource();
			created++;
		}
	}
}


void GameSimulator::startTurn()
{
	//	new turn
	std::cout << " Turn(" << ++_game.Turn << ")" << std::endl;

	if (_game.Turn % _parameters.World_TurnsTillDecrease == 0) {
		_game.Radius -= _parameters.World_RadiusDecrease;

		std::cout << " >> Play area decreased to " << _game.Radius << "." << std::endl;

		if (_game.Player1.getLocation().distanceToPoint(Point2D()) > _game.Radius) {
			_game.Player1.commitedSuicide();

			std::cout << " -- Player1 dies outside play area." << std::endl;
		}
		if (_game.Player2.getLocation().distanceToPoint(Point2D()) > _game.Radius) {
			_game.Player2.commitedSuicide();

			std::cout << " -- Player2 dies outside play area." << std::endl;
		}

		Point2D center = Point2D();
		for (auto it = _game.ResourceMap.begin(); it != _game.ResourceMap.end();)
		{
			if (it->first.distanceToPoint(center) > _game.Radius) {
				it = _game.ResourceMap.erase(it);
			}
			else
			{
				it++;
			}
		}

	}

	if (_game.Turn > 1) {
		//	generate resources
		std::uniform_int_distribution<int> newResourcesGenerator(0, _parameters.World_MaxResourceGeneratedPerTurn);
		unsigned int numberOfNewResources = newResourcesGenerator(_randomNumberEngine);
		this->generateResources(numberOfNewResources);
	}
}


void GameSimulator::collectResources()
{
	auto resource = _game.ResourceMap.find(_game.Player1.getLocation());
	if (resource != _game.ResourceMap.end())
	{
		if (resource->second == ResourceIndentifier::Gas) {
			_game.Player1.movementPoints += _parameters.PlayerAgent_MovementPointsGathered;
		}
		else
		{
			if (resource->second == ResourceIndentifier::Missile) {
				_game.Player1.setWeapon(WeaponIndentifier::Missile);
			}
			else {
				_game.Player1.setWeapon(WeaponIndentifier::OrbitalMissile);
			}
		}

		_game.ResourceMap.erase(_game.Player1.getLocation());
	}

	resource = _game.ResourceMap.find(_game.Player2.getLocation());
	if (resource != _game.ResourceMap.end())
	{
		if (resource->second == ResourceIndentifier::Gas) {
			_game.Player2.movementPoints += _parameters.PlayerAgent_MovementPointsGathered;
		}
		else
		{
			if (resource->second == ResourceIndentifier::Missile) {
				_game.Player2.setWeapon(WeaponIndentifier::Missile);
			}
			else {
				_game.Player2.setWeapon(WeaponIndentifier::OrbitalMissile);
			}
		}
		
		_game.ResourceMap.erase(_game.Player2.getLocation());
	}
}


void GameSimulator::simulateTurn()
{
	
	//	new turn
	this->startTurn();

	//	missiles advance
	_game.moveMissiles();
	
	//	get action
	//		Player1
	if (_game.Player1.isAlive()) {
		auto startTimer = std::chrono::high_resolution_clock::now();
		
		Action* player1_Action = _player1Controller->getAction();
		
		auto stopTimer = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> timerDiff = stopTimer - startTimer;
		
		//	do action if action didnt take more then max response time
		if (timerDiff <= _parameters.Algorithm_ResponseTime || true) {
			player1_Action->executeAction(_game, true);
		}

		delete player1_Action;
	}
	//		Player2
	if (_game.Player2.isAlive()) {
		auto startTimer = std::chrono::high_resolution_clock::now();

		Action* player2_Action = _player2Controller->getAction();

		auto stopTimer = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> timerDiff = stopTimer - startTimer;

		//	do action if action didnt take more then max response time
		if (timerDiff <= _parameters.Algorithm_ResponseTime || true) {
			player2_Action->executeAction(_game, false);
		}

		delete player2_Action;
	}
	//	collect resources
	this->collectResources();

	//	orbital missiles advance
	_game.advanceOrbitalMissiles();
	/*
	std::cout << "\t1 2" << std::endl;
	std::cout << "*Health\t" << _game.Player1.health()<< " " << _game.Player2.health()<< std::endl;
	std::cout << "--------------" << std::endl;
	*/
}


void GameSimulator::play()
{
	std::cout << "--------------------------------------------" << std::endl;
	while (_game.Player1.isAlive() && _game.Player2.isAlive())
	{
		this->simulateTurn();
	}


	std::cout << "--------------------------------------------" << std::endl;

	if (_game.Player1.isAlive()) {
		std::cout << " << Player1 won the game! >>" << std::endl;
	}
	else if (_game.Player2.isAlive()) {
		std::cout << " << Player2 won the game! >>" << std::endl;
	}
	else {
		std::cout << " << It's a draw! >>" << std::endl;
	}

	_game.IsDone = true;
}


GameState* GameSimulator::getGameState()
{
	return &(this->_game);
}

#pragma once
#include "Rotate.h"
#include "Move.h"
#include "MissileLaunch.h"
#include "OrbitalMissileLaunch.h"
#include "GameStateAdapter.h"

class AgentController
{
protected:
	GameStateAdapter _game;

public:
	explicit AgentController() {}
	virtual ~AgentController() {};

	void bindToGSAdapter(GameStateAdapter gsAdapter) { _game = gsAdapter; }

	virtual Action* getAction() = 0; //	must allocate derived class of Action on free store, gameSimulator is responsable for releasing the memory.
};


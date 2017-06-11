#pragma once
#include "WeaponIndentifier.h"
#include <chrono>

struct ConfigurableParameters
{
	explicit ConfigurableParameters();
	~ConfigurableParameters();

	unsigned int PlayerAgent_Radius;
	unsigned int PlayerAgent_HealthPoints;
	unsigned int PlayerAgent_MovementaPoints;
	WeaponIndentifier PlayerAgent_Weapon;
	unsigned int PlayerAgent_MovementPointsGathered;

	unsigned int Missile_Radius;
	unsigned int Missile_Speed;
	
	unsigned int OrbitalMissile_Radius;
	unsigned int OrbitalMissile_TurnsToTarget;

	unsigned int World_Radius;
	unsigned int World_RadiusDecrease;
	unsigned int World_TurnsTillDecrease;

	unsigned int World_PlayerSpawn_MinDistanceToCenter;
	unsigned int World_PlayerSpawn_MaxDistanceToCenter;

	unsigned int World_GenerateResourcesAtStart;
	unsigned int World_MaxResourceGeneratedPerTurn;

	unsigned int World_GasSpawnChance;
	unsigned int World_MissileSpawnChance;
	unsigned int World_OrbitalMissileSpawnChance;

	std::chrono::milliseconds Algorithm_ResponseTime;
	std::chrono::milliseconds Graphics_WaitTime;
};


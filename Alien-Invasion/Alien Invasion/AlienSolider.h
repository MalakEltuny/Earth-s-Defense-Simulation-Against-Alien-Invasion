#pragma once
#include "Unit.h"
class AlienSoldier :
	public Unit
{
public:
	AlienSoldier(int id, int health, int power, int attackCapacity)
		: Unit(id, health, power, attackCapacity, "AS") {};

	void attack(Game* game);
};


#pragma once
#include "Unit.h"

class AlienMonster : public Unit {
public:
	AlienMonster(int id = 0, int health = -1, int power = -1, int attackCapacity = 0)
		: Unit(id, health, power, attackCapacity, "AM") {};

	void attack(Game* game);
};

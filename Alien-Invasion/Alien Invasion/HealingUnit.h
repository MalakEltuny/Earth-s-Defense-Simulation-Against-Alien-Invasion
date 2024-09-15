#pragma once
#include "Unit.h"

class HealingUnit : public Unit {
public:
    HealingUnit(int id, int health, int power, int attackCapacity)
        : Unit(id, health, power, attackCapacity, "HU") {};

    void attack(Game* game);
};

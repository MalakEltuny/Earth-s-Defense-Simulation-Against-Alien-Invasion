#pragma once
#include "Unit.h"

class EarthTank : public Unit {
public:
    EarthTank(int id, int health, int power, int attackCapacity) : Unit(id, health, power, attackCapacity, "ET") {}

    void attack(Game* game);
};

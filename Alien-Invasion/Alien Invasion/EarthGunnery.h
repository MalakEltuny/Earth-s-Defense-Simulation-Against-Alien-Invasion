#pragma once
#include "Unit.h"

class EarthGunnery :
    public Unit
{
public:
    EarthGunnery(int id, int health, int power, int attackCapacity)
        : Unit(id, health, power, attackCapacity, "EG") {};

    void attack(Game* game);
};
#pragma once
#include "Unit.h"
class EarthSoldier :
    public Unit
{
public:
    EarthSoldier(int id, int health, int power, int attackCapacity) 
        : Unit(id, health, power, attackCapacity, "ES") {}
    void attack(Game* game);
};


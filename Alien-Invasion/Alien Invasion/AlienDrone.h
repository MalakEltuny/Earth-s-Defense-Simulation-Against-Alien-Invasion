#pragma once
#include "Unit.h"

class AlienDrone : public Unit {
public:
    AlienDrone(int id, int health, int power, int attackCapacity)
        : Unit(id, health, power, attackCapacity, "AD") {
        
    }

    void attack(Game* game);
};

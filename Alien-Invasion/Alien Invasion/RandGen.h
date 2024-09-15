#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "EarthSoldier.h"
#include "EarthTank.h"
#include "EarthGunnery.h"
#include"AlienSolider.h"
#include "AlienMonster.h"
#include "AlienDrone.h"
#include "EarthArmy.h"
#include "AlienArmy.h"

class RandGen {
private:
    int N;
    int ESPercent, ETPercent, EGPercent; 
    // Add hu percent
    int HUpercent;
    int ASPercent, AMPercent, ADPercent;
    int prob;
    int earthUnitID;
    int alienUnitID;

    // Each unit count
    int earthSoldierCount;
    int earthTankCount;
    int earthGunneryCount;
    int alienSoldierCount;
    int alienMonsterCount;
    int alienDroneCount;
    // HU count
    int healingUnitCount;

    struct UnitRanges {
        int powerMin, powerMax;
        int healthMin, healthMax;
        int attackMin, attackMax;
    };

    UnitRanges earthRanges;
    UnitRanges alienRanges;

    Unit* generateEarthSoldier();
    Unit* generateEarthTank();
    Unit* generateEarthGunnery();
    Unit* generateAlienSoldier();
    Unit* generateAlienMonster();
    Unit* generateAlienDrone();
    // HU function
    Unit* generateHealingUnit();
    

public:
    RandGen(int n, int es, int et, int eg, int hu, int as, int am, int ad, int p, UnitRanges earthRanges, UnitRanges alienRanges);

    void generateUnit(EarthArmy* earthArmy, AlienArmy* alienArmy, int timestep);

    //TODO getters fot the unit counts :done
    // Getter functions for unit counts
    int getEarthSoldierCount() const { return earthSoldierCount; }
    int getEarthTankCount() const { return earthTankCount; }
    int getEarthGunneryCount() const { return earthGunneryCount; }
    int getAlienSoldierCount() const { return alienSoldierCount; }
    int getAlienMonsterCount() const { return alienMonsterCount; }
    int getAlienDroneCount() const { return alienDroneCount; }
    // HU count getter
    int getHealingUnitCount() const { return healingUnitCount; }

};

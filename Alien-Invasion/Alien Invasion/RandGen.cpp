#include "RandGen.h"

Unit* RandGen::generateEarthSoldier() {
    int power = rand() % (earthRanges.powerMax - earthRanges.powerMin + 1) + earthRanges.powerMin;
    int health = rand() % (earthRanges.healthMax - earthRanges.healthMin + 1) + earthRanges.healthMin;
    int attack = rand() % (earthRanges.attackMax - earthRanges.attackMin + 1) + earthRanges.attackMin;

    return new EarthSoldier(earthUnitID++, power, health, attack);
}

Unit* RandGen::generateEarthTank() {
    int power = rand() % (earthRanges.powerMax - earthRanges.powerMin + 1) + earthRanges.powerMin;
    int health = rand() % (earthRanges.healthMax - earthRanges.healthMin + 1) + earthRanges.healthMin;
    int attack = rand() % (earthRanges.attackMax - earthRanges.attackMin + 1) + earthRanges.attackMin;

    return new EarthTank(earthUnitID++, power, health, attack);
}

Unit* RandGen::generateEarthGunnery() {
    int power = rand() % (earthRanges.powerMax - earthRanges.powerMin + 1) + earthRanges.powerMin;
    int health = rand() % (earthRanges.healthMax - earthRanges.healthMin + 1) + earthRanges.healthMin;
    int attack = rand() % (earthRanges.attackMax - earthRanges.attackMin + 1) + earthRanges.attackMin;

    return new EarthGunnery(earthUnitID++, power, health, attack);
}

Unit* RandGen::generateAlienSoldier() {
    int power = rand() % (alienRanges.powerMax - alienRanges.powerMin + 1) + alienRanges.powerMin;
    int health = rand() % (alienRanges.healthMax - alienRanges.healthMin + 1) + alienRanges.healthMin;
    int attack = rand() % (alienRanges.attackMax - alienRanges.attackMin + 1) + alienRanges.attackMin;

    return new AlienSoldier(alienUnitID++, power, health, attack);
}

Unit* RandGen::generateAlienMonster() {
    int power = rand() % (alienRanges.powerMax - alienRanges.powerMin + 1) + alienRanges.powerMin;
    int health = rand() % (alienRanges.healthMax - alienRanges.healthMin + 1) + alienRanges.healthMin;
    int attack = rand() % (alienRanges.attackMax - alienRanges.attackMin + 1) + alienRanges.attackMin;

    return new AlienMonster(alienUnitID++, power, health, attack);
}

Unit* RandGen::generateAlienDrone() {
    int power = rand() % (alienRanges.powerMax - alienRanges.powerMin + 1) + alienRanges.powerMin;
    int health = rand() % (alienRanges.healthMax - alienRanges.healthMin + 1) + alienRanges.healthMin;
    int attack = rand() % (alienRanges.attackMax - alienRanges.attackMin + 1) + alienRanges.attackMin;

    return new AlienDrone(alienUnitID++, power, health, attack);
}

Unit* RandGen::generateHealingUnit()
{
    int power = rand() % (earthRanges.powerMax - earthRanges.powerMin + 1) + earthRanges.powerMin;
    int health = rand() % (earthRanges.healthMax - earthRanges.healthMin + 1) + earthRanges.healthMin;
    int attack = rand() % (earthRanges.attackMax - earthRanges.attackMin + 1) + earthRanges.attackMin;

    return new HealingUnit(earthUnitID++, power, health, attack);
}

RandGen::RandGen(int n, int es, int et, int eg, int hu, int as, int am, int ad, int p, UnitRanges earthRanges, UnitRanges alienRanges)
    : N(n), ESPercent(es), ETPercent(et), EGPercent(eg), HUpercent(hu),
    ASPercent(as), AMPercent(am), ADPercent(ad), prob(p),
    earthRanges(earthRanges),
    alienRanges(alienRanges) {
    earthGunneryCount = earthSoldierCount = earthTankCount = healingUnitCount = 0;
    alienDroneCount = alienMonsterCount = alienSoldierCount = 0;
    earthUnitID = 1;
    alienUnitID = 2000;
    srand(time(nullptr));
}

void RandGen::generateUnit(EarthArmy* earthArmy, AlienArmy* alienArmy, int timestep) {
    int randomA = rand() % 100 + 1;

    if (randomA > prob) {
        return;
    }

    for (int i = 0; i < N; i++) {
        int randomB = rand() % 100 + 1;

        if (randomB <= ESPercent) {
            Unit* soldier = generateEarthSoldier();
            soldier->setJoinTime(timestep);
            earthArmy->addUnit(soldier);
            earthSoldierCount++;
        }
        else if (randomB <= ESPercent + ETPercent) {
            Unit* soldier = generateEarthTank();
            soldier->setJoinTime(timestep);
            earthArmy->addUnit(soldier);
            earthTankCount++;
        }
        else if (randomB <= ESPercent + ETPercent + EGPercent){
            Unit* soldier = generateEarthGunnery();
            soldier->setJoinTime(timestep);
            earthArmy->addUnit(soldier);
            earthGunneryCount++;
        }
        else {
            Unit* soldier = generateHealingUnit();
            soldier->setJoinTime(timestep);
            earthArmy->addUnit(soldier);
            healingUnitCount++;
        }
    }

    for (int i = 0; i < N; i++) {
        int randomB = rand() % 100 + 1;

        if (randomB <= ASPercent) {
            Unit* soldier = generateAlienSoldier();
            soldier->setJoinTime(timestep);
            alienArmy->addUnit(soldier);
            alienSoldierCount++;
        }
        else if (randomB <= ASPercent + AMPercent) {
            Unit* soldier = generateAlienMonster();
            soldier->setJoinTime(timestep);
            alienArmy->addUnit(soldier);
            alienMonsterCount++;
        }
        else {
            Unit* soldier = generateAlienDrone();
            soldier->setJoinTime(timestep);
            alienArmy->addUnit(soldier);
            alienDroneCount++;
        }
    }
}

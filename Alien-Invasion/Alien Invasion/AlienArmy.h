#pragma once
#include <iostream>
#include"AlienSolider.h"
#include "AlienMonster.h"
#include "AlienDrone.h"
#include "Queue.h"
#include "Dequeue.h"
#include "AlienMonstersArray.h"

class AlienArmy {
private:
    Queue<Unit*>* alienSoldiers;
    Dequeue<Unit*>* alienDrones;
    AlienMonstersArray* alienMonsters;

public:
    AlienArmy();
    ~AlienArmy();

    void addUnit(Unit* unit);
    void killAlienDrones(Queue<Unit*>* killedList);
    void reInsertAlienMonsters();
    bool allListsEmpty() const;

    void printArmy();

    Queue<Unit*>* getAlienSoldiers();
    Dequeue<Unit*>* getAlienDrones();
    AlienMonstersArray* getAlienMonsters();

    Queue<Unit*> attackingAlienUnits();
};

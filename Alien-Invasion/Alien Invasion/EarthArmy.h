#pragma once
#include <iostream>
#include "EarthSoldier.h"
#include "EarthTank.h"
#include "EarthGunnery.h"
#include "HealingUnit.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "Stack.h"

class EarthArmy {
private:
    Queue<Unit*>* earthSoldiers;
    Stack<Unit*>* earthTanks;
    PriorityQueue<Unit*>* earthGunneries;
    Stack<Unit*>* healingUnits;

public:
    EarthArmy();
    ~EarthArmy();

    void addUnit(Unit* unit);
    void reinsertEarthSoldier();
    Unit* pickEarthTank();
    void printArmy();

    bool allListsEmpty() const;

    Queue<Unit*>* getEarthSoldiers();
    Stack<Unit*>* getEarthTanks();
    PriorityQueue<Unit*>* getEarthGunneries();

    Queue<Unit*> attackingEarthUnits();
};

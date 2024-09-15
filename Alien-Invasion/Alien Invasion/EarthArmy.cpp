#include "EarthArmy.h"

EarthArmy::EarthArmy() {
    earthSoldiers = new Queue<Unit*>();
    earthTanks = new Stack<Unit*>();
    earthGunneries = new PriorityQueue<Unit*>();
    healingUnits = new Stack<Unit*>();
}

EarthArmy::~EarthArmy() {
    delete earthSoldiers;
    delete earthTanks;
    delete earthGunneries;
    delete healingUnits;
}

void EarthArmy::addUnit(Unit* unit) {
    if (EarthSoldier* soldier = dynamic_cast<EarthSoldier*>(unit)) {
        earthSoldiers->enqueue(soldier);
    }
    else if (EarthTank* tank = dynamic_cast<EarthTank*>(unit)) {
        earthTanks->push(tank);
    }
    else if (EarthGunnery* gunnery = dynamic_cast<EarthGunnery*>(unit)) {
        int combination = gunnery->getPower() * gunnery->getCurrentHealth() * -1;
        earthGunneries->insert(gunnery, combination);
    }
    else if (HealingUnit* healingUnit = dynamic_cast<HealingUnit*>(unit)) {
        healingUnits->push(healingUnit);
    }
    else {
        throw "wrong unit";
    }
}

void EarthArmy::reinsertEarthSoldier() {
    if (!earthSoldiers->isEmpty()) {
        Unit* temp = earthSoldiers->dequeue();
        earthSoldiers->enqueue(temp);
    }
}

Unit* EarthArmy::pickEarthTank() {
    if (!earthTanks->isEmpty()) {
        return earthTanks->pop();
    }
    else {
        return nullptr;
    }
}



void EarthArmy::printArmy() {
    std::cout << "======== Earth Army Alive Units ========" << std::endl;

    std::cout << earthSoldiers->getSize() << " ES ";
    earthSoldiers->print();

    std::cout << earthTanks->size() << " ET ";
    earthTanks->print();

    std::cout << earthGunneries->getSize() << " EG ";
    earthGunneries->print();

    std::cout << healingUnits->size() << " EH ";
    healingUnits->print();

    std::cout << std::endl;
}

bool EarthArmy::allListsEmpty() const
{
    return earthSoldiers->isEmpty() && earthTanks->isEmpty() &&
        earthGunneries->isEmpty();

}

Queue<Unit*>* EarthArmy::getEarthSoldiers() {
    return earthSoldiers;
}

Stack<Unit*>* EarthArmy::getEarthTanks() {
    return earthTanks;
}

PriorityQueue<Unit*>* EarthArmy::getEarthGunneries() {
    return earthGunneries;
}

Queue<Unit*> EarthArmy::attackingEarthUnits()
{
    Queue<Unit*> attackingUnits;
    while (!earthSoldiers->isEmpty()) {
		attackingUnits.enqueue(earthSoldiers->dequeue());
	}
    while (!earthTanks->isEmpty()) {
		attackingUnits.enqueue(earthTanks->pop());
	}
    while (!earthGunneries->isEmpty()) {
		attackingUnits.enqueue(earthGunneries->remove());
	}
    while (!healingUnits->isEmpty()) {
		attackingUnits.enqueue(healingUnits->pop());
	}
	return attackingUnits;
}

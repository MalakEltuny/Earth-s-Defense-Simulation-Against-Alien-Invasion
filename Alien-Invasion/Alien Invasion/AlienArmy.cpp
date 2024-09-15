#include "AlienArmy.h"

AlienArmy::AlienArmy() {
    alienSoldiers = new Queue<Unit*>();
    alienDrones = new Dequeue<Unit*>();
    alienMonsters = new AlienMonstersArray();
}

AlienArmy::~AlienArmy() {
    delete alienSoldiers;
    delete alienDrones;
    delete alienMonsters;
}

void AlienArmy::addUnit(Unit* unit) {
    if (AlienSoldier* soldier = dynamic_cast<AlienSoldier*>(unit)) {
        alienSoldiers->enqueue(soldier);
    }
    else if (AlienDrone* drone = dynamic_cast<AlienDrone*>(unit)) {
        alienDrones->pushFront(drone);
    }
    else if (AlienMonster* monster = dynamic_cast<AlienMonster*>(unit)) {
        alienMonsters->addMonster(monster);
    }
}


void AlienArmy::killAlienDrones(Queue<Unit*>* killedList) {
    int n = 3;
    while (!alienDrones->isEmpty() && n > 0) {
        Unit* drone = alienDrones->popFront();
        killedList->enqueue(drone);
        n--;
    }

    n = 3;
    while (!alienDrones->isEmpty() && n > 0) {
        Unit* drone = alienDrones->popBack();
        killedList->enqueue(drone);
        n--;
    }
}

void AlienArmy::reInsertAlienMonsters() {
    Queue<Unit*> tempQueue;
    int n = 5;

    while (!alienMonsters->isEmpty() && n > 0) {
        Unit* monster = alienMonsters->removeMonster();
        tempQueue.enqueue(monster);
        n--;
    }

    while (!tempQueue.isEmpty()) {
        alienMonsters->addMonster(tempQueue.dequeue());
    }
}

bool AlienArmy::allListsEmpty() const
{
    return alienSoldiers->isEmpty() && alienMonsters->isEmpty() &&
        alienDrones->isEmpty();
}

void AlienArmy::printArmy() {
    std::cout << "======== Alien Army Alive Units ========" << std::endl;

    std::cout << alienSoldiers->getSize() << " AS ";
    alienSoldiers->print();

    std::cout << alienDrones->getSize() << " AD ";
    alienDrones->print();

    std::cout << alienMonsters->getSize() << " AM ";
    alienMonsters->print();
    std::cout << "\n";
}

Queue<Unit*>* AlienArmy::getAlienSoldiers() {
    return alienSoldiers;
}

Dequeue<Unit*>* AlienArmy::getAlienDrones() {
    return alienDrones;
}

AlienMonstersArray* AlienArmy::getAlienMonsters() {
    return alienMonsters;
}

Queue<Unit*> AlienArmy::attackingAlienUnits()
{
    Queue<Unit*> attackingUnits;

    if (!alienSoldiers->isEmpty()) {
		attackingUnits.enqueue(alienSoldiers->peek());
	}

    if (!alienDrones->isEmpty()) {
        attackingUnits.enqueue(alienDrones->peekFront());
        attackingUnits.enqueue(alienDrones->peekBack());
    }

    if (!alienMonsters->isEmpty()) {
        int randIndex = rand() % alienMonsters->getSize();
        AlienMonstersArray monsters = *alienMonsters;
        Unit* monster = monsters[randIndex];
        attackingUnits.enqueue(monster);
	}

    return attackingUnits;
}

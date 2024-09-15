#include "AlienMonster.h"
#include "Game.h"

void AlienMonster::attack(Game* game) {

    Queue<Unit*>* earthSoldiers = game->getEarthArmy()->getEarthSoldiers();
    Stack<Unit*>* earthTanks = game->getEarthArmy()->getEarthTanks();

    int attackCapacity = getAttackCapacity();

    int earthSoldiersCount = earthSoldiers->getSize();
    int earthTanksCount = earthTanks->size();

    Queue<Unit*> tempEarthSoldiers;
    Queue<Unit*> tempEarthTanks;

    for (int i = 0; i < attackCapacity; i++) {
        if (!earthSoldiers->isEmpty()) {
            Unit* soldier = earthSoldiers->dequeue();
            int newHealth = soldier->getCurrentHealth() - ((getPower() * getCurrentHealth() / 100) / sqrt(soldier->getCurrentHealth()));
            soldier->setCurrentHealth(newHealth, game->getTimestep());
            addAttackedUnitId(soldier->getId());

            if (newHealth <= 0) {
                game->addKilledUnit(soldier);
            }
            else if (newHealth <= 0.2 * soldier->getInitialHealth()) {
                game->addToUML(soldier);
            }
            else {
                tempEarthSoldiers.enqueue(soldier);
            }
        }

        if (!earthTanks->isEmpty()) {
            Unit* tank = earthTanks->pop();
            int newHealth = tank->getCurrentHealth() - getPower();
            tank->setCurrentHealth(newHealth, game->getTimestep());
            addAttackedUnitId(tank->getId());

            if (newHealth <= 0) {
                game->addKilledUnit(tank);
            }
            else if (newHealth <= 0.2 * tank->getInitialHealth()) {
                game->addToUML(tank);
            }
            else {
                tempEarthTanks.enqueue(tank);
            }
        }

        if (earthSoldiers->isEmpty() && earthTanks->isEmpty()) {
            break;
        }
    }

    while (!tempEarthSoldiers.isEmpty()) {
        earthSoldiers->enqueue(tempEarthSoldiers.dequeue());
    }

    while (!tempEarthTanks.isEmpty()) {
        earthTanks->push(tempEarthTanks.dequeue());
    }

}

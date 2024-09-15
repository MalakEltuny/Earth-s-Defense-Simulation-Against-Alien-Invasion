#include "AlienDrone.h"
#include "Game.h"
void AlienDrone::attack(Game* game) {
    PriorityQueue<Unit*>* earthGunneryUnits = game->getEarthArmy()->getEarthGunneries();
    Stack<Unit*>* earthTanks = game->getEarthArmy()->getEarthTanks();

    int attackCapacity = getAttackCapacity();

    Queue<Unit*> tempEarthGunneryUnits;
    Queue<Unit*> tempEarthTanks;

    for (int i = 0; i < attackCapacity; i++) {
        
        if (!earthGunneryUnits->isEmpty()) {
            Unit* gunnery = earthGunneryUnits->remove();
            int newHealth = gunnery->getCurrentHealth() - ((getPower() * getCurrentHealth() / 100) / sqrt(gunnery->getCurrentHealth()));
            gunnery->setCurrentHealth(newHealth, game->getTimestep());

            addAttackedUnitId(gunnery->getId());

            if (newHealth <= 0) {
                game->addKilledUnit(gunnery);
            }
            else {
                tempEarthGunneryUnits.enqueue(gunnery);
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

        if (earthGunneryUnits->isEmpty() && earthTanks->isEmpty()) {
            break;
        }
    }


    while (!tempEarthGunneryUnits.isEmpty()) {
        int priority = tempEarthGunneryUnits.peek()->getPower() * tempEarthGunneryUnits.peek()->getCurrentHealth() * -1;
        earthGunneryUnits->insert(tempEarthGunneryUnits.dequeue(), priority);
    }

    while (!tempEarthTanks.isEmpty()) {
        earthTanks->push(tempEarthTanks.dequeue());
    }

}

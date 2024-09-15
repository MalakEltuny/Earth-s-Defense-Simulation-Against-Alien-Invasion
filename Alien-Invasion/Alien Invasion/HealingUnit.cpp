#include "HealingUnit.h"
#include "Game.h"

void HealingUnit::attack(Game* game) {
    PriorityQueue<Unit*>* umlsoldiers = game->getSoldiersUML();
    Queue<Unit*>* umltanks = game->getTanksUML();

    Queue<Unit*>* tempSoldiers = new Queue<Unit*>();
    Queue<Unit*>* tempTanks = new Queue<Unit*>();

    Queue<Unit*>* earthSoldiers = game->getEarthArmy()->getEarthSoldiers();
    Stack<Unit*>* earthTanks = game->getEarthArmy()->getEarthTanks();

    int healCapacity = getAttackCapacity();
    

    for (int i = 0; i < healCapacity; i++) {
        if (!umlsoldiers->isEmpty()) {
            Unit* soldier = umlsoldiers->remove();
            int newHealth = soldier->getCurrentHealth() + ((getPower() * getCurrentHealth()/100) / sqrt(soldier->getCurrentHealth()));
            soldier->setCurrentHealth(newHealth,game->getTimestep());
            addAttackedUnitId(soldier->getId());

            if (newHealth >= 0.2* soldier->getInitialHealth()) {
                earthSoldiers->enqueue(soldier);
            }
            else {
                tempSoldiers->enqueue(soldier);
            }
        }
        else if (!umltanks->isEmpty()) {
            Unit* tank = umltanks->dequeue();
            int newHealth = tank->getCurrentHealth() + ((getPower() * getCurrentHealth() / 100) / sqrt(tank->getCurrentHealth()));
            tank->setCurrentHealth(newHealth, game->getTimestep());
            addAttackedUnitId(tank->getId());

            if (newHealth >= 0.2 * tank->getInitialHealth()) {
                earthTanks->push(tank);
            }
            else {
                tempTanks->enqueue(tank);
            }

        }
        else {
            break;
        }

          }
    while (!tempSoldiers->isEmpty()) {
        Unit* unit = tempSoldiers->dequeue();
        game->addToUML(unit);
    }

    while (!tempTanks->isEmpty()) {
        Unit* unit = tempTanks->dequeue();
        game->addToUML(unit);
    }

   

}

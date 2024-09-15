#include "EarthTank.h"
#include "Game.h"

void EarthTank::attack(Game* game) {
    AlienMonstersArray* alienMonstersArray = game->getAlienArmy()->getAlienMonsters();
    Queue<Unit*>* earthSoldiers = game->getEarthArmy()->getEarthSoldiers();
    Queue<Unit*>* alienSoldiers = game->getAlienArmy()->getAlienSoldiers();

    int tankCapacity = getAttackCapacity();
    int earthSoldiersCount = earthSoldiers->getSize();
    int alienSoldiersCount = alienSoldiers->getSize();

    Queue<Unit*> tempMonsters;
    Queue<Unit*> tempAlienSoldiers;

    for (int i = 0; i < tankCapacity; i++) {
        if (!alienMonstersArray->isEmpty()) {
            Unit* monster = alienMonstersArray->removeMonster();
            int newHealth = monster->getCurrentHealth() - ((getPower() * getCurrentHealth() / 100) / sqrt(monster->getCurrentHealth()));

            if (newHealth <= 0) {
                game->addKilledUnit(monster);
            }
            else {
                monster->setCurrentHealth(newHealth, game->getTimestep());
                addAttackedUnitId(monster->getId());
                tempMonsters.enqueue(monster);
            }
        }
        else if (!alienSoldiers->isEmpty() && earthSoldiersCount < 0.3 * alienSoldiersCount) {
            Unit* alienSoldier = alienSoldiers->dequeue();
            int newHealth = alienSoldier->getCurrentHealth() - ((getPower() * getCurrentHealth() / 100) / sqrt(alienSoldier->getCurrentHealth()));

            if (newHealth <= 0) {
                game->addKilledUnit(alienSoldier);
            }
            else {
                alienSoldier->setCurrentHealth(newHealth, game->getTimestep());
                addAttackedUnitId(alienSoldier->getId());
                tempAlienSoldiers.enqueue(alienSoldier);
            }
        }
        else {
            break;
        }

        earthSoldiersCount = earthSoldiers->getSize();
        alienSoldiersCount = alienSoldiers->getSize();
    }

    while (!tempMonsters.isEmpty()) {
        alienMonstersArray->addMonster(tempMonsters.dequeue());
    }

    while (!tempAlienSoldiers.isEmpty()) {
        alienSoldiers->enqueue(tempAlienSoldiers.dequeue());
    }
}

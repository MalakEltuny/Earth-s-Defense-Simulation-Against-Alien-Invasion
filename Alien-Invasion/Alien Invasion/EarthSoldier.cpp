#include"EarthSoldier.h"
#include "Game.h"

void EarthSoldier::attack(Game* game)
{
    Queue<Unit*>* alienSoldiers = game->getAlienArmy()->getAlienSoldiers();

    Queue<Unit*> temp;

    int attackCapacity = getAttackCapacity();
    for (int i = 0; i < attackCapacity; i++)
    {
        if (!alienSoldiers->isEmpty()) {
            Unit* alienSoldier = alienSoldiers->dequeue();
            int newHealth = alienSoldier->getCurrentHealth() - ((getPower() * getCurrentHealth() / 100) / sqrt(alienSoldier->getCurrentHealth()));

            alienSoldier->setCurrentHealth(newHealth,game->getTimestep());

            addAttackedUnitId(alienSoldier->getId());

            if (alienSoldier->getCurrentHealth() <= 0)
            {
                game->addKilledUnit(alienSoldier);
            }
            else
            {
                temp.enqueue(alienSoldier);
            }
        }
    }

    while (!temp.isEmpty()) {
        alienSoldiers->enqueue(temp.dequeue());
    }

}

#include "AlienSolider.h"
#include "Game.h"

void AlienSoldier::attack(Game* game)
{
    Queue<Unit*>* earthSoldierQueue = game->getEarthArmy()->getEarthSoldiers();
    Queue<Unit*> temp;

    int attackCapacity = getAttackCapacity();
    for (int i = 0; i < attackCapacity && !earthSoldierQueue->isEmpty(); i++)
    {
        if (!earthSoldierQueue->isEmpty()) {
            Unit* earthSoldier = earthSoldierQueue->dequeue();
            int newHealth = earthSoldier->getCurrentHealth() - ((getPower() * getCurrentHealth() / 100) / sqrt(earthSoldier->getCurrentHealth()));
            earthSoldier->setCurrentHealth(newHealth,game->getTimestep());
            addAttackedUnitId(earthSoldier->getId());

            if (earthSoldier->isDead())
            {
                game->addKilledUnit(earthSoldier);
            }
            else if (earthSoldier->getCurrentHealth() < 0.2 * earthSoldier->getInitialHealth())
            {
                game->addToUML(earthSoldier);
            }
            else
            {
                temp.enqueue(earthSoldier);

            }
        }
    }

    while (!earthSoldierQueue->isEmpty())
	{
		temp.enqueue(earthSoldierQueue->dequeue());
	}
}

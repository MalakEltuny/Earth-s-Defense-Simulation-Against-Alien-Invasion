#include"EarthGunnery.h"
#include "Game.h"

void EarthGunnery::attack(Game* game)
{

    Queue<Unit*>tempMonster;
    Queue<Unit*>tempdrone;
    // Get the list of AM units that EG should attack
    AlienArmy* aaList = game->getAlienArmy();
    AlienMonstersArray* amList = aaList->getAlienMonsters();


    // Get the number of AM units that EG can attack
    int numAMToAttack = attackCapacity;
    if (numAMToAttack > amList->getSize())
    {
        numAMToAttack = amList->getSize();
    }

    // Attack each AM unit
    for (int i = 0; i < numAMToAttack; ++i) {
        // Get the first AM unit from the list
        Unit* amToAttack = amList->removeMonster();

        // Attack the AM unit

        int health = amToAttack->getCurrentHealth() - ((getPower() * getCurrentHealth() / 100) / sqrt(amToAttack->getCurrentHealth()));
        amToAttack->setCurrentHealth(health, game->getTimestep());

        addAttackedUnitId(amToAttack->getId());

        // If the health of the AM unit is 0 or less, remove it from the list
        if (amToAttack->getCurrentHealth() <= 0) {

            game->addKilledUnit(amToAttack);
        }
        else
        {
            tempMonster.enqueue(amToAttack);
        }
    }
    while (!tempMonster.isEmpty())
    {
        amList->addMonster(tempMonster.dequeue());
    }


    // Get the list of Ad units that EG should attack
    Dequeue<Unit*>* adList = aaList->getAlienDrones();


    // Get the number of Ad units that EG can attack
    numAMToAttack = attackCapacity;
    if (numAMToAttack > adList->getSize())
    {
        numAMToAttack = adList->getSize();
    }

    // Attack each Ad unit
    for (int i = 0; i < numAMToAttack; ++i) {
        // Get the first AD unit from the list
        if (adList->getSize() > 1) {
            Unit* adToAttack1 = adList->popFront();
            Unit* adToAttack2 = adList->popFront();
            // Attack the ADunit

            int health1 = adToAttack1->getCurrentHealth()- ((getPower() * getCurrentHealth() / 100) / sqrt(adToAttack1->getCurrentHealth()));

            adToAttack1->setCurrentHealth(health1 -= power, game->getTimestep());
            int health2 = adToAttack2->getCurrentHealth()- ((getPower() * getCurrentHealth() / 100) / sqrt(adToAttack1->getCurrentHealth()));

            adToAttack2->setCurrentHealth(health2 -= power, game->getTimestep());

            addAttackedUnitId(adToAttack2->getId());
            

            // If the health of the AD unit is 0 or less, remove it from the list
            if (adToAttack1->getCurrentHealth() <= 0) {

                game->addKilledUnit(adToAttack1);
            }
            else
            {
                tempdrone.enqueue(adToAttack1);


            }
            // If the health of the AD unit is 0 or less, remove it from the list
            if (adToAttack2->getCurrentHealth() <= 0) {

                game->addKilledUnit(adToAttack2);
            }
            else
            {
                tempdrone.enqueue(adToAttack2);
            }

        }
        else if (adList->getSize() == 1)
        {
            Unit* adToAttack1 = adList->popFront();
            // Attack the AD unit

            int health = adToAttack1->getCurrentHealth();
            adToAttack1->setCurrentHealth(health -= power, game->getTimestep());

            // If the health of the AD unit is 0 or less, remove it from the list
            if (adToAttack1->getCurrentHealth() <= 0) {

                game->addKilledUnit(adToAttack1);
            }
            else {
                tempdrone.enqueue(adToAttack1);

            }
        }
        else { break; }



    }
    while (!tempdrone.isEmpty())
    {
        adList->pushBack(tempdrone.dequeue());
    }


}

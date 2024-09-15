#pragma once
#include <string>
using namespace std;
class Game;

class Unit
{
protected:
    int id;
    int joinTime;
    int firstattackTime;
    int firstshotTime;
    int destructionTime;
    int initialHealth;
    int currentHealth;
    int power;
    int attackCapacity;
    int umlTime;

    int* attackedUnitIds;
    int attackedUnitIdsCount;
    string type;
    bool isAttacked;
    bool isShot;
    //TODO killed time; and its setters and getters:done
    //TODO bool isShot, isAttacked. give them false values in the constructor, create setters and getters for them:done
    //TODO firstShotTime, firstAttackTime. Create setters and getters for them:done

public:
    Unit(int id, int health, int power, int attackCapacity, string type);

    virtual void attack(Game* game) = 0;

    int getInitialHealth();
    int getCurrentHealth();
    int getPower();
    int getAttackCapacity();
    int getId();
    int getJoinTime();
    int getUmlTime();
    int getfirstattackTime();
    int getfirstshotTime();
    int getdestructionTime();
    int getfirstAttackDelay();
    int getdestructionDelay();
    int getbattleTime();
    bool getisAttacked();
    bool getisShot();

    //done
    //TODO firstAttackDelay getter -> return first attack time - join time
    //TODO destruction delay getter -> return killed time - join time
    //TODO battle time getter -> return killed time - first attack time

    void setCurrentHealth(int health, int timestep);
    void setJoinTime(int joinTime);
    void setUmlTime(int umlTime);
    void setfirstattackTime(int firstattackTime);
    void setfirstshotTime(int firstshotTime);
    void setdestructionTime(int destructionTime);
    void setisAttacked(bool);
    void setisShot(bool);

    bool isDead();
    bool isAlive();

    void addAttackedUnitId(int unitId);
    void printAttackedUnitIds();
    void resetAttackedUnitIds();

};


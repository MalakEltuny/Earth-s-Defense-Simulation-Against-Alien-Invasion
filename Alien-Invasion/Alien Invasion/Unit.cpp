#include "Unit.h"
#include <iostream>
using namespace std;

Unit::Unit(int id, int health, int power, int attackCapacity, string type)
	: id(id), initialHealth(health), power(power), attackCapacity(attackCapacity) , type(type)
{
	joinTime = 0;
	currentHealth = health;
	attackedUnitIds = new int[attackCapacity * 2];
	attackedUnitIdsCount = 0;
	umlTime = 0;
	isAttacked = false;
	isShot = false;
}

int Unit::getInitialHealth() { return initialHealth; }
int Unit::getCurrentHealth() { return currentHealth; }
int Unit::getPower() { return power; }
int Unit::getAttackCapacity() { return attackCapacity; }
int Unit::getId() { return id; }
int Unit::getJoinTime() { return joinTime; }

int Unit::getUmlTime()
{
	return umlTime;
}

int Unit::getfirstattackTime()
{
	return firstattackTime ;
}

int Unit::getfirstshotTime()
{
	return firstshotTime;
}

int Unit::getdestructionTime()
{
	return destructionTime;
}

int Unit::getfirstAttackDelay()
{
	return firstattackTime - joinTime;
}

int Unit::getdestructionDelay()
{
	return destructionTime-firstattackTime;
}

int Unit::getbattleTime()
{
	return destructionTime-joinTime;
}

bool Unit::getisAttacked()
{
	return isAttacked;
}

bool Unit::getisShot()
{
	return isShot;
}

void Unit::setCurrentHealth(int health, int timestep) { 
	//TODO check if the current health is equal to the initial health, if so, set the first attacked time and flag to false
	if (currentHealth == initialHealth) {
		setfirstattackTime(timestep);
		setisAttacked(true);
	}
	
	currentHealth = health; 
}
void Unit::setJoinTime(int joinTime) { this->joinTime = joinTime; }
void Unit::setUmlTime(int umlTime) { this->umlTime = umlTime; }

void Unit::setfirstattackTime(int firstattackTime)
{
	this->firstattackTime = firstattackTime;
}

void Unit::setfirstshotTime(int firstshotTime)
{
	this->firstshotTime = firstshotTime;
}

void Unit::setdestructionTime(int destructionTime)
{
	this->destructionTime = destructionTime;
}

void Unit::setisAttacked(bool isAtt)
{
	isAttacked = isAtt;
}

void Unit::setisShot(bool shot)
{
	isShot = shot;
}

bool Unit::isDead() { return currentHealth <= 0; }
bool Unit::isAlive() { return currentHealth > 0; }

void Unit::addAttackedUnitId(int unitId)
{
	attackedUnitIds[attackedUnitIdsCount++] = unitId;
}

void Unit::printAttackedUnitIds()
{
	cout << type << " " << id << " shots [";
	for (int i = 0; i < attackedUnitIdsCount; i++)
	{
		cout << attackedUnitIds[i] << ", ";
	}
	cout << "]" << endl;
}

void Unit::resetAttackedUnitIds()
{
	delete attackedUnitIds;
	attackedUnitIds = new int[attackCapacity * 2];
	attackedUnitIdsCount = 0;
}



#pragma once
class Unit;
#include <fstream>
#include <iostream>
#include "RandGen.h"
#include "EarthArmy.h"
#include "AlienArmy.h"
#include "Queue.h"

class Game {
private:
    RandGen* randomGenerator;
    EarthArmy* earthArmy;
    AlienArmy* alienArmy;
    Queue<Unit*>* killedUnits;
    PriorityQueue<Unit*>* umlEarthSoldiers;
    Queue<Unit*>* umlEarthTanks;
    void readFile();
    void armiesAttack();

    int timestep;
    int mode;
    int winner;

public:
    Game();
    ~Game(); // Destructor

    void startSimulation();

    // Getter methods
    AlienArmy* getAlienArmy();
    EarthArmy* getEarthArmy();
    PriorityQueue<Unit*>* getSoldiersUML();
    Queue<Unit*>* getTanksUML();
    int getTimestep();

    // Add killed unit
    void addKilledUnit(Unit* unit);

    void addToUML(Unit* unit);
    void checkandmovetokilledlist(Unit* unit);
    void outputFile();

};

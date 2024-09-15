#include "Game.h"

void Game::readFile() {
	ifstream file("input.txt");
	int n;
	file >> n;

	int es, et, eg, hu;
	file >> es >> et >> eg >> hu;
	int as, am, ad;
	file >> as >> am >> ad;

	int prob;
	file >> prob;

	int powerMin, powerMax;
	int healthMin, healthMax;
	int attackMin, attackMax;
	char dash;
	file >> powerMin >> dash >> powerMax;
	file >> healthMin >> dash >> healthMax;
	file >> attackMin >> dash >> attackMax;

	int powerMinA, powerMaxA;
	int healthMinA, healthMaxA;
	int attackMinA, attackMaxA;
	file >> powerMinA >> dash >> powerMaxA;
	file >> healthMinA >> dash >> healthMaxA;
	file >> attackMinA >> dash >> attackMaxA;

	randomGenerator = new RandGen(n, es, et, eg, hu, as, am, ad, prob,
		{ powerMin, powerMax, healthMin, healthMax, attackMin, attackMax },
		{ powerMinA, powerMaxA, healthMinA, healthMaxA, attackMinA, attackMaxA }
	);
}

void Game::armiesAttack() {
	Queue<Unit*> attackingEarthUnits = earthArmy->attackingEarthUnits();
	Queue<Unit*> attackingAlienUnits = alienArmy->attackingAlienUnits();

	while (!attackingEarthUnits.isEmpty()) {
		Unit* unit = attackingEarthUnits.dequeue();
		unit->attack(this);
		if (!unit->getisShot()) {
			unit->setisShot(true);
			unit->setfirstshotTime(timestep);
		}
		if (mode == 1) {
			unit->printAttackedUnitIds();

		}
		unit->resetAttackedUnitIds();
	}

	while (!attackingAlienUnits.isEmpty()) {
		Unit* unit = attackingAlienUnits.dequeue();
		unit->attack(this);
		if (!unit->getisShot()) {
			unit->setisShot(true);
			unit->setfirstshotTime(timestep);
		}
		if (mode == 1) {
			unit->printAttackedUnitIds();

		}
		unit->resetAttackedUnitIds();
	}
}

Game::Game() {
	earthArmy = new EarthArmy();
	alienArmy = new AlienArmy();
	killedUnits = new Queue<Unit*>();
	umlEarthSoldiers = new PriorityQueue<Unit*>();
	umlEarthTanks = new Queue<Unit*>();
	timestep = 0;
	readFile();
}

Game::~Game() {
	delete randomGenerator;
	delete earthArmy;
	delete alienArmy;
	delete killedUnits;
}

void Game::startSimulation() {
	cout << "Choose the mode\n1. Interactive\n2. Silent\n";
	cin >> mode;
	if (mode != 1 && mode != 2) {
		cout << "Invalid mode\n";
		return;
	}
	for (timestep = 0; timestep <= 40 || (!earthArmy->allListsEmpty() && !alienArmy->allListsEmpty()); timestep++) {
		randomGenerator->generateUnit(earthArmy, alienArmy, timestep);
		if (mode == 1) {
			cout << "Current timestep: " << timestep << endl;

			earthArmy->printArmy();
			alienArmy->printArmy();

			cout << "======== Units Fighting at current step ========\n";

		}

		armiesAttack();

		if (mode == 1) {
			cout << "======== Killed Units ========\n" << killedUnits->getSize() << " units ";
			killedUnits->print();

			cout << endl;
			//wiat for input
			cin.get();
		}
	}
	if (earthArmy->allListsEmpty()) {
		winner = 1;
	}
	else {
		winner = 2;
	}
	outputFile();

}


AlienArmy* Game::getAlienArmy() {
	return alienArmy;
}

EarthArmy* Game::getEarthArmy() {
	return earthArmy;
}

PriorityQueue<Unit*>* Game::getSoldiersUML()
{
	return umlEarthSoldiers;
}

Queue<Unit*>* Game::getTanksUML()
{
	return umlEarthTanks;
}

int Game::getTimestep()
{
	return timestep;
}

void Game::addKilledUnit(Unit* unit) {
	unit->setdestructionTime(timestep);
	killedUnits->enqueue(unit);
}

void Game::addToUML(Unit* unit)
{
	unit->setUmlTime(timestep);
	//check if unit is soldier or tank
	if (dynamic_cast<EarthSoldier*>(unit)) {
		umlEarthSoldiers->insert(unit, unit->getCurrentHealth());
	}
	else if (dynamic_cast<EarthTank*>(unit)) {
		umlEarthTanks->enqueue(unit);
	}
	else {
		throw "wrong unit";
	}
}
void Game::outputFile()
{
	// generate output file
	ofstream output("output.txt");
	while (!killedUnits->isEmpty())
	{
		Unit* unit = killedUnits->dequeue();
		// TODO
		//output << unit->getId() << " " << unit->getPower() << " " << unit->getCurrentHealth() << " " << unit->getAttack() << endl;
		int totalEarthSolidersCount = randomGenerator->getEarthSoldierCount();
		int totaltanksscount = randomGenerator->getEarthTankCount();
		int totalgunnrycount = randomGenerator->getEarthGunneryCount();
		int totalHealingUnits = randomGenerator->getHealingUnitCount();

		int totalAlienSoldiers = randomGenerator->getAlienSoldierCount();
		int totalAlienMonsters = randomGenerator->getAlienMonsterCount();
		int totalAlienDrones = randomGenerator->getAlienDroneCount();

		int totalDeadEarthSoliders = 0;
		int totalDeadTanks = 0;
		int totalDeadGunnery = 0;
		int totalDeadAlienSoldiers = 0;
		int totalDeadAlienMonsters = 0;
		int totalDeadAlienDrones = 0;
		int totalDeadHealingUnits = 0;

		int earthDfTotal = 0;
		int earthDdTotal = 0;
		int earthDbTotal = 0;

		int alienDfTotal = 0;
		int alienDdTotal = 0;
		int alienDbTotal = 0;

		output << "Td\tID\t\tTj\tDf\tDd\tDb\n";

		while (!killedUnits->isEmpty()) {
			Unit* unit = killedUnits->dequeue();
			output << unit->getdestructionTime() << "\t"
				<< unit->getId() << "\t"
				<< unit->getJoinTime() << "\t"
				<< unit->getfirstAttackDelay() << "\t"
				<< unit->getdestructionDelay() << "\t"
				<< unit->getbattleTime() << endl;
			if (dynamic_cast<EarthSoldier*>(unit)) {
				totalDeadEarthSoliders++;
				earthDfTotal += unit->getfirstshotTime();
				earthDdTotal += unit->getUmlTime();
				earthDbTotal += unit->getdestructionTime();
			}
			else if (dynamic_cast<EarthTank*>(unit)) {
				totalDeadTanks++;
				earthDfTotal += unit->getfirstshotTime();
				earthDdTotal += unit->getUmlTime();
				earthDbTotal += unit->getdestructionTime();
			}
			else if (dynamic_cast<EarthGunnery*>(unit)) {
				totalDeadGunnery++;
				earthDfTotal += unit->getfirstshotTime();
				earthDdTotal += unit->getUmlTime();
				earthDbTotal += unit->getdestructionTime();
			}
			else if (dynamic_cast<AlienSoldier*>(unit)) {
				totalDeadAlienSoldiers++;
				alienDfTotal += unit->getfirstshotTime();
				alienDdTotal += unit->getUmlTime();
				alienDbTotal += unit->getdestructionTime();
			}
			else if (dynamic_cast<AlienMonster*>(unit)) {
				totalDeadAlienMonsters++;
				alienDfTotal += unit->getfirstshotTime();
				alienDdTotal += unit->getUmlTime();
				alienDbTotal += unit->getdestructionTime();
			}
			else if (dynamic_cast<AlienDrone*>(unit)) {
				totalDeadAlienDrones++;
				alienDfTotal += unit->getfirstshotTime();
				alienDdTotal += unit->getUmlTime();
				alienDbTotal += unit->getdestructionTime();
			}
			else if (dynamic_cast<HealingUnit*>(unit)) {
				totalDeadHealingUnits++;
			}
		}
		// Announce winner
		output << "Winner: " << (winner == 1 ? "Earth" : "Alien") << "Army\n";
		//Earth Army Stats
		output << "Total Earth Soliders: " << totalEarthSolidersCount << endl;
		output << "Total Tanks: " << totaltanksscount << endl;
		output << "Total Gunnery: " << totalgunnrycount << endl;
		output << "Total Healing Units: " << totalHealingUnits << endl;
		//total dead units / total units
		output << "Percentage of total dead units realtive to total Earth Army Units: " <<
			(double)(totalDeadEarthSoliders + totalDeadTanks + totalDeadGunnery + totalDeadHealingUnits) /
			(double)(totalEarthSolidersCount + totaltanksscount + totalgunnrycount + totalHealingUnits) * 100 << "%" << endl;

		// Percentage of dead units relative to the total number of units, keep in mind casting to double
		output << "Percentage of dead Earth Soliders: " << (double)totalDeadEarthSoliders / (double)totalEarthSolidersCount * 100 << "%" << endl;
		output << "Percentage of dead Tanks: " << (double)totalDeadTanks / (double)totaltanksscount * 100 << "%" << endl;
		output << "Percentage of dead Gunnery: " << (double)totalDeadGunnery / (double)totalgunnrycount * 100 << "%" << endl;
		output << "Percentage of dead Healing Units: " << (double)totalDeadHealingUnits / (double)totalHealingUnits * 100 << "%" << endl;
		// Average Df, Dd, Db for Earth Army
		output << "Average Df for Earth Army: " << (double)earthDfTotal / (double)(totalDeadEarthSoliders + totalDeadTanks + totalDeadGunnery) << endl;
		output << "Average Dd for Earth Army: " << (double)earthDdTotal / (double)(totalDeadEarthSoliders + totalDeadTanks + totalDeadGunnery) << endl;
		output << "Average Db for Earth Army: " << (double)earthDbTotal / (double)(totalDeadEarthSoliders + totalDeadTanks + totalDeadGunnery) << endl;
		// df/db%, dd/db%
		output << "Df/Db% for Earth Army: " << (double)earthDfTotal / (double)earthDbTotal * 100 << "%" << endl;
		output << "Dd/Db% for Earth Army: " << (double)earthDdTotal / (double)earthDbTotal * 100 << "%" << endl;

		//Alien Army Stats
		output << "Total Alien Soliders: " << totalAlienSoldiers << endl;
		output << "Total Alien Monsters: " << totalAlienMonsters << endl;
		output << "Total Alien Drones: " << totalAlienDrones << endl;
		//total dead units / total units
		output << "Percentage of total dead units realtive to total Alien Army Units: " <<
			(double)(totalDeadAlienSoldiers + totalDeadAlienMonsters + totalDeadAlienDrones) /
			(double)(totalAlienSoldiers + totalAlienMonsters + totalAlienDrones) * 100 << "%" << endl;

		// Percentage of dead units relative to the total number of units, keep in mind casting to double
		output << "Percentage of dead Alien Soliders: " << (double)totalDeadAlienSoldiers / (double)totalAlienSoldiers * 100 << "%" << endl;
		output << "Percentage of dead Alien Monsters: " << (double)totalDeadAlienMonsters / (double)totalAlienMonsters * 100 << "%" << endl;
		output << "Percentage of dead Alien Drones: " << (double)totalDeadAlienDrones / (double)totalAlienDrones * 100 << "%" << endl;
		// Average Df, Dd, Db for Alien Army
		output << "Average Df for Alien Army: " << (double)alienDfTotal / (double)(totalDeadAlienSoldiers + totalDeadAlienMonsters + totalDeadAlienDrones) << endl;
		output << "Average Dd for Alien Army: " << (double)alienDdTotal / (double)(totalDeadAlienSoldiers + totalDeadAlienMonsters + totalDeadAlienDrones) << endl;
		output << "Average Db for Alien Army: " << (double)alienDbTotal / (double)(totalDeadAlienSoldiers + totalDeadAlienMonsters + totalDeadAlienDrones) << endl;
		// df/db%, dd/db%
		output << "Df/Db% for Alien Army: " << (double)alienDfTotal / (double)alienDbTotal * 100 << "%" << endl;
		output << "Dd/Db% for Alien Army: " << (double)alienDdTotal / (double)alienDbTotal * 100 << "%" << endl;


	}

}


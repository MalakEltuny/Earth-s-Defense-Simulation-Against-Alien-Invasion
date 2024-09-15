### 1- Create the Unit class. Include appropriate getters and setters for data members
### 2- Create EarthSoldier, AlienSoldier, EarthTank, AlienMonster, EarthGunnery, AlienDrone, and HealingUnit classes that inherites from the Unit class
### //The attack function will be discussed but its implmentation will be done in phase 2
### 3- Create the DSs classes. Queue, Stack and Priority Queue
### // We should discuss the need to create a seperate class for each list
### 4- Lists for each unit
### 	Soldiers -> Queue
### 	Tanks -> Stack
### 	Gunnery -> Priority Queue
### 	Monsters -> Array
### 	Healers -> Stack
### 	Unit Maintenance -> Priority Queue
### 	Drones -> Modified Queue
### 5- Create the Random Generator class. Initially it will take N, Prob, each unit probability and ranges as constructor arguments. It will have a function that generates a new Unit that returns a pointer to it
### 6- Create a class for each army holding lists for each unit type with the ability to add, remove and print units
### 7- Create the Game class that reads data from input file and insert it in the random generator class. Also has a function that starts the simulation loop
### 
### 
## Simulation Loop Logic:
### 
### 1- Read data from the input file
### 
### 2- Pass the data to Random Generator class
### 
### //The following is repeated for 50 timesteps
### 3- Call the RG, add the new units ,if there are any, to their lists
### 
### 4- Generate a number from 1 to 100:
### 	Refer to the document for further details
### 
### 5- Print the output screen
### 
### //End of the loop

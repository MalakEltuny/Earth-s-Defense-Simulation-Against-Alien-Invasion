#pragma once
#include "Unit.h"
#include <stdlib.h>
#include <iostream>
using namespace std;
class AlienMonstersArray
{
	Unit** alienMonsters;
	int size;
	int capacity;
public:
	AlienMonstersArray(int capacity = 10) {
		this->size = 0;
		this->capacity = capacity;
		this->alienMonsters = new Unit * [capacity];
	}

	void addMonster(Unit* monster) {
		// if the array is full, double the capacity
		if (size == capacity) {
			capacity *= 2;
			Unit** newAlienMonsters = new Unit * [capacity];
			for (int i = 0; i < size; i++) {
				newAlienMonsters[i] = alienMonsters[i];
			}
			delete[] alienMonsters;
			alienMonsters = newAlienMonsters;
		}
		alienMonsters[size++] = monster;
	}

	Unit* removeMonster() {
		if (size == 0) {
			return nullptr;
		}
		int index = rand() % size;
		Unit* monster = alienMonsters[index];
		alienMonsters[index] = alienMonsters[size - 1];
		size--;
		return monster;
	}

	Unit* operator[](int index) {
		if (index < 0 || index >= size) {
			return nullptr;
		}
		return alienMonsters[index];
	}

	int getSize() {
		return size;
	}

	bool isEmpty() {
		return size == 0;
	}

	void printIDs() {
		for (int i = 0; i < size; i++) {
			cout << alienMonsters[i]->getId() << " ";
		}
	}

	void print() {
		cout << "[";

		for (int i = 0; i < size; i++) {
			cout << alienMonsters[i]->getId();
			if (i < size - 1) {
				cout << ", ";
			}
		}

		cout << "]\n";
	}
};


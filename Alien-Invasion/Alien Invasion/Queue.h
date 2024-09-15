#pragma once
#include "Node.h"
#include <iostream>
using namespace std;

template <class T>
class Queue
{
	Node<T>* head;
	Node<T>* tail;
	int size;
public:
	Queue() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	~Queue() {
		while (head != nullptr) {
			Node<T>* temp = head;
			head = head->getNext();
			delete temp;
		}
	}

	void enqueue(T data) {
		Node<T>* temp = new Node<T>(data);
		if (head == nullptr) {
			head = temp;
			tail = temp;
		}
		else {
			tail->setNext(temp);
			tail = temp;
		}
		size++;
	}

	T dequeue() {
		if (head == nullptr) {
			throw "Queue is empty";
		}
		T data = head->getValue();
		Node<T>* temp = head;
		head = head->getNext();
		delete temp;
		size--;
		return data;
	}

	T peek() {
		if (head == nullptr) {
			throw "Queue is empty";
		}
		return head->getValue();
	}

	int getSize() {
		return size;
	}

	bool isEmpty() {
		return size == 0;
	}

	void print() {
		cout <<"[";

		Node<T>* temp = head;
		while (temp != nullptr) {
			// cast to Unit* to print the Unit
			Unit* u = (Unit*)temp->getValue();
			cout << u->getId() << ", ";
			temp = temp->getNext();
		}

		cout << "]\n";
	}
};


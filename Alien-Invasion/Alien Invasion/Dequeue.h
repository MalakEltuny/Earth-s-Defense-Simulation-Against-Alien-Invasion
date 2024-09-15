#pragma once
#include "DequeuNode.h"
template <class T>
class Dequeue
{
	DequeuNode<T>* head;
	DequeuNode<T>* tail;
	int size;

public:
	Dequeue() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	void pushFront(T data) {
		DequeuNode<T>* newNode = new DequeuNode<T>(data);
		if (head == nullptr) {
			head = newNode;
			tail = newNode;
		}
		else {
			newNode->setNext(head);
			head->setPrev(newNode);
			head = newNode;
		}
		size++;
	}
	void pushBack(T data) {
		DequeuNode<T>* newNode = new DequeuNode<T>(data);
		if (tail == nullptr) {
			head = newNode;
			tail = newNode;
		}
		else {
			newNode->setPrev(tail);
			tail->setNext(newNode);
			tail = newNode;
		}
		size++;
	}
	T popFront() {
		if (head == nullptr) {
			throw "Dequeue is empty";
		}
		T data = head->getData();
		DequeuNode<T>* temp = head;
		head = head->getNext();
		if (head != nullptr) {
			head->setPrev(nullptr);
		}
		else {
			tail = nullptr;
		}
		delete temp;
		size--;
		return data;
	}
	T popBack() {
		if (tail == nullptr) {
			throw "Dequeue is empty";
		}
		T data = tail->getData();
		DequeuNode<T>* temp = tail;
		tail = tail->getPrev();
		if (tail != nullptr) {
			tail->setNext(nullptr);
		}
		else {
			head = nullptr;
		}
		delete temp;
		size--;
		return data;
	}
	T peekFront() {
		if (head == nullptr) {
			throw "Dequeue is empty";
		}
		return head->getData();
	}
	T peekBack() {
		if (tail == nullptr) {
			throw "Dequeue is empty";
		}
		return tail->getData();
	}
	int getSize() {
		return size;
	}
	bool isEmpty() {
		return size == 0;
	}

	void print() {
		cout << "[";

		DequeuNode<T>* temp = head;
		while (temp != nullptr) {
			// cast to Unit* to print the Unit
			Unit* u = (Unit*)temp->getData();
			cout << u->getId() << ", ";
			temp = temp->getNext();
		}

		cout << "]\n";
	}

};



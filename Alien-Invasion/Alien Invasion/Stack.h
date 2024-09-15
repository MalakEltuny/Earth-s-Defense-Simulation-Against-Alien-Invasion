#pragma once
#include "Node.h"
template <class T>

class Stack {
	int count;
	Node<T>* head;
	Node<T>* tail;
public:

	Stack() {
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	
	void push(T data) {
		Node<T>* temp = new Node<T>(data);
		if (head == nullptr) {
			head = temp;
			tail = temp;
		}
		else {
			temp->setNext(head);
			head = temp;
		}
		count++;
	}
	
	T pop() {
		if (head == nullptr) {
			return NULL;
		}
		else {
			Node<T>* temp = head;
			head = head->getNext();
			T data = temp->getValue();
			delete temp;
			count--;
			return data;
		}
	}
	
	T peek() {
		if (head == nullptr) {
			return NULL;
		}
		else {
			return head->getValue();
		}
	}
	
	int size() {
		return count;
	}
	
	bool isEmpty() {
		return count == 0;
	}
	
	void print() {
		cout << "[";

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
#pragma once
#include "PriorityNode.h"
template <class T>
class PriorityQueue
{
	//generate a linked priority queue with head and tail pointers and a size variable in this inline class
	PriorityNode<T>* head;
	PriorityNode<T>* tail;
	int size;
	//this is an inline class so all the functions are defined here

public:
	PriorityQueue()
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	//insert a new node in the queue
	void insert(T data, int priority)
	{
		PriorityNode<T>* newNode = new PriorityNode<T>(data, priority);
		if (head == nullptr)
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			PriorityNode<T>* temp = head;
			PriorityNode<T>* prev = nullptr;
			while (temp != nullptr && temp->getPriority() <= priority)
			{
				prev = temp;
				temp = temp->getNext();
			}
			if (prev == nullptr)
			{
				newNode->setNext(head);
				head = newNode;
			}
			else if (temp == nullptr)
			{
				tail->setNext(newNode);
				tail = newNode;
			}
			else
			{
				prev->setNext(newNode);
				newNode->setNext(temp);
			}
		}
		size++;
	}
	//remove the node with the highest priority
	T remove()
	{
		if (head == nullptr)
		{
			throw "Queue is empty";
		}
		T data = head->getData();
		PriorityNode<T>* temp = head;
		head = head->getNext();
		delete temp;
		size--;
		return data;
	}
	//return the size of the queue
	int getSize()
	{
		return size;
	}
	//return the data of the node with the highest priority
	T peek()
	{
		if (head == nullptr)
		{
			throw "Queue is empty";
		}
		return head->getData();
	}

	bool isEmpty()
	{
		return size == 0;
	}

	void print() {
		cout << "[";

		PriorityNode<T>* temp = head;
		while (temp != nullptr) {
			// cast to Unit* to print the Unit
			Unit* u = (Unit*)temp->getData();
			cout << u->getId() << ", ";
			temp = temp->getNext();
		}

		cout << "]\n";
	}
};


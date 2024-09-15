#pragma once
template <typename T>
class Node
{
	T value;
	Node* next;
public:
	Node(T value) {
		this->value = value;
		this->next = nullptr;
	}

	void setNext(Node* next) {
		this->next = next;
	}

	Node* getNext() {
		return next;
	}

	T getValue() {
		return value;
	}

	void setValue(T value) {
		this->value = value;
	}
};


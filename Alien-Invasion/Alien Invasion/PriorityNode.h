#pragma once
template <class T>
class PriorityNode
{
	PriorityNode<T>* next;
T data;
int priority;
public:
	PriorityNode(T data, int priority) {
		this->data = data;
		this->priority = priority;
		next = nullptr;
	}
	T getData() {
		return data;
	}
	int getPriority() {
		return priority;
	}
	PriorityNode<T>* getNext() {
		return next;
	}
	void setNext(PriorityNode<T>* next) {
		this->next = next;
	}
};


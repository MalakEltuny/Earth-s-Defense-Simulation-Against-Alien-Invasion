#pragma once
template <class T>
class DequeuNode {
	DequeuNode<T>* next;
	DequeuNode<T>* prev;
	T data;
public:
	DequeuNode(T data) {
		this->data = data;
		next = nullptr;
		prev = nullptr;
	}
	DequeuNode<T>* getNext() {
		return next;
	}
	DequeuNode<T>* getPrev() {
		return prev;
	}
	void setNext(DequeuNode<T>* next) {
		this->next = next;
	}
	void setPrev(DequeuNode<T>* prev) {
		this->prev = prev;
	}
	T getData() {
		return data;
	}
	void setData(T data) {
		this->data = data;
	}
};


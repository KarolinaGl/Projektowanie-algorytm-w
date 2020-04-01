#pragma once

template <typename T>
class Node
{
public:
	T data;
	Node<T>* next;

	T getElement() { return data; }

	void setElement(T element) { this->data = element; }

	Node* getNext() { return next; }

	void setNext(Node* next) { this->next = next; }
};

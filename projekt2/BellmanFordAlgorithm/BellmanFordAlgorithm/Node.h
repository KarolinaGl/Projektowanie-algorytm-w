#pragma once

template <typename T>
class Node
{
public:
	T element;
	Node<T>* next;

	T getElement() { return element; }

	void setElement(T element) { this->element = element; }

	Node* getNext() { return next; }

	void setNext(Node* next) { this->next = next; }
};

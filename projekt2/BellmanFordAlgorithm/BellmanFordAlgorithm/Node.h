#pragma once

class Node
{
	int element;
	Node* next;

public:

	int getElement() { return element; }

	void setElement(int element) { this->element = element; }

	Node* getNext() { return next; }

	void setNext(Node* next) { this->next = next; }

	friend class LinkedList;
};

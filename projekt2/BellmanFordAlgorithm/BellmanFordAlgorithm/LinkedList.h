#pragma once
#include <stdio.h>
#include "Node.h"

class LinkedList
{
	Node* head;

public:
	LinkedList() 
	{ 
		this->head = nullptr;
	}

	~LinkedList() {}

	int front();

	void addFront(const int& element);

	void removeFront();

	void print();

	bool empty();
};

bool LinkedList::empty()
{
	return head == nullptr;
}

int LinkedList::front()
{
	return head->element;
}

void LinkedList::addFront(const int& element)
{
	Node* newNode = new Node();
	newNode->element = element;
	newNode->next = head;
	head = newNode;
}

void LinkedList::removeFront()
{
	Node* firstElement = head;
	try
	{
		head = head->next;
		delete firstElement;
	}
	catch (std::exception &e)
	{
		std::cerr << "exception caught: " << e.what() << '\n';
	}
}

void LinkedList::print()
{
	Node* currentElement = head;
	while (currentElement != nullptr)
	{
		std::cout << currentElement->element << " ";
		currentElement = currentElement->next;
	}
}

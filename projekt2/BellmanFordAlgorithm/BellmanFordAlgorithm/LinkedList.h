#pragma once
#include <stdio.h>
#include "Node.h"

template <typename T>
class LinkedList
{
	Node<T>* head;

public:
	LinkedList() 
	{ 
		this->head = nullptr;
	}

	~LinkedList() {}

	T front();

	void addFront(const T& element);

	void removeFront();

	void print();

	bool empty();
};

template <typename T>
bool LinkedList<T>::empty()
{
	return head == nullptr;
}

template <typename T>
T LinkedList<T>::front()
{
	return head->element;
}

template <typename T>
void LinkedList<T>::addFront(const T& element)
{
	Node* newNode = new Node();
	newNode->element = element;
	newNode->next = head;
	head = newNode;
}

template <typename T>
void LinkedList<T>::removeFront()
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

template <typename T>
void LinkedList<T>::print()
{
	Node* currentElement = head;
	while (currentElement != nullptr)
	{
		std::cout << currentElement->element << " ";
		currentElement = currentElement->next;
	}
}

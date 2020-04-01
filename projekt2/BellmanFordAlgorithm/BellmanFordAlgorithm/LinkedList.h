#pragma once
#include <stdio.h>
#include "Node.h"

template <typename T>
class LinkedList
{
	Node<T>* head;

public:
	LinkedList() : head(nullptr) {}

	~LinkedList() {}

	T front();

	void addFront(const T& data);

	void removeFront();

	void print();

	bool empty();

	template <typename T>
	class Iterator
	{
	public:
		Node<T>* node;

		Iterator(Node<T>* listNode) : node(listNode) {}

		void operator++() { node = node->next; }

		T operator*() { return node->data; }

		bool operator!=(Iterator it) { return this->node != it.node; }
	};

	Iterator<T> begin() { return Iterator<T>(head); }

	Iterator<T> end() { return Iterator<T>(nullptr); }
};

template <typename T>
bool LinkedList<T>::empty()
{
	return head == nullptr;
}

template <typename T>
T LinkedList<T>::front()
{
	return head->data;
}

template <typename T>
void LinkedList<T>::addFront(const T& data)
{
	Node<T>* newNode = new Node<T>();
	newNode->data = data;
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
		std::cout << currentElement->data << " ";
		currentElement = currentElement->next;
	}
}

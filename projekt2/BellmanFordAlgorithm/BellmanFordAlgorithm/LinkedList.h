#pragma once
#include <iostream>
#include "Node.h"

template <typename T>
class LinkedList
{
private:
	Node<T>* head;

public:
	LinkedList() : head(nullptr) { }

	~LinkedList() { while (head != nullptr) removeFront(); }

	const T front() const { return head->getData(); }

	void addFront(const T& data);

	void removeFront();

	bool empty() const { return head == nullptr; }

	template <typename T>
	class Iterator
	{
	public:
		Node<T>* node;

		Iterator(Node<T>* listNode) : node(listNode) {}

		void operator++() { node = node->getNext(); }

		T operator*() { return node->getData(); }

		bool operator!=(Iterator it) { return this->node != it.node; }
	};

	Iterator<T> begin() { return Iterator<T>(head); }

	Iterator<T> end() { return Iterator<T>(nullptr); }
};

template <typename T>
void LinkedList<T>::addFront(const T& data)
{
	Node<T>* newNode = new Node<T>();
	newNode->setData(data);
	newNode->setNext(head);
	head = newNode;
}

template <typename T>
void LinkedList<T>::removeFront()
{
	Node<T>* firstElement = head;
	try
	{
		head = head->getNext();
		delete firstElement;
	}
	catch (std::exception &e)
	{
		std::cerr << "exception caught: " << e.what() << '\n';
	}
}

#pragma once

template <typename T>
class Node
{
private:
	T data;
	Node<T>* next;

public:
	T getData() { return data; }

	Node* getNext() { return next; }

	void setData(T data) { this->data = data; }

	void setNext(Node<T>* next) { this->next = next; }
};

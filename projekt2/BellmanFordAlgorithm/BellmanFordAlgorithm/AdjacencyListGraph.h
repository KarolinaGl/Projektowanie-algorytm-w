#pragma once
#include <iostream>
#include "LinkedList.h"

class AdjancencyListGraph
{
private:
	struct Neighbour
	{
		int vertexIndex;

		int weight;
	};

public:
	LinkedList<Neighbour>* verticesArray;

	int edges;

	int vertices;

	AdjancencyListGraph(int edg, int ver) : edges(edg), vertices(ver)
	{
		verticesArray = new LinkedList<Neighbour>[vertices];
	}
	
	void addEdge(int fromIndex, int toIndex, int weight)
	{
		verticesArray[fromIndex].addFront({ toIndex, weight });
	}
	
	void printList()
	{
		for (int i = 0; i < vertices; i++)
		{
			std::cout << i << " ";
			for (Neighbour listElement : verticesArray[i])
				std::cout << "[" << listElement.vertexIndex << ", " << listElement.weight << "]";
			std::cout << "\n";
		}
	}
	
	~AdjancencyListGraph()
	{
		delete[] verticesArray;
	}
};

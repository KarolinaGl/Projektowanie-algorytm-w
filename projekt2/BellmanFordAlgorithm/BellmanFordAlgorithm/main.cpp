#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"
#include "LinkedList.h"
#include "AdjacencyMatrixGraph.h"
#include "AdjacencyListGraph.h"

void generateAdjancencyMatrix()
{
	std::ifstream myFile("data.txt");
	if (myFile.is_open())
	{
		int edges, vertices, startingPoint;
		myFile >> edges >> vertices >> startingPoint;
		AdjancencyMatrixGraph graph(edges, vertices);
		for (int i = 0; i < edges; i++)
		{
			int fromIndex, toIndex, weight;
			myFile >> fromIndex >> toIndex >> weight;
			graph.addEdge(fromIndex, toIndex, weight);
		}
		graph.printMatrixValue();
	}
}

void generateAdjacencyList()
{
	std::ifstream myFile("data.txt");
	if (myFile.is_open())
	{
		int edges, vertices, startingPoint;
		myFile >> edges >> vertices >> startingPoint;
		AdjancencyListGraph graph(edges, vertices);
		for (int i = 0; i < edges; i++)
		{
			int fromIndex, toIndex, weight;
			myFile >> fromIndex >> toIndex >> weight;
			graph.addEdge(fromIndex, toIndex, weight);
		}
		graph.printList();
	}
}

int main()
{
	return 0;
}

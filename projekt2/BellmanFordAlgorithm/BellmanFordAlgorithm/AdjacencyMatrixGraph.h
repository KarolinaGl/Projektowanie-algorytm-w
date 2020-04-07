#pragma once
#include <iostream>

class AdjancencyMatrixGraph
{
private:
	struct Neighbour
	{
		bool exists;

		int weight;
	};

public:
	int edges;

	int vertices;
	
	Neighbour** matrix;

	AdjancencyMatrixGraph(int edg, int ver) : edges(edg), vertices(ver) 
	{
		matrix = new Neighbour *[vertices];
		for (int i = 0; i < vertices; ++i)
		{
			matrix[i] = new Neighbour[vertices];
			for (int j = 0; j < vertices; ++j)
				matrix[i][j] = {false, 0};
		}
	}

	void addEdge(int fromIndex, int toIndex, int weight)
	{
		matrix[fromIndex][toIndex] = { true, weight };
	}

	void printMatrixValue()
	{
		for (int i = 0; i < vertices; ++i)
		{
			for (int j = 0; j < vertices; ++j)
				std::cout << matrix[i][j].weight << " ";
			std::cout << "\n";
		}
	}

	void printMatrixExists()
	{
		for (int i = 0; i < vertices; ++i)
		{
			for (int j = 0; j < vertices; ++j)
				std::cout << matrix[i][j].exists << " ";
			std::cout << "\n";
		}
	}

	~AdjancencyMatrixGraph() 
	{
		for (int i = 0; i < vertices; ++i)
			delete[] matrix[i];
		delete[] matrix;
	}
};

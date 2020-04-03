#pragma once

struct Edge
{
	bool exists;

	int value;
};

class AdjancencyMatrixGraph
{
public:
	int edges;

	int vertices;
	
	Edge** matrix;

	AdjancencyMatrixGraph(int edg, int ver) : edges(edg), vertices(ver) 
	{
		matrix = new Edge *[vertices];
		for (int i = 0; i < vertices; ++i)
		{
			matrix[i] = new Edge[vertices];
			for (int j = 0; j < vertices; ++j)
			{
				matrix[i][j] = {false, 0};
			}
		}
	}

	void addEdge(int fromIndex, int toIndex, int weight) {};

	~AdjancencyMatrixGraph() 
	{
		for (int i = 0; i < vertices; ++i)
			delete[] matrix[i];
		delete[] matrix;
	}
};

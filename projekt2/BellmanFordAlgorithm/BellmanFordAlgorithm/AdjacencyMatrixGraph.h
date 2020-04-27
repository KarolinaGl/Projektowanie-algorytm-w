#pragma once
#include <iostream>
#include "Graph.h"

class AdjancencyMatrixGraph : public Graph
{
	Edge*** matrix;
public:	
	AdjancencyMatrixGraph(int verticesNumber, int edgesNumber) :
		Graph(verticesNumber, edgesNumber)
	{
		matrix = new Edge**[numberOfVertices];
		for (int i = 0; i < numberOfVertices; ++i)
		{
			matrix[i] = new Edge*[numberOfVertices];
			for (int j = 0; j < numberOfVertices; ++j)
				matrix[i][j] = nullptr;
		}
	}

	~AdjancencyMatrixGraph() 
	{
		for (int i = 0; i < numberOfVertices; ++i)
			delete[] matrix[i];
		delete[] matrix;
	}

	void createEdge(int from, int to, int weight) override
	{
		Edge* edge = new Edge();
		edge->fromVertex = verticesArray[from];
		edge->toVertex = verticesArray[to];
		edge->weight = weight;
		edgesList.addFront(edge);
		matrix[from][to] = edge;
	}
};

#pragma once
#include <iostream>
#include "Utility.h"
#include "Graph.h"

class AdjancencyMatrixGraph : Graph
{
	Edge*** matrix;
	LinkedList<Edge*> edgesList;
	Vertex** verticesArray;
	int numberOfVertices;
	int numberOfEdges;

public:	
	AdjancencyMatrixGraph(int verticesNumber, int edgesNumber) :
		numberOfVertices(verticesNumber),
		numberOfEdges(edgesNumber),
		edgesList(LinkedList<Edge*>())
	{
		verticesArray = new Vertex* [numberOfVertices];
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
		removeVertices();
		removeEdges();
	}

	void createVertex(int vertexIndex) override
	{
		Vertex* vertex = new Vertex();
		vertex->index = vertexIndex;
		verticesArray[vertexIndex] = vertex;
	}

	void createEdge(int from, int to, int weight) override
	{
		Edge* edge = new Edge();
		edge->fromIndex = verticesArray[from];
		edge->toIndex = verticesArray[to];
		edge->weight = weight;
		edgesList.addFront(edge);
		matrix[from][to] = edge;
	}

	void removeVertices() override
	{
		for (int i = 0; i < numberOfVertices; ++i)
			delete verticesArray[i];
		delete[] verticesArray;
	}

	void removeEdges() override
	{
		for (int i = 0; i < numberOfEdges; ++i)
		{
			delete edgesList.front();
			edgesList.removeFront();
		}
	}

	LinkedList<Edge*>* incidentEdges(Vertex* vertex) override
	{
		LinkedList<Edge*>* list = new LinkedList<Edge*>();
		for (int i = 0; i < numberOfVertices; ++i)
		{
			if (matrix[vertex->index][i] != nullptr)
				list->addFront(matrix[vertex->index][i]);
		}
		return list;
	}

	const LinkedList<Edge*>& edges() override
	{
		return edgesList;
	}
};

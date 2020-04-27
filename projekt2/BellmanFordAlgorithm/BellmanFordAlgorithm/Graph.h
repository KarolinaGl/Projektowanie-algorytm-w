#pragma once
#include <iostream>
#include "LinkedList.h"

struct Vertex
{
	int index;
};

struct Edge
{
	Vertex* fromVertex;
	Vertex* toVertex;
	int weight;
};

class Graph
{
public:
	int numberOfVertices;
	int numberOfEdges;
	LinkedList<Edge*> edgesList;
	Vertex** verticesArray;

	Graph(int verticesNumber, int edgesNumber) :
		numberOfVertices(verticesNumber),
		numberOfEdges(edgesNumber),
		edgesList(LinkedList<Edge*>())
	{
		verticesArray = new Vertex* [numberOfVertices];
		for (int i = 0; i < numberOfVertices; ++i)
			verticesArray[i] = nullptr;
	}

	virtual ~Graph() 
	{
		removeVertices();
		removeEdges();
	}

	void createVertex(int vertexIndex) 
	{
		Vertex* vertex = new Vertex();
		vertex->index = vertexIndex;
		verticesArray[vertexIndex] = vertex;
	}

	virtual void createEdge(int from, int to, int weight) {}

	void removeVertices() 
	{
		for (int i = 0; i < numberOfVertices; ++i)
		{
			if (verticesArray[i] != nullptr)
				delete verticesArray[i];
		}
		delete[] verticesArray;
	}

	void removeEdges() 
	{
		while (!edgesList.empty())
		{
			delete edgesList.front();
			edgesList.removeFront();
		}
	}

	virtual const LinkedList<Edge*>& incidentEdges(Vertex* vertex) { throw "NotImplemented"; }

	const LinkedList<Edge*>& edges() { return edgesList; }
};

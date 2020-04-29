#pragma once
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
protected:
	int numberOfVertices;
	int numberOfEdges;
	LinkedList<Edge*> edgesList;
	Vertex** verticesArray;

public:
	Graph(int verticesNumber, int edgesNumber);

	virtual ~Graph() 
	{
		removeVertices();
		removeEdges();
	}

	void createVertex(int vertexIndex);

	virtual void createEdge(int from, int to, int weight) {}

	void removeVertices();

	void removeEdges();

	int getNumberOfVertices() { return numberOfVertices; }

	int getNumberOfEdges() { return numberOfEdges; }

	virtual const LinkedList<Edge*>& incidentEdges(Vertex* vertex) { throw "NotImplemented"; }

	const LinkedList<Edge*>& edges() { return edgesList; }
};

Graph::Graph(int verticesNumber, int edgesNumber) :
numberOfVertices(verticesNumber),
numberOfEdges(edgesNumber),
edgesList(LinkedList<Edge*>())
{
	verticesArray = new Vertex * [numberOfVertices];
	for (int i = 0; i < numberOfVertices; ++i)
		verticesArray[i] = nullptr;
}

void Graph::createVertex(int vertexIndex)
{
	Vertex* vertex = new Vertex();
	vertex->index = vertexIndex;
	verticesArray[vertexIndex] = vertex;
}

void Graph::removeVertices()
{
	for (int i = 0; i < numberOfVertices; ++i)
	{
		if (verticesArray[i] != nullptr)
			delete verticesArray[i];
	}
	delete[] verticesArray;
}

void Graph::removeEdges()
{
	while (!edgesList.empty())
	{
		delete edgesList.front();
		edgesList.removeFront();
	}
}

#pragma once
#include "LinkedList.h"
#include "Utility.h"

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
		verticesArray = new Vertex * [numberOfVertices];
	}

	virtual void createVertex(int vertexIndex) {}

	virtual void createEdge(int from, int to, int weight) {}

	virtual void removeVertices() {}

	virtual void removeEdges() {}

	virtual const LinkedList<Edge*>& incidentEdges(Vertex* vertex) 
	{
		return LinkedList<Edge*>();
	}

	virtual const LinkedList<Edge*>& edges() { return edgesList; }
};

#pragma once
#include <iostream>
#include "LinkedList.h"
#include "Utility.h"
#include "Graph.h"

class AdjancencyListGraph : Graph
{
	LinkedList<Edge*>* adjancencyList;
	LinkedList<Edge*> edgesList;
	Vertex** verticesArray;
	int numberOfVertices;
	int numberOfEdges;

public: 
	AdjancencyListGraph(int verticesNumber, int edgesNumber) :
		numberOfVertices(verticesNumber),
		numberOfEdges(edgesNumber),
		edgesList(LinkedList<Edge*>())
	{
		verticesArray = new Vertex*[numberOfVertices];
		adjancencyList = new LinkedList<Edge*>[numberOfVertices];
	}

	~AdjancencyListGraph()
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
		adjancencyList[from].addFront(edge);
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
		return &adjancencyList[vertex->index];
	}

	const LinkedList<Edge*>& edges() override
	{
		return edgesList;
	}
};

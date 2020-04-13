#pragma once
#include <iostream>
#include "LinkedList.h"

struct Vertex
{
	int index;
};

struct Edge
{
	Vertex* fromIndex;
	Vertex* toIndex;
	int weight;
};

class AdjancencyListGraph
{
public:
	LinkedList<Edge*>* adjancencyList;
	LinkedList<Edge*> edgesList;
	Vertex** verticesArray;
	int numberOfVertices;
	int numberOfEdges;

	AdjancencyListGraph(int verticesNumber, int edgesNumber) :
		numberOfVertices(verticesNumber),
		numberOfEdges(edgesNumber),
		edgesList(LinkedList<Edge*>()),
		verticesArray(new Vertex*[numberOfVertices]),
		adjancencyList(new LinkedList<Edge*>[numberOfVertices]){}

	~AdjancencyListGraph()
	{
		removeVertices();
		removeEdges();	
	}

	void createVertex(int vertexIndex)
	{
		Vertex* vertex = new Vertex();
		vertex->index = vertexIndex;
		verticesArray[vertexIndex] = vertex;
		std::cout << "create: " << vertex << "\n";
	}

	void createEdge(int from, int to, int weight)
	{
		Edge* edge = new Edge();
		edge->fromIndex = verticesArray[from];
		edge->toIndex = verticesArray[to];
		edge->weight = weight;
		edgesList.addFront(edge);
		adjancencyList[from].addFront(edge);
	}

	void removeVertices()
	{
		for (int i = 0; i < numberOfVertices; i++)
		{
			std::cout << "remove: " << verticesArray[i] << "\n";
			delete verticesArray[i];		
		}
		delete[] verticesArray;
	}
	
	void removeEdges()
	{
		for (int i = 0; i < numberOfEdges; i++)
		{
			delete edgesList.front();
			edgesList.removeFront();
		}
	}
	
	LinkedList<Edge*> incidentEdges(Vertex* vertex)
	{
		return adjancencyList[vertex->index];
	}
	
	LinkedList<Vertex*> vertices()
	{
		LinkedList<Vertex*> list;
		for (int i = 0; i < numberOfVertices; i++)
			list.addFront(verticesArray[i]);
		return list;
	}

	LinkedList<Edge*> edges()
	{
		return edgesList;
	}
};

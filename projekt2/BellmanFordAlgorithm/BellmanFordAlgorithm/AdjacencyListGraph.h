#pragma once
#include "Graph.h"

class AdjancencyListGraph : public Graph
{
	LinkedList<Edge*>* adjancencyList;
public: 
	AdjancencyListGraph(int verticesNumber, int edgesNumber);

	~AdjancencyListGraph() { delete[] adjancencyList; }

	void createEdge(int from, int to, int weight) override;
};

AdjancencyListGraph::AdjancencyListGraph(int verticesNumber, int edgesNumber) :
	Graph(verticesNumber, edgesNumber)
{
	adjancencyList = new LinkedList<Edge*>[numberOfVertices];
}

void AdjancencyListGraph::createEdge(int from, int to, int weight)
{
	Edge* edge = new Edge();
	edge->fromVertex = verticesArray[from];
	edge->toVertex = verticesArray[to];
	edge->weight = weight;
	edgesList.addFront(edge);
	adjancencyList[from].addFront(edge);
}
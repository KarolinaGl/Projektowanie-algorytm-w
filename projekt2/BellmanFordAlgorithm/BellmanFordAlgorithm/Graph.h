#pragma once
#include "LinkedList.h"
#include "Utility.h"

class Graph
{
	virtual void createVertex(int vertexIndex) {}

	virtual void createEdge(int from, int to, int weight) {}

	virtual void removeVertices() {}

	virtual void removeEdges() {}

	virtual LinkedList<Edge*>* incidentEdges(Vertex* vertex) {}

	virtual const LinkedList<Edge*>& edges() {}
};

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Node.h"
#include "LinkedList.h"
#include "AdjacencyMatrixGraph.h"
#include "AdjacencyListGraph.h"

int maxValue = 99999999;

void createRandomGraph(int numberOfVertices, int numberOfEdges)
{
	int lowerBound = -10;
	int upperBound = 20;
	int weightRange = upperBound - lowerBound + 1;
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<std::mt19937::result_type> verticesDistribution(0, numberOfVertices);
	std::uniform_int_distribution<std::mt19937::result_type> weightDistribution(0, weightRange);
	AdjancencyListGraph* graph = new AdjancencyListGraph(numberOfVertices, numberOfEdges);
	for (int i = 0; i < numberOfVertices; ++i)
		graph->createVertex(i);
	for (int i = 0; i < numberOfEdges; ++i)
	{
		int fromVertex = verticesDistribution(generator);
		int toVertex = verticesDistribution(generator);
		while (graph->edgeExists(fromVertex, toVertex))
		{
			fromVertex = verticesDistribution(generator);
			toVertex = verticesDistribution(generator);
		}
		graph->createEdge(fromVertex, toVertex, weightDistribution(generator) + lowerBound);
	}
	for (Edge* edge : graph->edges())
	{
		int u = (edge->fromVertex)->index;
		int v = (edge->toVertex)->index;
		int weight = edge->weight;
		std::cout << u << " " << v << " " << weight << "\n";
	}
}

void BellmanFordAlgorithm(Graph* graph)
{
	std::ifstream myFile("data.txt");
	int edges = 0;
	int vertices = 0;
	int startingPoint = 0;
	if (myFile.is_open())
	{
		myFile >> edges >> vertices >> startingPoint;
		for (int i = 0; i < vertices; ++i)
			graph->createVertex(i);
		int fromIndex, toIndex, weight;
		for (int i = 0; i < graph->numberOfEdges; ++i)
		{
			myFile >> fromIndex >> toIndex >> weight;
			graph->createEdge(fromIndex, toIndex, weight);
		}
	}

	int* distances = new int[graph->numberOfVertices];
	int* previous = new int[graph->numberOfVertices];

	for (int i = 0; i < graph->numberOfVertices; ++i)
	{
		distances[i] = maxValue;
	}
	for (int i = 0; i < graph->numberOfVertices; ++i)
	{
		previous[i] = NULL;
	}
	distances[startingPoint] = 0;
	for (int i = 1; i < graph->numberOfVertices; ++i)
	{
		for (Edge* edge : graph->edges())
		{
			int u = (edge->fromVertex)->index;
			int v = (edge->toVertex)->index;
			int weight = edge->weight;
			if (distances[u] != maxValue && distances[v] > distances[u] + weight)
			{
				distances[v] = distances[u] + weight;
				previous[v] = u;
			}
		}
	}
	for (Edge* edge : graph->edges())
	{
		int u = (edge->fromVertex)->index;
		int v = (edge->toVertex)->index;
		int weight = edge->weight;
		if (distances[u] != maxValue && distances[v] > distances[u] + weight)
			std::cout << "Negative cycle!\n";
	}
	std::cout << "distances\n";
	for (int i = 0; i < graph->numberOfVertices; ++i)
		std::cout << "i=" << i << " " << distances[i] << "\n";
	std::cout << "paths\n";
	for (int i = 0; i < graph->numberOfVertices; ++i)
	{
		LinkedList<int> list;
		int currentVertex = i;
		list.addFront(currentVertex);
		while (currentVertex != startingPoint)
		{
			currentVertex = previous[currentVertex];
			list.addFront(currentVertex);
		}
		std::cout << "i=" << i << " \n";
		for (int vertex : list)
		{
			std::cout << vertex << " -> ";
		}
		std::cout << "\n";
	}

	delete[] distances;
	delete[] previous;
}

int main()
{
	AdjancencyMatrixGraph* matrixGraph = new AdjancencyMatrixGraph(5, 6);
	AdjancencyListGraph* listGraph = new AdjancencyListGraph(6, 9);
	BellmanFordAlgorithm(matrixGraph);
	//createRandomGraph(10, 5);
	return 0;
}

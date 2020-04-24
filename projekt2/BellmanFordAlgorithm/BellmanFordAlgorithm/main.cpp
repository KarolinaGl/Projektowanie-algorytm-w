#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <ratio>
#include "Node.h"
#include "LinkedList.h"
#include "AdjacencyMatrixGraph.h"
#include "AdjacencyListGraph.h"

int maxValue = 99999999;

AdjancencyListGraph* createRandomGraph(int numberOfVertices, int numberOfEdges)
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
	/*
	for (Edge* edge : graph->edges())
	{
		int u = (edge->fromVertex)->index;
		int v = (edge->toVertex)->index;
		int weight = edge->weight;
		std::cout << u << " " << v << " " << weight << "\n";
	}*/
	return graph;
}

int uploadDataFromFile(Graph* graph)
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
	return startingPoint;
}

void printDistances(Graph* graph, int* distances)
{
	std::cout << "distances\n";
	for (int i = 0; i < graph->numberOfVertices; ++i)
		std::cout << i << ": " << distances[i] << "\n";
}

void printPaths(Graph* graph, int* previous, int startingPoint)
{
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
		std::cout << i << ": ";
		for (int vertex : list)
			std::cout << vertex << " ";
		std::cout << "\n";
	}
}

bool negativeCycleExists(Graph* graph, int* distances)
{
	for (Edge* edge : graph->edges())
	{
		int u = (edge->fromVertex)->index;
		int v = (edge->toVertex)->index;
		int weight = edge->weight;
		if (distances[u] != maxValue && distances[v] > distances[u] + weight)
		{
			return true;
			break;
		}
	}
	return false;
}

void BellmanFordAlgorithm(Graph* graph)
{
	int startingPoint = uploadDataFromFile(graph);
	int* distances = new int[graph->numberOfVertices];
	int* previous = new int[graph->numberOfVertices];
	for (int i = 0; i < graph->numberOfVertices; ++i)
	{
		distances[i] = maxValue;
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
	if (negativeCycleExists(graph, distances))
		std::cout << "Negative cycle detected!\n";
	else
	{
		printDistances(graph, distances);
		printPaths(graph, previous, startingPoint);
	}
	delete[] distances;
	delete[] previous;
}

double countAlgorithmExecutionTimeInMiliseconds(Graph* graph)
{
	using namespace std::chrono;
	high_resolution_clock::time_point start = high_resolution_clock::now();
	BellmanFordAlgorithm(graph);
	high_resolution_clock::time_point stop = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(stop - start);
	return time_span.count() * 1000;
}

int main()
{
	AdjancencyMatrixGraph* matrixGraph = new AdjancencyMatrixGraph(5, 6);
	AdjancencyListGraph* listGraph = new AdjancencyListGraph(5, 6);
	BellmanFordAlgorithm(matrixGraph);
	return 0;
}

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

struct RandomEdge
{
	int fromIndex;
	int toIndex;
};

void swapValues(RandomEdge array[], int firstIndex, int secondIndex)
{
	RandomEdge temp = array[firstIndex];
	array[firstIndex] = array[secondIndex];
	array[secondIndex] = temp;
}

template <typename G>
G* createRandomGraph(int numberOfVertices, int percent)
{
	std::cout << "created" << std::endl;
	int numberOfAllPossibleEdges = numberOfVertices * numberOfVertices - numberOfVertices;
	int numberOfEdges = percent / 100.0 * numberOfAllPossibleEdges;
	int lowerBound = -5;
	int upperBound = 30;
	int weightRange = upperBound - lowerBound;
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<std::mt19937::result_type> verticesDistribution(0, numberOfAllPossibleEdges - 1);
	std::uniform_int_distribution<std::mt19937::result_type> weightDistribution(0, weightRange);
	G* graph = new G(numberOfVertices, numberOfEdges);
	for (int i = 0; i < numberOfVertices; ++i)
		graph->createVertex(i);
	RandomEdge* allPossibleEdgesArray = new RandomEdge[numberOfAllPossibleEdges];
	int arraySize = 0;
	for (int i = 0; i < numberOfVertices; ++i)
	{
		for (int j = 0; j < numberOfVertices; ++j)
		{
			if (i != j)
			{
				allPossibleEdgesArray[arraySize] = { i, j };
				arraySize++;
			}
		}
	}
	for (int i = 0; i < numberOfEdges; ++i)
	{
		std::uniform_int_distribution<std::mt19937::result_type> randomVerticesDistribution(0, numberOfAllPossibleEdges - 1 - i);
		int randomEdgeNumber = randomVerticesDistribution(generator);
		int fromIndex = allPossibleEdgesArray[randomEdgeNumber].fromIndex;
		int toIndex = allPossibleEdgesArray[randomEdgeNumber].toIndex;
		int weight = weightDistribution(generator) + lowerBound;
		graph->createEdge(fromIndex, toIndex, weight);
		swapValues(allPossibleEdgesArray, randomEdgeNumber, numberOfAllPossibleEdges - 1 - i);
	}

	for (Edge* edge : graph->edges())
		std::cout << (edge->fromVertex)->index << " " << (edge->toVertex)->index << " " << edge->weight << "\n";

	delete[] allPossibleEdgesArray;
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

void printDistances(Graph* graph, int* distances, int startingPoint)
{
	std::cout << "distances\n";
	for (int i = 0; i < graph->numberOfVertices; ++i)
	{
		if (i != startingPoint)
			std::cout << i << ": " << (distances[i] == maxValue ? "infinity" : std::to_string(distances[i])) << "\n";
	}
}

void printPaths(Graph* graph, int* previous, int startingPoint, int* distances)
{
	std::cout << "paths\n";
	for (int i = 0; i < graph->numberOfVertices; ++i)
	{
		if (i != startingPoint)
		{
			if (distances[i] < maxValue)
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
			return true;
	}
	return false;
}

void BellmanFordAlgorithm(Graph* graph, int startingPoint)
{
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
		printDistances(graph, distances, startingPoint);
		printPaths(graph, previous, startingPoint, distances);
	}
	delete[] distances;
	delete[] previous;
}

double countAlgorithmExecutionTimeInMiliseconds(Graph* graph, int startingPoint)
{
	using namespace std::chrono;
	high_resolution_clock::time_point start = high_resolution_clock::now();
	BellmanFordAlgorithm(graph, startingPoint);
	high_resolution_clock::time_point stop = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(stop - start);
	return time_span.count() * 1000;
}

int main()
{
	BellmanFordAlgorithm(createRandomGraph<AdjancencyMatrixGraph>(6, 50), 2);
	return 0;
}

#pragma once
#include <random>
#include <string>
#include <algorithm>
#include <ratio>
#include <iostream>
#include <fstream>

int infinity = 1 << 20;

struct RandomEdge
{
	int fromIndex;
	int toIndex;
};

struct FileData
{
	int startingPoint;
	Graph* graph;
};
template <typename G>
FileData uploadGraphFromFile(std::string fileName)
{
	std::ifstream myFile(fileName);
	int edges = 0;
	int vertices = 0;
	int startingPoint = 0;
	Graph* matrixGraph = nullptr;
	if (myFile.is_open())
	{
		myFile >> edges >> vertices >> startingPoint;
		matrixGraph = new G(vertices, edges);
		for (int i = 0; i < vertices; ++i)
			matrixGraph->createVertex(i);
		int fromIndex, toIndex, weight;
		for (int i = 0; i < matrixGraph->getNumberOfEdges(); ++i)
		{
			myFile >> fromIndex >> toIndex >> weight;
			matrixGraph->createEdge(fromIndex, toIndex, weight);
		}
	}
	return {startingPoint, matrixGraph};
}

void swapValues(RandomEdge array[], int firstIndex, int secondIndex)
{
	RandomEdge temp = array[firstIndex];
	array[firstIndex] = array[secondIndex];
	array[secondIndex] = temp;
}

template <typename G>
G* createRandomGraph(int numberOfVertices, int percent)
{
	int numberOfAllPossibleEdges = numberOfVertices * numberOfVertices - numberOfVertices;
	int numberOfEdges = (int)(percent / 100.0 * numberOfAllPossibleEdges);
	int lowerBound = 0;
	int upperBound = 100;
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
	delete[] allPossibleEdgesArray;
	return graph;
}

void printDistances(std::ostream& stream, Graph* graph, int* distances, int startingPoint)
{
	stream << "distances\n";
	for (int i = 0; i < graph->getNumberOfVertices(); ++i)
	{
		if (i != startingPoint)
			stream << i << ": " << (distances[i] == infinity ? "infinity" : std::to_string(distances[i])) << "\n";
	}
}

void printPaths(std::ostream& stream, Graph* graph, int* previous, int startingPoint, int* distances)
{
	stream << "paths\n";
	for (int i = 0; i < graph->getNumberOfVertices(); ++i)
	{
		if (i != startingPoint)
		{
			if (distances[i] < infinity)
			{
				LinkedList<int> list;
				int currentVertex = i;
				list.addFront(currentVertex);
				while (currentVertex != startingPoint)
				{
					currentVertex = previous[currentVertex];
					list.addFront(currentVertex);
				}
				stream << i << ": ";
				for (int vertex : list)
					stream << vertex << " ";
				stream << "\n";
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
		if (distances[u] != infinity && distances[v] > distances[u] + weight)
			return true;
	}
	return false;
}

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include "Node.h"
#include "LinkedList.h"
#include "AdjacencyMatrixGraph.h"
#include "AdjacencyListGraph.h"
#include "Utility.h"

void BellmanFordAlgorithm(Graph* graph, int startingPoint, std::ostream& stream = std::cout)
{
	int vertices = graph->getNumberOfVertices();
	int* distances = new int[vertices];
	int* previous = new int[vertices];
	for (int i = 0; i < vertices; ++i)
		distances[i] = infinity;
	distances[startingPoint] = 0;
	for (int i = 1; i < vertices; ++i)
	{
		for (Edge* edge : graph->edges())
		{
			int u = (edge->fromVertex)->index;
			int v = (edge->toVertex)->index;
			int weight = edge->weight;
			if (distances[u] != infinity && distances[v] > distances[u] + weight)
			{
				distances[v] = distances[u] + weight;
				previous[v] = u;
			}
		}
	}
	if (negativeCycleExists(graph, distances))
		stream << "Negative cycle detected!\n";
	else
	{
		printDistances(stream, graph, distances, startingPoint);
		printPaths(stream, graph, previous, startingPoint, distances);
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

void testBellmanFordAlgorithmSpeed()
{
	int numberOfVertices[5] = { 10, 50, 100, 500, 1000 };
	int graphDensityInPercent[4] = { 25, 50, 75, 100 };
	std::string graphRepresentations[2] = { "matrix", "list" };
	int numberOfLoops = 1;
	double timeSum = 0;
	std::ofstream file;
	file.open("results.txt");
	for (std::string representation : graphRepresentations)
	{
		file << "adjancency " << representation << " graph\n";
		for (int vertices : numberOfVertices)
		{
			for (int density : graphDensityInPercent)
			{
				for (int i = 0; i < numberOfLoops; ++i)
				{
					Graph* graph;
					if (representation == "matrix")
						graph = createRandomGraph<AdjancencyMatrixGraph>(vertices, density);
					else
						graph = createRandomGraph<AdjancencyListGraph>(vertices, density);
					timeSum += countAlgorithmExecutionTimeInMiliseconds(graph, 0);
					delete graph;
				}
				file << timeSum / numberOfLoops << "\n";
				timeSum = 0;
			}
		}
	}
	file.close();
}

int main()
{
	std::ofstream stream;
	stream.open("results.txt");
	FileData data = uploadGraphFromFile<AdjancencyMatrixGraph>("data.txt");
	BellmanFordAlgorithm(data.graph, data.startingPoint, stream);
	stream.close();
	return 0;
}

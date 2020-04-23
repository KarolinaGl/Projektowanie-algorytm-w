#pragma once
#include <random>

struct Vertex
{
	int index;
};

struct Edge
{
	Vertex* fromVertex;
	Vertex* toVertex;
	int weight;
};

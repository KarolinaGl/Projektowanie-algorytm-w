#pragma once

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

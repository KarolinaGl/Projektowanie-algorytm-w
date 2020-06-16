#include <iostream>
#include <vector>
#include <stack>
#include <map>

#define POSITIONS 16
#define KING_POSITION_INDEX 1
#define KNIGHT_POSITION_INDEX 13

std::vector<std::vector<std::pair<int, int>>> positionsGraph;

std::map<int, char> indexLetterMap;
std::map<std::pair<int, int>, int> positionIndexMap;
std::vector<int> previousPositions(POSITIONS);

void createMaps()
{
	indexLetterMap[0] = 'G';
	indexLetterMap[1] = 'H';
	indexLetterMap[2] = 'I';
	indexLetterMap[3] = 'J';
	indexLetterMap[4] = 'L';
	indexLetterMap[5] = 'M';
	indexLetterMap[6] = 'N';
	indexLetterMap[7] = 'O';
	indexLetterMap[8] = 'Q';
	indexLetterMap[9] = 'R';
	indexLetterMap[10] = 'S';
	indexLetterMap[11] = 'T';
	indexLetterMap[12] = 'V';
	indexLetterMap[13] = 'W';
	indexLetterMap[14] = 'X';
	indexLetterMap[15] = 'Y';

	positionIndexMap[{ 1, 1 }] = 0;
	positionIndexMap[{ 1, 2 }] = 1;
	positionIndexMap[{ 1, 3 }] = 2;
	positionIndexMap[{ 1, 4 }] = 3;
	positionIndexMap[{ 2, 1 }] = 4;
	positionIndexMap[{ 2, 2 }] = 5;
	positionIndexMap[{ 2, 3 }] = 6;
	positionIndexMap[{ 2, 4 }] = 7;
	positionIndexMap[{ 3, 1 }] = 8;
	positionIndexMap[{ 3, 2 }] = 9;
	positionIndexMap[{ 3, 3 }] = 10;
	positionIndexMap[{ 3, 4 }] = 11;
	positionIndexMap[{ 4, 1 }] = 12;
	positionIndexMap[{ 4, 2 }] = 13;
	positionIndexMap[{ 4, 3 }] = 14;
	positionIndexMap[{ 4, 4 }] = 15;
}

void printGraph()
{
	for (unsigned int i = 0; i < positionsGraph.size(); i++)
	{
		for (unsigned int j = 0; j < positionsGraph[i].size(); j++)
			std::cout << "(" << positionsGraph[i][j].first << " " << positionsGraph[i][j].second << ") ";
		std::cout << std::endl;
	}
}

void addNeighbors(std::vector<std::vector<std::pair<int, int>>>& positions, std::pair<int, int> currentPosition)
{
	std::pair<int, int> possibleMoves[8] = { {-1,-2}, {-1, 2}, {1, -2}, {1, 2}, {-2, -1}, {2, -1}, {-2, 1}, {2, 1} };
	std::vector<std::pair<int, int>> neighbors;

	for (int j = 0; j < 8; j++)
	{
		if (currentPosition.first + possibleMoves[j].first > 0 && currentPosition.first + possibleMoves[j].first < 5
			&& currentPosition.second + possibleMoves[j].second > 0 && currentPosition.second + possibleMoves[j].second < 5)
			neighbors.push_back({ currentPosition.first + possibleMoves[j].first, currentPosition.second + possibleMoves[j].second });
	}
	positions.push_back(neighbors);
}

void createGraph()
{
	for (int i = 1; i < 5; i++)
	{
		for (int j = 1; j < 5; j++)
			addNeighbors(positionsGraph, { i, j });
	}
}

std::vector<int> createPath(int current)
{
	std::vector<int> path;
	path.push_back(current);
	while (current != KNIGHT_POSITION_INDEX)
	{
		current = previousPositions[current];
		path.push_back(current);
	}
	return path;
}

void DFS()
{
	std::stack<int> stack;
	std::vector<bool> wasVisited(POSITIONS, false);

	int currentIndex = 0;

	stack.push(KNIGHT_POSITION_INDEX);

	while (stack.empty() == false && currentIndex != 1)
	{
		currentIndex = stack.top();
		stack.pop();
		if (wasVisited[currentIndex] == false)
		{
			wasVisited[currentIndex] = true;

			for (unsigned int i = 0; i < positionsGraph[currentIndex].size(); i++)
			{
				std::pair<int, int> neighbour = positionsGraph[currentIndex][i];
				int neighbourPosition = positionIndexMap[neighbour];
				if (wasVisited[neighbourPosition] == false)
				{
					previousPositions[neighbourPosition] = currentIndex;
					stack.push(neighbourPosition);
				}
			}
		}
	}
}

int main()
{
	createMaps();
	createGraph();
	DFS();

	std::vector<int> path = createPath(KING_POSITION_INDEX);
	if (path.size() == 0)
		std::cout << "No path found" << std::endl;
	else
	{
		std::cout << "Found path: " << std::endl;
		for (int i = path.size() - 1; i >= 1; i--)
			std::cout << indexLetterMap[path[i]] << " -> ";
		std::cout << indexLetterMap[path[0]];
		std::cout << std::endl;
	}
	//printGraph();
	return 0;
}

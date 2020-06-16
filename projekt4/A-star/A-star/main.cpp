#include <iostream>
#include <iomanip>
#include <cmath>
#include <set>
#include <vector>
#include <map>

#define POSITIONS 16
#define KING_POSITION_INDEX 1
#define KNIGHT_POSITION_INDEX 13
#define INF 9999

int* f_cost;
int* g_cost;
int* h_cost;
std::vector<int> previousPositions(POSITIONS);
std::vector<std::vector<std::pair<int, int>>> positionsGraph;

std::map<int, char> indexLetterMap;
std::map<std::pair<int, int>, int> positionIndexMap;
std::map<int, std::pair<int, int>> indexPositionMap;


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

    for (auto iter = positionIndexMap.begin(); iter != positionIndexMap.end(); iter++)
        indexPositionMap[iter->second] = iter->first;
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
    std::pair<int, int> kingPosition = indexPositionMap[KING_POSITION_INDEX];
    for (int i = 1; i < 5; i++)
    {
        for (int j = 1; j < 5; j++)
            addNeighbors(positionsGraph, { i, j });
    }
    f_cost = new int[POSITIONS];
    g_cost = new int[POSITIONS];
    h_cost = new int[POSITIONS];
    for (int i = 0; i < POSITIONS; i++)
    {
        int x = indexPositionMap[i].first;
        int y = indexPositionMap[i].second;
        h_cost[i] = abs(kingPosition.first - x) + abs(kingPosition.second - y);
        g_cost[i] = INF;
        f_cost[i] = INF;
    }
}

void deleteArrays()
{
    delete[] f_cost;
    delete[] g_cost;
    delete[] h_cost;
}

int findLowestF_Cost(std::set<int>& openSet)
{
    int lowest_f_cost;
    int lowestValue = 2 * INF;
    for (auto iter = openSet.begin(); iter != openSet.end(); iter++)
    {
        if (f_cost[*iter] < lowestValue)
        {
            lowestValue = f_cost[*iter];
            lowest_f_cost = *iter;
        }
    }
    return lowest_f_cost;
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

std::vector<int> AStar(int startingIndex, int targetIndex)
{
    std::set<int> closedSet;
    std::set<int> openSet;
    openSet.insert(startingIndex);
    g_cost[startingIndex] = 0;
    f_cost[startingIndex] = g_cost[startingIndex] + h_cost[startingIndex];
    while (!openSet.empty())
    {
        int lowestF_scorePosition = findLowestF_Cost(openSet);
        if (lowestF_scorePosition == targetIndex)
            return createPath(targetIndex);
        openSet.erase(lowestF_scorePosition);
        closedSet.insert(lowestF_scorePosition);
        for (unsigned int i = 0; i < positionsGraph[lowestF_scorePosition].size(); i++)
        {
            std::pair <int, int> lowestF_scorePair = positionsGraph[lowestF_scorePosition][i];
            int lowestF_scoreIndex = positionIndexMap[lowestF_scorePair];
            if (closedSet.find(lowestF_scoreIndex) != closedSet.end())
                continue;
            int currentPosition = g_cost[lowestF_scoreIndex] + 3;
            bool isCurrentPositionBetter = false;
            if (openSet.find(lowestF_scoreIndex) == openSet.end())
            {
                openSet.insert(lowestF_scoreIndex);
                isCurrentPositionBetter = true;
            }
            else if (currentPosition < g_cost[lowestF_scoreIndex])
                isCurrentPositionBetter = true;
            if (isCurrentPositionBetter)
            {
                previousPositions[lowestF_scoreIndex] = lowestF_scorePosition;
                g_cost[lowestF_scoreIndex] = currentPosition;
                f_cost[lowestF_scoreIndex] = g_cost[lowestF_scoreIndex] + h_cost[lowestF_scoreIndex];
            }
        }
    }
    return std::vector<int>();
}

int main()
{
    createMaps();
    createGraph();
    std::vector<int> path = AStar(KNIGHT_POSITION_INDEX, KING_POSITION_INDEX);
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
    deleteArrays();
    return 0;
}

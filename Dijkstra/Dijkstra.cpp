#include <fstream>
#include <iostream>
#include <string>
using namespace std;
const int INF = 32767;
void Init(int **&weights, int *&distance, int *&path, bool *&visited, int &size, int &start);
void Dijkstra(int **&weights, int *&distance, int *&path, bool *&visited, const int &size, const int &start);
int main(int argc, char **argv)
{
	cout << "\t\t\tDijktra Algorithm\n\n";
	int size{0}, start{0};
	int **weights{0};
	int *distance{0};
	int *path{0};
	bool *visited{0};
	Init(weights, distance, path, visited, size, start);
	Dijkstra(weights, distance, path, visited, size, start);
	for (int i = 0; i < size; i++)
		delete[] weights[i];
	delete[] weights;
	delete[] distance;
	delete[] path;
	delete[] visited;
	cout << '\n';
	return 0;
}
void Init(int **&weights, int *&distance, int *&path, bool *&visited, int &size, int &start)
{
	fstream INPUT("input.txt", ios::in);
	INPUT >> size >> start;
	start--;
	// Ma tran trong so weights
	weights = new int *[size];
	string line;
	for (int i = 0; i < size; i++)
	{
		weights[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			INPUT >> line;
			if (line == "INF")
				weights[i][j] = INF;
			else weights[i][j] = stoi(line);
		}
	};
	INPUT.close();
	distance = new int[size];
	for (int i = 0; i < size; i++)
		distance[i] = INF;
	distance[start] = 0;

	path = new int[size];
	for (int i = 0; i < size; i++)
		path[i] = 0;
	path[start] = start;

	visited = new bool[size];
	for (int i = 0; i < size; i++)
		visited[i] = 0;
}
void Dijkstra(int **&weights, int *&distance, int *&path, bool *&visited, const int &size, const int &start)
{
	printf("\nStep |");
	for (int i = 0; i < size; i++)
		printf("%4d   |", i+1); 
	cout << "\n  0  |";
	for (int i = 0; i < size; i++)
	{
		if (i != start)
			printf(" INF,0 |"); 
		else
			printf(" %2d,%-2d |", distance[i], path[i] + 1); 
	}
	int Not_visited = size;
	while (Not_visited--)
	{
		printf("\n%3d  |", size - Not_visited);
		int min = INF;
		int pos = 0;
		// Loai diem den co khoang cach nho nhat
		for (int i = 0; i < size; i++)
		{
			if (!visited[i] && min > distance[i])
			{
				min = distance[i];
				pos = i;
			}
		}
		visited[pos] = 1;
		for (int i = 0; i < size; i++)
		{
			if (weights[pos][i] != INF && weights[pos][i] != 0 && distance[i] > distance[pos] + weights[pos][i])
			{
				distance[i] = distance[pos] + weights[pos][i];
				path[i] = pos;
			}
		}
		for (int i = 0; i < size; i++)
		{
			if (distance[i] == INF)
			{
				printf(" INF,0 |");
				continue;
			}
			if (visited[i])
				printf("   -   |");
			else
				printf(" %3d,%-2d|", distance[i], path[i] + 1);;
		}
	}
}
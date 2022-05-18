#include <fstream>
#include <iostream>
#include <string>
using namespace std;
const int INF = 32767;
void Init(int **&Weights, int *&Distance, int *&Path, int &Size, int &Start);
void Bellman_Ford(int **&Weights, int *&Distance, int *&Path, const int &Size, const int &Start);
void Find_Negative_Circle(int *&Path, const int &Size, const int &Start);
int main(int argc, char **argv)
{
	cout << "\tBellman-Ford Algorithm\n\n";
	int **Weights{0};
	int *Distance{0}, *Path{0};
	int Size{0}, Start{0};
	Init(Weights, Distance, Path, Size, Start);
	// Implementation here
	Bellman_Ford(Weights, Distance, Path, Size, Start);
	for (int i = 0; i <Size; i++)
		delete[] Weights[i];
	delete[] Weights;
	delete[] Distance;
	delete[] Path;
	return 0;
}

void Init(int **&Weights, int *&Distance, int *&Path, int &Size, int &Start)
{
	fstream INPUT("input.txt", ios::in);
	INPUT >> Size >> Start;
	Start--;
	string line;

	Weights = new int *[Size];
	for (int i = 0; i < Size; i++)
	{
		Weights[i] = new int[Size];
		for (int j = 0; j < Size; j++)
		{
			INPUT >> line;
			if (line == "INF")
				Weights[i][j] = INF;
			else Weights[i][j] = stoi(line);
		}
	}
	INPUT.close();

	Distance = new int[Size];
	for (int i = 0; i < Size; i++)
		Distance[i] = INF;
	Distance[Start] = 0;

	Path = new int[Size];
	for (int i = 0; i < Size; i++)
		Path[i] = 0;
	Path[Start] = Start;
};
void Bellman_Ford(int **&Weights, int *&Distance, int *&Path, const int &Size, const int &Start)
{
	printf("\nStep |");
	for (int i = 1; i <= Size; i++)
	{
		printf("%4d   |", i);
	}
	cout << "\n  0  |";
	for (int i = 0; i < Size; i++)
	{
		if (Distance[i] == INF)
		{
			printf(" INF,0 |");
		}
		else
		{
			printf("   0,%-2d|", Start + 1);
		}
	}
	// Implementation here
	for (int i = 0; i < Size; i++)
	{
		printf("\n%3d  |", i+1);
		for (int u = 0; u < Size; u++)
		{
			for (int v = 0; v < Size; v++)
			{
				if (Weights[u][v] == INF || u == v || Distance[u] == INF)
					continue;
				if (Distance[v] > Distance[u] + Weights[u][v])
				{
					Distance[v] = Distance[u] + Weights[u][v];
					Path[v] = u;
				}
			}
		}
		// print
		for (int i = 0; i < Size; i++)
		{
			if (Distance[i] == INF)
			{
				printf(" INF,0 |");
				continue;
			}
			else
			{
				printf(" %3d,%-2d|", Distance[i], Path[i] + 1);
			}
		}
		// Exist the negative circle
		if (Distance[Start] < 0)
		{
			cout << "\nGraph exists negative cycle\n";
			Find_Negative_Circle(Path, Size, Start);
			return;
		}
	}
};
void Find_Negative_Circle(int *&Path, const int &Size, const int &Start)
{
	bool *visited = new bool[Size];
	for (int i = 0; i < Size; i++)
	{
		visited[i] = 0;
	}
	int t = Start;
	while (!visited[t])
	{
		visited[t] = 1;
		t = Path[t];
	}
	printf("%d <- ", t+1);
	int y = Path[t];
	while (y != t)
	{
		printf("%d <- ", y+1);
		y = Path[y];
	}
	printf("%d", t+1);
	delete[] visited;
}
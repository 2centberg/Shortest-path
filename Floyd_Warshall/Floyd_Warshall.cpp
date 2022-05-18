#include <fstream>
#include <iostream>
#include <string>
using namespace std;
const int &&INF = 32767;
void Init(int **&Weights, int **&Distance, int **&Path, int &Size);
void Floyd_Warshall(int **&Weights, int **&Distance, int **&Path, const int &Size);
void Display(int **&Distance, int **&Path, const int &Size);
void Find_Negative_Circle(int **&Path, const int &Size, int Start);
int main(int argc, char **argv)
{
	cout << "\tFloyd-Warshall Algorithm\n\n";
	int **Weights{0}, **Distance{0}, **Path{0};
	int Size{0};
	Init(Weights, Distance, Path, Size);
	Floyd_Warshall(Weights, Distance, Path, Size);
	if (Size > 0)
	{
		for (int i = 0; i < Size; i++)
		{
			delete[] Distance[i];
			delete[] Weights[i];
			delete[] Path[i];
		}
		delete[] Distance;
		delete[] Weights;
		delete[] Path;
	}
	return 0;
}

void Init(int **&Weights, int **&Distance, int **&Path, int &Size)
{
	fstream INPUT("input.txt", ios::in);
	INPUT >> Size;
	Distance = new int *[Size];
	Weights = new int *[Size];
	Path = new int *[Size];
	string line;
	for (int i = 0; i < Size; i++)
	{
		Distance[i] = new int[Size];
		Weights[i] = new int[Size];
		Path[i] = new int[Size];
		for (int j = 0; j < Size; j++)
		{
			INPUT >> line;
			if (line == "INF")
			{
				Weights[i][j] = INF;
				Path[i][j] = 0;
			}
			else
			{
				Weights[i][j] = stoi(line);
				Path[i][j] = j;
			}
			Distance[i][j] = Weights[i][j];
		}
	}
	INPUT.close();
};
void Floyd_Warshall(int **&Weights, int **&Distance, int **&Path, const int &Size)
{
	//printf("  Step 0\n");
	//Display(Distance, Path, Size);
	for (int i = 0; i < Size; i++)
	{
		//printf("  Step %d\n", i+1);
		for (int u = 0; u < Size; u++)
		{
			if (u == i)
				continue;
			for (int v = 0; v < Size; v++)
			{
				if (Distance[u][i] == INF || Distance[i][v] == INF)
					continue;
				if (Distance[u][v] > Distance[u][i] + Distance[i][v])
				{
					Distance[u][v] = Distance[u][i] + Distance[i][v];
					Path[u][v] = Path[u][i];
				}
			}
		}
		//Display(Distance, Path, Size);
		if (Distance[i][i] < 0)
		{
			cout << "Graph exists negative cycle\n";
			Find_Negative_Circle(Path, Size, i);
			return;
		}
	}
	Display(Distance, Path, Size);
};
void Display(int **&Distance, int **&Path, const int &Size)
{
	printf("%s", "Distance Matrix");
	for (int i = 0; i < 4 * Size - 9; i++)
	{
		cout << ' ';
	}
	printf("%s", "Path Matrix\n");
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			if (Distance[i][j] == INF)
			{
				printf("INF ");
			}
			else
			{
				printf("%3d ", Distance[i][j]);
			}
		}
		printf("  |  ");
		for (int j = 0; j < Size; j++)
		{
			printf("%2d ", Path[i][j] + 1);
		}
		cout << '\n';
	}
}

void Find_Negative_Circle(int **&Path, const int &Size, int Start)
{
	bool *visited = new bool[Size];
	for (int i = 0; i < Size; i++)
		visited[i] = 0;
	int End = Start;
	while (!visited[Start])
	{
		visited[Start] = 1;
		Start = Path[Start][End];
	}
	End = Start;
	do 
	{
		cout << Start + 1 << " -> ";
		Start = Path[Start][End];
	} while (Start != End);
	cout << Start + 1;
	delete[] visited;
};

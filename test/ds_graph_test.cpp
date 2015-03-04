#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stack>

namespace
{

#define N (9)
#define INF	(65536)
enum
{
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I
};

static void InitMatrix(int ppMatrix[N][N], int inf)
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (i == j)
			{
				ppMatrix[i][j] = 0;
			}
			else
			{
				ppMatrix[i][j] = inf;
			}
		}
	}
}

static inline void InitMatrixVal(int ppMatrix[N][N], int i, int j, int val)
{
	ppMatrix[i][j] = val;
	ppMatrix[j][i] = val;
}

void DFS(int mark[N], int ppMatrix[N][N], int n, int i)
{
	const int link = 1;
	const int visited = 1;
	
	mark[i] = visited;
	for (int j = 0; j < n; ++j)
	{
		if (ppMatrix[i][j] != link)
		{
			continue;
		}
		if (mark[j] == visited)
		{
			continue;
		}
		printf("[%c,%c]", 'A' + i, 'A' + j);
		DFS(mark, ppMatrix, n, j);
	}
}

void DFSTraverse(int ppMatrix[N][N], int n)
{
	int mark[n];
	memset(mark, 0, n * sizeof(int));
	for (int i = 0; i < N; ++i)
	{
		DFS(mark, ppMatrix, n, i);
	}
	
	printf("\n");
}

void BFSTraverse(int ppMatrix[N][N], int n)
{
	const int link = 1;
	const int visited = 1;
	
	int mark[n];
	memset(mark, 0, n * sizeof(int));
	
	std::stack<int> stackkey;
	
	for (int i = 0; i < N; ++i)
	{
		if (mark[i] == visited)
		{
			continue;
		}
		mark[i] = visited;
		stackkey.push(i);
		while (!stackkey.empty())
		{
			int j = stackkey.top();
			stackkey.pop();
			for (int k = 0; k < N; ++k)
			{
				if (ppMatrix[j][k] != link || mark[k] == visited)
				{
					continue;
				}
				mark[k] = visited;
				stackkey.push(k);
				printf("[%c,%c]", 'A' + j, 'A' + k);
			}
		}
	}
	printf("\n");
}

static void InitXFSTest(int ppMatrix[N][N])
{
	const int link = 1;
	
	InitMatrixVal(ppMatrix, A, B, link);
	InitMatrixVal(ppMatrix, A, F, link);
	InitMatrixVal(ppMatrix, B, C, link);
	InitMatrixVal(ppMatrix, B, G, link);
	InitMatrixVal(ppMatrix, B, I, link);
	InitMatrixVal(ppMatrix, C, D, link);
	InitMatrixVal(ppMatrix, C, I, link);
	InitMatrixVal(ppMatrix, D, E, link);
	InitMatrixVal(ppMatrix, D, G, link);
	InitMatrixVal(ppMatrix, D, H, link);
	InitMatrixVal(ppMatrix, D, I, link);
	InitMatrixVal(ppMatrix, E, F, link);
	InitMatrixVal(ppMatrix, E, H, link);
	InitMatrixVal(ppMatrix, F, G, link);
	InitMatrixVal(ppMatrix, G, H, link);
}

TEST(graph, DFS)
{
	int ppMatrix[N][N];
	InitMatrix(ppMatrix, 0);
	InitXFSTest(ppMatrix);
	
	DFSTraverse(ppMatrix, N);
}

TEST(graph, BFS)
{
	int ppMatrix[N][N];
	InitMatrix(ppMatrix, 0);
	InitXFSTest(ppMatrix);
	
	BFSTraverse(ppMatrix, N);
}

}
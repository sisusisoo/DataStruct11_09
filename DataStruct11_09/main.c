#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
//필요한 라이브러리를 추가합니다.

//*다익스트라 알고리즘의 기초를 설정합니다.*//
#define TRUE 1
//True일때 1로 정의합니다.
#define FALSE 0
//False일때 0으로 정의합니다.
#define MAX_VERTICES	100	
//최대 정점의 수를 나타냅니다.
#define INF	1000
// 간선이 연결되어있지 않는 경우를 무한대로 나타냅니다.

typedef struct GraphType {
	int n;
	// 정점의 개수입니다. 
	int weight[MAX_VERTICES][MAX_VERTICES];
	//네트워크의 인접 행렬을 초기화
} GraphType;

int distance[MAX_VERTICES];
//시작 정점으로부터 최단경로의 거리를 설정합니다.
int found[MAX_VERTICES];
//방문한 정점을 표시합니다.
int choose(int distance[], int n, int found[])
//현재 distance배열에서 최소 가중치 값에 있는 노드를 골라 인덱스를 반환합니다.
{
	int i, min, minpos;
	//각 노드를 나타내는 변수를 설정합니다.

	min = INT_MAX;
	//min에 INT_MAX(무한대와 유사, 간선이 연결되지 않은 경우)를 삽입합니다.
	minpos = -1;
	for (i = 0; i < n; i++)
		//최소값 min을 찾는 for문입니다.
		//방문한 적 없는 노드들에 대해 distance 배열의 값을 비교합니다.
		if (distance[i] < min && !found[i]) {
			//만약 현재 방문하지 않는 노드 중 i로까지의 거리가 현재 최소값 min보다 작다면,
			min = distance[i];
			//최소 거리인 i로까지의 거리를 min으로 설정합니다.
			minpos = i;
			//최소값을 가진 노드의 인덱스 i를 minpos에 저장합니다.
		}
	return minpos;
	//최소 거리 노드 인덱스인 i를 반환합니다.
}

void print_status(GraphType* g)
//최단 경로를 출력하는 함수 입니다.
{
	static int step = 1;
	printf("STEP %d: ", step++);
	//첫번째 스텝에 1을 대입하여 출력하고 하나씩 늘려갑니다.
	printf("distance: ");
	for (int i = 0; i < g->n; i++) {
		//i가 n까지의 범위에서 하나씩 늘어가며 반복되는 for문입니다.
		if (distance[i] == INF)
			printf(" * ");
		//만약 거리가 무한대(간선이 연결되지 않은 경우)로 표시되어있다면 "*"을 출력하고,
		else
			printf("%2d ", distance[i]);
		//아니라면 거리값을 출력합니다.
	}
	printf("\n");
	printf("        found:    ");
	for (int i = 0; i < g->n; i++)
		//i가 n까지의 범위에서 하나씩 늘어가는 for문입니다.
		printf("%2d ", found[i]);
	//노드 인덱스 i를 방문했으면 1을, 방문하지 않았으면 0을 출력합니다.
	printf("\n\n");
}
void shortest_path(GraphType* g, int start)
//그래프에서 start노드부터의 최단 경로를 찾는 알고리즘입니다. 
{
	int i, u, w;
	for (i = 0; i < g->n; i++) /* 초기화 작업입니다.*/
		//i가 0부터 n까지 하나씩 증가하며 반복되는 for문입니다.
	{
		distance[i] = g->weight[start][i];
		//시작 정점 start를 기준으로 했을때 가중치로 distance 배열을 초기화합니다.
		found[i] = FALSE;
		//시작 전이므로 방문 여부를 False로 지정합니다.
	}
	found[start] = TRUE; /* 시작 정점을 방문 표시합니다*/
	//시작 정점을 방문했으므로 방문 여부를 True로 지정합니다.
	distance[start] = 0;
	//시작 정점의 distance배열 값은 0입니다.
	for (i = 0; i < g->n - 1; i++) {
		//i가 0부터 n-1까지 하나씩 증가하며 반복되는 for문입니다.
		//위에서 시작 정점을 설정했으므로 하나를 뺀 n-1만큼 반복합니다.
		print_status(g);
		//그래프의 최단 경로를 출력합니다.
		u = choose(distance, g->n, found);
		//최소값의 인덱스를 u로 지정합니다.
		found[u] = TRUE;
		//현재 distance배열에서 최소값 인덱스인 u를 정점으로 선택합니다.
		//인덱스u를 방문 표시합니다.
		for (w = 0; w < g->n; w++)
			//가중치가 가장 적은 값을 가진 정점을 집합S에 추가한 뒤 계속하여 새롭게 발견되는 최소 가중치 정보를 수정해나갑니다.
			//w가 0부터 n까지 1씩 증가하며 반복되는 for문입니다.
			if (!found[w])
				//아직 선택되지 않은 정점 w입니다.
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];
		//만약 u까지의 최단 거리와 u에서 w의 거리를 합친 거리가 기존의 기준점에서 w까지의 거리보다 가깝다면 그 값으로 정보를 수정해줍니다.
	}
}
int main(void)
{
	GraphType g = { 7,
	{{ 0,  7,  INF, INF,   3,  10, INF },
	{ 7,  0,    4,  10,   2,   6, INF },
	{ INF,  4,    0,   2, INF, INF, INF },
	{ INF, 10,    2,   0,  11,   9,   4 },
	{ 3,  2,  INF,  11,   0, INF,   5 },
	{ 10,  6,  INF,   9, INF,   0, INF },
	{ INF, INF, INF,   4,   5, INF,   0 } }
	};

	GraphType h = { 10,
		//0 1 2 3 4 5 6 7 8 9 10
		 {

		 {  0,  3,INF,INF,INF, 11, 12,INF,INF,INF},//1
		 {  3,  0,  5,  4,  1,  7,  8,INF,INF,INF},//2
		 {INF,  5,  0,  2,INF,INF,  6,  5,INF,INF},//3
		 {INF,  4,  2,  0, 13,INF,INF, 14,INF, 16},//4
		 {INF,  1,INF, 13,  0,  9,INF,INF, 18, 17},//5
		 { 11,  7,INF,INF,  9,  0,INF,INF,INF,INF},//6
		 { 12,  8,  6,INF,INF,INF,  0, 13,INF,INF},//7
		 {INF,INF,  5, 14,INF,INF, 13,  0,INF, 15},//8
		 {INF,INF,INF,INF, 18,INF,INF,INF,  0, 10},//9
		 {INF,INF,INF, 16, 17,INF,INF, 15, 10,  0},//10
		 }

	};
	printf("인접행렬 구현 \n");
	shortest_path(&h, 0);
	return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
//�ʿ��� ���̺귯���� �߰��մϴ�.

//*���ͽ�Ʈ�� �˰����� ���ʸ� �����մϴ�.*//
#define TRUE 1
//True�϶� 1�� �����մϴ�.
#define FALSE 0
//False�϶� 0���� �����մϴ�.
#define MAX_VERTICES	100	
//�ִ� ������ ���� ��Ÿ���ϴ�.
#define INF	1000
// ������ ����Ǿ����� �ʴ� ��츦 ���Ѵ�� ��Ÿ���ϴ�.

typedef struct GraphType {
	int n;
	// ������ �����Դϴ�. 
	int weight[MAX_VERTICES][MAX_VERTICES];
	//��Ʈ��ũ�� ���� ����� �ʱ�ȭ
} GraphType;

int distance[MAX_VERTICES];
//���� �������κ��� �ִܰ���� �Ÿ��� �����մϴ�.
int found[MAX_VERTICES];
//�湮�� ������ ǥ���մϴ�.
int choose(int distance[], int n, int found[])
//���� distance�迭���� �ּ� ����ġ ���� �ִ� ��带 ��� �ε����� ��ȯ�մϴ�.
{
	int i, min, minpos;
	//�� ��带 ��Ÿ���� ������ �����մϴ�.

	min = INT_MAX;
	//min�� INT_MAX(���Ѵ�� ����, ������ ������� ���� ���)�� �����մϴ�.
	minpos = -1;
	for (i = 0; i < n; i++)
		//�ּҰ� min�� ã�� for���Դϴ�.
		//�湮�� �� ���� ���鿡 ���� distance �迭�� ���� ���մϴ�.
		if (distance[i] < min && !found[i]) {
			//���� ���� �湮���� �ʴ� ��� �� i�α����� �Ÿ��� ���� �ּҰ� min���� �۴ٸ�,
			min = distance[i];
			//�ּ� �Ÿ��� i�α����� �Ÿ��� min���� �����մϴ�.
			minpos = i;
			//�ּҰ��� ���� ����� �ε��� i�� minpos�� �����մϴ�.
		}
	return minpos;
	//�ּ� �Ÿ� ��� �ε����� i�� ��ȯ�մϴ�.
}

void print_status(GraphType* g)
//�ִ� ��θ� ����ϴ� �Լ� �Դϴ�.
{
	static int step = 1;
	printf("STEP %d: ", step++);
	//ù��° ���ܿ� 1�� �����Ͽ� ����ϰ� �ϳ��� �÷����ϴ�.
	printf("distance: ");
	for (int i = 0; i < g->n; i++) {
		//i�� n������ �������� �ϳ��� �þ�� �ݺ��Ǵ� for���Դϴ�.
		if (distance[i] == INF)
			printf(" * ");
		//���� �Ÿ��� ���Ѵ�(������ ������� ���� ���)�� ǥ�õǾ��ִٸ� "*"�� ����ϰ�,
		else
			printf("%2d ", distance[i]);
		//�ƴ϶�� �Ÿ����� ����մϴ�.
	}
	printf("\n");
	printf("        found:    ");
	for (int i = 0; i < g->n; i++)
		//i�� n������ �������� �ϳ��� �þ�� for���Դϴ�.
		printf("%2d ", found[i]);
	//��� �ε��� i�� �湮������ 1��, �湮���� �ʾ����� 0�� ����մϴ�.
	printf("\n\n");
}
void shortest_path(GraphType* g, int start)
//�׷������� start�������� �ִ� ��θ� ã�� �˰����Դϴ�. 
{
	int i, u, w;
	for (i = 0; i < g->n; i++) /* �ʱ�ȭ �۾��Դϴ�.*/
		//i�� 0���� n���� �ϳ��� �����ϸ� �ݺ��Ǵ� for���Դϴ�.
	{
		distance[i] = g->weight[start][i];
		//���� ���� start�� �������� ������ ����ġ�� distance �迭�� �ʱ�ȭ�մϴ�.
		found[i] = FALSE;
		//���� ���̹Ƿ� �湮 ���θ� False�� �����մϴ�.
	}
	found[start] = TRUE; /* ���� ������ �湮 ǥ���մϴ�*/
	//���� ������ �湮�����Ƿ� �湮 ���θ� True�� �����մϴ�.
	distance[start] = 0;
	//���� ������ distance�迭 ���� 0�Դϴ�.
	for (i = 0; i < g->n - 1; i++) {
		//i�� 0���� n-1���� �ϳ��� �����ϸ� �ݺ��Ǵ� for���Դϴ�.
		//������ ���� ������ ���������Ƿ� �ϳ��� �� n-1��ŭ �ݺ��մϴ�.
		print_status(g);
		//�׷����� �ִ� ��θ� ����մϴ�.
		u = choose(distance, g->n, found);
		//�ּҰ��� �ε����� u�� �����մϴ�.
		found[u] = TRUE;
		//���� distance�迭���� �ּҰ� �ε����� u�� �������� �����մϴ�.
		//�ε���u�� �湮 ǥ���մϴ�.
		for (w = 0; w < g->n; w++)
			//����ġ�� ���� ���� ���� ���� ������ ����S�� �߰��� �� ����Ͽ� ���Ӱ� �߰ߵǴ� �ּ� ����ġ ������ �����س����ϴ�.
			//w�� 0���� n���� 1�� �����ϸ� �ݺ��Ǵ� for���Դϴ�.
			if (!found[w])
				//���� ���õ��� ���� ���� w�Դϴ�.
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];
		//���� u������ �ִ� �Ÿ��� u���� w�� �Ÿ��� ��ģ �Ÿ��� ������ ���������� w������ �Ÿ����� �����ٸ� �� ������ ������ �������ݴϴ�.
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
	printf("������� ���� \n");
	shortest_path(&h, 0);
	return 0;
}



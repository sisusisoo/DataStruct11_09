#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

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
int choose(int distance[], int n, int found[]) //n�� �ִ� �ε���  
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
		//���� ���� start�� �������� ������ ����ġ�� distance �迭�� �ʱ�ȭ
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





//------------------------------------------------------

struct node {
	int v;
	int weight;
	struct node* next;
};
#define NUM_VERTEX 10
int stack[NUM_VERTEX];
int top = -1;
struct dijkstra {
	int found;//found, �ִܰŸ��� �˷����°� 1=yes, 0=no
	int distance;
	int prev_vrtex;
};
struct dijkstra dtable[NUM_VERTEX];
struct node* graph[NUM_VERTEX] = { 0 };

void print_status2()
//�ִ� ��θ� ����ϴ� �Լ� �Դϴ�.
{
	static int step = 1;
	printf("STEP %d: ", step++);
	//ù��° ���ܿ� 1�� �����Ͽ� ����ϰ� �ϳ��� �÷����ϴ�.
	printf("distance: ");
	for (int i = 0; i < NUM_VERTEX; i++) {
		//i�� n������ �������� �ϳ��� �þ�� �ݺ��Ǵ� for���Դϴ�.
		if (dtable[i].distance == 99999)
			printf(" * ");
		//���� �Ÿ��� ���Ѵ�(������ ������� ���� ���)�� ǥ�õǾ��ִٸ� "*"�� ����ϰ�,
		else
			printf("%2d ", dtable[i].distance);
		//�ƴ϶�� �Ÿ����� ����մϴ�.
	}
	printf("\n");
	printf("        found:    ");
	for (int i = 0; i < NUM_VERTEX; i++)
		//i�� n������ �������� �ϳ��� �þ�� for���Դϴ�.
		printf("%2d ", dtable[i].found);
	//��� �ε��� i�� �湮������ 1��, �湮���� �ʾ����� 0�� ����մϴ�.
	printf("\n\n");
}

void push(char s)
{
	if (top == NUM_VERTEX - 1)
		return;
	top++;
	stack[top] = s;
}
int pop()
{
	if (top == -1)
		return -1;
	int temp = stack[top];
	top--;
	return temp;

}
void initDtable()
{
	int i;
	for (i = 0; i < NUM_VERTEX; i++)
	{
		dtable[i].found = 0;
		dtable[i].distance = 99999;
		dtable[i].prev_vrtex = -1;
	}
}
void addEdge(int from, int to, int weight)
{
	struct node* cur = (struct node*)malloc(sizeof(struct node));
	cur->v = to;
	cur->weight = weight;
	cur->next = 0;

	if (graph[from] == 0)//ó�� ���� ���� ��
	{
		graph[from] = cur;
		return;
	}
	else
	{
		struct node* temp = graph[from];
		while (temp->next != 0)
			temp = temp->next;
		temp->next = cur;
		return;
	}
}
//�ִܰŸ����˷����� ���� vertex �߿��� 
//�Ÿ��� ���� ª�� vertex ��ȯ
//-1�̸� ���� ��� vertex �ִܰŸ��� �˷����� ���

int findDijkstraNextVertex()
{
	int i;
	int smallest_distance = 99999;
	int smallest_vertex = -1;

	for (i = 0; i < NUM_VERTEX; i++)
	{
		if (dtable[i].found == 0 && dtable[i].distance < smallest_distance)
		{
			smallest_vertex = i;
			smallest_distance = dtable[i].distance;
		}
	}
	return smallest_vertex;
}
void showDtable()
{
	int i;

	for (i = 0; i < NUM_VERTEX; i++)
		printf("%d | %d %d %d\n", i, dtable[i].found, dtable[i].distance, dtable[i].prev_vrtex);
}
void updateDTable(int v)
{
	struct node* cur = graph[v];
	while (cur != 0)
	{
		//�ִܰŸ��� �˷����� �ʾҰ�, 
		//���� �˷��� �Ÿ����� v�� ���Ұ��, �� ������ dtable�� ������Ʈ��
		if (dtable[cur->v].found == 0 &&
			(dtable[cur->v].distance > dtable[v].distance + cur->weight))
		{
			dtable[cur->v].distance = dtable[v].distance + cur->weight;
			dtable[cur->v].prev_vrtex = v;
		}
		cur = cur->next;
	}
}
void DoDijkstra(int v)
{
	int next_vertex = -1;
	dtable[v].distance = 0;
	while ((next_vertex = findDijkstraNextVertex()) != -1)
	{
		dtable[next_vertex].found = 1;
		updateDTable(next_vertex);
	}
}
void print_vertex(int num)
{
	int i = 0;
	printf("�ִܰ��: ");
	while ((i = pop()) != -1)
		printf("%d  ", i+1);//+1 
	printf("\n���� %d �Դϴ�\n", dtable[num].distance);
}
void find_dijkstra_vertex(int end)
{
	int start = 0;
	push(end);
	int i = end;
	while (1)
	{
		int prev = dtable[i].prev_vrtex;
		print_status2();
		if (prev == -1)
			break;
		else
		{
			push(prev);
			i = prev;
		}
	}
	print_vertex(end);
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
	printf("���Ḯ��Ʈ ���� \n");
	//������ �ִ� �׷���
	addEdge(0, 1, 3);//A->B
	addEdge(0, 5, 11);
	addEdge(0, 6, 12);

	addEdge(1, 0, 3);
	addEdge(1, 2, 5);
	addEdge(1, 3, 4);
	addEdge(1, 4, 1);
	addEdge(1, 5, 7);
	addEdge(1, 6, 8);

	addEdge(2, 1, 5);
	addEdge(2, 3, 2);
	addEdge(2, 6, 6);
	addEdge(2, 7, 5);

	addEdge(3, 1, 4);
	addEdge(3, 2, 2);
	addEdge(3, 4, 13);
	addEdge(3, 7, 14);
	addEdge(3, 9, 16);

	addEdge(4, 1, 1);
	addEdge(4, 3, 13);
	addEdge(4, 5, 9);
	addEdge(4, 8, 18);
	addEdge(4, 9, 17);

	addEdge(5, 0, 11);
	addEdge(5, 1, 7);
	addEdge(5, 4, 9);

	addEdge(6, 0, 12);
	addEdge(6, 1, 8);
	addEdge(6, 2, 6);
	addEdge(6, 7, 13);

	addEdge(7, 6, 13);
	addEdge(7, 2, 5);
	addEdge(7, 3, 14);
	addEdge(7, 9, 15);

	addEdge(8, 4, 18);
	addEdge(8, 9, 10);

	addEdge(9, 3, 16);
	addEdge(9, 4, 17);
	addEdge(9, 7, 15);
	addEdge(9, 8, 10);








	initDtable();
	DoDijkstra(0);
	int num = 0;
	printf("1~10������ vertex�� �ϳ��� �Է��ϼ���: ");
	
	scanf_s("%d", &num);
	num = num - 1;
	find_dijkstra_vertex(num);

	return 0;
}



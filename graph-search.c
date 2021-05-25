#include <stdio.h>
#include <stdlib.h>

/* �ִ� ������ ���� 10���� ���� */
#define MAX_VERTEX_NUM 10
#define MAX_QUEUE_NUM 20

#define TRUE 1
#define FALSE 0

int Queue[MAX_QUEUE_NUM];
int front = -1;
int rear = -1;

/* ���� ����ü */
typedef struct Vertex {
	int VertexNum;
	struct List* list;
	int visitflag;
} Vertex;

/* ���� ǥ���� ���� ����Ʈ ����ü */
typedef struct List {
	int adjNode;
	struct List* list;
	int visitflag;
} List;

void InitializeGraph(Vertex**);
void freeGraph(Vertex**);
void InsertVertex(Vertex**);
void InsertEdge(int tail, int head,Vertex**);
void printGraph(Vertex **);
void makeList(Vertex* v, int i);
void DepthFirstSearch(Vertex**, int);
void BreathFirstSearch(Vertex**, int);
int deQueue();
void enQueue(int aNode);
void InitializeVisitFlag(Vertex** head);

int main(void)
{
	char command;
	int a, b;
	/* �����(����)�� �迭 ���� */
	Vertex* head[MAX_VERTEX_NUM] = {NULL};

	printf("[----- [Yoon Yong Jin] [2016039040] -----]");

	/* �����⼺�� �����׷����� ���� */

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                        Graph Searches                          \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph          = z							    	\n");
		printf(" Insert Vertex             = v     Insert Edge              = e \n");
		printf(" Depth First Search        = d     Breath First Search      = b \n");
		printf(" Print Graph               = p     Quit                     = q \n");
		printf("----------------------------------------------------------------\n");
		
		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			InitializeGraph(&head);
			break;
		case 'q': case 'Q':
			freeGraph(&head);
			break;
		case 'v': case 'V':
			InsertVertex(&head);
			break;
		case 'e': case 'E':
			printf("Current Graph\n");
			printGraph(&head);
			printf("Enter the number of the two vertices to connect.\n");
			scanf("%d %d", &a, &b);
			InsertEdge(a, b, &head);
			break;
		case 'd': case 'D':
			printf("Enter the number of the vertex to start.\n");
			scanf("%d", &a);
			DepthFirstSearch(&head,a);
			InitializeVisitFlag(head);
			break;
		case 'b': case 'B':
			printf("Enter the number of the vertex to start.\n");
			scanf("%d", &a);
			BreathFirstSearch(&head,a);
			InitializeVisitFlag(head);
			break;
		case 'p': case 'P':
			printGraph(&head);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

/* �׷��� �ʱ�ȭ�Լ� */
void InitializeGraph(Vertex** head)
{
	if (*head != NULL)
		freeGraph(head);

	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		head[i] = (Vertex*)malloc(sizeof(Vertex));
		head[i]->VertexNum = -1;
		head[i]->list = NULL;
		head[i]->visitflag = FALSE;
	}
}

void freeGraph(Vertex** head)
{
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		free(head[i]);
	}
}

void InsertVertex(Vertex** head)
{
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		if (head[i]->VertexNum == -1)
		{
			head[i]->VertexNum = i;
			head[i]->list = NULL;
			head[i]->visitflag = FALSE;
			break;
		}
	}
}

void InsertEdge(int tail,int head,Vertex** h)
{
	makeList(h[tail], head);
	makeList(h[head], tail);
}

void makeList(Vertex* v, int i)
{
	List* p;
	List* temp = (List*)malloc(sizeof(List));
	temp->adjNode = i;
	temp->list = NULL;
	temp->visitflag = 0;

	p = v;
	if (p->list == NULL);
	else while (p->list != NULL)
	{
		/* �ڱ� ���� �� ���� ������ �ߺ� ���� */
		if (p->adjNode == i) return;
		p->visitflag = FALSE;
		p = p->list;
	}
	/* �ڱ� ���� �� ���� ������ �ߺ� ���� */
	if (p->adjNode == i) return;
	p->list = temp;
}


void printGraph(Vertex **head)
{
	Vertex* p;
	List* p2;
	int i = 0;

	p = head[0];
	while (i < MAX_VERTEX_NUM && p->VertexNum != -1)
	{
		printf("����� [%d]", i);
		p2 = p->list;
		while (p2 != NULL)
		{
			printf(" -> ");
			printf("[%d]",p2->adjNode);
			p2 = p2->list;
		}
		printf("\n");
		i++;
		p = head[i];
	}
}

void DepthFirstSearch(Vertex** head, int i)
{
	List* p;
	head[i]->visitflag = TRUE;
	printf("%5d", i);
	for (p = head[i]; p; p = p->list)
	{
		if (head[p->adjNode]->visitflag==FALSE)
			DepthFirstSearch(head, p->adjNode);
	}
}

void BreathFirstSearch(Vertex** head, int i)
{
	List* p;
	front = rear = -1;
	printf("%5d", i);
	head[i]->visitflag = TRUE;
	enQueue(i);

	while (1) {
		i = deQueue(); /* dequeue */
		if (i==-1) break;
		for (p = head[i]; p; p = p->list)
			if (head[p->adjNode]->visitflag == FALSE) 
			{
				printf("%5d", p->adjNode);
				enQueue(p->adjNode);
				head[p->adjNode]->visitflag = TRUE;
			}
	}
}

/* ť deQueue */
int deQueue()
{
	/* ť�� �����̸� ���� */
	if (front == rear) return -1;/* front�� rear�� ���� ���ٸ� ť�� � ��嵵 ����. */
	front++;/* ť�� ������ ����Ű��(front �������� ��尡 ť�� Ż��(����)��) front���� 1��ŭ ������Ų��. */
	int temp = Queue[front];/* ������ ��� ���� */
	Queue[front] = -1;/* ��� ���� */
	return temp;/* ��� ��ȯ */
}

/* ť enQueue */
void enQueue(int aNode)
{
	/* ť�� ���� á�ٸ� */
	if (rear == MAX_QUEUE_NUM - 1)
	{
		/* ���� ť ������ ������� */
		int size = rear - front;/* ť�� �����ִ� ����� ���� ���Ѵ�. */
		for (int i=0;i<size;i++)/* ���� ��� �� ��ŭ �ݺ� */
		{
			Queue[i] = Queue[front+(i+1)];/* ������ ť�� ������ �̵���Ų��*/
			Queue[front + (i + 1)] = NULL;
		}
		front = -1;/* front �ʱ�ȭ */
		rear = size-1; /* rear���� size-1�� �ʱ�ȭ �Ͽ� front�� rear���� �Ÿ� ���� */
		return;
	}
	rear++;/* ť�� ���� ����Ű�� rear���� 1��ŭ ������Ų��.*/
	Queue[rear] = aNode;/* ���ο� ��� ���� */
}

void InitializeVisitFlag(Vertex** head)
{
	List* p;
	for (int i = 0; i < MAX_VERTEX_NUM && head[i]->VertexNum!= -1; i++)
	{
		for (p = head[i]; p; p = p->list)
		{
			p->visitflag = FALSE;
		}
	}
}
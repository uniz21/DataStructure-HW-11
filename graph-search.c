#include <stdio.h>
#include <stdlib.h>

/* 최대 정점의 수는 10개로 설정 */
#define MAX_VERTEX_NUM 10
#define MAX_QUEUE_NUM 20

#define TRUE 1
#define FALSE 0

int Queue[MAX_QUEUE_NUM];
int front = -1;
int rear = -1;

/* 정점 구조체 */
typedef struct Vertex {
	int VertexNum;
	struct List* list;
	int visitflag;
} Vertex;

/* 간선 표현을 위한 리스트 구조체 */
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
	/* 헤드노드(정점)의 배열 선언 */
	Vertex* head[MAX_VERTEX_NUM] = {NULL};

	printf("[----- [Yoon Yong Jin] [2016039040] -----]");

	/* 무방향성의 인접그래프로 설정 */

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

/* 그래프 초기화함수 */
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
		/* 자기 간선 및 동일 간선의 중복 제외 */
		if (p->adjNode == i) return;
		p->visitflag = FALSE;
		p = p->list;
	}
	/* 자기 간선 및 동일 간선의 중복 제외 */
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
		printf("헤드노드 [%d]", i);
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

/* 큐 deQueue */
int deQueue()
{
	/* 큐가 공백이면 종료 */
	if (front == rear) return -1;/* front와 rear의 값이 같다면 큐에 어떤 노드도 없다. */
	front++;/* 큐의 시작을 가르키는(front 방향으로 노드가 큐를 탈출(삭제)함) front값을 1만큼 증가시킨다. */
	int temp = Queue[front];/* 삭제할 노드 저장 */
	Queue[front] = -1;/* 노드 삭제 */
	return temp;/* 노드 반환 */
}

/* 큐 enQueue */
void enQueue(int aNode)
{
	/* 큐가 가득 찼다면 */
	if (rear == MAX_QUEUE_NUM - 1)
	{
		/* 선형 큐 앞으로 끌어당기기 */
		int size = rear - front;/* 큐에 남아있는 노드의 수를 구한다. */
		for (int i=0;i<size;i++)/* 남은 노드 수 만큼 반복 */
		{
			Queue[i] = Queue[front+(i+1)];/* 노드들을 큐의 앞으로 이동시킨다*/
			Queue[front + (i + 1)] = NULL;
		}
		front = -1;/* front 초기화 */
		rear = size-1; /* rear값은 size-1로 초기화 하여 front와 rear간의 거리 유지 */
		return;
	}
	rear++;/* 큐의 끝을 가르키는 rear값을 1만큼 증가시킨다.*/
	Queue[rear] = aNode;/* 새로운 노드 삽입 */
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
#include <stdio.h>
#include <stdlib.h>

/* 최대 정점의 수는 10개로 설정 */
#define MAX_VERTEX_NUM 10

#define TRUE 1
#define FALSE 0

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
			break;
		case 'b': case 'B':
			printf("Enter the number of the vertex to start.\n");
			scanf("%d", &a);
			BreathFirstSearch(&head,a);
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

}

void InitializeVisitFlag(Vertex** head)
{
	List* p;
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		for (p = head[i]; p; p = p->list)
		{

		}
	}
}
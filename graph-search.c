#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 10

typedef struct Vertex {
	int VertexNum;
	struct List* list;
} Vertex;

typedef struct List {
	int adjNode;
	struct List* list;
}List;

void InitializeGraph(Vertex**);
void freeGraph(Vertex**);
void InsertVertex(Vertex**);
void InsertEdge(int tail, int head,Vertex**);
void printGraph(Vertex **);
void makeList(Vertex* v, int i);

int main(void)
{
	char command;
	int a, b;
	//Vertex* head = NULL;
	Vertex* head[MAX_VERTEX_NUM] = {NULL};

	printf("[----- [Yoon Yong Jin] [2016039040] -----]");

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

			break;
		case 'b': case 'B':

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

void InitializeGraph(Vertex** head)
{
	if (*head != NULL)
		freeGraph(head);

	//*head = (Vertex*)malloc(sizeof(Vertex) * MAX_VERTEX_NUM);
	/*(*head)->VertexNum = -1;
	(*head)->list = NULL;*/

	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		head[i] = (Vertex*)malloc(sizeof(Vertex));
		head[i]->list = NULL;
		head[i]->VertexNum = -1;
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

	p = v;
	if (p->list == NULL);
	else while (p->list != NULL)
	{
		if (p->adjNode == i) return;
		p = p->list;
	}
	if (p->adjNode == i) return;
	p->list = temp;
}

void printGraph(Vertex **head)
{
	Vertex* p;
	List* p2;
	int i = 0;

	p = head[0];
	while (p->VertexNum != -1 && i < MAX_VERTEX_NUM)
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
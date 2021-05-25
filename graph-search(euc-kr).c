#include <stdio.h>
#include <stdlib.h>

/* �ִ� ������ ���� 10���� ���� */
#define MAX_VERTEX_NUM 10
#define MAX_QUEUE_NUM 10

/* ������ ���� */
#define TRUE 1
#define FALSE 0

/* int���� ť ���� */
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
/* �� ����ü�� ���� ������ ��������, 
*  ������ ����Ʈ��带 �����ϱ� ���� �ѷ� ��������.*/

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
			/* �׷��� �ʱ�ȭ */
			InitializeGraph(&head);
			break;
		case 'q': case 'Q':
			/* �׷��� �޸� �Ҵ� ���� */
			freeGraph(&head);
			break;
		case 'v': case 'V':
			/* ���� �߰� */
			InsertVertex(&head);
			break;
		case 'e': case 'E':
			/* �׷��� �ʱ�ȭ ��ó�� */
			if (*head == NULL)
			{
				printf("Initialize First\n");
				break;
			}
			/* ���� �׷����� ����� � �������� ������ �� �ִ��� Ȯ�� */
			printf("Current Graph\n");
			printGraph(&head);
			/* �������� ������ �� ������ �Է¹޴´� */
			printf("Enter the number of the two vertices to connect.\n");
			scanf("%d %d", &a, &b);
			InsertEdge(a, b, &head);
			break;
		case 'd': case 'D':
			/* �׷��� �ʱ�ȭ ��ó�� */
			if (*head == NULL)
			{
				printf("Initialize First\n");
				break;
			}
			/* ���� �켱 Ž���� ������ ������ �����Ѵ�. */
			printf("Enter the number of the vertex to start.\n");
			scanf("%d", &a);
			/* ���� a�������� �����ϴ� ���̿켱 Ž�� */
			DepthFirstSearch(&head,a);
			/* �� ������ �湮���θ� �ʱ�ȭ��, ���� Ž���� �����ϵ��� �Ѵ�. */
			InitializeVisitFlag(head);
			break;
		case 'b': case 'B':
			/* �׷��� �ʱ�ȭ ��ó�� */
			if (*head == NULL)
			{
				printf("Initialize First\n");
				break;
			}
			/* �ʺ� �켱 Ž���� ������ ������ �����Ѵ�. */
			printf("Enter the number of the vertex to start.\n");
			scanf("%d", &a);
			/* ���� a�������� �����ϴ� �ʺ�켱 Ž�� */
			BreathFirstSearch(&head,a);
			/* �� ������ �湮���θ� �ʱ�ȭ��, ���� Ž���� �����ϵ��� �Ѵ�. */
			InitializeVisitFlag(head);
			break;
		case 'p': case 'P':
			/* �׷��� ��� */
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
	/* ���� �׷����� �ִ� ��� �޸� ���� �� �ʱ�ȭ */
	if (*head != NULL)
		freeGraph(head);

	/* Vertex[] �ʱ�ȭ */
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		head[i] = (Vertex*)malloc(sizeof(Vertex));
		/* �ش� ������ �̸�(��ȣ), ������ �����ϱ� ������ -1�� �ʱ�ȭ */
		head[i]->VertexNum = -1;
		/* ������ �������� ����� ����Ʈ ��� */
		head[i]->list = NULL;
		/* Ž�� �� �ش� ��� �湮 ���� */
		head[i]->visitflag = FALSE;
	}
}

/* �޸� ���� */
void freeGraph(Vertex** head)
{
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		free(head[i]);
	}
}

/* ���� ���� */
void InsertVertex(Vertex** head)
{
	/* �׷��� �ʱ�ȭ ��ó�� */
	if (*head == NULL)
	{
		printf("Initialize First\n");
		return;
	}

	/* ������ �ʱ�ȭ��, Vertex[] Ž�� */
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		/* ���� ó������ ������ VertexNum�� -1�� ���� �ش� ��尡 ���� �߰����� �ʾ�, �̹��� �߰��� ������� �� �� �ִ�. */
		if (head[i]->VertexNum == -1)
		{
			/* ��� �̸� �ο� */
			head[i]->VertexNum = i;
			/* �������� ����� ����Ʈ ��� ���� */
			head[i]->list = NULL;
			/* ���� �湮���� �������� �ʱ�ȭ */
			head[i]->visitflag = FALSE;
			break; /* �� ���� -> �ѹ��� �ϳ��� ��常 �߰� */
		}
	}
}

/* ���� �߰�, ������ �� ����� �̸�(��ȣ)�� �Է¹��� */
void InsertEdge(int tail,int head,Vertex** h)
{
	/* �׷��� �ʱ�ȭ ��ó�� */
	if (*h == NULL)
	{
		printf("Initialize First\n");
		return;
	}

	/* ������ �׷��� �̹Ƿ� �ϳ��� ������ �ΰ��� ����Ʈ ��尡 �ʿ��ϴ�. */
	makeList(h[tail], head);
	makeList(h[head], tail);
}

/* ����Ʈ ��� ���� */
/* DFS, BFS�� ���� Ž���� �� �� ���� Edge�� ���� ���,
*  ������ ��ȣ�� ���������� Ž���ϵ��� �ϱ� ����
*  ����Ʈ ��带 ������������ �����ؾ��Ѵ�. */
void makeList(Vertex* v, int i)
{
	/* Vertex[i]�� ����Ʈ ������ Ž���ϱ� ���� p�� ���� */
	List* p;
	List* prev = (List*)malloc(sizeof(List));
	/* ���Ӱ� �߰��� ����Ʈ ��� ���� */
	List* temp = (List*)malloc(sizeof(List));
	temp->adjNode = i;
	temp->list = NULL;
	temp->visitflag = 0;

	/* ����Ʈ ��� Ž�� */
	p = v;
	/* ù ����Ʈ��尡 ����ִ°�� == ���� ����� ��尡 ���� ��� */
	if (p == NULL);
	/* ������ ����� ����Ʈ ��尡 �ִ� ��� */
	else
	{
		do
		{
			/* �ڱ� ���� �� ���� ������ �ߺ� ���� */
			if (p->adjNode == i) return;
			/* �������� ���� */
			if (p!=v && p->adjNode > i)/* i���� ū ��ȣ�� ����Ʈ ��� �߽߰� �տ� ����Ʈ��� ���� */
			{
				temp->list = p;
				prev->list = temp;
				return;
			}
			/* ���� ����Ʈ ��� Ž�� */
			prev = p;
			p = p->list;
		} while (p != NULL);
	}
	prev->list = temp;/* ����Ʈ��� ���� */
}

/* �׷��� ��� */
void printGraph(Vertex **head)
{
	/* �׷��� �ʱ�ȭ ��ó�� */
	if (*head == NULL)
	{
		printf("Initialize First\n");
		return;
	}

	/* Vertex[]�� Ž�� */
	Vertex* p;
	/* p=Vertex[i]�� ����Ʈ ������ Ž�� */
	List* p2;
	int i = 0;

	p = head[0];
	/* �ִ� 10���� ������ Ž���Ѵ�. */
	while (i < MAX_VERTEX_NUM && p->VertexNum != -1)
	{
		/* p�� �ش��ϴ� ����� ��� */
		printf("����� [%d]", i);
		/* ����� ������ ����Ʈ ������ Ž��*/
		p2 = p->list;
		while (p2 != NULL)
		{
			/* ����Ʈ ��� ��� */
			printf(" -> ");
			printf("[%d]",p2->adjNode);
			p2 = p2->list;
		}
		printf("\n");
		i++;
		p = head[i];
	}
}

/* ���̿켱 Ž�� */
void DepthFirstSearch(Vertex** head, int i)
{
	/* �׷��� �ʱ�ȭ ��ó�� */
	if (*head == NULL)
	{
		printf("Initialize First\n");
		return;
	}
	/* 10�̻��� ��ȣ�� Ž�� �õ� ó�� */
	if(i>=MAX_VERTEX_NUM)
	{
		printf("Out of range\n");
		return;
	}
	/* �������� ���� ���� Ž�� �õ� */
	if(head[i]->VertexNum == -1)
	{
		printf("There is no [%d] Vertex\n",i);
		return;
	}
	
	List* p;
	int min;
	/* ���� ������� �湮���� ������ ���� */
	head[i]->visitflag = TRUE;
	/* Ž���� ���� ��� ��� */
	printf("%5d", i);
	/* ���� �湮���� ���� �������� ����� ��� Ž�� */
	for (p = head[i]; p; p = p->list)
	{
		/* �湮���� ���� ��� �߽߰� */
		if (head[p->adjNode]->visitflag==FALSE)
			/* ��������� Ž�� */
			DepthFirstSearch(head, p->adjNode);
	}
	/* �������� �������� ����� ��带 Ž�� �ϰ� Ž���� ��带 �ٽ� �������� ��� Ž���ϱ� ������ ���� �켱 Ž���� �̷������. */
}

/* �ʺ�켱 Ž�� */
void BreathFirstSearch(Vertex** head, int i)
{
	/* �׷��� �ʱ�ȭ ��ó�� */
	if (*head == NULL)
	{
		printf("Initialize First\n");
		return;
	}
	/* 10�̻��� ��ȣ�� Ž�� �õ� ó�� */
	if (i >= MAX_VERTEX_NUM)
	{
		printf("Out of range\n");
		return;
	}
	/* �������� ���� ���� Ž�� �õ� */
	if(head[i]->VertexNum == -1)
	{
		printf("There is no [%d] Vertex\n",i);
		return;
	}
	
	List* p;
	front = rear = -1;
	/* ���� Ž�� ��� ��� */
	printf("%5d", i);
	/* ���� ������� �湮���� ������ ���� */
	head[i]->visitflag = TRUE;
	/* ���� ��� ť�� ���� */
	enQueue(i);

	/* ���ѹݺ� */
	while (1) {
		/* ť�κ��� Ž���� ���� ����� ��ȣ ����*/
		i = deQueue(); /* dequeue */
		if (i==-1) break;/* ����ִ� ��尡 ����Ǹ� �ݺ� ���� */
		for (p = head[i]; p; p = p->list)/* �ش� ���� ����� ����Ʈ ������ Ž�� */
			/* ���� �湮���� ���� ��� �߰� �� */
			if (head[p->adjNode]->visitflag == FALSE) 
			{
				printf("%5d", p->adjNode);/* ��� */
				enQueue(p->adjNode);/* ť�� ���� */
				head[p->adjNode]->visitflag = TRUE;/* �湮 �ߴ� ������� ����Ѵ�. */
			}
	}
	/* Ž�� �켱 ������ ť�� �����ѵ� ť�� �������� Ž���ϱ� ������ �ʺ� �켱 Ž���� �̷������. */
}

/* ť deQueue ���� Ž�� Ʈ��2�� ť�� ��Ȱ�� */
int deQueue()
{
	/* ť�� �����̸� ���� */
	if (front == rear) return -1;/* front�� rear�� ���� ���ٸ� ť�� � ��嵵 ����.
								 (int�� ť�� �����Ͽ��� ������ NULL�� 0���� 0�� ������ ���� Ž���� ���ذ� �ǹǷ� -1�� ��ü) */
	front++;/* ť�� ������ ����Ű��(front �������� ��尡 ť�� Ż��(����)��) front���� 1��ŭ ������Ų��. */
	int temp = Queue[front];/* ������ ��� ���� */
	Queue[front] = -1;/* ��� ����(int�� ť�� �����Ͽ��� ������ NULL�� 0���� 0�� ������ ���� Ž���� ���ذ� �ǹǷ� -1�� ��ü) */
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

/* VisitFlag �ʱ�ȭ, �ѹ� Ž���� ���� �ʱ�ȭ ���� ������, 
*  ��� ��带 �̹� �湮�� ������ ����ϱ� ������ ���� Ž���� �Ұ����ϴ�. */
void InitializeVisitFlag(Vertex** head)
{
	/* �׷��� �ʱ�ȭ ��ó�� */
	if (*head == NULL) return;

	List* p;
	for (int i = 0; i < MAX_VERTEX_NUM && head[i]->VertexNum!= -1; i++)
	{   /* Vertex[]�� ��� �� insertVertex()�Լ��� ������ �������� Ž�� */
		for (p = head[i]; p; p = p->list) /* ������, ������ ����� ����Ʈ ������ Ž���Ͽ� �湮���� �ʱ�ȭ */
		{
			p->visitflag = FALSE; /* �湮���� �ʱ�ȭ */
		}
	}
}
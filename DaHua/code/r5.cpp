//卡片游戏
#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0

typedef struct qnode {
	int data;
	struct qnode *next;
}QNODE, *QUEUEPTR;

typedef struct {            //队列结构 
	QUEUEPTR front, rear;
}LINKQUEUE;

LINKQUEUE *initQueue(void);            //初始化队列 
int inQueue(LINKQUEUE *queue, int e);   //入队 
int outQueue(LINKQUEUE *queue, int *e);  //出队 
int printQueue(LINKQUEUE *queue);
int destoyQueue(LINKQUEUE *queue);
int card(LINKQUEUE *queue);
int queueLength(LINKQUEUE *queue);      //求队列长度 


int queueLength(LINKQUEUE *queue)
{
	QUEUEPTR p = queue->front;
	int count = 0;
	while (queue->front != NULL)         //遍历队列，求得队列长度 
	{
		queue->front = queue->front->next;
		count++;
	}

	queue->front = p;         //重置队列首指针 

	return count;        //返回队列长度 
}

int card(LINKQUEUE *queue)
{
	int len = queueLength(queue);

	QUEUEPTR p, q;

	while (len >= 2)
	{
		p = queue->front;
		queue->front = queue->front->next;
		q = queue->front;
		queue->front = queue->front->next;
		//printf("queue->front->data = %d   p->next->data = %d\n",queue->front->data,p->next->data);
		inQueue(queue, q->data);
		//queue->front = queue->front->next;
		printf("%d ", p->data);
		free(p);
		free(q);
		len--;
	}
	//printf("\n");
	while (queue->front != NULL)          //打印最后剩下的元素 
	{
		printf("%d ", queue->front->data);
		queue->front = queue->front->next;
	}

	free(queue);
	return OK;
}

/*
int destroyQueue(LINKQUEUE *queue)
{
QUEUEPTR p;
p = queue->front;

while(p != queue->rear)
{
queue->front = queue->front->next;
free(p);
p = queue->front;
}

free(queue);

return OK;
}
*/

/*
int printQueue(LINKQUEUE *queue)
{
QUEUEPTR p;
p = queue->front;

while(queue->front != NULL)       //考虑queue->front == queue->rear 做判断条件为何会少打印一个元素
{
printf("%d ",queue->front->data);
queue->front = queue->front->next;
}

queue->front = p;

return OK;
}
*/

LINKQUEUE *initQueue(void)        //初始化队列，创建一空队列 
{
	LINKQUEUE *queue = (LINKQUEUE *)malloc(sizeof(LINKQUEUE));

	if (!queue)
		exit(0);

	queue->front = NULL;
	queue->rear = NULL;

	return queue;
}


int inQueue(LINKQUEUE *queue, int e)
{
	QUEUEPTR p = (QUEUEPTR)malloc(sizeof(QNODE));
	if (!p)
		exit(0);

	p->data = e;
	p->next = NULL;


	if (queue->front == NULL)     //为了判断是否是空队列，else 的为队列添加元素在空队列时不能使用，不能对rear == NULL 时取 rear->next 
	{
		queue->front = p;
		queue->rear = p;
		//queue->rear->next = p;	    
	}
	else
	{
		queue->rear->next = p;
		queue->rear = p;
	}

	//queue->rear->next = p;
	//queue->rear = p;


	return OK;

}

/*
int outQueue(LINKQUEUE *queue,int *e)
{
if(queue->front == queue->rear)        //对空队列做判断
{
printf("the queue is empty\n");
return ERROR;
}

QUEUEPTR p;
p = queue->front->next;
*e = p->data;
queue->front->next = p->next;

if(queue->rear == p)       //如果即将释放的结点是尾结点，则重新指向队首
queue->rear = queue->front;

free(p);

return OK;

}
*/

int main(void)
{
	freopen("r9.txt", "r", stdin);

	LINKQUEUE *queue = initQueue();     //初始化队列 

	int n;
	scanf("%d", &n);

	int i = 1;
	while (i <= n)          //初始化编号 
	{
		inQueue(queue, i);
		i++;
	}

	//printQueue(queue);        debug 

	card(queue);          //处理问题函数 

						  //destroyQueue(queue);        不需要在另外释放，在card中就在不断释放结点 

	return 0;
}


/*******************范例代码**********************/
#include<stdio.h>
const int MAXN = 50
int queue[MAXN];
int main(void)
{
	int n, front, rear;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		queue[i] = i + 1;
	front = 0;
	rear = n;

	while (front < rear)
	{
		printf("%d ", queue[front++]);
		queue[rear++] = queue[front++];
	}
	return 0;
}



//C++   STL队列
#include<cstdio>
#include<queue>
using namespace std;

queue<int> q;
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		q.push(i + 1);           //初始化队列

	while (!q.empty())
	{
		printf("%d ", q.front());
		q.pop();
		q.push(q.front());
		q.pop();
	}
	return 0;
}
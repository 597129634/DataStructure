//队列的基本操作--顺序结构 

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXSIZE 100
#define ERROR 0
#define OK 1

typedef struct {
	char data[MAXSIZE];
	int front, rear;
}QUEUE;


QUEUE *initQueue(void);    //创建空队列 
int inQueue(QUEUE *queue, char e);  //入队列操作 
int printQueue(QUEUE *queue);  //打印队列
int outQueue(QUEUE *queue);    //出队列操作 

int outQueue(QUEUE *queue)
{
	if (queue->front == queue->rear)
	{
		printf("the queue is empty\n");
		return ERROR;
	}
	else
		++queue->front;

	return OK;
}



int printQueue(QUEUE *queue)
{
	QUEUE temp;
	temp.front = queue->front;  //用来遍历完重新初始化队列首指标 

	while (queue->front <= queue->rear)
		printf("%c", queue->data[queue->front++]);

	queue->front = temp.front;

	return OK;
}

int inQueue(QUEUE *queue, char e)
{
	if (queue->rear == MAXSIZE)
	{
		printf("queue is full\n");
		return ERROR;
	}
	else
	{
		queue->data[queue->rear++] = e;
		return OK;
	}
}

QUEUE *initQueue(void)
{
	QUEUE *queue = (QUEUE *)malloc(sizeof(QUEUE));    //不要忘记分配内存 
	queue->front = 0;
	queue->rear = 0;
	memset(queue->data, 0, sizeof(char)*MAXSIZE);

	return queue;
}

int main(void)
{
	freopen("r6.txt", "r", stdin);

	QUEUE *queue = initQueue();

	char n;
	while (scanf("%c", &n) != EOF)
	{
		inQueue(queue, n);
	}

	printQueue(queue);

	int i = 1;
	while (i<5)
	{
		outQueue(queue);
		i++;
	}

	printQueue(queue);

	free(queue);
	return 0;
}
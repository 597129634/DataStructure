//链式队列
#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1 

typedef struct qnode {       //结点结构 
	int data;
	struct qnode *next;
}QNODE, *QUEUEPTR;

typedef struct {          //队列的链表结构 
	QUEUEPTR front, rear;
}LINKQUEUE;

int inQueue(LINKQUEUE *queue, int e)
{
	QUEUEPTR s = (QUEUEPTR)malloc(sizeof(QNODE));
	if (!s)         //储存分配失败 
		exit(OVERFLOW)

	s->data = e;
	s->next = NULL;
	queue->rear->next = s;    //把该结点接到队尾 
	queue->rear = s;          //更新尾结点指针 

	return OK;
}

int outQueue(LINKQUEUE *queue, int *e)
{
	QUEUEPTR p;

	if (queue->front == queue->rear)    //空表 
		return ERROR;

	p = queue->front->next;
	*e = p->data;
	queue->front->next = p->next;

	if (queue->rear == p)     //如果队头是队尾，则删除后将 rear 指向头节点 
		queue->rear = queue->front;

	free(p);

	return OK;
}
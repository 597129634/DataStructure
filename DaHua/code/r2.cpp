#include<stdio.h>
#include<stdlib.h>

//链栈的结构定义 
typedef struct StackNode {    //栈结点结构 
	int data;
	struct StackNode *next;
}StackNode, *LinkStackPtr;

typedef struct LinkStack {        //栈 
	LinkStackPtr top;
	int count;
}LinkStack;

LinkStack *creatStack(void);
void print(LinkStack *S);
void destroyStack(LinkStack *S);

void destroyStack(LinkStack *S)
{
	LinkStackPtr temp;
	while (S->top != NULL)
	{
		temp = S->top;
		S->count--;
		S->top = S->top->next;
		//printf("S->count = %d\n",S->count);
		free(temp);
	}

}

LinkStack *creatStack(void)
{
	LinkStack *S = (LinkStack *)malloc(sizeof(LinkStack));   //创建栈头，分配空间 
	S->count = 0;
	S->top = NULL;

	LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
	s->next = NULL;
	int a = 0;
	while (scanf("%d", &a) != EOF)   //读到文件末尾
	{
		LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
		s->next = NULL;
		s->data = a;
		s->next = S->top;
		S->top = s;
		S->count++;


	}

	return S;
}

void print(LinkStack *S)
{
	LinkStackPtr head = S->top;
	while (S->top != NULL)
	{
		printf("%d ", S->top->data);
		S->top = S->top->next;
	}
	S->top = head;    //循环打印遍历链栈时，光靠上面循环会使栈顶指针已经指向栈顶，应该设一个临时变量保存一开始的栈顶指针，在循环结束后重置栈顶指针，以便进行后继操作 
	printf("\nthe count is %d\n", S->count);
}

int main(void)
{
	freopen("r3.txt", "r", stdin);
	LinkStack *S;
	S = creatStack();
	//printf("S->top = %d \n",S->top->data);
	//printf("S->top->next = %d\n",S->top->next->data);
	//printf("S->top->next->next = %d",S->top->next->next->data);
	print(S);

	destroyStack(S);
	print(S);

	return 0;
}




/**********************************************/
int Pop(LinkStack *S, int *e)   //在原函数中声明 int *e 时要分配内存（别忘记释放）
{
	if (S->top == NULL)   //判断是否是空栈 
		return ERROR;

	*e = S->top->data;
	LinkStackPtr temp = S->top;
	S->top = S->top->next;
	S->count--;
	free(temp);

	return OK;
}

void Push(LinkStack *S, int e)
{
	LinkStackPtr temp = (LinkStackPtr)malloc(sizeof(StackNode));
	temp->next = NULL;

	temp->data = e;
	temp->next = S->top;
	S->top = temp;

	S->count++;
}
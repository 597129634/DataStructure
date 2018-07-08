//栈的顺序结构   进出栈操作
//栈的结构定义 
typedef struct {
	char data[MAXSIZE];
	int top;   //栈顶指针 
}SqStack;

//出栈操作
int Pop(SqStack *S, char *d)
{
	if (S->top == -1)
		return ERROR;

	*d = S->data[S->top--];
	//S->top--;

	return OK;
}


//进栈操作
int Push(SqStack *S, int e)    //进栈 
{
	if (S->top == MAXSIZE - 1)  // 栈满 
		return ERROR;

	S->data[++S->top] = e;

	return OK;
}


/****************测试************************/
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define OK 1
#define ERROR 0

//栈的结构定义 
typedef struct {
	char data[MAXSIZE];
	int top;   //栈顶指针 
}SqStack;

int Push(SqStack *S, int e);
void print(SqStack *S);
SqStack *creatStack(void);
int Pop(SqStack *S, char *d);

int Pop(SqStack *S, char *d)
{
	if (S->top == -1)
		return ERROR;

	*d = S->data[S->top--];
	//S->top--;

	return OK;
}

SqStack *creatStack(void)    //创建栈
{
	SqStack *S;
	S = (SqStack *)malloc(sizeof(SqStack));   //为栈申请空间
	S->top = -1;

	int a = getchar();   //读取元素   
	int i = 0;
	while (a&&i<MAXSIZE)
	{
		S->data[++S->top] = a;
		a = getchar();
		if (a == '\n')
			break;

		i++;
	}

	return S;
}

void print(SqStack *S)
{
	for (int i = 0; i<MAXSIZE&&i <= S->top; i++)   //top 指向的既是栈顶元素，并非栈顶的下一个元素 
	{
		printf("%d ", S->data[i] - '0');    //字符转整形  ASCII - '0'
	}
}


int Push(SqStack *S, int e)    //进栈 
{
	if (S->top == MAXSIZE - 1)  // 栈满 
		return ERROR;

	S->data[++S->top] = e;

	return OK;
}

int main(void)
{
	freopen("r2.txt", "r", stdin);

	SqStack *S;
	S = creatStack();
	printf("the Stack is: ");
	print(S);
	printf("\n");

	char e = getchar();
	//printf("e = %d \n",e-'0');


	Push(S, e);
	printf("The Stack is: ");
	print(S);
	printf("\n");

	char *d = (char *)malloc(sizeof(char *));   //注意使用指针的时候要分配内存，在这里如果仅是声明 char *d就进行传参会出现错误
												//分配完记得释放内存 
	Pop(S, d);
	printf("The Stack is: ");
	print(S);
	printf("\n");

	printf("%d ", *d - '0');

	free(S);
	free(d);
	printf("\n***************\n");

	return 0;
}
//测试数据
12345678   //原栈中元素
9          //操作元素，先插后删
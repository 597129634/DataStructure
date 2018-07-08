第四章 栈与队列
栈 ：仅在表尾进行插入和删除操作的线性表
队列 ：只允许在一端进行插入操作，在另一端进行删除操作

4.2.1 栈
Last in First Out
栈的抽象数据类型
ADT 栈（stack）
Data  同线性表，元素具有相同类型，相邻元素有前驱和后继关系
Operation
    InitStack（*S）：初始化操作，建立一个空栈
	....

/********************************************************************/
栈的顺序储存结构
用下标为 0 的一端做栈底比较好，因为首元素都存在栈底，变化最小
定义top变量来指示栈顶元素在数组中的位置
当栈存在一个元素时，top = 0，通常把空栈的判定条件定为 top = -1
栈的结构定义
typedef int SElemType     // SElemType 类型根据实际情况而定，这里假设 int
typedef struct
{
	SElemType data[MAXSIZE];
	int top;
}SqStack;

进栈操作 push
//插入元素为 e 的新栈顶元素
Status Push(SqStack *S, SElemType e)
{
	if (S->top == MAXSIZE - 1)  //如果栈满 对栈的编号为 从 0 到 MAXSIZE - 1
		return ERROR;
	
	S->top++;   //栈顶指针加 1
	S->data[S->top] = e;   //更新栈顶元素

	return OK;
}

出栈操作 pop
//若栈不空，则删除栈顶元素，用 e 返回其值
Status Pop(SqStack *S, SElemType *e)
{
	if (S->top == -1)
		return ERROR;

	*e = S->data[S->top];
	S->top--;

	return OK;
}
//两者没有涉及循环 时间复杂度为 O（1）


4.5 两栈共享空间
用一个数组存储两个栈--节约空间
photo见 p119
一个数组有两个端点，让一个栈的栈底为 0，另一个为 n-1，填充元素时向数组中间加
当两栈满时 top1 + 1 == top2
typedef struct
{
	SElemType data[MAXSIZE];
	int top1;
	int top2;
}SqDoubleStack;
对于两栈共享空间的push方法，除了要插入元素值参数外，还要有一个判断是 栈1 还是 栈2 的栈号参数stackNumber
//插入元素 e 为新的栈顶元素
Status Push(SqDoubleStack *S, SElemType e, int stackNumber)
{
	if (S->top1 + 1 == S->top2)  //栈满
		return ERROR;

	if (stackNumber == 1)  //栈 1 有元素进栈
		S->data[++S->top1] = e;  //先 top1 + 1 后给数组赋值
	else if (stackNumber == 2)  //栈 2 有元素进栈
		S->data[--S->top2] = e;  //先 top2 - 1 后给数组赋值

	return OK;
}

对于两栈共享空间的 pop 方法，参数仅是判断 栈1 栈2 的参数 stackNumber
//若栈不空，删除栈顶元素，用e返回其值
Status Pop(SqDoubleStack *S, SElemType *e, int stackNumber)
{
	if (stackNumber == 1)
	{
		if (S->top1 == -1)  //栈 1 空栈
			return ERROR; 

		*e = S->data[S->top1--];  //将栈1 的栈顶元素出栈
	}
	else if (stackNumber == 2)
	{
		if (S->top2 == MAXSIZE)
			return ERROR;

		*e = S->data[S->top2++];
	}

	return OK;
}
NOTE 一般使用这样的数据结构，通常都是两个栈对空间的需求有相反关系时，即一个栈增长时，另一个栈缩短


/*********************************************************************************/
栈的链式结构 -- 链栈
栈只在栈顶做插入删除操作，链表需要头指针，不妨把栈顶放在单链表头部而非尾部
这样做，一般就不再需要头节点
对于链栈，一般不存在栈满的情况，除非内存没有可以使用的空间
对于空栈，链表原定义头指针指向空，则链栈的空为 top == NULL
定义链栈的结构
typedef struct StackNode
{
	SElemType data;
	struct StackNode *next;
}StackNode,*LinkStackPtr;

typedef struct LinkStack
{
	LinkStackPtr top;
	int count;
}LinkStack;
链栈的大部分操作同链表，只是插入和删除稍微特殊

进栈
//插入元素e为新的栈顶元素
Status Push(LinkStack *S, SElemType e)
{
	LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
	s->data = e;
	s->next = S->top;  //把当前的栈顶元素赋值给新结点的直接后继
	S->top = s;     //将新结点s变成栈顶指针
	
	S->count++;

	return OK;
}

出栈
//若栈不空，删除栈顶元素，用e返回其值
Status Pop(LinkStack *S, SElemType *e)
{
	LinkStackPtr p;
	if (StackEmpty(*S))
		return ERROR;

	*e = S->top->data;
	p = S->top;         //将栈顶结点赋给p
	S->top = S->top->next; //下移栈顶指针
	free(p);
	S->count--;

	return OK;
}


/*************************************************/
栈的应用--递归
例--斐波那契数列
递推式 f（n）= f（n-1）+ f（n-2）
常规迭代
int main()
{
	int i;
	int a[40];
	a[0] = 0;
	a[1] = 1;
	printf("%d ", a[0]);
	printf("%d ", a[1]);

	for (int i = 2; i < 40; i++)
	{
		a[i] = a[i - 1] + a[i - 2];
		printf("%d ", a[i]);
	}

	return 0;
}

递归实现
int Fbi(int i)
{
	if (i < 2)
		return i == 0 ? 0 : 1;

	return Fbi(i - 1) + Fbi(i - 2); //Fbi 自己调用自己
}

int main()
{
	int i;
	for (int i = 0; i < 40; i++)
		printf("%d ", Fbi(i));

	return 0;
}

递归定义
直接调用自己或通过一系列调用语句间接调用自己的函数称递归函数
每个递归定义必须至少有一个条件，满足时递归不再进行


栈的引用--四则运算表达式求值
1. 后缀（逆波兰）表示法定义
9 + （ 3 - 1 ）* 3 + 10 / 2  的后缀表示 9 3 1 - 3 * + 10 2 / +
叫后缀的原因是所有的符号都是在要运算的数字后面出现
2. 后缀表达式计算结果
后缀表达式 9 3 1 - 3 * +10 2 / +
规则：从左到右遍历表达式的每个数字和符号，遇到数字就进栈，遇到符号就将处于栈顶的两个元素出栈，
      进行运算，运算结果进栈，直到得到最终结果

中缀表达式转后缀表达式
平时使用的四则运算 9 + （ 3 - 1 ） * 3 + 10 / 2 叫中缀表达式
如何将中缀表达式转化为后缀表达式？
规则：从左到右遍历中缀表达式的每个数字和符号，数字就输出，即成为后缀表达式的一部分
符号则判断其与栈顶符号的优先级，是右括号或优先级低于栈顶符号（乘除优先加减）则栈顶元素依次出栈并输出，并将当前符号进栈
一直到最后输出后缀表达式为止









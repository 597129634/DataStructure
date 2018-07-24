//朴素的模式匹配算法
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define OK 1 
#define ERROR 0
#define MAXSIZE 100

typedef struct {
	char str[MAXSIZE];
	int sum;
}S;

int index(S *s, S *t);      //s 原串 ，t 子串 

int index(S *s, S *t)
{
	for (int i = 0; i<MAXSIZE&&s->str[i] != '\0'; i++)      //检索主串 
	{
		int temp = i;   //设置跟进的临时变量 
		int flag = 1;   //设置关于检索状态的状态变量 
		for (int j = 0; j<MAXSIZE&&t->str[j] != '\0'; j++)      //检索子串 
		{
			if (s->str[temp] == t->str[j])      //主串当前元素和子串一样，检索下一个元素 
				temp++;
			else   //不匹配结束当前循环，主串匹配位置下移一个 
			{
				flag = 0;
				break;

			}
		}

		if (flag == 1)    //找到位置 
			return i + 1;  //由于数组是从下标0开始，对应习惯，返回值加1
	}

	return ERROR;   //最后也未找到 
}

int main(void)
{
	freopen("r10.txt", "r", stdin);
	S *s = (S *)malloc(sizeof(S));
	S *t = (S *)malloc(sizeof(S));

	char i;
	int j = 0;
	while (scanf("%c", &i) == 1 && i != '\n')
	{
		s->str[j] = i;
		//j++;
		//printf("s->str[%d] = %c\n",j,s->str[j]);
		j++;
	}

	j = 0;
	while (scanf("%c", &i) != EOF)
	{
		t->str[j] = i;
		//printf("t->str[%d] = %c\n",j,t->str[j]);
		j++;
	}

	/*debug
	for(int i = 0;i<MAXSIZE&&s->str[i] != '\0';i++)
	printf("s->str[%d] = %c\n",i,s->str[i]);
	for(int i = 0;i<MAXSIZE&&t->str[i] != '\0';i++)
	printf("t->str[%d] = %c\n",i,t->str[i]);
	*/

	int flag = index(s, t);

	if (flag == ERROR)
	{
		printf("ERROR\n");
	}
	else
		printf("%d\n", flag);

	free(s);
	free(t);

	return 0;
}



/*************示例代码*****************/
/*返回子串T在主串S中第pos个字符之后的位置，若不存在，函数返回值为0*/
/*T非空，1 <= pos <= StrLength(S)*/
int index(String S, String T, int pos)
{
	int i = pos; //i 用于主串S中当前位置下标，若pos不为1，则从pos开始匹配
	int j = 1; //j 用于子串T中当前位置下标值
	while (i <= S[0] && j <= T[0]) //若 i 小于S长度且 j 小于 T的长度时循环
	{
		if (S[i] == T[j])  //两字母相同则继续
		{
			++i;
			++j;
		}
		else  //指针后退开始重新匹配
		{
			i = i - j + 2;  //i 退回上次匹配首位的下一位
			j = 1;  //j 退回到子串T的首位
		}
	}
	if (j > T[0])
		return i - T[0];
	else
		return 0;
}
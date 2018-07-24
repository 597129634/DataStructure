//KMP模式匹配算法
//1 计算next数组的值
//2 匹配
/***************范例代码*********************/
/*通过计算返回子串T的next数组*/
void get_next(String T, int *next)
{
	int i, j;
	i = 1;
	j = 0;
	next[1] = 0;   
	while (i < T[0])  //此处T[0]表示串T的长度
	{
		if (j == 0 || T[i] == T[j]) //T[i]表示后缀的单个字符
		{                           //T[j]表示前缀的单个字符
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];    //若字符不相同，则j值回溯
	}
}
//NOTE 前后缀一个字符相等，k = 2，两个 k = 3，n个 k = n+1

/*返回子串T在主串S中第pos个字符之后的位置，若不存在，则函数返回值为0*/
/*T非空，1<=pos<=StrLength(S)*/
int index_KMP(String S, String T, int pos)
{
	int i = pos; //i 用于主串S当前位置下标值，若pos不为1，则从pos位置开始匹配
	int j = 1; //j 用于子串T中当前位置下标值
	int next[255]; //定义 next数组
	get_next(T, next); //对串T分析，得到next数组
	while (i <= S[0] && j <= T[0]) //若i小于S的长度且j小于T的长度时
	{
		if (j == 0 || S[i] == T[j]) //两字母相等则继续，与朴素算法增加了 j = 0 判断
		{
			++i;
			++j;
		}
		else
		{
			j = next[j];  //指针退回合适位置，i值不变
		}
	}
	if (j > T[0])
		return i - T[0];
	else
		return 0;
}



/*************示例代码*****************/
/*返回子串T在主串S中第pos个字符之后的位置，若不存在，函数返回值为0*/
/*T非空，1 <= pos <= StrLength(S)*/
int index(String S, String T, int pos) //朴素匹配
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




//改进KMP算法
void get_nextval(String T, int *nextval)
{
	int i, j;
	i = 1;
	j = 0;
	nextval[1] = 0;
	while (i < T[0])
	{
		if (j == 0 || T[i] == T[j])
		{
			++i;
			++j;
			if (T[i] != T[j])       //若当前字符与前缀字符不同，则当前j为nextval在i位置的值
				nextval[i] = j;
			else
				nextval[i] = nextval[j]; //若与前缀字符相同，则将前缀字符的nextval值赋值给nextval在i位置的值
		}
		else
			j = nextval[j];
	}
}


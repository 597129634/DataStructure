第六章 树
树是n个结点的有限集，n = 0 时称为空树，在任意一颗非空树中
1 有且仅有一个特定的称为根的结点
2 当 n > 1 时，其余结点可分为m个互不相交的有限集 T1, T2, ...Tm，其中每一个集合本身又是一颗树，并且称为根的子树
根 Root
树 Tree
子树 SubTree
NOTE1 n > 0 时结点的唯一的，不可能存在多个根结点
NOTE2 m > 0 时，子树的个数没有限制，但它们一定是互不相交的

结点分类
树的结点包含一个数据元素及若干指向其子树的分支
结点拥有的子树数称为结点的度(Degree)
度为 0 的结点称叶节点（Leaf）或终端节点
度不为 0 的结点称为非终端节点或分支节点
除根结点外，分支节点也称内部结点
树的度是树内个结点的度的最大值

结点间关系
结点的子树的根称为该结点的孩子（Child）, 相应地，该结点称为孩子的双亲（Parent）
同一个双亲的孩子之间互称兄弟（Sibling）
结点的祖先是从根到该节点所经分支上的所有结点，以某结点为根的子树中的任一结点都称为该节点的子孙

其他相关概念
结点的层次（Level）从根开始定义起，根为第一层，根的孩子为第二层
双亲在同一层的结点互为堂兄弟
树中结点的最大层次称为树的深度（Depth）或高度
如果将树种结点的各子树看成从左至右是有次序的，不能互换的，称该树为有序树，否则称为无序树
森林（Forest）是 m 棵互不相交的树的集合

树的存储结构
1 双亲表示法
假设以一组连续空间存储树的结点，同时在每个结点中附设一个指示器指示其双亲结点到链表中的位置
/*树的双亲表示法结点结构定义*/
#define MAX_TREE_SIZE 100
typedef int TElemType;    //树结点的数据类型
typedef struct PTNode {     //结点结构
	TElemType data;         //节点数据
	int parent;             //双亲位置
}PTNode;
typedef struct {         //树结构
	PTNode nodes[MAX_TREE_SIZE];   //结点数组
	int r, n;    //根位置和结点数
}PTree;
由于根结点无双亲，约定根结点位置域设为 -1


2 孩子表示法
由于树中每个结点可能有多棵子树，可以考虑使用多重链表
每个结点有多个指针域，其中每个指针指向一棵子树的根结点，称多重链表表示法
方案一 指针域的个数等于树的度
方案二 每个结点指针域的个数等于该结点的度，专门取一个位置来存储结点指针域的个数
/*孩子表示法结构定义*/
#define MAX_TREE_SIZE 100
typedef struct CTNode {       //孩子结点
	int child;
	struct CTNode *next;
}*ChildPtr;
typedef struct {   //表头结构
	TElemType data;
	ChildPtr firstchild;
}CTBox;
typedef struct {
	CTBox nodes[MAX_TREE_SIZE];  //结点数组
	int r, n;    //根的位置和结点数
}CTree;
/*可能有误
NOTE 在表头中插入指示双亲位置的变量可以在遍历时知道某个结点的双亲，如
typedef struct {   //表头结构
	TElemType data;
	ChildPtr firstchild;
	int parent;
}CTBox;
*/


3 孩子兄弟表示法
任意一棵树，他结点的第一个孩子如果存在就是唯一的，它的右兄弟如果存在也是唯一的，
可以设置两个指针分别指向该结点的第一个孩子和此结点的右兄弟
/*孩子兄弟表示法结构定义*/
typedef struct CSNode {
	TElemType data;
	struct CSNode *firstchild, *rightsib;
}CSNode,*CSTree;
//该表示法把一个树转化成了二叉树，方便遍历
//可以用此结构方便地查找某结点的孩子，如果要查找双亲，可以增加一个parent指针域来实现



二叉树

二叉树定义
二叉树（Binary Tree）是 n 个结点的有限集合，该集合或者为空集称空二叉树，或者由一个根结点和两棵互不相交的，分别称
为根结点的左子树和右子树的二叉树组成

二叉树特点
1 每个结点最多有两棵子树，即没有度大于 2 的结点
2 左右子树是有顺序的，不能任意颠倒
3 即使树中某结点只有一棵子树，也要区分是左还是右子树

二叉树有 5 种基本形态
1 空二叉树
2 只有一个根结点
3 根结点只有左子树
4 根结点只有右子树
5 根结点既有左子树又有右子树

特殊二叉树
1 斜树
所有结点都只有左子树的二叉树叫左斜树，所有结点都是只有右子树的二叉树叫右斜树

2 满二叉树
在一颗二叉树中，所有分支节点都存在左右子树，并且所有叶子都在同一层上称满二叉树
NOTE 在同样深度的二叉树中，满二叉树的结点数最多，叶子数最多

3 完全二叉树
对一颗具有 n 个结点的二叉树按层序编号，如果编号为 i (1<=i<=n) 的结点域同样深度的满二叉树中编号为 i 的结点在二叉树中的位置
完全相同，则称为完全二叉树
NOTE 满二叉树一定是完全二叉树，完全二叉树未必满
完全二叉树的特点
1 叶子结点只能出现在最下面两层
2 最下层叶子一定集中在左部且连续
3 倒数二层若有叶子结点，一定在右部连续位置
4 若结点度为 1 则该结点只有左孩子，不存在只有右子树的情况
5 同样结点数的二叉树，完全二叉树的深度最小

二叉树的数学性质

二叉树的存储结构
1 顺序存储结构
用一维数组来表示，一般只用于完全二叉树

2 二叉链表
二叉树每个结点最多有两个孩子，设计一个数据域两个指针域
有 n 个结点的二叉链表有 n+1 个空链域
/*结构定义*/
typedef struct BiNode {
	TElemType data;
	struct BiNode *lchild, *rchild;  //左右孩子指针
}BiTNode,*BiTree;

遍历二叉树
二叉树的遍历是指从根结点出发，按照某种次序依次访问二叉树中所有结点，使得每个结点被且仅被访问一次
主要有 4 种方法 前序，中序，后序，层序
1 前序遍历
void PreOrderTraverse(BiTree T)
{
	if (T == NULL)
		return;
	printf("%c", T->data);        //显示结点数据，可以更改为对其他结点操作
	PreOrderTraverse(T->lchild);  //先遍历左子树
	PreOrderTraverse(T->rchild);  //后遍历右子树
}

2 中序遍历
void InOrderTraverse(BiTree T)
{
	if (T == NULL)
		return;
	InOrderTraverse(T->lchild);  //中序遍历左子树
	printf("%c", T->data);       //显示结点数据，可以更改为对其他结点操作
	InOrderTraverse(T->rchild);  //后遍历右子树
}

3 后序遍历
void PostOrderTraverse(BiTree T)
{
	if (T == NULL)
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c", T->data);
}

二叉树的建立
/*按前序输入二叉树中结点的值（一个字符）*/
/* # 表示空树，构造二叉链表表示二叉树 T */
void CreatBiTree(BiTree *T)   //创建时使用二维指针
{
	TElemType ch;
	scanf("%c", &ch);
	if (ch == '#')
		*T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		if (!*T)
			exit(0);
		(*T)->data = ch;
		CreatBiTree(&(*T)->lchild);  //构造左子树
		CreatBiTree(&(*T)->rchild);  //构造右子树
	}
}

BiTree creatTree(void)
{
	BiTree T;
	TElemType ch;
	scanf("%c", &ch);
	
	if (ch == '#')
		T == NULL;
	else
	{
		T = (BiTree)malloc(sizeof(BiTNode));
		if (!T)
			exit(0);
		T->data = ch;
		T->lchild = creatTree();
		T->rchild = creatTree();
	}

	return T;
}


线索二叉树
在二叉链表的基础上，将其空指针域改为指向前驱和后继的指针，该种指针称为线索，相应的二叉树称为线索二叉树
为了区分lchild 和 rchild 是指向孩子还是前后驱，需要增设一个区分标志
在每个结点增设两个标志域ltag和rtag，ltag 和 rtag 只存放 0 或 1
区别如
ltag 为 0 时指向左孩子，为 1 时指向前驱，rtag类似
/*结构定义*/
typedef enum {   //Link == 0 表示指向左右孩子指针
	Link,Thread  //Thread == 1 表示指向前驱或后继的线索
}PointerTag;

typedef struct BiThrNode {      //二叉线索存储结构结点
	TElemType data;   //数据
	struct BiThrNode *lchild, *rchild;  //左右孩子指针
	PointerTag LTag, RTag;   //左右标志
}BiThrNode,*BiThrTree;

//中序遍历线索化递归函数代码
//NOTE 所谓线索化就是在遍历过程中修改空指针
BiThrTree pre; //全局变量，始终指向刚刚访问过的结点
void InThreading(BiThrTree p)
{
	if (p)
	{
		InThreading(p->lchild);
		if (!p->lchild)
		{
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!pre->rchild)
		{
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;
		InThreading(p->rchild);
	}
}
/*遍历代码*/
/*T指向头结点，头结点左链lchild指向根结点，头结点右链rchild指向中序遍历的最后一个结点*/
/*中序遍历线索二叉树*/
Status InOrderTraverse_Thr(BiThrTree T)
{
	BiThrTree p;
	p = T->lchild;   //p 指向根结点
	while (p != T)   //空树或遍历结束时，p==T
	{
		while (p->LTag == Link) //当LTag==0时循环到中序序列第一个结点
			p = p->lchild;
		printf("%c", p->data);    //显示结点数据，可以更改为其他对结点操作
		while (p->RTag == Thread&&p->rchild != T)
		{
			p = p->rchild;
			printf("%c", p->data);
		}
		p = p->rchild; //p进至右子树根
	}

	return OK;
}

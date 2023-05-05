#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:6031)
#include<iostream>
using namespace std;
#include<stdio.h>
#define  OK 1
#define Error 0
#define OVERFLOW -2 
typedef int Status;


typedef struct OLNode 
{
	int i, j;//非零元素的行、列下标
	int e;//非零元素的值
	struct OLNode* right, * down;//分别指向同行和同列下一个非零结点的指针
}OLNode, * OLink;//矩阵中非零结点结构和结构体指针

typedef struct 
{
	OLink* rhead, * chead;//行、列头指针链
	int nr, nc, ne;//（number of row/column/elem）
}Crosslist;//稀疏矩阵的十字链表储存结构（以两个链表来表示矩阵）

Status Initsmatrix(Crosslist* M) 
{
	(*M).rhead = (*M).chead = NULL;
	(*M).nr = (*M).nc = (*M).ne = 0;
	return OK;
}//初始化稀疏矩阵

Status Createsmatrix(Crosslist* M) 
{
	int i, j, k, m, n, t;
	int e;
	OLNode* p, * q;
	cout << "请输入稀疏矩阵的行数、列数、非零元素个数：" << endl;
	cin >> m >> n >> t;
	(*M).nr = m;
	(*M).nc = n;
	(*M).ne = t;
	(*M).rhead = new OLink[m + 1];
	if (!(*M).rhead)
		exit(OVERFLOW);//为行指针链分配空间(第0个位置不用，所以空间为行数+1）
	(*M).chead = new OLink[n + 1];
	if (!(*M).chead)
		exit(OVERFLOW);//为列指针链分配空间(第0个位置不用，所以空间为列数+1）
	for (k = 1; k <= m; k++)
		(*M).rhead[k] = NULL;//将所有行头指针置空
	for (k = 1; k <= n; k++)
		(*M).chead[k] = NULL;//将所有列头指针置空
	cout << "请输入各个非零元素所在行、列及其值：" << endl;

	for (k = 0; k < t; k++) 
	{
		cin >> i >> j >> e;
		while (i > m || j > n) 
		{
			cout << "输入位置错误，请重新输入该元素的情况" << endl;
			cin >> i >> j >> e;
		}
		p = new OLNode;
		if (!p)exit(OVERFLOW);//为每个矩阵元素结点申请空间
		p->i = i;
		p->j = j;
		p->e = e;//为结点赋值（行、列位置和元素值）
		if (!(*M).rhead[i] || (*M).rhead[i]->j > j) 
		{
			p->right = (*M).rhead[i];
			(*M).rhead[i] = p;
		}//p插在该行的第一个结点处
		//当插入时，第i行无非零元素，则(*M).rhead[i] == NULL，此时为将p->right置空，让(*M).rhead[i]指向p。即p为第i行第一个元素
		//当插入时，第i行已有元素，则需要对比将插入元素和已有的第一个元素所处列位置，若插入元素列在原有元素列之前，则需要对指针进行改变，插入到头指针和该元素结点之间
		else 
		{
			for (q = (*M).rhead[i]; q->right && q->right->j < j; q = q->right);
			p->right = q->right;
			q->right = p;
		}//寻找行表中的位置并插入
		//若插入时该行已有多个元素，则需要一个个对比跟将插入元素的列值大小，直到找到合适的列位置（列大小位于某两个元素之间，或者放到该行最后一个位置）
		if (!(*M).chead[j] || (*M).chead[j]->i > i) 
		{
			p->down = (*M).chead[j];
			(*M).chead[j] = p;
		}//p插在该列的第一个结点处
		//当插入时，第j列无非零元素，则(*M).chead[j] == NULL，此时为将p->right置空，让(*M).chead[j]指向p。即p为第j列第一个元素
		//当插入时，第j列已有元素，则需要对比将插入元素和已有的第一个元素所处行位置，若插入元素列在原有元素行之前，则需要对指针进行改变，插入到头指针和该元素结点之间
		else 
		{
			for (q = (*M).chead[j]; q->down && q->down->i < i; q = q->down);
			p->down = q->down;
			q->down = q;
		}//寻找列表中的位置并插入
		//若插入时该列已有多个元素，则需要一个个对比跟将插入元素的行值大小，直到找到合适的行位置（行大小位于某两个元素之间，或者放到该列最后一个位置）
	}
	return OK;
}//创建稀疏矩阵

Status Destroysmatrix(Crosslist* M)
{
	int i;
	OLNode* p, * q;
	for (i = 1; i <= (*M).nr; i++)
	{
		p = *((*M).rhead + i);
		while (p)
		{
			q = p;
			p = p->right;
			delete q;
		}
	}//按行对每一个头指针后的第一个元素开始，一个个往后删除
	delete (*M).rhead;
	delete (*M).chead;//删除两个指针链表
	(*M).rhead = NULL;
	(*M).chead = NULL;
	return OK;
}//销毁存在的矩阵

void Printsmatrix(Crosslist M) 
{
	int i, j;
	for (i = 1; i <= M.nr; i++) 
	{
		if (!M.rhead[i]) 
		{
			for (j = 1; j <= M.nc; j++) 
			{
				cout << "0 ";
			}
			cout << endl;//如果该行没有非零元素，则该行的每一列都输出0
		}
		else
		{
			int n = 1;
			OLink p = M.rhead[i];
			while (n <= M.nc) 
			{
				if (!p || (n < p->j)) 
				{
					cout << "0 ";
				}//在找到非零元素前，为判断条件(n < p->j)；后面的0元素判断输出条件为!p
				else
				{
					cout << p->e << " ";
					p = p->right;//输出了一个非零元素，p指向该行的后一个元素
				}
				n++;
			}
			cout << endl;//如果该行有元素，则一个个往后输出，
		}
	}
	cout << endl;
}//输出矩阵

Status Addsmatrix(Crosslist M, Crosslist N, Crosslist* Q)
{
	int i = 1, k = 1;
	OLink p, pq = NULL, pm, pn;
	OLink* col;
	if (M.nr != N.nr || M.nc != N.nc)
	{
		cout << "两个矩阵是不同类型的,无法相加（同类型矩阵行列相等），若要再次运行矩阵相加请重新打开程序" << endl;
		exit(OVERFLOW);
	}
	(*Q).nr = M.nr;
	(*Q).nc = M.nc;//初始化矩阵Q（用于储存矩阵M+N的结果）
	(*Q).ne = 0; //Q矩阵开始是没有元素的
	(*Q).rhead = new OLink[(*Q).nr + 1];
	if (!(*Q).rhead)
		exit(OVERFLOW);
	(*Q).chead = new OLink[(*Q).nc + 1];
	if (!(*Q).chead)
		exit(OVERFLOW);//为Q的两个链表分配空间
	for (k = 1; k <= (*Q).nr; k++)
		(*Q).rhead[k] = NULL;
	for (k = 1; k <= (*Q).nc; k++)
		(*Q).chead[k] = NULL;//对Q的两条链内全部指针置空
	col = new OLink[(*Q).nc + 1];
	if (!col)
		exit(OVERFLOW);/* 生成指向列的最后结点的数组 */
	for (k = 1; k <= (*Q).nc; k++)
		col[k] = NULL;//对col链表各内容置空

	/*-------------------------------------------以下为得到到Q矩阵中的元素定值（来自M和N的结果）-------------------------------------------*/

	for (i = 1; i <= M.nr; i++) // 按行的顺序相加 
	{
		pm = M.rhead[i]; // pm指向矩阵M的第i行的第1个结点 
		pn = N.rhead[i]; // pn指向矩阵N的第i行的第1个结点 
		while (pm && pn) // pm和pn均不空 
		{
			if (pm->j < pn->j) //矩阵M当前结点的列小于矩阵N当前结点的列 
			{
				p = new OLNode;
				if (!p)
					exit(OVERFLOW); // 生成矩阵Q的元素结点 
				(*Q).ne++; //Q矩阵内的非零元素数量+1
				p->i = i;
				p->j = pm->j;
				p->e = pm->e; //给结点赋值 
				p->right = NULL;
				pm = pm->right; // pm指针向右移,找M矩阵该行的下一个元素
			}
			else if (pm->j > pn->j) //矩阵M当前结点的列大于矩阵N当前结点的列 
			{
				p = new OLNode;
				if (!p)
					exit(OVERFLOW);  // 生成矩阵Q的元素结点 
				(*Q).ne++;//Q矩阵内的非零元素数量+1
				p->i = i;
				p->j = pn->j;
				p->e = pn->e;//给结点赋值 
				p->right = NULL;
				pn = pn->right; // pn指针向右移,找N矩阵该行的下一个元素
			}
			else if ((pm->e + pn->e) != 0) // 矩阵M、N当前结点的列相等且两元素之和不为0
			{
				p = new OLNode;
				if (!p)
					exit(OVERFLOW);  // 生成矩阵Q的元素结点 
				(*Q).ne++;//Q矩阵内的非零元素数量+1
				p->i = i;
				p->j = pn->j;
				p->e = pm->e + pn->e;//给结点赋值 
				p->right = NULL;
				pm = pm->right; // pm指针向右移,找M矩阵该行的下一个元素
				pn = pn->right; // pn指针向右移, 找N矩阵该行的下一个元素
			}
			else // 矩阵M、N当前结点的列相等且两元素之和为0
			{
				pm = pm->right;// pm指针向右移,找M矩阵该行的下一个元素
				pn = pn->right;// pn指针向右移, 找N矩阵该行的下一个元素
				continue;
			}

			/*-----------------------------------------------以下为对元素结点插入到矩阵Q中----------------------------------------------*/

			if (!(*Q).rhead[i]) // p为Q矩阵该行的第1个结点
			{
				(*Q).rhead[i] = p;
				pq = p;
			}// p插在该行的第一列位置(p插入后p成为该行的最后一个结点，pq标记的最后一个元素变为p)
			else // 插入时已有元素，则插在pq所指结点之后
			{
				pq->right = p; //pq的后一项指向要插入的p（上面是由前向后一个个读取的，所以要插入的一定在已插入的之后）
				pq = p; // 插入后最后一个结点改变，pq指向该行插入后的最后一个结点p
			}
			if (!(*Q).chead[p->j]) // p为Q矩阵该列的第1个结点(原本在的p->j列值为空）
			{
				(*Q).chead[p->j] = p;//将p插入到原本为空的p->j列处
				col[p->j] = p;
			}// p插在该列表头，插入后p->j列的最后一个元素由NULL变为p
			else // 插入时已有元素，则插在col[p->j]所指结点之后
			{
				col[p->j]->down = p; //col[p->j]的后一项指向要插入的p
				col[p->j] = col[p->j]->down; // 插入后最后一个结点改变，col[p->j]指向该列的最后一个结点p
			}
		}

		/*------------------------------------当一个矩阵的非零值已经放入完，则直接插入另一个矩阵所有元素------------------------------------*/

		while (pm) //N矩阵的所有非零元素皆已经插入，上方pn条件不成立，则将矩阵M该行的剩余元素插入矩阵Q
		{
			p = new OLNode;  // 生成矩阵Q的元素结点 
			if (!p)
				exit(OVERFLOW);
			(*Q).ne++; //Q矩阵内的非零元素数量+1
			p->i = i;
			p->j = pm->j;
			p->e = pm->e; // 给结点赋值
			p->right = NULL;
			pm = pm->right; // pm指针向右移,找M矩阵该行的下一个元素
			if (!(*Q).rhead[i])  // p为Q矩阵该行的第1个结点
			{
				(*Q).rhead[i] = p;
				pq = p;
			}// p插在该行的第一列位置(p插入后p成为该行的最后一个结点，pq标记的最后一个元素变为p)
			else // 插入时已有元素，则插在pq所指结点之后
			{
				pq->right = p; //pq的后一项指向要插入的p（上面是由前向后一个个读取的，所以要插入的一定在已插入的之后）
				pq = p; // 插入后最后一个结点改变，pq指向该行插入后的最后一个结点p
			}
			if (!(*Q).chead[p->j]) // p为Q矩阵该列的第1个结点(原本在的p->j列值为空）
			{
				(*Q).chead[p->j] = p;//将p插入到原本为空的p->j列处
				col[p->j] = p;
			}// p插在该列表头，插入后p->j列的最后一个元素由NULL变为p
			else // 插入时已有元素，则插在col[p->j]所指结点之后
			{
				col[p->j]->down = p; //col[p->j]的后一项指向要插入的p
				col[p->j] = col[p->j]->down; // 插入后最后一个结点改变，col[p->j]指向该列的最后一个结点p
			}
		}
		while (pn) //M矩阵的所有非零元素皆已经插入，上方pm条件不成立，则将矩阵N该行的剩余元素插入矩阵Q
		{
			p = new OLNode; // 生成矩阵Q的元素结点 
			if (!p)
				exit(OVERFLOW);
			(*Q).ne++; //Q矩阵内的非零元素数量+1
			p->i = i;
			p->j = pn->j;
			p->e = pn->e; // 给结点赋值
			p->right = NULL;
			pn = pn->right;  // pn指针向右移,找N矩阵该行的下一个元素
			if (!(*Q).rhead[i])  // p为Q矩阵该行的第1个结点
			{
				(*Q).rhead[i] = p;
				pq = p;
			}// p插在该行的第一列位置(p插入后p成为该行的最后一个结点，pq标记的最后一个元素变为p)
			else  // 插入时已有元素，则插在pq所指结点之后
			{
				pq->right = p; //pq的后一项指向要插入的p（上面是由前向后一个个读取的，所以要插入的一定在已插入的之后）
				pq = p; // 插入后最后一个结点改变，pq指向该行插入后的最后一个结点p
			}
			if (!(*Q).chead[p->j]) // p为Q矩阵该列的第1个结点(原本在的p->j列值为空）
			{
				(*Q).chead[p->j] = p;//将p插入到原本为空的p->j列处
				col[p->j] = p;
			}// p插在该列表头，插入后p->j列的最后一个元素由NULL变为p
			else // 插入时已有元素，则插在col[p->j]所指结点之后
			{
				col[p->j]->down = p; //col[p->j]的后一项指向要插入的p
				col[p->j] = col[p->j]->down; // 插入后最后一个结点改变，col[p->j]指向该列的最后一个结点p
			}
		}
	}
	for (k = 1; k <= (*Q).nc; k++)
		if (col[k]) // k列有元素结点
			col[k]->down = NULL; //  令该列最后一个结点的down指针为空 
	delete[]col;
	return OK;
}//矩阵相加

int main() {
	int a = 1; int flag = 0;
	do 
	{
		if (a == 1) 
		{
			Crosslist A, B, C;
			Initsmatrix(&A);
			Initsmatrix(&B);
			cout << "请输入第一个矩阵的情况----------" << endl;
			Createsmatrix(&A);
			cout << "请输入第二个矩阵的情况----------" << endl;
			Createsmatrix(&B);
			Addsmatrix(A, B, &C);
			cout << endl << "两矩阵相加后所得结果如下：" << endl;
			Printsmatrix(C);
			cout << "请选择接下来的操作：" << endl;
			cout << "输入0：结束程序" << endl;
			cout << "输入1：重新执行此程序" << endl;
			Destroysmatrix(&A);
			Destroysmatrix(&B);
			Destroysmatrix(&C);
		}
		cin >> a;
		if (a == 0) 
		{
			flag = 1;
			cout << "程序结束，生活愉快下次再来~" << endl;
		}
	} while (a && flag == 0);
	return 0;
}
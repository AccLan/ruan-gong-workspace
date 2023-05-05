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
	int i, j;//����Ԫ�ص��С����±�
	int e;//����Ԫ�ص�ֵ
	struct OLNode* right, * down;//�ֱ�ָ��ͬ�к�ͬ����һ���������ָ��
}OLNode, * OLink;//�����з�����ṹ�ͽṹ��ָ��

typedef struct 
{
	OLink* rhead, * chead;//�С���ͷָ����
	int nr, nc, ne;//��number of row/column/elem��
}Crosslist;//ϡ������ʮ��������ṹ����������������ʾ����

Status Initsmatrix(Crosslist* M) 
{
	(*M).rhead = (*M).chead = NULL;
	(*M).nr = (*M).nc = (*M).ne = 0;
	return OK;
}//��ʼ��ϡ�����

Status Createsmatrix(Crosslist* M) 
{
	int i, j, k, m, n, t;
	int e;
	OLNode* p, * q;
	cout << "������ϡ����������������������Ԫ�ظ�����" << endl;
	cin >> m >> n >> t;
	(*M).nr = m;
	(*M).nc = n;
	(*M).ne = t;
	(*M).rhead = new OLink[m + 1];
	if (!(*M).rhead)
		exit(OVERFLOW);//Ϊ��ָ��������ռ�(��0��λ�ò��ã����Կռ�Ϊ����+1��
	(*M).chead = new OLink[n + 1];
	if (!(*M).chead)
		exit(OVERFLOW);//Ϊ��ָ��������ռ�(��0��λ�ò��ã����Կռ�Ϊ����+1��
	for (k = 1; k <= m; k++)
		(*M).rhead[k] = NULL;//��������ͷָ���ÿ�
	for (k = 1; k <= n; k++)
		(*M).chead[k] = NULL;//��������ͷָ���ÿ�
	cout << "�������������Ԫ�������С��м���ֵ��" << endl;

	for (k = 0; k < t; k++) 
	{
		cin >> i >> j >> e;
		while (i > m || j > n) 
		{
			cout << "����λ�ô��������������Ԫ�ص����" << endl;
			cin >> i >> j >> e;
		}
		p = new OLNode;
		if (!p)exit(OVERFLOW);//Ϊÿ������Ԫ�ؽ������ռ�
		p->i = i;
		p->j = j;
		p->e = e;//Ϊ��㸳ֵ���С���λ�ú�Ԫ��ֵ��
		if (!(*M).rhead[i] || (*M).rhead[i]->j > j) 
		{
			p->right = (*M).rhead[i];
			(*M).rhead[i] = p;
		}//p���ڸ��еĵ�һ����㴦
		//������ʱ����i���޷���Ԫ�أ���(*M).rhead[i] == NULL����ʱΪ��p->right�ÿգ���(*M).rhead[i]ָ��p����pΪ��i�е�һ��Ԫ��
		//������ʱ����i������Ԫ�أ�����Ҫ�ԱȽ�����Ԫ�غ����еĵ�һ��Ԫ��������λ�ã�������Ԫ������ԭ��Ԫ����֮ǰ������Ҫ��ָ����иı䣬���뵽ͷָ��͸�Ԫ�ؽ��֮��
		else 
		{
			for (q = (*M).rhead[i]; q->right && q->right->j < j; q = q->right);
			p->right = q->right;
			q->right = p;
		}//Ѱ���б��е�λ�ò�����
		//������ʱ�������ж��Ԫ�أ�����Ҫһ�����Աȸ�������Ԫ�ص���ֵ��С��ֱ���ҵ����ʵ���λ�ã��д�Сλ��ĳ����Ԫ��֮�䣬���߷ŵ��������һ��λ�ã�
		if (!(*M).chead[j] || (*M).chead[j]->i > i) 
		{
			p->down = (*M).chead[j];
			(*M).chead[j] = p;
		}//p���ڸ��еĵ�һ����㴦
		//������ʱ����j���޷���Ԫ�أ���(*M).chead[j] == NULL����ʱΪ��p->right�ÿգ���(*M).chead[j]ָ��p����pΪ��j�е�һ��Ԫ��
		//������ʱ����j������Ԫ�أ�����Ҫ�ԱȽ�����Ԫ�غ����еĵ�һ��Ԫ��������λ�ã�������Ԫ������ԭ��Ԫ����֮ǰ������Ҫ��ָ����иı䣬���뵽ͷָ��͸�Ԫ�ؽ��֮��
		else 
		{
			for (q = (*M).chead[j]; q->down && q->down->i < i; q = q->down);
			p->down = q->down;
			q->down = q;
		}//Ѱ���б��е�λ�ò�����
		//������ʱ�������ж��Ԫ�أ�����Ҫһ�����Աȸ�������Ԫ�ص���ֵ��С��ֱ���ҵ����ʵ���λ�ã��д�Сλ��ĳ����Ԫ��֮�䣬���߷ŵ��������һ��λ�ã�
	}
	return OK;
}//����ϡ�����

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
	}//���ж�ÿһ��ͷָ���ĵ�һ��Ԫ�ؿ�ʼ��һ��������ɾ��
	delete (*M).rhead;
	delete (*M).chead;//ɾ������ָ������
	(*M).rhead = NULL;
	(*M).chead = NULL;
	return OK;
}//���ٴ��ڵľ���

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
			cout << endl;//�������û�з���Ԫ�أ�����е�ÿһ�ж����0
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
				}//���ҵ�����Ԫ��ǰ��Ϊ�ж�����(n < p->j)�������0Ԫ���ж��������Ϊ!p
				else
				{
					cout << p->e << " ";
					p = p->right;//�����һ������Ԫ�أ�pָ����еĺ�һ��Ԫ��
				}
				n++;
			}
			cout << endl;//���������Ԫ�أ���һ�������������
		}
	}
	cout << endl;
}//�������

Status Addsmatrix(Crosslist M, Crosslist N, Crosslist* Q)
{
	int i = 1, k = 1;
	OLink p, pq = NULL, pm, pn;
	OLink* col;
	if (M.nr != N.nr || M.nc != N.nc)
	{
		cout << "���������ǲ�ͬ���͵�,�޷���ӣ�ͬ���;���������ȣ�����Ҫ�ٴ����о�����������´򿪳���" << endl;
		exit(OVERFLOW);
	}
	(*Q).nr = M.nr;
	(*Q).nc = M.nc;//��ʼ������Q�����ڴ������M+N�Ľ����
	(*Q).ne = 0; //Q����ʼ��û��Ԫ�ص�
	(*Q).rhead = new OLink[(*Q).nr + 1];
	if (!(*Q).rhead)
		exit(OVERFLOW);
	(*Q).chead = new OLink[(*Q).nc + 1];
	if (!(*Q).chead)
		exit(OVERFLOW);//ΪQ�������������ռ�
	for (k = 1; k <= (*Q).nr; k++)
		(*Q).rhead[k] = NULL;
	for (k = 1; k <= (*Q).nc; k++)
		(*Q).chead[k] = NULL;//��Q����������ȫ��ָ���ÿ�
	col = new OLink[(*Q).nc + 1];
	if (!col)
		exit(OVERFLOW);/* ����ָ���е����������� */
	for (k = 1; k <= (*Q).nc; k++)
		col[k] = NULL;//��col����������ÿ�

	/*-------------------------------------------����Ϊ�õ���Q�����е�Ԫ�ض�ֵ������M��N�Ľ����-------------------------------------------*/

	for (i = 1; i <= M.nr; i++) // ���е�˳����� 
	{
		pm = M.rhead[i]; // pmָ�����M�ĵ�i�еĵ�1����� 
		pn = N.rhead[i]; // pnָ�����N�ĵ�i�еĵ�1����� 
		while (pm && pn) // pm��pn������ 
		{
			if (pm->j < pn->j) //����M��ǰ������С�ھ���N��ǰ������ 
			{
				p = new OLNode;
				if (!p)
					exit(OVERFLOW); // ���ɾ���Q��Ԫ�ؽ�� 
				(*Q).ne++; //Q�����ڵķ���Ԫ������+1
				p->i = i;
				p->j = pm->j;
				p->e = pm->e; //����㸳ֵ 
				p->right = NULL;
				pm = pm->right; // pmָ��������,��M������е���һ��Ԫ��
			}
			else if (pm->j > pn->j) //����M��ǰ�����д��ھ���N��ǰ������ 
			{
				p = new OLNode;
				if (!p)
					exit(OVERFLOW);  // ���ɾ���Q��Ԫ�ؽ�� 
				(*Q).ne++;//Q�����ڵķ���Ԫ������+1
				p->i = i;
				p->j = pn->j;
				p->e = pn->e;//����㸳ֵ 
				p->right = NULL;
				pn = pn->right; // pnָ��������,��N������е���һ��Ԫ��
			}
			else if ((pm->e + pn->e) != 0) // ����M��N��ǰ�������������Ԫ��֮�Ͳ�Ϊ0
			{
				p = new OLNode;
				if (!p)
					exit(OVERFLOW);  // ���ɾ���Q��Ԫ�ؽ�� 
				(*Q).ne++;//Q�����ڵķ���Ԫ������+1
				p->i = i;
				p->j = pn->j;
				p->e = pm->e + pn->e;//����㸳ֵ 
				p->right = NULL;
				pm = pm->right; // pmָ��������,��M������е���һ��Ԫ��
				pn = pn->right; // pnָ��������, ��N������е���һ��Ԫ��
			}
			else // ����M��N��ǰ�������������Ԫ��֮��Ϊ0
			{
				pm = pm->right;// pmָ��������,��M������е���һ��Ԫ��
				pn = pn->right;// pnָ��������, ��N������е���һ��Ԫ��
				continue;
			}

			/*-----------------------------------------------����Ϊ��Ԫ�ؽ����뵽����Q��----------------------------------------------*/

			if (!(*Q).rhead[i]) // pΪQ������еĵ�1�����
			{
				(*Q).rhead[i] = p;
				pq = p;
			}// p���ڸ��еĵ�һ��λ��(p�����p��Ϊ���е����һ����㣬pq��ǵ����һ��Ԫ�ر�Ϊp)
			else // ����ʱ����Ԫ�أ������pq��ָ���֮��
			{
				pq->right = p; //pq�ĺ�һ��ָ��Ҫ�����p����������ǰ���һ������ȡ�ģ�����Ҫ�����һ�����Ѳ����֮��
				pq = p; // ��������һ�����ı䣬pqָ����в��������һ�����p
			}
			if (!(*Q).chead[p->j]) // pΪQ������еĵ�1�����(ԭ���ڵ�p->j��ֵΪ�գ�
			{
				(*Q).chead[p->j] = p;//��p���뵽ԭ��Ϊ�յ�p->j�д�
				col[p->j] = p;
			}// p���ڸ��б�ͷ�������p->j�е����һ��Ԫ����NULL��Ϊp
			else // ����ʱ����Ԫ�أ������col[p->j]��ָ���֮��
			{
				col[p->j]->down = p; //col[p->j]�ĺ�һ��ָ��Ҫ�����p
				col[p->j] = col[p->j]->down; // ��������һ�����ı䣬col[p->j]ָ����е����һ�����p
			}
		}

		/*------------------------------------��һ������ķ���ֵ�Ѿ������꣬��ֱ�Ӳ�����һ����������Ԫ��------------------------------------*/

		while (pm) //N��������з���Ԫ�ؽ��Ѿ����룬�Ϸ�pn�������������򽫾���M���е�ʣ��Ԫ�ز������Q
		{
			p = new OLNode;  // ���ɾ���Q��Ԫ�ؽ�� 
			if (!p)
				exit(OVERFLOW);
			(*Q).ne++; //Q�����ڵķ���Ԫ������+1
			p->i = i;
			p->j = pm->j;
			p->e = pm->e; // ����㸳ֵ
			p->right = NULL;
			pm = pm->right; // pmָ��������,��M������е���һ��Ԫ��
			if (!(*Q).rhead[i])  // pΪQ������еĵ�1�����
			{
				(*Q).rhead[i] = p;
				pq = p;
			}// p���ڸ��еĵ�һ��λ��(p�����p��Ϊ���е����һ����㣬pq��ǵ����һ��Ԫ�ر�Ϊp)
			else // ����ʱ����Ԫ�أ������pq��ָ���֮��
			{
				pq->right = p; //pq�ĺ�һ��ָ��Ҫ�����p����������ǰ���һ������ȡ�ģ�����Ҫ�����һ�����Ѳ����֮��
				pq = p; // ��������һ�����ı䣬pqָ����в��������һ�����p
			}
			if (!(*Q).chead[p->j]) // pΪQ������еĵ�1�����(ԭ���ڵ�p->j��ֵΪ�գ�
			{
				(*Q).chead[p->j] = p;//��p���뵽ԭ��Ϊ�յ�p->j�д�
				col[p->j] = p;
			}// p���ڸ��б�ͷ�������p->j�е����һ��Ԫ����NULL��Ϊp
			else // ����ʱ����Ԫ�أ������col[p->j]��ָ���֮��
			{
				col[p->j]->down = p; //col[p->j]�ĺ�һ��ָ��Ҫ�����p
				col[p->j] = col[p->j]->down; // ��������һ�����ı䣬col[p->j]ָ����е����һ�����p
			}
		}
		while (pn) //M��������з���Ԫ�ؽ��Ѿ����룬�Ϸ�pm�������������򽫾���N���е�ʣ��Ԫ�ز������Q
		{
			p = new OLNode; // ���ɾ���Q��Ԫ�ؽ�� 
			if (!p)
				exit(OVERFLOW);
			(*Q).ne++; //Q�����ڵķ���Ԫ������+1
			p->i = i;
			p->j = pn->j;
			p->e = pn->e; // ����㸳ֵ
			p->right = NULL;
			pn = pn->right;  // pnָ��������,��N������е���һ��Ԫ��
			if (!(*Q).rhead[i])  // pΪQ������еĵ�1�����
			{
				(*Q).rhead[i] = p;
				pq = p;
			}// p���ڸ��еĵ�һ��λ��(p�����p��Ϊ���е����һ����㣬pq��ǵ����һ��Ԫ�ر�Ϊp)
			else  // ����ʱ����Ԫ�أ������pq��ָ���֮��
			{
				pq->right = p; //pq�ĺ�һ��ָ��Ҫ�����p����������ǰ���һ������ȡ�ģ�����Ҫ�����һ�����Ѳ����֮��
				pq = p; // ��������һ�����ı䣬pqָ����в��������һ�����p
			}
			if (!(*Q).chead[p->j]) // pΪQ������еĵ�1�����(ԭ���ڵ�p->j��ֵΪ�գ�
			{
				(*Q).chead[p->j] = p;//��p���뵽ԭ��Ϊ�յ�p->j�д�
				col[p->j] = p;
			}// p���ڸ��б�ͷ�������p->j�е����һ��Ԫ����NULL��Ϊp
			else // ����ʱ����Ԫ�أ������col[p->j]��ָ���֮��
			{
				col[p->j]->down = p; //col[p->j]�ĺ�һ��ָ��Ҫ�����p
				col[p->j] = col[p->j]->down; // ��������һ�����ı䣬col[p->j]ָ����е����һ�����p
			}
		}
	}
	for (k = 1; k <= (*Q).nc; k++)
		if (col[k]) // k����Ԫ�ؽ��
			col[k]->down = NULL; //  ��������һ������downָ��Ϊ�� 
	delete[]col;
	return OK;
}//�������

int main() {
	int a = 1; int flag = 0;
	do 
	{
		if (a == 1) 
		{
			Crosslist A, B, C;
			Initsmatrix(&A);
			Initsmatrix(&B);
			cout << "�������һ����������----------" << endl;
			Createsmatrix(&A);
			cout << "������ڶ�����������----------" << endl;
			Createsmatrix(&B);
			Addsmatrix(A, B, &C);
			cout << endl << "��������Ӻ����ý�����£�" << endl;
			Printsmatrix(C);
			cout << "��ѡ��������Ĳ�����" << endl;
			cout << "����0����������" << endl;
			cout << "����1������ִ�д˳���" << endl;
			Destroysmatrix(&A);
			Destroysmatrix(&B);
			Destroysmatrix(&C);
		}
		cin >> a;
		if (a == 0) 
		{
			flag = 1;
			cout << "�����������������´�����~" << endl;
		}
	} while (a && flag == 0);
	return 0;
}
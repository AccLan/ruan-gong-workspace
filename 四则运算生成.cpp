#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:6031)
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>

FILE* p;
int n, max, fuhao, fa, fl, kuohao, file;

void po_answer(double y[])     //小数运算答案
{
	int i;
	if (file == 1)
	{
		printf("\n正确答案：\n");
		for (i = 1; i < n + 1; i++)
			printf("(%d) %.2f\n", i, y[i]);
	}
	else
	{
		fprintf(p, "\n正确答案：\n");
		for (i = 1; i < n + 1; i++)
			fprintf(p, "(%d) %.2f\n", i, y[i]);
	}
}

void zs_answer(int y[])       //整数运算答案
{
	int i;
	if (file == 1)      //输出到文件
	{
		printf("\n正确答案：\n");
		for (i = 1; i < n + 1; i++)
			printf("(%d) %d\n", i, y[i]);
	}
	else         //输出到屏幕
	{
		fprintf(p, "\n正确答案：\n");
		for (i = 1; i < n + 1; i++)
			fprintf(p, "(%d) %d\n", i, y[i]);
	}
}

void zs_op()  //简单运算，整数的四则运算
{
	int i, a, b, x[1000];
	char c = ' ';
	for (i = 1; i < n + 1; i++)
	{
		a = rand() % max;    //随机数获取
		b = rand() % max;
		if (fuhao == 1)
		{
			c = '+';
			x[i] = a + b;
		}
		else if (fuhao == 2)
		{
			c = '-';
			x[i] = a - b;
		}
		else if (fuhao == 3)
		{
			c = '*';
			x[i] = a * b;
		}
		else if (fuhao == 4)
		{
			c = '/';
			while (b == 0)
			{
				b = rand() % max;
			}
			x[i] = a / b;
		}
		if (file == 1)
			printf("(%d) %d%c%d=\n", i, a, c, b);
		else
			fprintf(p, "(%d) %d%c%d=\n", i, a, c, b);
	}
	zs_answer(x);   //获取答案
}

void xs_op()  //简单运算，小数的四则运算
{
	int i;
	double x[1000], a, b;
	char c = ' ';
	for (i = 1; i < n + 1; i++)
	{
		a = rand() % (max * 100) / 100.00;   //随即小数获取
		b = rand() % (max * 100) / 100.00;
		if (fuhao == 1)
		{
			c = '+';
			x[i] = a + b;
		}
		else if (fuhao == 2)
		{
			c = '-';
			x[i] = a - b;
		}
		else if (fuhao == 3)
		{
			c = '*';
			x[i] = a * b;
		}
		else if (fuhao == 4)
		{
			c = '/';
			while (b == 0)
			{
				b = rand() % (max * 100) / 100.00 + 1;
			}
			x[i] = a / b;
		}
		if (file == 1)
			printf("(%d) %.2f%c%.2f=\n", i, a, c, b);
		else
			fprintf(p, "(%d) %.2f%c%.2f=\n", i, a, c, b);
	}
	po_answer(x);   //获取答案
}

void mixxs_op()  //混合运算（小数）
{
	int i;
	double x[1000], a, b, c;
	char d, e;
	for (i = 1; i < n + 1; i++)
	{
		a = rand() % (max * 100) / 100.00 + 1;
		b = rand() % (max * 100) / 100.00 + 1;
		c = rand() % (max * 100) / 100.00 + 1;
		if (i % 4 == 0)    //  a-b*c,(a-b)*c
		{
			d = '-';
			e = '*';
			if (kuohao == 1)   //有括号
				x[i] = a - b * c;
			else
				x[i] = (a - b) * c;
		}
		else if (i % 3 == 0)    //a+b/c,(a+b)/c
		{
			d = '+';
			e = '/';
			while (b == 0)
			{
				c = rand() % (max * 100) / 100.00 + 1;
			}
			if (kuohao == 1)
				x[i] = a + b / c;
			else
				x[i] = (a + b) / c;
		}
		else if (i % 2 == 0)    //a-b/c,(a-b)/c
		{
			d = '-';
			e = '/';
			while (b == 0)
			{
				b = rand() % (max * 100) / 100.00 + 1;
			}
			if (kuohao == 1)
				x[i] = a - b / c;
			else
				x[i] = (a - b) / c;
		}
		else   //a+b*c,(a+b)*c
		{
			d = '+';
			e = '*';
			if (kuohao == 1)
				x[i] = a + b * c;
			else
				x[i] = (a + b) * c;
		}
		if (file == 1)
		{
			if (kuohao == 1)
				printf("(%d) %.2f%c%.2f%c%.2f=\n", i, a, d, b, e, c);
			else
				printf("(%d) (%.2f%c%.2f)%c%.2f=\n", i, a, d, b, e, c);
		}
		else
		{
			if (kuohao == 1)
				fprintf(p, "(%d) %.2f%c%.2f%c%.2f=\n", i, a, d, b, e, c);
			else
				fprintf(p, "(%d) (%.2f%c%.2f)%c%.2f=\n", i, a, d, b, e, c);
		}
	}
	po_answer(x);   //获取答案
}

void  mixzs_op()  //混合运算（整数）
{
	int i, a, b, c;
	int x[1000];
	char d, e;
	for (i = 1; i < n + 1; i++)
	{
		a = rand() % max;
		b = rand() % max;
		c = rand() % max;
		if (i % 4 == 0)    //  a-b*c,(a-b)*c
		{
			d = '-';
			e = '*';
			if (kuohao == 1)   //无括号
				x[i] = a - b * c;
			else             //有括号
				x[i] = (a - b) * c;
		}
		else if (i % 3 == 0)    //a+b/c,(a+b)/c
		{
			d = '+';
			e = '/';
			while (c == 0)
			{
				c = rand() % max;
			}
			if (kuohao == 1)
				x[i] = a + b / c;
			else
				x[i] = (a + b) / c;
		}
		else if (i % 2 == 0)    //a-b/c,(a-b)/c
		{
			d = '-';
			e = '/';
			while (c == 0)
			{
				c = rand() % max;
			}
			if (kuohao == 1)
				x[i] = a - b / c;
			else
				x[i] = (a - b) / c;
		}
		else   //a+b*c,(a+b)*c
		{
			d = '+';
			e = '*';
			if (kuohao == 1)
				x[i] = a + b * c;
			else
				x[i] = (a + b) * c;
		}
		if (file == 1)   //输出到屏幕
		{
			if (kuohao == 1)
				printf("(%d) %d%c%d%c%d=\n", i, a, d, b, e, c);
			else
				printf("(%d) (%d%c%d)%c%d=\n", i, a, d, b, e, c);
		}
		else //输出到文件
		{
			if (kuohao == 1)
				fprintf(p, "(%d) %d%c%d%c%d=\n", i, a, d, b, e, c);
			else
				fprintf(p, "(%d) (%d%c%d)%c%d=\n", i, a, d, b, e, c);
		}
	}
	zs_answer(x);   //获取答案
}

int main()
{
	printf("\n\n\t*******************欢迎进入小学生四则运算自动生成程序*******************\n\n");
	printf("\n--------------------本程序适用于小学，小数均保留两位数计算------------------------\n\n");
	printf("1.请定制题目数量：");
	scanf("%d", &n);
	printf("\n2.请选择运算符号（1.加法    2.减法    3.乘法    4.除法    5.混合运算）：");
	scanf("%d", &fuhao);
	printf("\n3.请设置练习的最大数（如十以内、百以内等）：");
	scanf("%d", &max);
	printf("\n4.请设置是否有小数（1.无   2.有）：");
	scanf("%d", &fl);
	printf("\n5.请设置是否有括号（1.无   2.有）备注：此选项仅混合运算时选择，其他选项选1即可 ：");
	scanf("%d", &kuohao);
	printf("\n6.请设置输出方式（1.直接显示在屏幕上   2.输出到文件） ：");
	scanf("%d", &file);
	if (file == 2)
		printf("\n已生成四则运算.txt文件，请于文件夹种查看");
	p = fopen("四则运算.txt", "w");
	printf("\n\n");
	if (fuhao != 5)
	{
		if (fl == 1)
			zs_op();  //简单运算（无小数）
		else
			xs_op();  //简单运算（有小数）
	}
	else
	{
		if (fl == 1)
			mixzs_op();  //混合运算（无小数、有无括号）
		else
			mixxs_op(); //混合运算（有小数、有无括号）
	}
	fclose(p);
	printf("\n是否重新运行运行该程序?   <1>是   <2>退出\n");
	scanf("%d", &fa);
	if (fa == 1)
	{
		system("cls");  //清屏，重新运行
		main();
	}
}
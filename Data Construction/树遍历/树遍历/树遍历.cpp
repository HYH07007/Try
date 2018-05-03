// 树遍历.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>

struct node {
	int value;
	node * rchild;
	node * lchild;
};

int count = 1;
node *stack[10000] = { 0 };

void postorder(node * root);
void preorder(node * root);
void inorder(node * root);
void creat(node * p, int num);


int main()
{
	node * p0 = (node *)malloc(sizeof(node));
	p0->value = 0;
	for (int i = 0;i < 3;i++) creat(p0, i);
	preorder(p0);
	inorder(p0);
	postorder(p0);
	system("pause");
    return 0;
}

void creat(node*p, int num)
{
	if (num == 0)
	{
		node * p1 = (node *)malloc(sizeof(node));
		node * p2 = (node *)malloc(sizeof(node));
		p1->value = count++;
		p2->value = count++;
		p1->lchild = p1->rchild = p2->lchild = p2->rchild = NULL;
		p->lchild = p1;
		p->rchild = p2;
	}
	else
	{
		creat(p->lchild, num - 1);
		creat(p->rchild, num - 1);
	}
}

void postorder(node * root)
{
	printf("Postorder: ");
	node * p = root;
	int top = 0;
	stack[top++] = p;
	stack[top++] = NULL;
	while (1)
	{
		if (p->rchild) stack[top++] = p->rchild;
		if (p->lchild) stack[top++] = p->lchild;
		if (stack[top - 1]!= NULL)
		{
			p = stack[top - 1];
			stack[top++] = NULL;
		}
		else
		{
			top -= 2;
			for (;stack[top - 1] == NULL && top > -1;top -= 2) printf("%d  ", stack[top]->value);
			if (top < 0) break;
			printf("%d  ", stack[top]->value);
			p = stack[top - 1];
			stack[top++] = NULL;
		}
	}
	printf("\n");
}

void preorder(node * root)
{
	printf("Preorder: ");
	node * p = root;
	int top = 0;
	while (1)
	{
		printf("%d  ", p->value);
		if (p->lchild)
		{
			if (p->rchild) stack[top++] = p->rchild;
			p = p->lchild;
		}
		else if (p->rchild)
			p = p->rchild;
		else
		{
			if (top == 0) break;
			else
				p = stack[--top];
		}
	}
	printf("\n");
}

void inorder(node * root)
{
	printf("Inorder: ");
	node * p = root;
	int top = 0;
	while(1)
	{
		if (p->lchild)
		{
			stack[top++] = p;
			p = p->lchild;
		}
		else
		{
			printf("%d  ",p->value);
			if (p->rchild)
			{
				stack[top++] = p->rchild;
				p = p->rchild;
			}
			else
			{
				for (;top > 0 && !stack[top - 1]->rchild;top--)
					printf("%d  ", stack[top]->value);	
				if (top-- == 0) break;
				printf("%d  ", stack[top]->value);
				p = stack[top]->rchild;
			}
		}
	}
	printf("\n");
}


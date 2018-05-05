// 模式匹配.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

char s[22] = { 22,'A','D','B','A','D','A','B','B','A','A','B','A','D','A','B','B','A','D','A','D','A' };
char pat[11] = { 11,'A','D','A','B','B','A','D','A','D','A' };

struct elem
{
	int i;
	int j;
	int value;
};

elem mat1[16] = { {1,1,5},{2,1,3},{2,4,7},{3,2,3},{4,4,9} };
elem mat2[16] = { 0 };


void KMP(char * s, char * pat);
void show(char *s, char * pat, int i, int j);
void show_mat(elem * mat);
void transpose(elem * mat1, elem * mat2);
void KMP_11(char * s, char * pat);

int main()
{
	//show_mat(mat1);
	//transpose(mat1, mat2);
	//printf("\n");
	//show_mat(mat2);
	KMP(s, pat);
	KMP_11(s, pat);
	system("pause");
	return 0;
}

void transpose(elem * mat1, elem *mat2)
{
	int volu[5] = { 0 };
	for(int i=0;mat1[i].i!=0;i++)
		volu[mat1[i].j]++;
	for (int i = 1;i < 5;i++) volu[i] += volu[i - 1];
	mat2[volu[4]] = { 0,0,0 };
	for (int i = 0;mat1[i].i != 0;i++)
		mat2[volu[mat1[i].j - 1]++] = { mat1[i].j,mat1[i].i,mat1[i].value };
}

void show_mat(elem * mat)
{
	int x = 1, y = 1;
	for (int i = 0;mat[i].i != 0;)
	{
		if (mat[i].i != x)
		{
			printf("\n");
			x = mat[i].i; y = 1;
		}
		else
		{
			for (int k = mat[i].j - y;k > 0;k--) printf(" ");
			printf("%d", mat[i].value);
			y = mat[i].j;
			i++;
		}
	}
	printf("\n");
}


void KMP(char * s, char * pat)
{
	int i = 0, j = 1;
	char next[12] = { 0 };
	for (;j < pat[0];)
	{
		if (pat[i] == pat[j] || i == 0)
		{
			i++;j++;
			next[j] = (pat[j]==pat[i]&&i!=1)? next[i]:i;
		}
		else
			i = next[i];
	}
	for (i = 1;i < pat[0]; i++) printf("%d ", next[i]);
	printf("\n\n");
	show(s, pat, 1, 1);
	for (i = 1,j = 1;i < s[0]&&j < pat[0];)
	{
		if (s[i] != pat[j])
		{
			if (j == 1)
			{
				i++;
				show(s, pat, i, j);
			}
			else 
			{
				j = next[j];
				show(s, pat, i, j);
			}
		}
		else
		{
			i++;
			j++;
			show(s, pat, i, j);
		}
	}
}

void show(char *s, char * pat, int i, int j)
{
	if (i < s[0] && j < pat[0])
	{
		for (int k = 1;k < s[0];k++) printf("%c ", s[k]);
		printf("\n");
		for (int k = 1;k < i;k++) printf("  ");
		printf("|\n");
		for (int k = 0;k < i - j;k++) printf("  ");
		for (int k = 1;k < pat[0];k++) printf("%c ", pat[k]);
		printf("\n\n");
	}
}


void KMP_11(char * s, char * pat)
{
	// Next
	int next[100] = { 0 };
	next[2] = 1;
	for (int i=3,j=1;i < pat[0] + 1;)
	{
		if (pat[i - 1] == pat[j])
		{
			next[i] = (pat[i] == pat[j + 1]) ? next[j + 1] : j + 1;
			i++;j++;
		}
		else if (j == 1)
			next[i++] = 1;
		else
			j = next[j];
	}
	for (int i = 1;i < pat[0]; i++) printf("%d ", next[i]);
	// Pattern
	for (int i = 1,j = 1;;)
	{
		if (s[i] == pat[j])
		{
			show(s, pat, i, j);
			if (j == pat[0])
			{
				printf("Successfully patterned!\n");
				break;
			}
			i++;j++;
		}
		else
		{
			show(s, pat, i, j);
			if (j == 1) i++;
			else j = next[j];
		}
	}
}
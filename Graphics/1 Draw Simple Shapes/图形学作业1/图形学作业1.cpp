// 图形学作业1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<gl/glut.h>
#include<stdio.h>
#include<math.h>
#define PI 3.1415926535

typedef float point[3];

typedef struct cor
{
	float x;
	float y;
} cor;

typedef struct triangle
{
	point p1;
	point p2;
	point p3;
} triangle;

typedef float matrix[3][3];

void init_triangle(triangle * obj_addr, float p11, float p12, float p21, float p22, float p31, float p32, float s)
{
	obj_addr->p1[0] = p11;
	obj_addr->p1[1] = p12;
	obj_addr->p2[0] = p21;
	obj_addr->p2[1] = p22;
	obj_addr->p3[0] = p31;
	obj_addr->p3[1] = p32;
	obj_addr->p1[2] = obj_addr->p2[2] = obj_addr->p3[2] = 1.;
}

void SetupRC(void)
{
	//设置窗口背景颜色为白色
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void show_point(float x, float y, float size)
{
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

float mod_2pi(float theta1, float theta2)
{
	while (theta1 > theta2)
		theta1 -= 2 * PI;
	while (theta1 < theta2)
		theta1 += 2 * PI;
	return theta1;
}


//绘制三角形
void DrawTriangle(triangle obj)
{
	glBegin(GL_TRIANGLES);
	glVertex2f(obj.p1[0] * obj.p1[2], obj.p1[1] * obj.p1[2]);
	glVertex2f(obj.p2[0] * obj.p2[2], obj.p2[1] * obj.p2[2]);
	glVertex2f(obj.p3[0] * obj.p3[2], obj.p3[1] * obj.p3[2]);
	glEnd();
}

//采用Bresenham算法绘制直线
void BresenhamLine(float x0, float y0, float x1, float y1, int color)
{
	float k;
	if (x0 == x1)
		k = 999999.;
	else
		k = (y1 - y0) / (x1 - x0);
	float pix = 0.001;
	float e = -pix / 2.;
	float y = y0;
	if(color == 0)
		glColor3f(1.0f, 0.0f, 0.0f);
	else if(color == 1)
		glColor3f(0.0f, 1.0f, 0.0f);
	else
		glColor3f(0.0f, 0.0f, 1.0f);
	for (float x = x0; x < x1; x += pix)
	{
		show_point(x, y, 1.);
		e += pix * k;
		if (e > 0)
		{
			y += pix;
			e -= pix;
		}
	}
}

//圆弧的绘制
void show_arc(float r, float angel_1, float angel_2, float x, float y, int color)
{
	if (color == 0)
		glColor3f(1.0f, 0.0f, 0.0f);
	else if (color == 1)
		glColor3f(0.0f, 1.0f, 0.0f);
	else
		glColor3f(0.0f, 0.0f, 1.0f);
	angel_1 = angel_1 / 180. * PI;
	angel_2 = angel_2 / 180. * PI;
	angel_1 = mod_2pi(angel_1, 0.);
	angel_2 = mod_2pi(angel_2, angel_1);
	float xx, yy;
	float angel = angel_1;
	while (angel < angel_2)
	{
		xx = x + cos(angel) * r;
		yy = y + sin(angel) * r;
		show_point(xx, yy, 1);
		angel += 0.001;
	}
}

void ChangeSize(int w, int h)
{
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//设置裁剪空间
	if (w <= h)
		glOrtho(-200.0f, 200.0f, -200.0f*h / w, 200.0f*h / w, -200.0f, 200.0f);
	else
		glOrtho(-200.0f*w / h, 200.0f*w / h, -200.0f, 100.0f, -200.0f, 200.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//设置当前操作矩阵为模型视图矩阵，并复位为单位矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//绘制黑色的坐标轴
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(-200.0f, 0.0f);
	glVertex2f(200.0f, 0.0f);
	glVertex2f(0.0f, -200.0f);
	glVertex2f(0.0f, 200.0f);
	glEnd();

	//使用Bresenham算法绘制(10,20)到(100,50)的蓝色直线
	BresenhamLine(10., 20., 100., 50., 2);

	//绘制红色三角形
	triangle a;
	init_triangle(&a, 0., 0., -40., 0., -20., -40., 1.);
	glColor3f(1.0f, 0.0f, 0.0f);
	DrawTriangle(a);

	//绘制半径为70，从60度到250，圆心为(0, 20)的绿色圆弧
	show_arc(70, 60, 250, 0, 20, 1);

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{

	//glutInit is used to initialize the GLUT library
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("图形学作业1");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);


	SetupRC();
	glutMainLoop();

	return 0;
}


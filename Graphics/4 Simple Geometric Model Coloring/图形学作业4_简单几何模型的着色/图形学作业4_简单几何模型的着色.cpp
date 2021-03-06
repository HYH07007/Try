// 图形学作业4_简单几何模型的着色.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <gl/glut.h>
#include <stdio.h>
#include <math.h>

#define MIN_DIS 0.001

typedef struct point
{
	float x, y;
	point()
	{
		x = 0.0f;
		y = 0.0f;
	}
	point(const point& p)
	{
		x = p.x;
		y = p.y;
	}
	point(float xx, float yy)
	{
		x = xx;
		y = yy;
	}
	point operator=(const point& p)
	{
		x = p.x;
		y = p.y;
		return *this;
	}
	point operator+(const point& p)
	{
		point temp;
		temp.x = x + p.x;
		temp.y = y + p.y;
		return temp;
	}
	point operator-(const point& p)
	{
		point temp(x - p.x, y - p.y);
		return temp;
	}
	float length()
	{
		return sqrtf(x * x + y * y);
	}
} point;

point p0, p1, p2, p3, p4, p5;

float get_k(point p1, point p2)
{
	if (p1.x == p2.x)
		return 9999999.;
	else
		return (p1.y - p2.y) / (p1.x - p2.x);
}

void show_vertex(point p, float c1, float c2, float c3)
{
	glColor3f(c1, c2, c3);
	glVertex2f(p.x, p.y);
}
void draw_line(float x, float y1, float y2, int color_mode)
{
	float c1, c2, c3;
	if (y2 - y1 <= MIN_DIS) // y2 must be greater than y1
		return;
	if (color_mode == 0)
	{
		c1 = 0.;
		c2 = (x - p1.x) / (p2.x - p1.x);
		c3 = (x - p2.x) / (p1.x - p2.x);
	}
	else
	{
		c1 = (x - p1.x) / (p5.x - p1.x);
		c2 = 0.;
		c3 = (x - p5.x) / (p1.x - p5.x);
	}
		;
	glColor3f(c1, c2,  c3);
	glVertex2f(x, (y1 + y2) / 2);

	draw_line(x, y1, (y1 + y2) / 2., color_mode);
	draw_line(x, (y1 + y2) / 2, y2, color_mode);
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
		glOrtho(-2.0f, 2.0f, -2.0f*h / w, 2.0f*h / w, -2.0f, 2.0f);
	else
		glOrtho(-2.0f*w / h, 2.0f*w / h, -2.0f, 1.0f, -2.0f, 2.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Display()
{
	p0 = point(0.0, 0.1);
	p1 = point(0.0, 1.0);
	p2 = point(-0.5, -0.1);
	p3 = point(0.0, -0.1);
	p4 = point(0.0, -1.0);
	p5 = point(0.5, 0.1);


	// 采用扫描法，并进行线性插值。
	glBegin(GL_POINTS);
	float k1 = get_k(p1, p2);
	float k2 = get_k(p4, p5);
	for (float dx = p2.x; dx <= p5.x; dx += 0.001)
	{
		if (dx < p0.x)
			draw_line(dx, p2.y, k1*dx + p1.y, 0);
		else
			draw_line(dx, k2*dx + p4.y, p5.y, 1);
	}
	glEnd();

	// 平移图形，用于比对。
	point d = point(-1, 0);
	p0 = p0 + d;
	p1 = p1 + d;
	p2 = p2 + d;
	p3 = p3 + d;
	p4 = p4 + d;
	p5 = p5 + d;

	// 利用OpenGL直接进行上色。
	glLineWidth(3.0);
	glBegin(GL_POLYGON);
	show_vertex(p0, 0., 0., 1.);
	show_vertex(p1, 0., 0., 1.);
	show_vertex(p2, 0., 1., 0.);
	show_vertex(p3, 0., 0., 1.);
	show_vertex(p4, 0., 0., 1.);
	show_vertex(p5, 1., 0., 0.);
	glEnd();

	glFlush();
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glutInitWindowPosition(300, 300);
	glutInitWindowSize(500, 500);

	glutCreateWindow("简单几何模型的着色");

	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();

	return 0;
}
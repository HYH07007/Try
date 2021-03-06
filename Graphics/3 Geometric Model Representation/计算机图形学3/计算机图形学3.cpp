// 计算机图形学3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include "pch.h"
#include <gl/glut.h>
#include <stdio.h>
#include <math.h>

#define MIN_DIS 0.001

typedef struct point
{
	float x, y, z;
	point()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	point(const point& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
	}
	point(float xx, float yy, float zz)
	{
		x = xx;
		y = yy;
		z = zz;
	}
	point operator*(float mul)
	{
		point temp;
		temp.x = x * mul;
		temp.y = y * mul;
		temp.z = z * mul;
		return temp;
	}
	point operator=(const point& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		return *this;
	}
	point operator+(const point& p)
	{
		point temp;
		temp.x = x + p.x;
		temp.y = y + p.y;
		temp.z = z + p.z;
		return temp;
	}
	point operator-(const point& p)
	{
		point temp(x - p.x, y - p.y, z - p.z);
		return temp;
	}
	float length()
	{
		return sqrtf(x * x + y * y + z * z);
	}
} point;

point p0, p1, p2, p3;

void show_point(point p, float size)
{
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex3f(p.x, p.y, p.z);
	glEnd();
}

void show_frame()
{
	glBegin(GL_LINE_STRIP);
	glVertex3f(p0.x, p0.y, p0.z);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p0.x, p0.y, p0.z);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(p0.x, p0.y, p0.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(p0.x, p0.y, p0.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glVertex3f(p1.x, p1.y, p1.z);
	glEnd();
}


void Display()
{
	float u, v;

	p0 = point(0., 0., 0.);
	p1 = point(0.5, 0., 0.);
	p2 = point(0, 0.5, 0.);
	p3 = point(0., 0., 0.5);

	gluLookAt(0.1, 0.1, 0.1,    0.0, 0.0, 0.,    -0.1, -0.1, 0.1);

	glColor3f(1.0f, 1.0f, 1.0f);

	show_point(p0, 0.1);
	show_point(p1, 0.1);
	show_point(p2, 0.1);
	show_point(p3, 0.1);
	show_frame();

	point draw_point;
	point draw_point0;
	point draw_point1;

	for (u = 0.0; u < 1.0; u += 0.001)
	{
		draw_point0 = (p0 * pow(1 - u, 3)) + (p1 * 3. * u * pow(1. - u, 2.)) + (p2 * 3 * pow(u, 2.) * (1 - u)) + (p0 * pow(u, 3.));
		draw_point1 = (p3 * pow(1 - u, 3)) + (p1 * 3. * u * pow(1. - u, 2.)) + (p2 * 3 * pow(u, 2.) * (1 - u)) + (p3 * pow(u, 3.));
		glColor3f(0.f, 1.f, 0.f);
		show_point(draw_point0, 2);
		show_point(draw_point1, 2);
		for (v = 0.0; v < 1.0; v += 0.001)
		{
			glColor3f(0.f, 0.f, 1.f);
			draw_point = (draw_point0 * v) + (draw_point1 * (1 - v));
			show_point(draw_point, 0.1);
		}
	}

	glutSwapBuffers();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ChangeSize(int w, int h)
{
	float size = .5;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//设置裁剪空间
	if (w <= h)
		glOrtho(-size, size, -size*h / w, size*h / w, -size, size);
	else
		glOrtho(-size*w / h, size*w / h, -size, size, -size, size);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(300, 300);
	glutInitWindowSize(500, 500);

	glutCreateWindow("四面体及其一种Bezier曲面");

	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();

	return 0;
}
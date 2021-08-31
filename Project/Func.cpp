#include <gl/glut.h>
#include <iostream>
#include <math.h>
#include "Func.h"
#define PI 3.141592

float length(float x1, float x2, float y1, float y2, float z1, float z2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));
}
float length(float x1, float x2, float y1, float y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
float length(float x1, float x2)
{
	return abs(x1 - x2);
}
float getceta(float x_length, float z_length)
{
	return atan(x_length / z_length);
}
float radian(float ceta)
{
	return ceta * 180 / PI;
}

void cylinder(float centerx, float centery, float centerz, float radius, float h)
{
#define GL_PI 3.1415f


	/* function createCyliner()
	������� �߽� x,y,z��ǥ, ������, ���̸� �޾� ������� �����ϴ� �Լ�(+z�������� ������ �þ)
	centerx : ����� ���� �߽� x��ǥ
	centery : ����� ���� �߽� y��ǥ
	centerz : ����� ���� �߽� z��ǥ
	radius : ������� ������
	h : ������� ����
	*/
	GLfloat x, y, angle;

	glBegin(GL_TRIANGLE_FAN);           //������� ����
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(centerx, centery, centerz);  //<p>< / p>

	for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI / 8.0f))
	{
		x = centerx + radius*sin(angle);
		y = centery + radius*cos(angle);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(x, y, centerz);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);            //������� ����
	for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI / 8.0f))
	{
		x = centerx + radius*sin(angle);
		y = centery + radius*cos(angle);
		glNormal3f(sin(angle), cos(angle), 0.0f);
		glVertex3f(x, y, centerz);
		glVertex3f(x, y, centerz + h);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);           //������� �ظ�
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(centerx, centery, centerz + h);
	for (angle = (2.0f*GL_PI); angle > 0.0f; angle -= (GL_PI / 8.0f))
	{
		x = centerx + radius*sin(angle);
		y = centery + radius*cos(angle);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(x, y, centerz + h);
	}
	glEnd();
}


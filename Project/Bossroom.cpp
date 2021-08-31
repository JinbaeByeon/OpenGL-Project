#include <gl/glut.h>
#include <Windows.h>
#include <iostream>
#include "Bossroom.h"

void Bossroom::draw() const
{
	glPushMatrix(); {
		glTranslatef(0, 0, -2500);
		glColor3f(203/255.f, 29/255.f, 33/255.f);

		glPushMatrix(); { //왼쪽 (-2500~1700)
			glTranslatef(-400,500,0);
			glScalef(4.2, 1, 0.01);
			glutSolidCube(1000);
		}glPopMatrix();
		glPushMatrix(); { // 오른쪽 (1900~2500)
			glTranslatef(2200, 500, 0);
			glScalef(0.6, 1, 0.01);
			glutSolidCube(1000);
		}glPopMatrix();
		glPushMatrix(); { // 위 (1700~1900/400~1000)
			glTranslatef(1800, 700, 0);
			glScalef(0.2, 0.6, 0.01);
			glutSolidCube(1000);
		}glPopMatrix();
		glPushMatrix(); { // 문 (1700~1900/0~400)
			glColor3f(0.5, 0.5, 0.5);
			glTranslatef(1800, 200, 0);
			glRotatef(yRotate, 0, 1, 0);
			glScalef(0.2, 0.4, 0.01);
			glutSolidCube(1000);
		}glPopMatrix();
	}glPopMatrix();
}

void Bossroom::update()
{
	if (isOpen)
		yRotate = std::min(90, yRotate - 5);
}

void Bossroom::door_open()
{
	isOpen = true;
}
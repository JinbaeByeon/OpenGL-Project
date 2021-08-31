#include <gl/glut.h>
#include <stdio.h>
#include "tree.h"
#include "default_value.h"
#include "util.h"

Tree::Tree(float xPos, float yPos, float zPos) :size(Size_Tree)
{
	x = xPos;
	y = yPos;
	z = zPos;
}

void Tree::draw() const
{
	glPushMatrix();
		glTranslatef(x, y, z);

		glTranslatef(0, size / 4, 0);
		glPushMatrix();
			glScalef(0.5, 1, 0.5);
			glColor3f(0.6, 0.3, 0.2);
			glutSolidCube(size / 2);
		glPopMatrix();

		glTranslatef(0, size / 4, 0);
		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			glColor3f(0, 0.7, 0);
			glutSolidCone(4*size/10, size / 2, 20, 20);
		glPopMatrix();
		
		glTranslatef(0, size / 4, 0);
		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			glColor3f(0, 0.6, 0);
			glutSolidCone(3 * size / 10, size / 2, 20, 20);
		glPopMatrix();

		glTranslatef(0, size / 4, 0);
		glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glColor3f(0, 0.5, 0);
		glutSolidCone(2 * size / 10, size / 2, 20, 20);
		glPopMatrix();
	glPopMatrix();
}

bool Tree::collide(int xPos, int yPos, int zPos) const
{
	if (Length(x - xPos, y - yPos, z - zPos) <= Size_Tree)
		return true;
	return false;
}


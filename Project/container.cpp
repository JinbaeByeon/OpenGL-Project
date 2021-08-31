#include <gl/glut.h>
#include <cmath>
#include "container.h"
#include "default_value.h"

Container::Container() :x(0), y(0), z(0)
{
	xSize = xSize_Container;
	ySize = ySize_Container;
	zSize = zSize_Container;

	yRotate = 0;
}

Container::Container(int xPos, int yPos, int zPos, int yRotate) : x(xPos), y(yPos), z(zPos), yRotate(yRotate)
{
	xSize = xSize_Container;
	ySize = ySize_Container;
	zSize = zSize_Container;
}

void Container::draw(unsigned int texture) const
{
	glPushMatrix();{
		glTranslatef(x, y, z);
		
		glRotatef(yRotate, 0, 1, 0);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS); {	// Left
			glTexCoord2f(0.f, 0.f);
			glVertex3f(-xSize / 2, 0, -zSize / 2);
			glTexCoord2f(1.f, 0.f);
			glVertex3f(-xSize / 2, ySize, -zSize / 2);
			glTexCoord2f(1.f, 1.f);
			glVertex3f(-xSize / 2, ySize, zSize / 2);
			glTexCoord2f(0.f, 1.f);
			glVertex3f(-xSize / 2, 0, zSize / 2);
		}glEnd();
		glBegin(GL_QUADS); {	// Right
			glTexCoord2f(0.f, 0.f);
			glVertex3f(xSize / 2, 0, -zSize / 2);
			glTexCoord2f(0.f, 1.f);
			glVertex3f(xSize / 2, 0, zSize / 2);
			glTexCoord2f(1.f, 1.f);
			glVertex3f(xSize / 2, ySize, zSize / 2);
			glTexCoord2f(1.f, 0.f);
			glVertex3f(xSize / 2, ySize, -zSize / 2);
		}glEnd();
		glBegin(GL_QUADS); {	// Front
			glTexCoord2f(0.f, 0.f);
			glVertex3f(-xSize / 2, 0, zSize / 2);
			glTexCoord2f(0.f, 1.f);
			glVertex3f(-xSize / 2, ySize, zSize / 2);
			glTexCoord2f(1.f, 1.f);
			glVertex3f(xSize / 2, ySize, zSize / 2);
			glTexCoord2f(1.f, 0.f);
			glVertex3f(xSize / 2, 0, zSize / 2);
		}glEnd();
		glBegin(GL_QUADS); {	// Back
			glTexCoord2f(0.f, 0.f);
			glVertex3f(-xSize / 2, 0, -zSize / 2);
			glTexCoord2f(0.f, 1.f);
			glVertex3f(xSize / 2, 0, -zSize / 2);
			glTexCoord2f(1.f, 1.f);
			glVertex3f(xSize / 2, ySize, -zSize / 2);
			glTexCoord2f(1.f, 0.f);
			glVertex3f(-xSize / 2, ySize, -zSize / 2);
		}glEnd();
		glBegin(GL_QUADS); {	// Roof
			glTexCoord2f(0.f, 0.f);
			glVertex3f(-xSize / 2, ySize, -zSize / 2);
			glTexCoord2f(0.f, 1.f);
			glVertex3f(xSize / 2, ySize, -zSize / 2);
			glTexCoord2f(1.f, 1.f);
			glVertex3f(xSize / 2, ySize, zSize / 2);
			glTexCoord2f(1.f, 0.f);
			glVertex3f(-xSize / 2, ySize, zSize / 2);
		}glEnd();
	}glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

bool Container::inContainer(const float xPos, const float yPos, const float zPos) const
{
	if (abs(x - xPos) < xSize&&abs(y - yPos) < ySize&&abs(z - zPos) < zSize)
		return true;

	return false;
}

int Container::getSize_X() const
{
	return xSize;
}

int Container::getSize_Y() const
{
	return ySize;
}

int Container::getSize_Z() const
{
	return zSize;
}
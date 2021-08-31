#include <gl\glut.h>
#include "Item_ground.h"
#include "Func.h"


void FlameThrower_g::draw() {
	if (false == Draw) {
		glPushMatrix(); {
			glColor3f(0, 0, 128 / 255.0);
			glTranslatef(x, y+40 , z - 80);
			glScalef(0.5, 0.5, 0.5);
			glPushMatrix(); {
				cylinder(0, 0, 0, 10, 100);
			}glPopMatrix();
			glPushMatrix(); {
				glTranslatef(0, 10, 50);
				glScalef(0.4, 0.4, 0.4);
				glutSolidCube(20);
			}glPopMatrix();
			glPushMatrix(); {
				glColor3f(0.2, 0.2, 0.2);
				glTranslatef(0, 0, 50);
				cylinder(0, 0, 0, 3, 130);
			}glPopMatrix();
			glPushMatrix(); {
				glColor3f(0.2, 0.2, 0.2);
				glTranslatef(-10, 0, 180);
				glRotatef(90, 0, 1, 0);
				cylinder(0, 0, 0, 3, 12);
			}glPopMatrix();
			glColor3f(0, 0, 128 / 255.0);
			glTranslatef(-30, -15, 180);
			glScalef(1, 1, 0.3);
			glutSolidCube(40);
		}glPopMatrix();

	}
}


Vaccine_g::Vaccine_g(int x, int y, int z) : x(x), y(y), z(z) {}

void Vaccine_g::draw() {
	if (false == Draw) {
		glPushMatrix(); {
			glTranslatef(x, y, z);
			glPushMatrix(); {
				glScalef(3, 1, 1);
				glColor3f(0.9, 0.9, 0.9);
				glutSolidCube(10);
			}glPopMatrix();
			glTranslatef(20, 0, 0);
			glColor3f(1, 0, 0);
			glutSolidCube(10);
		}glPopMatrix();
	}
}

void Potion_g::draw() {
	if (false == Draw) {
		glPushMatrix(); {
			glTranslatef(x, y+10, z);
			glPushMatrix(); {
				glRotatef(90, 0, 0, 1);
				glColor3f(1, 0, 0);
				glutSolidSphere(10, 6, 6);
			}glPopMatrix();
			glTranslatef(0, 12, 0);
			glColor3f(0.1, 0.1, 0.1);
			glutSolidCube(7);
		}glPopMatrix();
	}
}

void Grenade_g::draw(){
	/*if (false == Draw) {
		glPushMatrix(); {
			glTranslatef(x, y+10, z);
			glPushMatrix(); {
				glRotatef(90, 0, 0, 1);
				glColor3f(0, 64 / 255.0, 0);
				glutSolidSphere(10, 6, 6);
			}glPopMatrix();
			glTranslatef(0, 12, 0);
			glColor3f(0.1, 0.1, 0.1);
			glutSolidCube(7);
		}glPopMatrix();
	}*/
}

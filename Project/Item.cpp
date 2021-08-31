#include <gl\glut.h>
#include <random>
#include "Item.h"
#include <iostream>
#include <Windows.h>
#include "Func.h"
using namespace std;

Pistol::Pistol()
{
	x = 0;
	y = 0;
	z = 0;
}

Pistol::Pistol(float vx, float vy, float vz)
{
	x = vx;
	y = vy;
	z = vz;
	reloading = 0;
	num_bullet = 0;
}

void Pistol::draw() const {
	glPushMatrix(); {
		glColor3f(128 / 255.0, 128 / 255.0, 128 / 255.0);
		glTranslatef(x, y, z);
		glRotatef(-90, 0, 1, 0);
		glPushMatrix(); {
			glScalef(1, 0.2, 0.2);
			glutSolidCube(50);
		}glPopMatrix();
		glTranslatef(20, -10, 0);
		glScalef(1, 1.5, 1);
		glutSolidCube(10);
	}glPopMatrix();
}

void Pistol::draw_bullet()
{
	if (animation) {
		angle = max(0, angle - 5);
		if (angle == 0)animation = false;

		glRotatef(-angle, 1, 0, 0);

	}
}

void Pistol::shot(float x, float y, float z)
{
	if (0 == reloading) {
		sound.pSound_Pistol();
		animation = true;
		angle = 40;
		reloading = 10;
	}
}

void Pistol::update() {
	reloading = max(0, reloading - 1);
}

FlameThrower::FlameThrower()
{
	x = 0;
	y = 0;
	z = 0;
}

FlameThrower::FlameThrower(float vx, float vy, float vz)
{
	x = vx;
	y = vy;
	z = vz;

	reloading = 2;
	num_bullet = 0;
}

void FlameThrower::draw() const {
	glPushMatrix(); {
		glColor3f(0, 0, 128 / 255.0);
		glTranslatef(x, y - 10, z - 80);
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

void FlameThrower::draw_bullet()
{
	for (int i = 0; i < min(1000, num_bullet * 4); i++) {
		if (bullet[i][3][0]>0) {
			glPushMatrix(); {
				glTranslatef(bullet[i][0][0], bullet[i][1][0], bullet[i][2][0]);
				glColor3f(1, 0, 0);
				glutSolidCube(5);
				//if(length(bullet[i][0][0], bullet[i][1][0], bullet[i][2][0]) <= 50)
			}glPopMatrix();
		}
	}
}

void FlameThrower::update() {
	reloading = max(0, reloading - 1);
}

void FlameThrower::shot(float x, float y, float z)
{
	if (reloading == 0) {
		isShot = true;

		for (int i = (num_bullet * 4) % 1000; i < (num_bullet * 4 + 4) % 1000; i++) {
			bullet[i][0][0] = 0;
			bullet[i][1][0] = 0;
			bullet[i][2][0] = -80;
			bullet[i][3][0] = 30;

			bullet[i][0][1] = -3 + rand() % 6;
			bullet[i][1][1] = -3 + rand() % 6;
			bullet[i][2][1] = -15 + rand() % 10;
		}
		num_bullet++;
		reloading = 2;
	}
	for (int i = 0; i < min(1000, num_bullet * 4); i++) {
		for (int j = 0; j < 3; j++) {
			bullet[i][j][0] += bullet[i][j][1];
			//			cout << bullet[i][j][0] << endl;
		}
		bullet[i][3][0]--;
	}
}

Vaccine::Vaccine(int x, int y, int z) : x(x), y(y), z(z) {}

void Vaccine::draw() {
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

void Potion::draw() {
	glPushMatrix(); {
		glTranslatef(x, y, z);
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

Grenade::Grenade()
{
	x = 0;
	y = 0;
	z = 0;
}

Grenade::Grenade(float vx, float vy, float vz)
{
	x = vx;
	y = vy;
	z = vz;
}

void Grenade::draw() const {
	//glPushMatrix(); {
	//	glTranslatef(x, y-10, z);
	//	glPushMatrix(); {
	//		glRotatef(90, 0, 0, 1);
	//		glColor3f(0, 64 / 255.0, 0);
	//		glutSolidSphere(10, 6, 6);
	//	}glPopMatrix();
	//	glTranslatef(0, 12, 0);
	//	glColor3f(0.1, 0.1, 0.1);
	//	glutSolidCube(7);
	//}glPopMatrix();
}

void Grenade::draw_bullet()
{

}

void Grenade::update() {

}

void Grenade::shot(float x, float y, float z) {}


void Grenade::clear()
{

}

void FlameThrower::clear()
{
	num_bullet = 0;
}

void Pistol::clear()
{

}

void Pistol::stop_shot()
{

}

void FlameThrower::stop_shot()
{
	isShot = false;
}

void Grenade::stop_shot()
{

}
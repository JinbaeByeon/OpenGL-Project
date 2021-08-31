#include <gl\glut.h>
#include <iostream>
#include <math.h>
#include "Zombie.h"
#include "Func.h"
#define SPEED 5
#define ZOMBIE_SIZE 60

void Zombie::draw() {
	if (hp > 0) {
		glPushMatrix();
		{
			glColor4f(0, 32 / 255.0, 0, alpha);
			glTranslatef(x, y, z);				// 좀비위치
			if (x_e == 1) {
				if (z_e == 1) glRotatef(radian(ceta), 0, 1, 0);
				else glRotatef(180 - radian(ceta), 0, 1, 0);
			}
			else if (x_e == -1) {
				if (z_e == 1) glRotatef(-radian(ceta), 0, 1, 0);
				else glRotatef(180 + radian(ceta), 0, 1, 0);
			}
			{
				glTranslatef(0, 40, 0);
				glPushMatrix();						// 다리
				{
					glTranslatef(-3, 40, 0);
					glRotatef(-leg_ceta, 1, 0, 0);
					glTranslatef(-10, -40, 0);
					glScalef(0.3, 2, 0.3);
					glutSolidCube(40);
				}
				glPopMatrix();
				glPushMatrix();
				{
					glTranslatef(3, 40, 0);
					glRotatef(leg_ceta, 1, 0, 0);
					glTranslatef(10, -40, 0);
					glScalef(0.3, 2, 0.3);
					glutSolidCube(40);
				}
			}
			glPopMatrix();
			{
				glTranslatef(0, 50, 0);				// 몸통
				glPushMatrix();
				glPushMatrix();
				glPushMatrix();
				glScalef(1, 1.5, 0.3);
				glutSolidCube(40);

				glPopMatrix();
				glRotatef(arm_ceta, 1, 0, 0);
				glTranslatef(25, 20, 20);
				glRotatef(80, 0, 1, 0);
				glScalef(1, 0.3, 0.5);
				glutSolidCube(40);					// 팔

				glPopMatrix();
				glRotatef(arm_ceta, 1, 0, 0);
				glTranslatef(-25, 20, 20);
				glRotatef(-80, 0, 1, 0);
				glScalef(1, 0.3, 0.5);
				glutSolidCube(40);

				glPopMatrix();
				glTranslatef(0, 50, 0);
				glutSolidSphere(20, 30, 30);		// 머리
			}
			glPushMatrix();
			{										// 눈
				glPushMatrix();
				glColor4f(1, 0.4, 0.4, alpha);
				glTranslatef(-7, 5, 20);
				glRotatef(90, 1, 0, 0);
				glScalef(1, 0.1, 1);
				glutSolidSphere(5, 10, 10);

				glPopMatrix();
				glTranslatef(7, 5, 20);
				glRotatef(90, 1, 0, 0);
				glScalef(1, 0.1, 1);
				glutSolidSphere(5, 10, 10);

			}
			glPopMatrix();
		}glPopMatrix();
	}
}

bool Zombie::update(float vx, float vy, float vz) {
	if (hp < 0) y = -2500;
	if (length(x, vx, y, vy, z, vz) < 100)
		return attack();
	else if (length(x, vx, y, vy, z, vz) < 2000)
		move(vx, vy, vz);
	return 0;
	

}

void Zombie::move(float vx, float vy, float vz) {
	if(Move_count == 0)
		ceta = getceta(length(x, vx), length(z, vz));

	if (Move_count == 0) {
		if (vx > x) x_e = 1;
		else if (vx < x) x_e = -1;
		if (vz > z) z_e = 1;
		else if (vz < z) z_e = -1;
	}
	Move_count++;
	if (Move_count == 30)
		Move_count = 0;

	

	if (false == Collision)
	{
		x += SPEED * sin(ceta) * x_e;
		z += SPEED * cos(ceta) * z_e;
	}
	else {
		if (Move == 1)
			x -= SPEED;
		else if (Move == 2)
			x += SPEED;
		else if (Move == 3)
			z -= SPEED;
		else
			z += SPEED;

	}
	
	leg_ceta += 3 * leg_e;
	if (leg_ceta >= 30)
	{
		leg_e = -1;
	}
	if (leg_ceta <= -30)
		leg_e = 1;

}

bool Zombie::attack(){
	arm_ceta += 6 * arm_e;
	if (arm_ceta >= 30)
		arm_e = -1;
	if (arm_ceta <= -30)
		arm_e = 1;
	if (arm_ceta == -6) {
		arm_ceta += 6 * arm_e;
		return true;
	}
	return 0;
}

void Zombie::collision(float other_x, float other_y, float other_z, int other_x_size, int other_y_size, int other_z_size) 
{

	float other_x1 = 0;
	float other_x2 = 0;
	float other_z1 = 0;
	float other_z2 = 0;

	if (other_x_size == other_z_size) {
		if (length(x, other_x, z, other_z) <= other_x_size/2  + ZOMBIE_SIZE) {
			Collision = true;
			if (length(x, other_x) >= length(z, other_z)) {
				if (z > other_z)
					Move = 4;	//앞으로이동
				else
					Move = 3;	//뒤로이동
			}
			else {
				if (x > other_x)
					Move = 2;	// 오른쪽 이동
				else
					Move = 1;	// 왼쪽 이동
			}
		}
	}
	else if (other_x_size > other_z_size) {
		other_x1 = (other_x + other_x - other_x_size) / 2;
		other_x2 = (other_x + other_x + other_x_size) / 2;

		if (length(x, other_x1, z, other_z) <= other_x_size / 2 + 20) {
			Collision = true;
			if (length(x, other_x1) >= length(z, other_z)) {
				if (z > other_z)
					Move = 4;	//앞으로이동
				else
					Move = 3;	//뒤로이동
			}
			else {
				if (x > other_x1)
					Move = 2;	// 오른쪽 이동
				else
					Move = 1;	// 왼쪽 이동
			}
		}
		if (length(x, other_x2, z, other_z) <= other_x_size / 2 + 20) {
			Collision = true;
			if (length(x, other_x2) >= length(z, other_z)) {
				if (z > other_z)
					Move = 4;	//앞으로이동
				else
					Move = 3;	//뒤로이동
			}
			else {
				if (x > other_x2)
					Move = 2;	// 오른쪽 이동
				else
					Move = 1;	// 왼쪽 이동
			}
		}
	}

	else if (other_x_size < other_z_size) {
		other_z1 = other_z + other_z - other_z_size;
		other_z2 = other_z + other_z + other_z_size;

		if (length(x, other_x, z, other_z1) <= other_z_size / 2 + 50) {
			Collision = true;
			if (length(x, other_x) >= length(z, other_z1)) {
				if (z > other_z1)
					Move = 4;	//앞으로이동
				else
					Move = 3;	//뒤로이동
			}
			else {
				if (x > other_x)
					Move = 2;	// 오른쪽 이동
				else
					Move = 1;	// 왼쪽 이동
			}
		}

		if (length(x, other_x, z, other_z2) <= other_z_size / 2 + 50) {
			Collision = true;
			if (length(x, other_x) >= length(z, other_z2)) {
				if (z > other_z2)
					Move = 4;	//앞으로이동
				else
					Move = 3;	//뒤로이동
			}
			else {
				if (x > other_x)
					Move = 2;	// 오른쪽 이동
				else
					Move = 1;	// 왼쪽 이동
			}
		}
	}
}
void Zombie::setHp(int n) { hp-=n; }
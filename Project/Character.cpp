#include <iostream>
#include <Windows.h>
#include <gl\glut.h>
#include "Character.h"
#include "Func.h"
#define SPEED 10
#define CHAR_SIZE 60
#define PI 3.141592

void Character::draw()
{
	glPushMatrix(); {
		if (hp > 0) {
			glColor4f(0, 32 / 255.0, 0, alpha);
			glTranslatef(x, y, z);            // 위치
			glRotatef(180 - yRotate, 0, 1, 0);
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
				glPushMatrix();                  // 다리
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
				glTranslatef(0, 50, 0);            // 몸통
				glPushMatrix(); {
					glPushMatrix(); {
						glPushMatrix(); {
							glScalef(1, 1.5, 0.3);
							glutSolidCube(40);

						}glPopMatrix();
						//               glRotatef(xRotate, 1, 0, 0);
						glTranslatef(30, 0, 0);
						glRotatef(100, 0, 0, 1);
						glScalef(1.5, 0.3, 0.5);
						glColor4f(253 / 255.0, 235 / 255.0, 187 / 255.0, alpha);
						glutSolidCube(40);               // 팔

					}glPopMatrix();
					glPushMatrix(); {
						if (isShot&&state == 2)
							glTranslatef(-1 + rand() % 3, -2 + rand() % 5, -2 + rand() % 5);
						if (state == 1) {
							gun->draw_bullet();
						}
						glTranslatef(-25, 30, 0);
						glRotatef(xRotate, 1, 0, 0);
						glTranslatef(0, 0, 20);
						glPushMatrix(); {
							glRotatef(100, 0, 0, 1);
							glRotatef(-80, 0, 1, 0);
							glScalef(1.5, 0.3, 0.5);
							glColor4f(253 / 255.0, 235 / 255.0, 187 / 255.0, alpha);
							glutSolidCube(40);
						}glPopMatrix();
						glTranslatef(-3, 30, 35);
						glRotatef(180, 0, 1, 0);
						glRotatef(15, 1, 0, 0);
						glRotatef(-5, 0, 0, 1);
						gun->draw();
						if (isShot&&state == 2) {
							glDisable(GL_LIGHTING);
							gun->draw_bullet();
							glEnable(GL_LIGHTING);
						}
					}glPopMatrix();

				}glPopMatrix();
				if (1 != state_Eye) {
					glTranslatef(0, 50, 0);
					glColor4f(253 / 255.0, 235 / 255.0, 187 / 255.0, alpha);
					glutSolidSphere(20, 30, 30);      // 머리
				}
			}
			glPushMatrix();
			{                              // 눈
				if (1 != state_Eye) {
					glPushMatrix();
					glColor4f(1, 1, 1, alpha);
					glTranslatef(-7, 5, 20);
					glRotatef(90, 1, 0, 0);
					glScalef(1, 0.1, 1);
					glutSolidSphere(5, 10, 10);
					glColor4f(0, 0, 0, alpha);
					glTranslatef(0, 30, 0);
					glutSolidSphere(2, 10, 10);

					glPopMatrix();
					glColor4f(1, 1, 1, alpha);
					glTranslatef(7, 5, 20);
					glRotatef(90, 1, 0, 0);
					glScalef(1, 0.1, 1);
					glutSolidSphere(5, 10, 10);
					glColor4f(0, 0, 0, alpha);
					glTranslatef(0, 30, 0);
					glutSolidSphere(2, 10, 10);
				}
			}
			glPopMatrix();

		}glPopMatrix();
	}
}

void Character::update(int yRotate, int xRotate)
{

	this->yRotate = yRotate;
	this->xRotate = xRotate;

}

void Character::move(float vx, float vy, float vz)
{
	if (Num_Vaccine == 4) exit(0);
	if (hp < 0) exit(0);

	int y_rotate = 0;
	if (yRotate < 0) y_rotate = 360 - (abs(yRotate) % 360);

	x += vx;
	y += vy;
	z += vz;

	x = max(-2500, min(2500, x));
	z = max(-2500, min(2500, z));



	if (0 == vx && 0 == vy && 0 == vz)
		leg_ceta = 0;
	else {
		leg_ceta += 3 * leg_e;
		if (leg_ceta >= 30)
		{
			leg_e = -1;
		}
		if (leg_ceta <= -30)
			leg_e = 1;
	}
}

void Character::setGun(int num) {
	if (gun == nullptr || state != num) {
		state = num;

		if (state == 1)   gun = new Pistol(0, 0, 0);
		else if (state == 2) gun = new FlameThrower(0, 0, 0);
		else if (state == 3) gun = new Grenade(0, 0, 0);
	}
}

void Character::update_gun()
{
	gun->update();
	if (isShot) {
		gun->shot(x, y, z);
		if (2 != state) {
			isShot = false;
		}
	}
	else {
		gun->stop_shot();
	}

}

void Character::shot()
{
	if (false == isShot) {
		isShot = true;
		if (state == 2)
			sound.pSound_FlameThrower();

	}
}

void Character::stop_shot()
{
	if (true == isShot) {
		isShot = false;
		gun->clear();
		if (state == 2)
			sound.sSound_FlameThrower();
	}
}

int Character::collision(float other_x, float other_y, float other_z, int other_x_size, int other_y_size, int other_z_size) {
	{

		int y_rotate = 0;
		if (yRotate < 0) y_rotate = 360 - (abs(yRotate) % 360);
		else y_rotate = yRotate % 360;
		float left_x = x - CHAR_SIZE;
		float right_x = x + CHAR_SIZE;
		float bottom_y = y - CHAR_SIZE;
		float top_y = y + CHAR_SIZE;
		float back_z = z - CHAR_SIZE;
		float front_z = z + CHAR_SIZE;

		//////////////////////////////

		float left_other_x = other_x - other_x_size;
		float right_other_x = other_x + other_x_size;
		float bottom_other_y = other_y - other_y_size;
		float top_other_y = other_y + other_y_size;
		float back_other_z = other_z - other_z_size;
		float front_other_z = other_z + other_z_size;

		// 1번 도형을 기준으로 충돌 체크 (충돌 면이 1번 기준)   //1,2,3,4,5,6 = 왼,오,뒤,앞,아래,위

		// 왼쪽
		if ((length(left_x, right_other_x)) <= SPEED) {
			if (bottom_y > top_other_y)
				return 0;
			if (top_y < bottom_other_y)
				return 0;
			if (back_z > front_other_z)
				return 0;
			if (front_z < back_other_z)
				return 0;
			//         std::cout << "왼쪽 y_rotate   " << y_rotate << std::endl;
			if (y_rotate >= 315 || y_rotate < 45)
				return 1;
			else if (y_rotate >= 45 && y_rotate < 135)
				return 3;
			else if (y_rotate >= 135 && y_rotate < 225)
				return 2;
			else return 4;
		}
		// 오른쪽
		if ((length(right_x, left_other_x)) <= SPEED) {
			if (bottom_y > top_other_y)
				return 0;
			if (top_y < bottom_other_y)
				return 0;
			if (back_z > front_other_z)
				return 0;
			if (front_z < back_other_z)
				return 0;
			//         std::cout << "오른쪽 y_rotate   " << y_rotate << std::endl;
			if (y_rotate >= 315 || y_rotate < 45)
				return 2;
			else if (y_rotate >= 45 && y_rotate < 135)
				return 4;
			else if (y_rotate >= 135 && y_rotate < 225)
				return 1;
			else return 3;

		}
		// 뒷쪽
		if ((length(back_z, front_other_z)) <= SPEED) {
			if (left_x > right_other_x)
				return 0;
			if (right_x < left_other_x)
				return 0;
			if (bottom_y > top_other_y)
				return 0;
			if (top_y < bottom_other_y)
				return 0;
			//         std::cout << "뒤쪽 y_rotate   " << y_rotate << std::endl;
			if (y_rotate >= 315 || y_rotate < 45)
				return 4;
			else if (y_rotate >= 45 && y_rotate < 135)
				return 1;
			else if (y_rotate >= 135 && y_rotate < 225)
				return 3;
			else return 2;
		}
		// 앞쪽
		if ((length(front_z, back_other_z)) <= SPEED) {
			if (left_x > right_other_x)
				return 0;
			if (right_x < left_other_x)
				return 0;
			if (bottom_y > top_other_y)
				return 0;
			if (top_y < bottom_other_y)
				return 0;
			//         std::cout << "앞쪽 y_rotate   " << y_rotate << std::endl;
			if (y_rotate >= 315 || y_rotate < 45)
				return 3;
			else if (y_rotate >= 45 && y_rotate < 135)
				return 2;
			else if (y_rotate >= 135 && y_rotate < 225)
				return 4;
			else return 1;
		}
		// 아래쪽
		if ((length(bottom_y, top_other_y)) <= SPEED) {
			if (left_x > right_other_x)
				return 0;
			if (right_x < left_other_x)
				return 0;
			if (back_z > front_other_z)
				return 0;
			if (front_z < back_other_z)
				return 0;
			return 5;
		}
		// 위쪽
		if ((length(top_y, bottom_other_y)) <= SPEED) {
			if (left_x > right_other_x)
				return 0;
			if (right_x < left_other_x)
				return 0;
			if (back_z > front_other_z)
				return 0;
			if (front_z < back_other_z)
				return 0;
			return 6;
		}
		return 0;
	}
}

void Character::setcollision(int side)
{
	collision_side = side;
}

bool Character::collision_item(float ix, float iy, float iz, int isize)
{
	if (length(x, ix, y, iy, z, iz) <= isize / 2 + CHAR_SIZE / 2)
		return true;
	return false;
}
void Character::set_item(int n) {
	sound.pSound_Item();
	if (n == 2)
		Num_Flame++;
	else if (n == 3)
		Num_Grenade++;
	else if (n == 4) {
		hp += 30;
		hp = min(100, hp);
	}
	else
		Num_Vaccine++;
}

bool Character::collision_bullet(float eye_x, float eye_y, float eye_z, float zx, float zy, float zz) {
	float bullet_x = 0;
	float bullet_y = 0;
	float bullet_z = 0;
	float y_rotate = 0;
	int x_e = 1;
	int z_e = 1;

	/*if (yRotate < 0 || yRotate > 180) {
	x_e = -1;
	y_rotate = 90 - (abs(yRotate) % 90);
	}
	else {
	x_e = 1;
	y_rotate = yRotate % 90;
	}
	if(yRotate <0)
	yRotate = 360 - (abs(yRotate) % 360);

	if (yRotate > 270 || yRotate < 90)
	z_e = 1;
	else
	z_e = -1;*/

	while (true) {
		bullet_x += sin(yRotate * PI / 180.0) * CHAR_SIZE;
		bullet_z -= cos(yRotate * PI / 180.0) * CHAR_SIZE;
		bullet_y -= tan(xRotate * PI / 180.0) * CHAR_SIZE;

		if (length(zx, eye_x + bullet_x, zy + CHAR_SIZE / 2, eye_y + bullet_y, zz, eye_z + bullet_z) <= CHAR_SIZE * 5)
		{
			return true;
		}
		if (length(eye_x, bullet_x, eye_z, bullet_z) >= 1500)
			break;
	}
	return false;


}
bool Character::collision_bullet(float zx, float zy, float zz)
{
	if (state == 2 && isShot == true)
		if (length(x, zx, y, zy, z, zz) <= 300)
			return true;
	return 0;
}


void Character::setHp(int n) {
	hp -= n;
	std::cout << "hp " << hp << std::endl;
}

void Character::change_stateEye()
{
	if (state_Eye == 1)
		state_Eye = 3;
	else
		state_Eye = 1;
}
#include <gl/glut.h>
#include <Windows.h>
#include <iostream>
#include <cmath>
#include "map.h"
#include "default_value.h"
#include "util.h"
//#include "Item.h"
#include "Character.h"
#include "Zombie.h"
#include "FlashLight.h"

#define WIDTH 800
#define HEIGHT 600
#define PI 3.141592

#pragma comment (lib, "glut32.lib")

//using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timerfunction(int value);
void Timerfunction_Clock(int value);
void Timerfunction_start(int value);
void Keyboard_Up(unsigned char key, int x, int y);
void Keyboard_Down(unsigned char key, int x, int y);
void SpecialKeyboard(int key, int x, int y);
void MouseMove(int x, int y);
void Mouse(int button, int state, int x, int y);
GLvoid SetupRC();
GLubyte* LoadDIBitmap(const char* filename, BITMAPINFO** info);


const int Start_EyePos[3] = { 2000,140,2000 };

double EYE[3], UP[3], AT[3]; // 카메라

GLfloat AmbientLight[] = { .5,.5,.5,.5 };
GLfloat DiffuseLight[] = { 1.,1.,1.,1. };
GLfloat SpecularLight[] = { 1.,1.,1.,1. };
GLfloat specref[] = { 1,1,1,1 };
GLfloat Sun_Pos[] = { 1000,1000,1000,0 };


float yRotate, xRotate;

GLuint texture[5];
GLubyte *pBytes;
BITMAPINFO *info;

Map map;
Tree** trees;
Container** containers;
Vaccine_g** vaccines;
Potion_g** potions;

unsigned int clock_second;
int sky;

Zombie** zombie;
Character* character;

int dir_X, dir_Z;
const int Mouse_X = WIDTH / 2;
const int Mouse_Y = HEIGHT / 2;

int Head_Z;
int tree_collision;
int container_collision;

bool Stop;
bool View = true;
int viewpoint;

Gun* gun;

pSound sound;

int Jump_Power;
int tmp_Y = 0;

int tmp_eyeY, tmp_eyeZ;

void main()
{

	SetupRC();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("좀비서바이벌");
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(Keyboard_Down);
	glutKeyboardUpFunc(Keyboard_Up);
	glutSpecialFunc(SpecialKeyboard);
	glutPassiveMotionFunc(MouseMove);
	glutMotionFunc(MouseMove);
	glutMouseFunc(Mouse);
	glutTimerFunc(30, Timerfunction, 1);
	glutTimerFunc(1000, Timerfunction_Clock, 2);
	glutTimerFunc(30, Timerfunction_start, 3);
	glutReshapeFunc(Reshape);

	sound.pSound_BGM();

	glutMainLoop();

	for (int i = 0; i < Num_Zombie; ++i)
		delete zombie[i];
	delete[] zombie;
}

GLvoid SetupRC()
{
	ShowCursor(FALSE);

	viewpoint = 10000;
	gun = new FlameThrower(0, 100, 0);

	dir_X = 0;
	dir_Z = 0;

	sky = DAY;
	clock_second = 0;

	xRotate = 0;
	yRotate = 0;

	UP[1] = 1;
	for (int i = 0; i < 3; i++) {
		EYE[i] = Start_EyePos[i];
		AT[i] = Start_EyePos[i];
	}
	AT[2] -= 300;

	character = new Character(2000, 0, 2000);
	character->setGun(1);

	int tmp_X, tmp_Z;

	zombie = new Zombie*[Num_Zombie];
	for (int i = 0; i < Num_Zombie; i++) {
		tmp_X = -Width_Ground / 2 + rand() % Width_Ground;
		tmp_Z = -Height_Ground / 2 + rand() % Height_Ground;
		while (true == map.collide_Object(tmp_X, 0, tmp_Z)) {
			tmp_X = rand() % Width_Ground - Width_Ground / 2;
			tmp_Z = rand() % Height_Ground - Height_Ground / 2;
		}
		zombie[i] = new Zombie(tmp_X, 0, tmp_Z);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    // 바탕색을 검정으로 지정
}

void draw_aim()
{
	glDisable(GL_LIGHTING);
	glPushMatrix(); {
		glTranslatef(EYE[0], EYE[1], EYE[2]);
		glTranslatef(0, 0, -10);
		glLineWidth(2);
		glColor4f(1, 0, 0, 1);

		glBegin(GL_LINES); {
			glVertex3f(0, 0.1, 0);
			glVertex3f(0, 0.3, 0);
			glVertex3f(0, -0.1, 0);
			glVertex3f(0, -0.3, 0);
			glVertex3f(0.1, 0, 0);
			glVertex3f(0.25, 0, 0);
			glVertex3f(-0.1, 0, 0);
			glVertex3f(-0.25, 0, 0);
		}glEnd();
	}glPopMatrix();
	// 체력 바
	glPushMatrix(); {
		glColor3f(1, 0, 0);
		glTranslatef(EYE[0], EYE[1], EYE[2]);
		glTranslatef(-5.5, 4.5, -10);
		for (int i = 0; i < character->getHp(); ++i) {
			glTranslatef(0.025, 0, 0);
			glBegin(GL_LINES); {
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, 1.0f, 0.0f);
			}glEnd();
		}
	}glPopMatrix();
	// 백신
	glPushMatrix(); {
		glTranslatef(EYE[0], EYE[1], EYE[2]);
		glTranslatef(-6.5, -4.5, -10);
		for (int i = 0; i < character->getVaccine(); ++i) {
			glTranslatef(0.8, 0, 0);
			glColor3f(1, 1, 1);
			glBegin(GL_POLYGON); {
				glVertex3f(0, 0, 0);
				glVertex3f(0.5, 0, 0);
				glVertex3f(0.5, 1, 0);
				glVertex3f(0, 1, 0);
			}glEnd();
			glColor3f(1, 0, 0);
			glBegin(GL_POLYGON); {
				glVertex3f(0, 1, 0);
				glVertex3f(0.5, 1, 0);
				glVertex3f(0.5, 1.5, 0);
				glVertex3f(0, 1.5, 0);
			}glEnd();
		}
	}glPopMatrix();
	glEnable(GL_LIGHTING);
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix(); {
		if (View)
			gluLookAt(0, viewpoint, 0, 0, 0, 0, 0, 0, -90);
		else
			gluLookAt(EYE[0], EYE[1] + tmp_Y + tmp_eyeY, EYE[2] + tmp_eyeZ, AT[0], AT[1] + tmp_Y, AT[2], UP[0], UP[1], UP[2]);
		glPushMatrix();
		glTranslatef(0, tmp_Y, 0);
		draw_aim();
		glPopMatrix();

		glTranslatef(EYE[0], EYE[1] + tmp_Y, EYE[2]);
		glRotatef(xRotate, 1, 0, 0);
		glTranslatef(0, 0, -Head_Z);
		glRotatef(yRotate, 0, 1, 0);
		glTranslatef(-EYE[0], -EYE[1] - tmp_Y, -EYE[2] + Head_Z);


		map.draw(texture[0], texture[3]);
		trees = map.getTree();
		containers = map.getContainer();
		vaccines = map.getVaccine();

		potions = map.getPotion();


		glPushMatrix();
		glTranslatef(0, tmp_Y, 0);
		character->draw();
		glPopMatrix();

		character->setcollision(0);

		//   나무 충돌체크
		for (int i = 0; i < Num_Tree; ++i) {
			tree_collision = character->collision(trees[i]->getX(), trees[i]->getY(), trees[i]->getZ(), 75, 500, 75);
			if (tree_collision)
			{
				character->setcollision(tree_collision);
				break;
			}

		}
		//   컨테이너 충돌체크
		for (int i = 0; i < Num_Container; ++i) {
			if (containers[i]->getyRotate() == 0)
				container_collision = character->collision(containers[i]->getX(), containers[i]->getY(), containers[i]->getZ(), xSize_Container / 2 + 15, ySize_Container, zSize_Container / 2 + 30);
			else
				container_collision = character->collision(containers[i]->getX(), containers[i]->getY(), containers[i]->getZ(), zSize_Container / 2 + 30, ySize_Container / 2, xSize_Container / 2 + 15);

			if (container_collision)
			{
				character->setcollision(container_collision);
				break;
			}
		}
		//   백신 충돌체크
		for (int i = 0; i < Num_Vaccine; ++i) {
			if (character->collision_item(vaccines[i]->getX(), vaccines[i]->getY(), vaccines[i]->getZ(), Size_Vaccine)) {
				character->set_item(5);
				vaccines[i]->setDraw();
				break;
			}
		}


		//   포션 충돌체크
		for (int i = 0; i < Num_Potion; ++i) {
			if (character->collision_item(potions[i]->getX(), potions[i]->getY(), potions[i]->getZ(), Size_Potion)) {
				character->set_item(4);
				potions[i]->setDraw();
				break;
			}
		}


		// SUN
		glPushMatrix(); {
			glEnable(GL_LIGHT0);
			glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
			glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
			glLightfv(GL_LIGHT0, GL_POSITION, Sun_Pos);
			glTranslatef(Sun_Pos[0], Sun_Pos[1], Sun_Pos[2]);
			glColor3f(1, 1, 1);
			glutSolidSphere(10, 20, 20);
		}glPopMatrix();
		// SUN

		// SKY
		glPushMatrix(); {
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);

			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			if (NIGHT == sky)
				glBindTexture(GL_TEXTURE_2D, texture[1]);
			else
				glBindTexture(GL_TEXTURE_2D, texture[2]);
			glutSolidSphere(Width_Ground, 10, 10);

			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_TEXTURE_2D);
		}glPopMatrix();
		// SKY

		glPushMatrix(); {
			glColor3f(1, 0, 0);
			glutSolidCube(20);
		}glPopMatrix();

		glPushMatrix(); {
			for (int i = 0; i < Num_Zombie; i++) {
				zombie[i]->set_collision(0);
				for (int j = 0; j < Num_Container; ++j) {
					if (containers[j]->getyRotate() == 0)
						(zombie[i]->collision(containers[j]->getX(), containers[j]->getY(), containers[j]->getZ(), xSize_Container / 2 + 15, ySize_Container, zSize_Container / 2 + 30));
					else
						(zombie[i]->collision(containers[j]->getX(), containers[j]->getY(), containers[j]->getZ(), zSize_Container / 2 + 30, ySize_Container / 2, xSize_Container / 2 + 15));
					if (zombie[i]->get_collision())
						break;
				}
				for (int j = 0; j < Num_Tree; ++j) {
					(zombie[i]->collision(trees[j]->getX(), trees[j]->getY(), trees[j]->getZ(), 75, 500, 75));
					if (zombie[i]->get_collision())
						break;
				}
				if (character->getGun() == 2) {
					if (character->collision_bullet(zombie[i]->getX(), zombie[i]->getY(), zombie[i]->getZ()))
					{
						zombie[i]->setHp(1);
					}
				} 
				if (zombie[i]->update(character->getX(), character->getY(), character->getZ()))
					if (sky == DAY)
						character->setHp(1);
					else
						character->setHp(2);
				zombie[i]->draw();
			}
		}glPopMatrix();

	}glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(60.f, w / h, 1., 10000.);


	glMatrixMode(GL_MODELVIEW);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 64);

	glGenTextures(5, texture);

	glBindTexture(GL_TEXTURE_2D, texture[0]); {
		pBytes = LoadDIBitmap(".\\resource\\Container.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 299, 114, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, texture[1]); {
		pBytes = LoadDIBitmap(".\\resource\\Night.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 789, 621, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, texture[2]); {
		pBytes = LoadDIBitmap(".\\resource\\Day.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 1192, 551, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

}

void Timerfunction_Clock(int value)
{
	if (++clock_second % 360 == 0) {
		sky = DAY;
		clock_second = 0;
	}
	else if (clock_second % 180 == 0) {
		sky = NIGHT;
	}
	std::cout << clock_second << std::endl;
	glutPostRedisplay();                        // 화면 재 출력
	if (!Stop)
		glutTimerFunc(1000, Timerfunction_Clock, 2);     // 타이머함수 재 설정
}

void Timerfunction(int value)
{
	// 사운드
	sound.update_Sound();
	// 사운드



	// 이동

	if (character->getcollision() == 1)
		if (dir_X == -1)
			dir_X = 0;
	if (character->getcollision() == 2)
		if (dir_X == 1)
			dir_X = 0;
	if (character->getcollision() == 3)
		if (dir_Z == 1)
			dir_Z = 0;
	if (character->getcollision() == 4)
		if (dir_Z == -1)
			dir_Z = 0;


	AT[0] += 5 * dir_X *cos(yRotate*PI / 180);
	EYE[0] += 5 * dir_X*cos(yRotate*PI / 180);
	AT[2] += 5 * dir_X *sin(yRotate*PI / 180);
	EYE[2] += 5 * dir_X*sin(yRotate*PI / 180);


	AT[2] += 5 * dir_Z *cos(yRotate*PI / 180);
	EYE[2] += 5 * dir_Z*cos(yRotate*PI / 180);
	AT[0] += 5 * dir_Z *sin(-yRotate*PI / 180);
	EYE[0] += 5 * dir_Z*sin(-yRotate*PI / 180);

	int tmp_X = EYE[0] * (-sin(yRotate*PI / 180)) + EYE[2] * cos(yRotate*PI / 180);
	int tmp_Z = EYE[0] * cos(yRotate*PI / 180) + EYE[2] * sin(yRotate*PI / 180);


	Jump_Power -= 2;
	tmp_Y = std::max(0, tmp_Y + Jump_Power);

	character->move(5 * dir_X *cos(yRotate*PI / 180) + 5 * dir_Z*sin(-yRotate*PI / 180), 0, 5 * dir_X*sin(yRotate*PI / 180) + 5 * dir_Z*cos(yRotate*PI / 180));
	// 이동

	EYE[0] = std::max(-2500.0, std::min(2500.0, EYE[0]));
	EYE[2] = std::max(-2500., std::min(2500., EYE[2]));
	AT[0] = std::max(-2500., std::min(2500., AT[0]));
	AT[2] = std::max(-2500., std::min(2500., AT[2]));


	// 마우스 고정
	glutWarpPointer(Mouse_X, Mouse_Y);
	// 마우스 고정

	// 총알
	character->update_gun();
	// 총알

	glutPostRedisplay();                        // 화면 재 출력
	if (!Stop)
		glutTimerFunc(30, Timerfunction, 1);     // 타이머함수 재 설정
}

void MouseMove(int x, int y)
{
	yRotate += atan2f(x - Mouse_X, 300) * 10;
	xRotate = std::max(-90.f, std::min(90.f, xRotate + atan2f(y - Mouse_Y, 300.) * 10));
	EYE[2] -= Head_Z;
	Head_Z = -50 * sin(xRotate*PI / 180);
	EYE[2] += Head_Z;
	character->update(yRotate, xRotate);
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			character->shot();
			if (character->getGun() == 1) {
				for (int i = 0; i < Num_Zombie; ++i)
					if (character->collision_bullet(EYE[0], EYE[1], EYE[2], zombie[i]->getX(), zombie[i]->getY(), zombie[i]->getZ()))
					{
						zombie[i]->setHp(3);
						break;
					}
			}

		}
		if (state == GLUT_UP) {
			character->stop_shot();
		}
	}
}

void Keyboard_Down(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'w':case 'W':
		dir_Z = -1;
		break;
	case's':case 'S':
		dir_Z = 1;
		break;
	case'd':case 'D':
		dir_X = 1;
		break;
	case'a':case 'A':
		dir_X = -1;
		break;
	case 'q':
		sound.Release();
		std::exit(0);
		break;
	case '1':
		character->setGun(1);
		break;
	case '2':
		character->setGun(2);
		break;
		//case '3':
		//   character->setGun(3);
		//   break;
	case 't':case'T':
		if (tmp_eyeZ == 0) {
			tmp_eyeZ = 200;
			tmp_eyeY = 100;
		}
		else {
			tmp_eyeZ = 0;
			tmp_eyeY = 0;
		}
		character->change_stateEye();
		break;
	}
}

void Keyboard_Up(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'w':case 'W':
		if (-1 == dir_Z)
			dir_Z = 0;
		break;
	case's':case 'S':
		if (1 == dir_Z)
			dir_Z = 0;
		break;
	case'd':case 'D':
		if (1 == dir_X)
			dir_X = 0;
		break;
	case'a':case 'A':
		if (-1 == dir_X)
			dir_X = 0;
		break;
	case 'j':
		Jump_Power = 20;
		break;
	}
}

void SpecialKeyboard(int key, int x, int y)
{
	
}

GLubyte* LoadDIBitmap(const char* filename, BITMAPINFO** info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;

	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}

	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}

	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		std::exit(0);
		return NULL;
	}

	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
			(*info)->bmiHeader.biBitCount + 7) / 8.f *
		abs((*info)->bmiHeader.biHeight);

	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}
void Timerfunction_start(int value)
{
	viewpoint -= 200;
	if (viewpoint == 0) {
		View = false;
	}
	if (View == true)
		glutTimerFunc(30, Timerfunction_start, 3);     // 타이머함수 재 설정

}
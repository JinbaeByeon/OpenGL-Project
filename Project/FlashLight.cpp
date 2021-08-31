#include <gl\glut.h>
#include <math.h>
#include "FlashLight.h"
#include "Func.h"

void FlashLight::draw() {
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(0.5, 0.5, 0.5);
	cylinder(0, 0, 0, 10, 30);
	glTranslatef(0, 0, 30);
	glColor3f(0.7, 0.7, 0.7);
	cylinder(0, 0, 0, 11, 10);
	glPopMatrix();

}

void FlashLight::flash(float vx, float vy, float vz) {
	GLfloat LightPos[4]{ x+30,y-30,z,1 };
	GLfloat SpotlightPos[3]{ vx,vy,vz };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION,SpotlightPos);
	glEnable(GL_COLOR_MATERIAL);

}


#include <gl/glut.h>
#include "ground.h"
#include "default_value.h"

Ground::Ground() :Width(Width_Ground), Height(Height_Ground)
{

}

void Ground::draw(unsigned int texture) const
{
	float p[2][2][3] = {
		{{-Width / 2,0,Height/2},{Width / 2,0,Height/2} } ,
		{ { -Width / 2,0,-Height/2 },{ Width / 2,0,-Height/2 } }
	};

	glPushMatrix(); {

		glColor3fv(Color_Ground);
		glMap2f(GL_MAP2_VERTEX_3, 0.f, 1.f, 3, 2, 0.f, 1.f, 6, 2, &p[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		glMapGrid2f(100, 0.f, 1.f, 100, 0.f, 1.f);
		glEvalMesh2(GL_FILL, 0, 100, 0, 100);

		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, texture);
		//glBegin(GL_QUADS);
		//glTexCoord2f(0.f,0.f);
		//glVertex3f(-Width / 2, 1, Height / 2);
		//glTexCoord2f(1.f, 0.f);
		//glVertex3f(Width / 2, 1, Height / 2);
		//glTexCoord2f(1.f, 1.f);
		//glVertex3f(Width / 2, 1, -Height / 2);
		//glTexCoord2f(0.f, 1.f);
		//glVertex3f(-Width / 2, 1, -Height / 2);
		//glEnd();
		//glDisable(GL_TEXTURE_2D);
	}glPopMatrix();
}
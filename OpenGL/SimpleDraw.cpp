#include "stdafx.h"
#include "SimpleDraw.h"

void SimpleDrawTest::display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 0.0, 1.0);
	//glLineWidth(5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(45, 0, 0, 1);
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex3i(5, 5, 0);
	glVertex3i(45, 5, 0);
	glVertex3i(45, 45, 0);
	glVertex3i(5, 45, 0);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3i(45, 5, 0);
	glVertex3i(55, 25, 0);
	glVertex3i(55, 65, 0);
	glVertex3i(45, 45, 0);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

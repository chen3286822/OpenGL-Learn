#include "stdafx.h"
#include "CullFace.h"


void CullFaceTest::display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);/* clear all pixels   */

	//裁剪背面，使多边形看不到了
	//因为多边形顺时针绘制，背面对着我们
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3i(55, 65, 0);
	glVertex3i(55, 25, 0);
	glVertex3i(5, 5, 0);
	glVertex3i(5, 45, 0);
	glEnd();
	glDisable(GL_CULL_FACE);
	
	glFlush();
}
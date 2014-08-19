#include "stdafx.h"
#include "StrippleLine.h"

void StrippleLineTest::display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);/* clear all pixels   */

	glLineStipple(1, 0x7777);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex3i(5, 85, 0);
	glVertex3i(95, 85, 0);
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	glFlush();
}
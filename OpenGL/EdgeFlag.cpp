#include "stdafx.h"
#include "EdgeFlag.h"

void EdgeFlagTest::display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);/* clear all pixels   */

	//����ض�����Ϊ�Ǳ߽�㣬ʹ�û��ƶ����ʱ�Ըõ�Ϊ���ı߲������
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);
	glEdgeFlag(GL_TRUE);
	glVertex3i(65, 5, 0);
	glEdgeFlag(GL_FALSE);
	glVertex3i(85, 5, 0);
	glEdgeFlag(GL_TRUE);
	glVertex3i(85, 45, 0);
	glEnd();

	glFlush();
}

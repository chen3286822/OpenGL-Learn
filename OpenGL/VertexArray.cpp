#include "stdafx.h"
#include "VertexArray.h"

void VertexArrayTest::display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);/* clear all pixels   */

	//混合顶点数组绘制图形
	static GLfloat pentagon[] = {
		65.0, 55.0, 0.0, 1.0, 0.0, 0.0,
		75.0, 55.0, 0.0, 0.0, 1.0, 0.0,
		80.0, 65.0, 0.0, 0.0, 0.0, 1.0,
		70.0, 75.0, 0.0, 1.0, 1.0, 0.0,
		60.0, 65.0, 0.0, 0.0, 1.0, 1.0
	};
	glPolygonMode(GL_FRONT, GL_FILL);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, 6 * sizeof(GL_FLOAT), &pentagon[3]);
	glVertexPointer(3, GL_FLOAT, 6 * sizeof(GL_FLOAT), &pentagon[0]);
	// 	glBegin(GL_POLYGON);
	// 	glArrayElement(0);
	// 	glArrayElement(1);
	// 	glArrayElement(2);
	// 	glArrayElement(3);
	// 	glArrayElement(4);
	// 	glEnd();
	//或者用索引
	static GLbyte index[] = { 0, 1, 2, 3, 4 };
	glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, index);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glFlush();
}
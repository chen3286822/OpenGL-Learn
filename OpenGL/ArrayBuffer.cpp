#include "stdafx.h"
#include "ArrayBuffer.h"

void ArrayBufferTest::init(void)
{
	glewInit();
	glClearColor(0.0, 0.0, 0.0, 0.0);/* select clearing color   */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 300.0, 0.0, 300.0, -10.0, 10.0);/* initialize viewing values   */
}

void ArrayBufferTest::display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);/* clear all pixels   */

	//使用缓冲区对象
	static GLfloat vertices[][2] = {
		{100.0, 100.0},
		{200.0, 100.0},
		{150.0, 150.0}
	};
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexPointer(2, GL_FLOAT, 0, (GLvoid*)0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glBegin(GL_TRIANGLES);
	glArrayElement(0);
	glArrayElement(1);
	glArrayElement(2);
	glEnd();
	glDeleteBuffers(1, &buffer);

	glFlush();
}
#include "stdafx.h"
#include "RecursiveSubdivision.h"

#define X 5.2573
#define Z 8.5065
void RecursiveSubdivisionTest::init(void)
{
	glewInit();
	glClearColor(0.0, 0.0, 0.0, 0.0);/* select clearing color   */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);/* initialize viewing values   */
}

void RecursiveSubdivisionTest::normalize10(GLfloat* v)
{
	GLfloat normL = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] = v[0] * 10 /normL;
	v[1] = v[1] * 10 /normL;
	v[2] = v[2] * 10 /normL;
}

void RecursiveSubdivisionTest::drawTriangle(GLfloat* v1, GLfloat* v2, GLfloat* v3)
{
	//计算法线向量
	GLfloat vec1[3], vec2[3], norm[3];
	for (int j = 0; j < 3; ++j)
	{
		vec1[j] = v1[j] - v2[j];
		vec2[j] = v3[j] - v2[j];
	}
	//v1 和 v2 叉积得到面的法线向量
	norm[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	norm[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	norm[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
	// 单位化法线向量
	normalize10(norm);

	glBegin(GL_TRIANGLES);
	glNormal3fv(norm);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
	glEnd();
}

void RecursiveSubdivisionTest::subDivision(GLfloat* v1, GLfloat* v2, GLfloat* v3, GLint depth)
{
	GLfloat v12[3], v23[3], v13[3];

	if (depth == 0)
	{
		drawTriangle(v1, v2, v3);
		return;
	}

	for (GLint i = 0; i < 3; ++i)
	{
		v12[i] = (v1[i] + v2[i]) / 2;
		v23[i] = (v2[i] + v3[i]) / 2;
		v13[i] = (v1[i] + v3[i]) / 2;
	}
	normalize10(v12);
	normalize10(v23);
	normalize10(v13);
	subDivision(v1, v12, v13, depth - 1);
	subDivision(v2, v23, v12, depth - 1);
	subDivision(v3, v13, v23, depth - 1);
	subDivision(v12, v23, v13, depth - 1);
}

void RecursiveSubdivisionTest::display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);/* clear all pixels   */

	//绘制一个20面体
	static GLfloat vData[12][3] =
	{
		{ -X, 0.0, Z }, { X, 0.0, Z }, { -X, 0.0, -Z }, { X, 0.0, -Z },
		{ 0.0, Z, X }, { 0.0, Z, -X }, { 0.0, -Z, X }, { 0.0, -Z, -X },
		{ Z, X, 0.0 }, { -Z, X, 0.0 }, { Z, -X, 0.0 }, { -Z, -X, 0.0 }
	};
	static GLuint tindices[20][3] =
	{
		{ 1, 4, 0 }, { 4, 9, 0 }, { 4, 5, 9 }, { 8, 5, 4 }, { 1, 8, 4 },
		{ 1, 10, 8 }, { 10, 3, 8 }, { 8, 3, 5 }, { 3, 2, 5 }, { 3, 7, 2 },
		{ 3, 10, 7 }, { 10, 6, 7 }, { 6, 11, 7 }, { 6, 0, 11 }, { 6, 1, 0 },
		{ 10, 1, 6 }, { 11, 0, 9 }, { 2, 11, 9 }, { 5, 2, 9 }, { 11, 2, 7 },
	};
	
	for (int i = 0; i < 20; i++)
	{
		subDivision(&vData[tindices[i][0]][0], &vData[tindices[i][1]][0], &vData[tindices[i][2]][0], 1);
	}
	//使用glDrawElements 一次性绘制所有面
	// 	glEnableClientState(GL_VERTEX_ARRAY);
	// 	glVertexPointer(3, GL_FLOAT, 0, vData);
	// 	glDrawElements(GL_TRIANGLES, 60, GL_UNSIGNED_INT, tindices);
	// 	glDisableClientState(GL_VERTEX_ARRAY);
	glFlush();/* start processing buffered OpenGL routines   */
}
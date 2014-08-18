// OpenGL.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>

#pragma comment(lib, "glew32s.lib")

#define X 5.2573
#define Z 8.5065
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);/* clear all pixels   */
	/*
	glColor3f(0.0, 0.0, 1.0);
	//glLineWidth(5.0);
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
	*/

	/*
	//裁剪背面，使第三个多边形看不到了
	//因为第三个多边形顺时针绘制，背面对着我们
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



	glLineStipple(1, 0x7777);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex3i(5, 85, 0);
	glVertex3i(95, 85, 0);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	*/

	/*
	//标记特定顶点为非边界点，使得绘制多边形时以该点为起点的边不会绘制
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);
	glEdgeFlag(GL_TRUE);
	glVertex3i(65, 5, 0);
	glEdgeFlag(GL_FALSE);
	glVertex3i(85, 5, 0);
	glEdgeFlag(GL_TRUE);
	glVertex3i(85, 45, 0);
	glEnd();
	*/

	/*
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
	*/

	/*
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
	*/

	//绘制一个20面体
	static GLfloat vData[12][3] =
	{
		{ -X, 0.0, Z }, { X, 0.0, Z }, { -X, 0.0, -Z }, { X, 0.0, -Z },
		{ 0.0, Z, X }, { 0.0, Z, -X }, { 0.0, -Z, X }, {0.0, -Z, -X},
		{ Z, X, 0.0 }, { -Z, X, 0.0 }, { Z, -X, 0.0 }, {-Z, -X, 0.0}
	};
	static GLuint tindices[20][3] = 
	{
		{1, 4, 0}, {4, 9, 0}, {4, 5, 9}, {8, 5, 4}, {1, 8, 4},
		{1, 10, 8}, {10, 3, 8}, {8, 3, 5}, {3, 2, 5}, {3, 7, 2},
		{3, 10, 7}, {10, 6, 7}, {6, 11, 7}, {6, 0, 11}, {6, 1, 0},
		{10, 1, 6}, {11, 0, 9}, {2, 11, 9}, {5, 2, 9}, {11, 2, 7},
	};
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 20;i++)
	{
		//计算法线向量
		GLfloat v1[3], v2[3], norm[3];
		for (int j = 0; j < 3; ++j)
		{
			v1[j] = vData[tindices[i][0]][j] - vData[tindices[i][1]][j];
			v2[j] = vData[tindices[i][2]][j] - vData[tindices[i][1]][j];
		}
		//v1 和 v2 叉积得到面的法线向量
		norm[0] = v1[1] * v2[2] - v1[2] * v2[1];
		norm[1] = v1[2] * v2[0] - v1[0] * v2[2];
		norm[2] = v1[0] * v2[1] - v1[1] * v2[0];
		// 单位化法线向量
		GLfloat normL = sqrt(norm[0] * norm[0] + norm[1] * norm[1] + norm[2] * norm[2]);
		norm[0] /= normL;
		norm[1] /= normL;
		norm[2] /= normL;
		glNormal3fv(norm);
		glVertex3fv(&vData[tindices[i][0]][0]);
		glVertex3fv(&vData[tindices[i][1]][0]);
		glVertex3fv(&vData[tindices[i][2]][0]);
	}
	glEnd();
	//使用glDrawElements 一次性绘制所有面
// 	glEnableClientState(GL_VERTEX_ARRAY);
// 	glVertexPointer(3, GL_FLOAT, 0, vData);
// 	glDrawElements(GL_TRIANGLES, 60, GL_UNSIGNED_INT, tindices);
// 	glDisableClientState(GL_VERTEX_ARRAY);
	glFlush();/* start processing buffered OpenGL routines   */
}

void init(void)
{
	glewInit();
	glClearColor(0.0, 0.0, 0.0, 0.0);/* select clearing color   */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);/* initialize viewing values   */
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);/*Declare initial display mode(single buffer and RGBA).*/
	glutInitWindowSize(250, 250); /*Declare initial window size.*/
	glutInitWindowPosition(100, 100);/*Declare initial window position.*/
	glutCreateWindow("hello");/*Open window with "hello"in its title bar.*/
	init();/*Call initialization routines.*/
	glutDisplayFunc(display); /*Register callback function to display graphics.*/
	glutMainLoop();/*Enter main loop and process events.*/
	return 0;    /* ANSI C requires main to return int. */
}
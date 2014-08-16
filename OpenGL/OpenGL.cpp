// OpenGL.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <GL/glut.h>

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);/* clear all pixels   */
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

	glFlush();/* start processing buffered OpenGL routines   */
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);/* select clearing color   */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0, -50.0, 50.0);/* initialize viewing values   */
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
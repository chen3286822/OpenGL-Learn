// OpenGL.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "OpenGL.h"

#include "ArrayBuffer.h"
#include "Cube.h"
#include "CullFace.h"
#include "EdgeFlag.h"
#include "RecursiveSubdivision.h"
#include "ShaderTest.h"
#include "SimpleDraw.h"
#include "StrippleLine.h"
#include "VertexArray.h"

OpenGLTest* g_Test;

void OpenGLTest::init(void)
{
	glewInit();
	glClearColor(0.0, 0.0, 0.0, 0.0);/* select clearing color   */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0, -10.0, 10.0);/* initialize viewing values   */
}

void OpenGLTest::reshape(GLint w, GLint h)
{
	GLint length = w > h ? h : w;
	glViewport(0, 0, (GLsizei)length, (GLsizei)length);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0, -10.0, 10.0);
}

void OpenGLTest::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLTest::keyboard(GLubyte key, GLint x, GLint y)
{

}


void gInit(void)
{
	g_Test->init();
}

void gDisplay(void)
{
	g_Test->display();
}

void gReshape(GLint w, GLint h)
{
	g_Test->reshape(w, h);
}

void gKeyboard(GLubyte key, GLint x, GLint y)
{
	g_Test->keyboard(key, x, y);
}


void gRelease()
{
	delete g_Test;
}

int main(int argc, char** argv)
{
	//注册释放资源函数
	atexit(gRelease);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);/*Declare initial display mode(single buffer and RGBA).*/
	glutInitWindowSize(100, 100); /*Declare initial window size.*/
	glutInitWindowPosition(100, 100);/*Declare initial window position.*/
	glutCreateWindow("hello");/*Open window with "hello"in its title bar.*/

	const GLubyte * name = glGetString(GL_VENDOR);
	const GLubyte * biaoshifu = glGetString(GL_RENDERER);
	const GLubyte * OpenGLVersion = glGetString(GL_VERSION);
	const GLubyte * gluVersion = gluGetString(GLU_VERSION);
	printf("OpenGL实现厂商的名字：%s\n", name);
	printf("渲染器标识符：%s\n", biaoshifu);
	printf("OOpenGL实现的版本号：%s\n", OpenGLVersion);
	printf("OGLU工具库版本：%s\n", gluVersion);

	g_Test = RecursiveSubdivisionTest::create();
	gInit();
	glutDisplayFunc(gDisplay); /*Register callback function to display graphics.*/
	glutReshapeFunc(gReshape);
	glutKeyboardFunc(gKeyboard);
	glutMainLoop();/*Enter main loop and process events.*/

	
	return 0;    /* ANSI C requires main to return int. */
}
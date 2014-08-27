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

#define GLUT_DISABLE_ATEXIT_HACK

//显示 回调函数
void OnDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0.7f, 0.7f, 0.7f);
	glutSolidSphere(50.0f, 50.0f, 50.0f); //绘制一个浅灰色的球体

	glutSwapBuffers();

}
//窗口尺寸变化后的回调函数
void OnReShape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION); //将当前矩阵指定为投影模式
	glLoadIdentity();

	GLfloat aspect = (float)w / (float)h;

	if (w <= h)
	{
		glOrtho(-100.0f, 100.0f, -100.0f / aspect, 100.0f / aspect, -100.0f, 100.0f);
	}
	else
	{
		glOrtho(-100.0f*aspect, 100.0f*aspect, -100.0f, 100.0f, -100.0f, 100.0f);
	}
}
//按键处理回调函数
void OnKey(GLubyte key, GLint x, GLint y)
{
	switch (key)
	{
	case 0x31:                    //打开红色射灯
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glEnable(GL_LIGHT1);
		break;

	case 0x32:                    //打开绿色射灯
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT3);
		glEnable(GL_LIGHT2);
		break;

	case 0x33:                    //打开蓝色射灯
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT3);
		break;

	case 0x34:                    //打开红色主光源
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT4);
		break;

	default:                    //关闭所有射灯并将主光源换成白色
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT4);
		glEnable(GL_LIGHT0);
		break;

	}
	glutPostRedisplay();
}
//设置渲染环境
void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}
//设置光照
void SetupLights()
{
// 	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };//白色主光源环境光
// 	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };//白色主光源漫反射
 	GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };//白色主光源镜面光

// 	GLfloat redAmbiLight[] = { 0.2f, 0.0f, 0.0f, 1.0f };//红色主光源环境光
// 	GLfloat redDiffLight[] = { 0.8f, 0.0f, 0.0f, 1.0f };//红色主光源漫反射
// 	GLfloat redSpecLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };//红色主光源镜面光

//	GLfloat lightPos[] = { 50.0f, 120.0f, 120.0f, 1.0f };	//光源位置
	GLfloat spotLightPos[] = { 0.0f, 0.0f, 200.0f, 1.0f };	//射灯位置
	GLfloat spotDir[] = { 0.0f, 0.0f, -1.0f };			//射灯方向

	GLfloat redLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };		//红色光源
	//GLfloat greenLight[] = { 0.0f, 1.0f, 0.0f, 1.0f };		//绿色光源
	//GLfloat blueLight[] = { 0.0f, 0.0f, 1.0f, 1.0f };		//蓝色光源


 	glEnable(GL_LIGHTING);							//启用光照
// 	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);	//设置环境光源
// 	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);	//设置漫反射光源
// 	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);	//设置镜面光源
// 	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);		//设置灯光位置
// 	glEnable(GL_LIGHT0);							//打开白色主光源

// 	glLightfv(GL_LIGHT4, GL_AMBIENT, redAmbiLight);
// 	glLightfv(GL_LIGHT4, GL_DIFFUSE, redDiffLight);
// 	glLightfv(GL_LIGHT4, GL_SPECULAR, redSpecLight);
// 	glLightfv(GL_LIGHT4, GL_POSITION, lightPos);

	glLightfv(GL_LIGHT1, GL_SPECULAR, redLight);		//红色射灯
	glLightfv(GL_LIGHT1, GL_POSITION, spotLightPos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 85.0f);
	glEnable(GL_LIGHT1);


	glEnable(GL_COLOR_MATERIAL);						//启用材质的颜色跟踪
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);	//指定材料着色的面
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);	//指定材料对镜面光的反应
	glMateriali(GL_FRONT, GL_SHININESS, 100);				//指定反射系数
}
/*
// main
void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 480);
	glutCreateWindow("OpenGL光源");

	glutReshapeFunc(OnReShape);
	glutDisplayFunc(OnDisplay);
	glutKeyboardFunc(OnKey);

	SetupRC();
	SetupLights();

	glutMainLoop();
}*/
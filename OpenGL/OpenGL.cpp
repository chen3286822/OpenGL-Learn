// OpenGL.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//ע���ͷ���Դ����
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
	printf("OpenGLʵ�ֳ��̵����֣�%s\n", name);
	printf("��Ⱦ����ʶ����%s\n", biaoshifu);
	printf("OOpenGLʵ�ֵİ汾�ţ�%s\n", OpenGLVersion);
	printf("OGLU���߿�汾��%s\n", gluVersion);

	g_Test = RecursiveSubdivisionTest::create();
	gInit();
	glutDisplayFunc(gDisplay); /*Register callback function to display graphics.*/
	glutReshapeFunc(gReshape);
	glutKeyboardFunc(gKeyboard);
	glutMainLoop();/*Enter main loop and process events.*/

	
	return 0;    /* ANSI C requires main to return int. */
}

#define GLUT_DISABLE_ATEXIT_HACK

//��ʾ �ص�����
void OnDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0.7f, 0.7f, 0.7f);
	glutSolidSphere(50.0f, 50.0f, 50.0f); //����һ��ǳ��ɫ������

	glutSwapBuffers();

}
//���ڳߴ�仯��Ļص�����
void OnReShape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION); //����ǰ����ָ��ΪͶӰģʽ
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
//��������ص�����
void OnKey(GLubyte key, GLint x, GLint y)
{
	switch (key)
	{
	case 0x31:                    //�򿪺�ɫ���
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glEnable(GL_LIGHT1);
		break;

	case 0x32:                    //����ɫ���
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT3);
		glEnable(GL_LIGHT2);
		break;

	case 0x33:                    //����ɫ���
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT3);
		break;

	case 0x34:                    //�򿪺�ɫ����Դ
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT4);
		break;

	default:                    //�ر�������Ʋ�������Դ���ɰ�ɫ
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT4);
		glEnable(GL_LIGHT0);
		break;

	}
	glutPostRedisplay();
}
//������Ⱦ����
void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}
//���ù���
void SetupLights()
{
// 	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };//��ɫ����Դ������
// 	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };//��ɫ����Դ������
 	GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };//��ɫ����Դ�����

// 	GLfloat redAmbiLight[] = { 0.2f, 0.0f, 0.0f, 1.0f };//��ɫ����Դ������
// 	GLfloat redDiffLight[] = { 0.8f, 0.0f, 0.0f, 1.0f };//��ɫ����Դ������
// 	GLfloat redSpecLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };//��ɫ����Դ�����

//	GLfloat lightPos[] = { 50.0f, 120.0f, 120.0f, 1.0f };	//��Դλ��
	GLfloat spotLightPos[] = { 0.0f, 0.0f, 200.0f, 1.0f };	//���λ��
	GLfloat spotDir[] = { 0.0f, 0.0f, -1.0f };			//��Ʒ���

	GLfloat redLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };		//��ɫ��Դ
	//GLfloat greenLight[] = { 0.0f, 1.0f, 0.0f, 1.0f };		//��ɫ��Դ
	//GLfloat blueLight[] = { 0.0f, 0.0f, 1.0f, 1.0f };		//��ɫ��Դ


 	glEnable(GL_LIGHTING);							//���ù���
// 	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);	//���û�����Դ
// 	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);	//�����������Դ
// 	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);	//���þ����Դ
// 	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);		//���õƹ�λ��
// 	glEnable(GL_LIGHT0);							//�򿪰�ɫ����Դ

// 	glLightfv(GL_LIGHT4, GL_AMBIENT, redAmbiLight);
// 	glLightfv(GL_LIGHT4, GL_DIFFUSE, redDiffLight);
// 	glLightfv(GL_LIGHT4, GL_SPECULAR, redSpecLight);
// 	glLightfv(GL_LIGHT4, GL_POSITION, lightPos);

	glLightfv(GL_LIGHT1, GL_SPECULAR, redLight);		//��ɫ���
	glLightfv(GL_LIGHT1, GL_POSITION, spotLightPos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 85.0f);
	glEnable(GL_LIGHT1);


	glEnable(GL_COLOR_MATERIAL);						//���ò��ʵ���ɫ����
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);	//ָ��������ɫ����
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);	//ָ�����϶Ծ����ķ�Ӧ
	glMateriali(GL_FRONT, GL_SHININESS, 100);				//ָ������ϵ��
}
/*
// main
void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 480);
	glutCreateWindow("OpenGL��Դ");

	glutReshapeFunc(OnReShape);
	glutDisplayFunc(OnDisplay);
	glutKeyboardFunc(OnKey);

	SetupRC();
	SetupLights();

	glutMainLoop();
}*/
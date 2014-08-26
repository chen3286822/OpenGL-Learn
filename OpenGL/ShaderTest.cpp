#include "stdafx.h"
#include "ShaderTest.h"

void ShaderTest::init()
{
	glewInit();
	glClearColor(0.0, 0.0, 0.0, 0.0);/* select clearing color   */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0, -10.0, 10.0);/* initialize viewing values   */

	const GLchar* vShader[] = {
		"attribute vec4 vPos;"
		"void main()"
		"{"
		"	vec4 tmp = vPos * gl_Vertex;"
		"	gl_Position = gl_ModelViewProjectionMatrix * tmp;"
		"	gl_FrontColor = vec4(1.0, 1.0, 0.0, 0.0);"
		"	gl_BackColor = gl_SecondaryColor;"
		"}"
	};
	GLuint program;
	GLint compiled, linked, validated;
	GLuint shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader, 1, vShader, nullptr);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLint length;
		GLchar* log;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		log = new GLchar[length];
		glGetShaderInfoLog(shader, length, &length, log);
		std::cout << "compile log : " << log << std::endl;
		delete[] log;
	}
	program = glCreateProgram();
	glAttachShader(program, shader);

	glBindAttribLocation(program, 5, "vPos");
	GLenum __error = glGetError();
	

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLint length;
		GLchar* log;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		log = new GLchar[length];
		glGetProgramInfoLog(program, length, &length, log);
		std::cout << "link log : " << log << std::endl;
		delete[] log;
	}

	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &validated);
	if (!validated)
	{
		GLint length;
		GLchar* log;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		log = new GLchar[length];
		glGetProgramInfoLog(program, length, &length, log);
		std::cout << "validate log : " << log << std::endl;
		delete[] log;
	}

	GLint index = glGetAttribLocation(program, "vPos");

	glVertexAttrib3f(5, 45.0, 5.0, 0.0);

	m_program = program;
	glUseProgram(program);
}

void ShaderTest::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);

	glVertexAttrib3f(5, 2.0, 1.0, 1.0);

	glBegin(GL_POLYGON);
// 	glVertexAttrib3f(5, 45.0, 5.0, 0.0);
// 	glVertexAttrib3f(5, 55.0, 25.0, 0.0);
// 	glVertexAttrib3f(5, 55.0, 65.0, 0.0);
// 	glVertexAttrib3f(5, 45.0, 45.0, 0.0);
	glVertex3i(45, 5, 0);
	glVertex3i(55, 25, 0);
	glVertex3i(55, 65, 0);
	glVertex3i(45, 45, 0);
	glEnd();

	glFlush();
}
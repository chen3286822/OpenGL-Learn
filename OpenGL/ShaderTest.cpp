#include "stdafx.h"
#include "ShaderTest.h"

struct Vertex{
	float Position[2];
	float Color[4];
};

const Vertex vertices[] = {
		{ { -0.5, -0.866 }, { 0.5, 1, 0.5, 1 } },
		{ { 0.5, -0.866 }, { 0.2, 0.6, 0.5, 1 } },
		{ { 0, 1 }, { 0.6, 0.1, 0.8, 1 } },
		{ { 0.5, -0.866 }, { 0.5, 0.5, 0.5, 1 } },
		{ { 1.5, -0.866 }, { 0.5, 0.5, 0.5, 1 } },
		{ { 1, 0.4 }, { 0.5, 0.5, 0.5, 1 } }
};

void ShaderTest::init()
{
	glewInit();
	glClearColor(0.0, 0.0, 0.0, 0.0);/* select clearing color   */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 3.0, -2.0, 3.0, -1.0, 1.0);/* initialize viewing values   */

	const GLchar* vShader[] = {
		"attribute vec4 vPos;"
		"attribute vec4 vColor;"
		"void main()"
		"{"
		"	gl_Position = gl_ModelViewProjectionMatrix * vPos;"
		"	gl_FrontColor = vColor;"
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

// 	glBindAttribLocation(program, 5, "vPos");
// 	GLenum __error = glGetError();
	

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

	//glVertexAttrib3f(5, 45.0, 5.0, 0.0);

	m_program = program;
	glUseProgram(program);
}

void ShaderTest::reshape(GLint w, GLint h)
{
	GLint length = w > h ? h : w;
	glViewport(0, 0, (GLsizei)length, (GLsizei)length);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 3.0, -2.0, 3.0, -1.0, 1.0);
}

void ShaderTest::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(0.0, 0.0, 1.0);

	//glVertexAttrib3f(5, 2.0, 1.0, 1.0);

	GLint posIndex = glGetAttribLocation(m_program, "vPos");
	GLint colorIndex = glGetAttribLocation(m_program, "vColor");
	glEnableVertexAttribArray(posIndex);
	glEnableVertexAttribArray(colorIndex);

	GLsizei stride = sizeof(Vertex);
	const GLvoid* pCoords = &vertices[0].Position[0];
	const GLvoid* pColors = &vertices[0].Color[0];
	glVertexAttribPointer(posIndex, 2, GL_FLOAT, GL_FALSE, stride, pCoords);
	glVertexAttribPointer(colorIndex, 4, GL_FLOAT, GL_FALSE, stride, pColors);
	GLsizei vertexCount = sizeof(vertices) / sizeof(Vertex);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	glDisableVertexAttribArray(posIndex);
	glDisableVertexAttribArray(colorIndex);
// 	glBegin(GL_POLYGON);
// 	glVertex3i(45, 5, 0);
// 	glVertex3i(55, 25, 0);
// 	glVertex3i(55, 65, 0);
// 	glVertex3i(45, 45, 0);
// 	glEnd();

	glFlush();
}
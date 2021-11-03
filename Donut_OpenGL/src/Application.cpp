#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

constexpr auto PI = = 3.1415926535;;
using namespace std;

static unsigned int CompileShader(unsigned int type, const string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = &source[0];
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << endl;
		cout << message << endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const string& vertexShader, const string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

//this is OpenGL ver.4
int main(void)
{
	GLFWwindow* window;

	cout << " fuck git fucking bloody, sorry mate i changed my mind, FUCK YOU BLOODY";

	//initials
	if (!glfwInit())
		return -1;


	//window
	window = glfwCreateWindow(900, 900, "Donut", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//context menu
	glfwMakeContextCurrent(window);
	glewInit();
	const int rot_angle = 2 * PI / 5;
		if (glewInit() != GLEW_OK)
			cout << "Error\n";
	float positions[4][2] = {	{0,0}, 
								{cos(rot_angle),sin(rot_angle)},
								{cos(rot_angle) + 2,sin(rot_angle)},
								{1,0} };
	float rotations[2][2] = { {cos(rot_angle),sin(rot_angle)},
							{-sin(rot_angle),cos(rot_angle)} };
	unsigned int buffer;

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);                                  // GL_ARRAY_BUFFER is simply saying that this buffer is an array
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);//we can use sizeof(positions) but it's more practical this way

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	string vertexShader =
		"#version 330 core "
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"\n"
		"void main()"
		"{\n"
		"	gl_Position = position;\n"
		"}\n";

	string fragmentShader =
		"#version 330 core "
		"\n"
		"layout(location = 0) out vec4 color;"
		"\n"
		"void main()"
		"{\n"
		"	color = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";

	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	//loop
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_POLYGON, 0, 4);
		/*glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, positions);*/

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}




	glfwTerminate();
	return 0;
}
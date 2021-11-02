#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;
//this is OpenGL ver.4
int main(void)
{
	GLFWwindow* window;

	cout << " fuck git fucking bloody";

	//initials
	if (!glfwInit())
		return -1;


	//window
	window = glfwCreateWindow(900, 800, "Donut", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//context menu
	glfwMakeContextCurrent(window);

	float positions[6] = { -0.5f, -0.5f,                                     //this is practicaly a buffer because it is array of contiguous memory 
						   0.0f,  0.5f,
						   0.5f, -0.5f };
	unsigned int buffer;

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);                                  // GL_ARRAY_BUFFER is simply saying that this buffer is an array
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);//we can use sizeof(positions) but it's more practical this way



	//loop
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, positions);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}




	glfwTerminate();
	return 0;
}
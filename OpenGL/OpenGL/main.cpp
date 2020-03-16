#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int main(void) {
	
	GLFWwindow *window;

	// start GL context and O/S window using the GLFW helper library
	if (!glfwInit()) 
	{
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return -1;
	}

	// create a windowed mode and its OpenGL Context
	window = glfwCreateWindow(640, 480, "OpenGL Project", NULL, NULL);

	if (!window)
	{
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return -1;
	}

	// make the window's context current
	glfwMakeContextCurrent(window);

	// set up triangle
	float vertices[] =
	{
		0.0, 0.5, 0.0, // middle top corner
		-.5, -.5, 0.0, // buttom left corner
		0.5, -.5, 0.0  // buttom right corner
	};

	//loop until the user close the window
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// render the OpenGL here
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableClientState(GL_VERTEX_ARRAY);
		// sweap front and back buffers
		glfwSwapBuffers(window);

		// poll for and process envets
		glfwPollEvents();
	}

	glfwTerminate();
}
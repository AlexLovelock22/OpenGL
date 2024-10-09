#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VAO.h"
#include"EBO.h"

// Verticies of triangle

	GLfloat vertices[] =
	{		
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f
	};

	GLuint indices[] =
		{
			0,3,5, // Lower Left
			3,2,4, // Lower Right
			5,4,1 // Upper Triangle
		};




int main() {
	// Initialise GLFW
	glfwInit();

	// Configure GLFW on which version and profile is to be used.
	// Used profile is the modern instruction set.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	

	



	// Create a window (But will not *use* it as of now). 
	// Has 800 x 800, title of OpenGL, first NULL is fullscreen or no, second NULL is not important.
	// A check is also run to terminate if the window fails to be created.
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Tell GLFW to use the created window
	glfwMakeContextCurrent(window);

	// Load GLAD so it confused OpenGL.
	gladLoadGL();
	
	// Specify the VIEWPORT (not window size). X,Y,X,Y
	glViewport(0, 0, 800, 800);


	// ------------------------------------- Creating shaders, drawing triangles ---------------------------------- // 

	// Create reference to VAO, and VBO
	// VAO = Vertex Array Object
	// VBO = Vertex Buffer Object
	GLuint VAO, VBO, EBO;

	

	// Generate a single (1) object of each, 
	glGenBuffers(1, &EBO);
	
	// Make the VAO the CURRENT Vertex Array Object by byinding it

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	

	// Bind VGO and VAO to 0, so it's not accidentally modified 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// ------------------------------------ Background Colour ---------------------------------- // 

	// Create a color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// Clean the backbuffer, then swap the two buffers. 
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);


	// ------------------------------------- Main Loop ---------------------------------- // 

	// To stop the window from instantly closing, !glfwWindowShouldClose it used, polling all events inside. 
	while (!glfwWindowShouldClose(window)) {
		
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL which shader program we want to use.

		// Bind VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		// Draw the triangle using GL_TRIANGLES. 
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	// Delete all created objects
	glDeleteBuffers(1, &EBO);

	// Destroy window and terminate GLFW. 
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
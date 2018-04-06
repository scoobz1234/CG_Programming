#include "Renderer.h"

void BeginRenderingLoop() {

		GLuint vertexArrayID = 0;
		glGenVertexArrays(1, &vertexArrayID);
		glBindVertexArray(vertexArrayID);

		//Create and compile glsl program from shaders...
		GLuint programID = LoadShaders("BasicVertexShader.vertexshader", "BasicFragmentShader.fragmentshader");

		GLuint triangleID = LoadTriangle();
		GLuint quadID = LoadQuad();

		do {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUseProgram(programID);
			//RenderTriangle(triangleID);
			RenderQuad(quadID);

			glfwSwapBuffers(window);
			glfwPollEvents();

		} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0);
}
#include "Renderer.h"

namespace {
	int leftKeyPressed = 0;

	double lastTime = glfwGetTime();
	float deltaTime = 0.0;

	auto quadPos = glm::vec3(0, 0, 0);

	glm::mat4 TransformQuad() {

		//handle keyboard input
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			quadPos.x += deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT)) {
			quadPos.x -= deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_UP)) {
			quadPos.y += deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN)) {
			quadPos.y -= deltaTime;
		}

		//matrix math
		glm::mat4 model;
		model = glm::translate(model, quadPos);

		return model;
	}
}

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

			//RenderTriangle(triangleID);
			RenderQuad(quadID, TransformQuad(),programID);

			glfwSwapBuffers(window);
			glfwPollEvents();
			//set delta time...
			deltaTime = glfwGetTime() - lastTime;
			//setlast time...			
			lastTime = glfwGetTime();

		} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0);
}

void RenderVertex(GLuint vertexBuffer, glm::mat4 model, GLuint programID /*shader program id*/) {
	glUseProgram(programID);

	GLuint uniformModel = glGetUniformLocation(programID, "model");
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glVertexAttribPointer(
		0,			//attribute layout
		3,			//Elements in array
		GL_FLOAT,	//Each element is of type float
		GL_FALSE,	//Normalized?
		0,			//Stride...
		(void*)0	//Array buffer offset...
	);
}

void RenderQuad(GLuint vertexBuffer, glm::mat4 model,GLuint programID) {
	RenderVertex(vertexBuffer, model, programID);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
}

void RenderTriangle(GLuint vertexBuffer, glm::mat4 model, GLuint programID) {
	RenderVertex(vertexBuffer, model, programID);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}
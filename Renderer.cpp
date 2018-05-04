#include "Renderer.h"

namespace {

	int leftKeyPressed = 0;

	double lastTime = glfwGetTime();
	float deltaTime = 0.0;

	float angle = 0.0f;

	auto objPos = glm::vec3(0, 0, 0);

	glm::mat4 TransformObject() {
		//handle keyboard input
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			objPos.x += deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT)) {
			objPos.x -= deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_UP)) {
			objPos.y += deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN)) {
			objPos.y -= deltaTime;
		}

		if (glfwGetKey(window, GLFW_KEY_Q)) {
			angle += deltaTime * 60.0f;
		}

		if (glfwGetKey(window, GLFW_KEY_E)) {
			angle -= deltaTime * 60.0f;
		}

		//matrix math
		glm::mat4 model;	

		model = glm::rotate(model, angle, glm::vec3(1, 1, 0));

		//angle += deltaTime;
		//model = glm::translate(model, objPos);

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
		GLuint cubeID = LoadCube();

		do {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			RenderCube(cubeID, TransformObject(), programID);

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

void RenderCube(GLuint vertexBuffer, glm::mat4 model, GLuint programID) {
	RenderVertex(vertexBuffer, model, programID);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableVertexAttribArray(0);
}

void RenderTriangle(GLuint vertexBuffer, glm::mat4 model, GLuint programID) {
	RenderVertex(vertexBuffer, model, programID);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}
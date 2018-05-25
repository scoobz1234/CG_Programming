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

		return model;
	}

	void PrepareToRender(glm::mat4 model, GLuint programID) {
		glUseProgram(programID);
		GLuint uniformModel = glGetUniformLocation(programID, "model");
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	}

	void RenderVertices(GLuint vertexBufferID) {
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,	0, (void*)0);
	}
	
	void RenderTextureCoords(GLuint textureBufferID) {
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, textureBufferID);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	void RenderNormals(GLuint normalBufferID) {
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	void RenderFaces(GLuint faceBufferID) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceBufferID);
		
		int size;  
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

		glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

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
		auto cube = LoadObj("zeCube.obj");

		do {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//RenderCube(cubeID, TransformObject(), programID);
			RenderOBJ(cube, TransformObject(), programID);

			glfwSwapBuffers(window);
			glfwPollEvents();
			//set delta time...
			deltaTime = glfwGetTime() - lastTime;
			//setlast time...			
			lastTime = glfwGetTime();

		} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0);
}

void RenderCube(GLuint vertexBufferID, glm::mat4 model, GLuint programID) {
	PrepareToRender(model, programID);
	RenderVertices(vertexBufferID);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableVertexAttribArray(0);
}

void RenderQuad(GLuint vertexBufferID, glm::mat4 model, GLuint programID) {
	PrepareToRender(model, programID);
	RenderVertices(vertexBufferID);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
}

void RenderTriangle(GLuint vertexBufferID, glm::mat4 model, GLuint programID) {
	PrepareToRender(model, programID);
	RenderVertices(vertexBufferID);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}

void RenderOBJ(ObjLoader::OBJData data, glm::mat4 model, GLuint programID) {
	PrepareToRender(model, programID);
	RenderVertices(data.vertID);
	RenderTextureCoords(data.texID);
	RenderNormals(data.normID);
	RenderFaces(data.faceID);
	
	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
	
	for (int i = 0; i < 4; ++i) {
		glDrawArrays(GL_TRIANGLES, i, data.numFaces);
	}
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
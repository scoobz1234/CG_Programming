#pragma once
#include "InitOpenGL.h"
#include "OBJLoader.h"


void BeginRenderingLoop();

void RenderQuad(GLuint vertexBufferID, glm::mat4 model, GLuint programID);
void RenderCube(GLuint vertexBufferID, glm::mat4 model, GLuint programID);
void RenderTriangle(GLuint vertexBufferID, glm::mat4 model, GLuint programID);
void RenderOBJ(ObjLoader::OBJData data, glm::mat4 model, GLuint programID);


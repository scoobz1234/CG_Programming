#pragma once
#include "InitOpenGL.h"


void BeginRenderingLoop();

void RenderVertex(GLuint vertexBuffer, glm::mat4 model, GLuint programID /*shader program id*/);
void RenderQuad(GLuint vertexBuffer, glm::mat4 model, GLuint programID);
void RenderTriangle(GLuint vertexBuffer, glm::mat4 model, GLuint programID);


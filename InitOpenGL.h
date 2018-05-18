#pragma once

#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <fstream>
#include <string>
#include <glm/gtc/matrix_transform.hpp> //for matrices...
#include <glm/gtc/type_ptr.hpp>
#include "OBJLoader.h"

//Defines…
#define GLFW_DLL
#define APP_NAME "<<POOP!>>"
#define EXIT_WITH_ERROR -1
#define EXIT_WITH_SUCCESS 0
#define OPEN_GL_VERSION 3  //Specifies OpenGL 3.3
#define ANTIALIASING 4  //nx antialiasing
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define GLFW_FAIL 0 

//External Globals…
extern GLFWwindow* window;
extern GLint shaderStatus;
extern bool activeRef;

//function decl...
int InitWindow();
GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
int InitGlewFailed();
GLuint& LoadQuad();
GLuint& LoadTriangle();
GLuint& LoadCube();
ObjLoader::OBJData LoadObj(const char* filePath);
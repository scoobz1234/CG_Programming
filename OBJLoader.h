#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#pragma once


namespace ObjLoader {

	struct OBJData {
		unsigned int *faces = nullptr;
		float *vertices = nullptr, *normals = nullptr, *uvs = nullptr;
		unsigned int numVertices = 0, numNormals = 0, 
			numUVs = 0, numFaces = 0;
	};

	//TODO:: Make a function to clean up model data!
	int Load(const char *fileName, OBJData &data);

};

#include "OBJLoader.h"
#include <sstream>
#include <iostream>

namespace {
	
	int RecursiveLoad(const char * fileName, ObjLoader::OBJData &data) {

		std::ifstream file(fileName);
		std::string nextLine;

		while (std::getline(file, nextLine)) {

			std::stringstream ss(nextLine);

			if (nextLine.length() > 2) {

				switch (nextLine[0]) {
				case 'v':
					switch (nextLine[1]) {
					case 32: // reading Vertices...
						if (data.vertices == nullptr) {
							++data.numVertices;
							continue;
						}
						for (int i = 0; i < 3; ++i) {

							ss >> *data.vertices++;
						}
						break;
					case 't': // reading UVs...
						if (data.uvs == nullptr) {
							++data.numUVs;
							continue;
						}
						break;
					case 'n': // reading Normals...
						if (data.normals == nullptr) {
							++data.numNormals;
							continue;
						}
						break;
					}
					break;
				case'f': // reading faces...
					if (nextLine[1] == 32 && data.faces == nullptr) {
						++data.numFaces;
					}
					break;
				}
			}
		}
			//if faces == nullptr, then we did not set the faces!
			if (data.faces == nullptr) {
				data.faces = (unsigned int*)malloc(data.numFaces * 3);
				data.vertices = (float*)malloc(data.numVertices * 3);
				data.normals = (float*)malloc(data.numNormals * 3);
				data.uvs = (float*)malloc(data.numUVs * 3);
				return RecursiveLoad(fileName, data);
			}

			return 0;
		}
	}



int ObjLoader::Load(const char * fileName, OBJData &data) {
	return RecursiveLoad(fileName, data);
	
}

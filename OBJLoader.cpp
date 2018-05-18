#include "OBJLoader.h"
	
int RecursiveLoad(const char *fileName, ObjLoader::OBJData &data) {

	std::ifstream file(fileName);
	std::string nextLine;

	//temporary values we will use to increment...
	auto vertices = data.vertices;
	auto normals = data.normals;
	auto uvs = data.uvs;
	auto faces = data.faces;

	while (std::getline(file, nextLine)) {

		if (nextLine.length() > 2) {
			switch (nextLine[0]) {
			case 'v':
				switch (nextLine[1]) {
				case 32: // reading Vertices...
					if (data.vertices == nullptr) {
						++data.numVertices;
						continue;
					}

					sscanf(nextLine.c_str(), "%*c %f %f %f", &vertices[0], &vertices[1], &vertices[2]);
					vertices += 3;
					
					break;
				case 't': // reading UVs...
					if (data.uvs == nullptr) {
						++data.numUVs;
						continue;
					}

					sscanf(nextLine.c_str(), "%*2c %f %f", &uvs[0], &uvs[1]);
					uvs += 2;

					break;
				case 'n': // reading Normals...
					if (data.normals == nullptr) {
						++data.numNormals;
						continue;
					}

					sscanf(nextLine.c_str(), "%*2c %f %f %f", &normals[0], &normals[1], &normals[2]);
					normals += 3;

					break;
				}
				break;
			case'f': // reading faces...
				if (nextLine[1] == 32 && data.faces == nullptr) {
					++data.numFaces;
					continue;
				}

				sscanf(nextLine.c_str(), "%*1c %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
					&faces[0], &faces[1], &faces[2], &faces[3], &faces[4], &faces[5], 
					&faces[6], &faces[7], &faces[8], &faces[9], &faces[10], &faces[11]);
				faces += 12;
				break;
			}
		}
	}
		//if faces == nullptr, then we did not set the faces!
		if (data.faces == nullptr) {
			data.faces = (unsigned int*)malloc(data.numFaces * sizeof(unsigned int) * 12);
			data.vertices = (float*)malloc(data.numVertices * sizeof(float) * 3);
			data.normals = (float*)malloc(data.numNormals * sizeof(float) * 3);
			data.uvs = (float*)malloc(data.numUVs * sizeof(float) * 2);
			return RecursiveLoad(fileName, data);
		}

		return 0;
	}


int ObjLoader::Load(const char * fileName, OBJData &data) {
	return RecursiveLoad(fileName, data);
}

#ifndef GEOMETRY_INFO_H
#define GEOMETRY_INFO_H

#include <GL\glew.h>
#include <glm\glm.hpp>

struct GeometryInfo
{
	GLuint indexingMode;
	GLuint offset;
	GLuint indexOffset;
	glm::uint numIndices;
	unsigned int vertexArrayID;
	unsigned int bufferID;
	unsigned short* indices;
	bool isAvailable;
	GeometryInfo();
	GeometryInfo(GLuint offset, unsigned int numIndices, GLuint indexOffset, GLuint indexingMode, unsigned short* indices, unsigned int bufferID);
};

#endif
#ifndef CUBE_H
#define CUBE_H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <Qt\qglobal.h>
#include "Vertex.h"

typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;

struct Cube
{
	static const glm::uint SIZE = 24;
	static const glm::uint AMOUNT_OF_VERTICES = 36;

	Vertex vertices[SIZE];
	ushort indices[AMOUNT_OF_VERTICES];
	Cube();
	void createCubeVerticesAndColor();
	void createCubeIndices();
};

#endif
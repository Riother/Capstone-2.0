#ifndef PLANE_H
#define PLANE_H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <Qt\qglobal.h>
#include "Vertex.h"

typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;

struct Plane
{
	static const glm::uint SIZE = 4;
	static const glm::uint AMOUNT_OF_VERTICES = 6;

	Vertex vertices[SIZE];
	ushort indices[AMOUNT_OF_VERTICES];
	Plane();
	void createPlaneVerticesAndColor();
	void createPlaneIndices();
};

#endif
#ifndef SPHERE_BUILDER_H
#define SPHERE_BUILDER_H

#include <glm\glm.hpp>
#include <vector>
#include "RendererWindow.h"
#include "Vertex.h"
#define _USE_MATH_DEFINES
#include <math.h>

class SphereBuilder
{
	float sphereSize;
	float divisions;
	bool isCreated;
	std::vector<glm::vec3> positions;
	std::vector<Vertex> vertices;
	std::vector<ushort> tempIndices;
	std::vector<ushort> actualIndices;
	GeometryInfo* geometry;
public:
	SphereBuilder();
	SphereBuilder(int size, int subdivisions);
	GeometryInfo* GetSphere();
	void CreatePositions();
	void PlaceTempIndices();
	void PlaceActualIndices();
	void PlacePositions();
	void PlaceNormals();
	Vector2 CalculateUV(Vector3 position);
	Vector3 LERP(Vector3 start, Vector3 end);
};

#endif
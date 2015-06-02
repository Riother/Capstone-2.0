#ifndef CYLINDER_BUILDER_H
#define CYLINDER_BUILDER_H

#include <glm\glm.hpp>
#include <vector>
#include "RendererWindow.h"
#include "Vertex.h"
#define _USE_MATH_DEFINES
#include <math.h>

class CylinderBuilder
{
	float columnSize;
	float divisions;
	bool isCreated;
	std::vector<glm::vec3> positions;
	std::vector<Vertex> vertices;
	std::vector<ushort> tempIndices;
	std::vector<ushort> actualIndices;
	GeometryInfo* geometry;
public:
	CylinderBuilder();
	CylinderBuilder(int size, int subdivisions);
	GeometryInfo* GetCylinder();
	void CreatePositions();
	void PlaceTempIndices();
	void PlaceActualIndices();
	void PlacePositions();
	void PlaceNormals();
	Vector2 CalculateUV(Vector3 position, float radius);
};

#endif
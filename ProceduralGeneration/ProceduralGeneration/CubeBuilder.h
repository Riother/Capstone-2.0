#ifndef CUBE_BUILDER_H
#define CUBE_BUILDER_H

#include <glm\glm.hpp>
#include <vector>
#include "RendererWindow.h"
#include "Vertex.h"

class CubeBuilder
{
	float cubeSize;
	float divisions;
	bool isCreated;
	std::vector<glm::vec3> positions;
	std::vector<Vertex> vertices;
	std::vector<ushort> tempIndices;
	std::vector<ushort> actualIndices;
	GeometryInfo* geometry;
public:
	CubeBuilder();
	CubeBuilder(int size, int subdivisions);
	GeometryInfo* GetCube();
	void CreatePositions();
	void PlaceTempIndices();
	void PlaceActualIndices();
	void PlacePositions();
	void PlaceNormals();
	void PlaceUVs();
};

#endif
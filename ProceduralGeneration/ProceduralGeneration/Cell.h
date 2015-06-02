#ifndef VOXEL_H
#define VOXEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>

struct Cell
{
	enum Type
	{
		None = 0,
		Room = 1,
		Hall = 2,
		Wall = 3,
	};

	Type spaceType;
	int x, y;
	bool isEdgeCell;
	bool isVisited;

	Cell();
	Cell(Type type, int x, int y, bool isEdge = false);
	bool isEmpty();
	bool isEmptyOrWall();
};

#endif
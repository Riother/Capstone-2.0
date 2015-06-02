#ifndef DUNGEON_NODE_H
#define DUNGEON_NODE_H

#include "Vertex.h"

struct DungeonNode
{
	enum FloorType
	{
		Empty = 0,
		Room = 1,
		Hall = 2,
		Wall = 3,
	};

	Vertex topLeft;
	Vertex topRight;
	Vertex botLeft;
	Vertex botRight;

	FloorType floorType;
	int roomNumber;
	bool isVisited;

	DungeonNode* leftNeighbor;
	DungeonNode* topNeighbor;
	DungeonNode* rightNeighbor;
	DungeonNode* botNeighbor;

	bool isEdgeNode();
};

#endif
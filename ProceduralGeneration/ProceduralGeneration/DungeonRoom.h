#ifndef DUNGEON_ROOM_H
#define DUNGEON_ROOM_H

#include "RendererWindow.h"
#include "Vertex.h"

class DungeonRoom
{
	std::vector<GeometryInfo*> walls;
	GeometryInfo* topWall;
	GeometryInfo* botWall;
	GeometryInfo* leftWall;
	GeometryInfo* rightWall;
	GeometryInfo* frontWall;
	GeometryInfo* backWall;

	RenderableInfo* top;
	RenderableInfo* bot;
	RenderableInfo* left;
	RenderableInfo* right;
	RenderableInfo* front;
	RenderableInfo* back;

	bool showRoof;
	int text;
public:
	DungeonRoom(bool showRoof = true);
	DungeonRoom(std::vector<GeometryInfo*> walls, bool showRoof);
	DungeonRoom(std::vector<GeometryInfo*> walls);
	DungeonRoom(GeometryInfo* sphere);
	void CreateSquareRoom();
	void CreateDomeRoom();
	void CreateSphere();
	void CreateColumn();
	void AddShaderStreamedParameters(GeometryInfo* info);
};

#endif
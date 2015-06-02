#ifndef DUNGEON_GRAPH_H
#define DUNGEON_GRAPH_H

#include <GL\glew.h>
#include <QtGui\qwidget.h>
#include <QtGui\qboxlayout.h>
#include <Qt\qmainwindow.h>
#include <noise/noise.h>
#include <Qt\qpushbutton.h>
#include "noiseutils.h"
#include "RendererWindow.h"
#include "Vertex.h"
#include "DungeonRoom.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stack>
#include <random>
#include <algorithm>
#include "LabeledSpinbox.h"
#include "LabeledCheckBox.h"
#include <iostream>
#include "Plane.h"
#include "Cube.h"
#include "DungeonNode.h"
//#include "GeometryEditor.h"


class DungeonGraph : public QWidget
{
	Q_OBJECT

	//QTabWidget* dungeonEditor;
	//QTabWidget* textureEditor;
	//QTabWidget* geometryEditor;
	//QTabWidget* roomLightingEditor;
	//QTabWidget* roomTextureEditor;
	//QTabWidget* hallTextureEditor;

	QVBoxLayout* mainLayout;
	
	LabeledSpinbox* dungeonLength;
	LabeledSpinbox* dungeonWidth;
	LabeledSpinbox* dungeonHeight;
	LabeledSpinbox* numberOfRooms;
	LabeledSpinbox* placeAttempts;
	LabeledSpinbox* minRoomLength;
	LabeledSpinbox* maxRoomLength;
	LabeledSpinbox* minRoomWidth;
	LabeledSpinbox* maxRoomWidth;
	LabeledSpinbox* hallways;

	LabeledCheckBox* showRoofs;
	LabeledCheckBox* showRooms;
	LabeledCheckBox* showHalls;
	
	QPushButton* updateDimensions;
	//GeometryEditor* editor;
	Cube cube;

	DungeonNode** dungeon;
	int width;
	int length;
	int corridorTexture;
	int roomTexture;
	int wallTexture;
	std::vector<bool> roomDoors;
	std::vector<RenderableInfo*> corridors;
	std::vector<RenderableInfo*> rooms;
	std::vector<RenderableInfo*> walls;
	int noTexture;
	bool isLoaded;
private slots:
	void updateDungeon();
	void updateSettings();
public:
	DungeonGraph();
	void ClearGraph();
	void PrepareGraph();
	void CreateRooms();
	bool PlaceRoom(int locationX, int locationY, int roomNumber);
	void CreateHalls();

	bool HasValidNeighbors(DungeonNode* node);
	bool IsValidNeighbor(DungeonNode* node);
	bool HasMoreThanTwoWalls(DungeonNode* node);
	bool IsValidWall(DungeonNode* node);
	bool IsValidDoor(DungeonNode* node);
	void SetLeftNeighbor(int x, int y);
	void SetTopNeighbor(int x, int y);
	void SetRightNeighbor(int x, int y);
	void SetBotNeighbor(int x, int y);
	void PrintDungeon(std::string filename);
	void ClearDoors();
	void DrawDungeon();
	void AddShaderStreamedParameters(GeometryInfo* info);
	void setCorridorFloorTexture(int cTexture);
	void setRoomFloorTexture(int rTexture);
	void setWallTexture(int wTexture);
	void updateTextures();
};

#endif
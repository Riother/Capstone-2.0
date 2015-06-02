#ifndef DUNGEON_H
#define DUNGEON_H

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
#include "Cell.h"
#include <iostream>
#include "Plane.h"

class Dungeon : public QMainWindow
{
	Q_OBJECT

	QWidget* mainWidget;
	QHBoxLayout* mainLayout;
	QVBoxLayout* rendererLayout;
	QVBoxLayout* guiLayout;
	Cell** cells;
	int prevLength;
	int prevWidth;
	int prevHeight;

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

	bool loadedDungeon;
private slots:
	void updateDungeon();
	void updateSettings();
public:
	Dungeon();
	void ClearDungeon();
	void PrepareDungeon();
	void CreateDungeon();
	bool CreateRoom(int width, int length, int height);
	void CreateHalls();
	glm::vec2 PickDirection(int x, int y);
	bool AllCellsVisited();
	bool ConnectedToBlank(int x, int y, int previousDirection);
	int CheckForSpaces(int x, int y);
	void PrintDungeon(std::string fileName);
	void DrawDungeon();
	void AddShaderStreamedParameters(GeometryInfo* info);
};

#endif
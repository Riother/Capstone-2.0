#ifndef DUNGEON_MAKER_H
#define DUNGEON_MAKER_H

#include <GL\glew.h>
#include <QtGui\qwidget.h>
#include <QtGui\qboxlayout.h>
#include <Qt\qmainwindow.h>
#include <Qt\qpushbutton.h>
#include <Qt\qtimer.h>
#include "RendererWindow.h"
#include "DungeonGraph.h"
#include "GeometryEditor.h"
#include "CorridorFloorTextureEditor.h"
#include "RoomFloorTextureEditor.h"
#include "WallTextureEditor.h"

class DungeonMaker : public QMainWindow
{
	Q_OBJECT

	QWidget* mainWidget;
	QTabWidget* tabs;

	QHBoxLayout* mainLayout;
	QVBoxLayout* tabsLayout;
	QVBoxLayout* rendererLayout;

	DungeonGraph* dungeon;

	CorridorFloorTextureEditor* cFloor;
	RoomFloorTextureEditor* rFloor;
	WallTextureEditor* walls;

	QTimer updateTimer;
private slots:
	void update();

public:
	DungeonMaker();
};

#endif
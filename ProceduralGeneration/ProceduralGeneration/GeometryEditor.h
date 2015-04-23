#ifndef GEOMETRY_EDITOR_H
#define GEOMETRY_EDITOR_H

#include <GL\glew.h>
#include <QtGui\qwidget.h>
#include <QtGui\qboxlayout.h>
#include <Qt\qmainwindow.h>
#include <noise/noise.h>
#include "noiseutils.h"
#include "RendererWindow.h"
#include "Vertex.h"
#include "LabeledSpinbox.h"
#include "DungeonRoom.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

class GeometryEditor : public QMainWindow
{
	QWidget* mainWidget;
	QHBoxLayout* mainLayout;
	QVBoxLayout* rendererLayout;
	QVBoxLayout* guiLayout;
	std::vector<DungeonRoom> rooms;
public:
	GeometryEditor();
	void MakeRoom(float size, float subdivisions);
	void MakeDome(float size, float subdivisions, bool showFloor = true);
};

#endif
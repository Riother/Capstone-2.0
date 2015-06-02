#ifndef GEOMETRY_EDITOR_H
#define GEOMETRY_EDITOR_H

#include <GL\glew.h>
#include <QtGui\qwidget.h>
#include <QtGui\qboxlayout.h>
#include <Qt\qmainwindow.h>
#include <noise/noise.h>
#include <Qt\qpushbutton.h>
#include "noiseutils.h"
#include "RendererWindow.h"
#include "Vertex.h"
#include "LabeledSpinbox.h"
#include "DungeonRoom.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>
#include "LabeledSpinbox.h"
#include "LabeledCheckBox.h"
#include "CylinderBuilder.h"
#include "CubeBuilder.h"
#include "SphereBuilder.h"
#include "DomeBuilder.h"
#include "Cube.h"

class GeometryEditor : public QMainWindow
{
	Q_OBJECT

	QWidget* mainWidget;
	QHBoxLayout* mainLayout;
	QVBoxLayout* rendererLayout;
	QVBoxLayout* guiLayout;
	std::vector<DungeonRoom> rooms;
	DungeonRoom room;
	LabeledSpinbox* roomSize;
	LabeledSpinbox* divisions;
	LabeledCheckBox* showDome;
	QPushButton* drawRoom;
	QPushButton* drawDome;
	QPushButton* drawSphere;
	QPushButton* drawColumn;
	int textureID;
private slots:
	void updateValues();
	void MakeRoom();
	void MakeDome();
	void MakeSphere();
	void MakeColumn();
public:
	GeometryEditor();
	//GeometryInfo* MakeRoom();
	//GeometryInfo* MakeDome();
	//GeometryInfo* MakeSphere();
	//GeometryInfo* MakeColumn();
	void AddShaderStreamedParameters(GeometryInfo* info);
	Vector2 CartesianToCylindrical(Vector3 cartesianVector, float radius);
};

#endif
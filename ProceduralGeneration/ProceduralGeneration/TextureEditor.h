#ifndef TEXTURE_EDITOR_H
#define TEXTURE_EDITOR_H

#include <GL\glew.h>
//#include <QtGui\qwidget.h>
#include <QtGui\qboxlayout.h>
#include <Qt\qmainwindow.h>
#include <noise/noise.h>
#include "noiseutils.h"
#include "RendererWindow.h"
#include "Plane.h"
#include "LabeledSpinbox.h"
#include "GeometryEditor.h"

class TextureEditor //: public QMainWindow
{
	//Q_OBJECT

	//QWidget* mainWidget;
	//QHBoxLayout* mainLayout;
	//QVBoxLayout* rendererLayout;
	//QVBoxLayout* guiLayout;
	//
	//LabeledSpinbox* red;
	//LabeledSpinbox* green;
	//LabeledSpinbox* blue;
	//LabeledSpinbox* alpha;
	//LabeledSpinbox* sinFrequency;
	//LabeledSpinbox* marbleFrequency;
	//LabeledSpinbox* woodFrequency;
	//
	//RenderableInfo* shape;
	//RenderableInfo* testPlane;

	//GeometryEditor geo;
//private slots:
//	void updateColors();

public:
	TextureEditor();
	QImage UtilImageToQImage(noise::utils::Image image);
	QColor UtilColorToQColor(noise::utils::Color color);
	QColor UtilColorToQColor(noise::utils::Color color, int mod);
	QImage Sin(int width, int height, int red, int green, int blue, int alpha, int frequency);
	QImage TiledPatterOne(int width, int height, int red, int green, int blue, int alpha);
	QImage GenerateBasePerlinNoise();
	QImage MarbleType1(int width, int height, int red, int green, int blue, int alpha, int marbleFrequency);
	QImage MarbleType2(int width, int height, int red, int green, int blue, int alpha, int marbleFrequency, int sinFrequency);
	//QImage MarbleType3(int width, int height, int red, int green, int blue, int alpha, int marbleFrequency);
	QImage WoodType1(int width, int height, int red, int green, int blue, int alpha, int woodFrequency);
	void AddShaderStreamedParameters(GeometryInfo* info);
};

#endif
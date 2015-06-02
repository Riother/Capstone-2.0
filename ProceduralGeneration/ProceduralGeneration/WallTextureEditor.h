#ifndef WALL_TEXTURE_EDITOR
#define WALL_TEXTURE_EDITOR

#include <QtGui\qwidget.h>
#include <Qt\qmainwindow.h>
#include <Qt\qpushbutton.h>
#include <Qt\qmenu.h>
#include <Qt\qmenubar.h>
#include <Qt\qboxlayout.h>
#include <glm\glm.hpp>
#include <noise/noise.h>
#include "noiseutils.h"z
#include "LabeledSpinbox.h"
#include "LabeledCheckBox.h"
#include "RendererWindow.h"
//#include "TextureEditor.h"

class WallTextureEditor : public QWidget
{
	Q_OBJECT

//	TextureEditor floor;
	QVBoxLayout* mainLayout;

	LabeledSpinbox* dimensions;
	LabeledSpinbox* red;
	LabeledSpinbox* green;
	LabeledSpinbox* blue;
	LabeledSpinbox* alpha;

	LabeledSpinbox* woodFrequency;
	LabeledSpinbox* nRings;
	LabeledSpinbox* turbulence;

	QPushButton* updateChanges;

	int dmns;
	int r;
	int g;
	int b;
	int a;

	float wFrequency;
	int rings;
	float turbPow;

	int wTexture;

private slots:
	void update();

public:
	WallTextureEditor();
	void Marble();
	void Wood();
	void Rock();
	int getTexture();
};

#endif
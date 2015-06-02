#ifndef CORRIDOR_FLOOR_TEXTURE_EDITOR
#define CORRIDOR_FLOOR_TEXTURE_EDITOR

#include <QtGui\qwidget.h>
#include <Qt\qmainwindow.h>
#include <Qt\qpushbutton.h>
#include <Qt\qmenu.h>
#include <Qt\qmenubar.h>
#include <Qt\qboxlayout.h>
#include <glm\glm.hpp>
#include "LabeledSpinbox.h"
#include "LabeledCheckBox.h"
#include "RendererWindow.h"
//#include "TextureEditor.h"

class CorridorFloorTextureEditor : public QWidget
{
	Q_OBJECT

//	TextureEditor floor;
	QVBoxLayout* mainLayout;

	LabeledSpinbox* dimensions;
	LabeledSpinbox* red;
	LabeledSpinbox* green;
	LabeledSpinbox* blue;
	LabeledSpinbox* alpha;

	QPushButton* updateChanges;

	int dmns;
	int r;
	int g;
	int b;
	int a;

	int cTexture;

private slots:
	void update();

public:
	CorridorFloorTextureEditor();
	void FloorPattern();
	int getTexture();
};

#endif
#ifndef ROOM_FLOOR_TEXTURE_EDITOR
#define ROOM_FLOOR_TEXTURE_EDITOR

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
#include <noise/noise.h>
#include "noiseutils.h"
//#include "TextureEditor.h"

class RoomFloorTextureEditor : public QWidget
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

	int rTexture;

private slots:
	void update();

public:
	RoomFloorTextureEditor();
	void FloorPattern();
	int getTexture();
};

#endif
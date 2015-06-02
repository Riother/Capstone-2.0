#include "RoomFloorTextureEditor.h"

RoomFloorTextureEditor::RoomFloorTextureEditor()
{
	mainLayout = new QVBoxLayout;

	dimensions = new LabeledSpinbox("Image Size", true, 50, 250, 100);
	red = new LabeledSpinbox("Red", true, 0, 255, 100);
	green = new LabeledSpinbox("Green", true, 0, 255, 100);
	blue = new LabeledSpinbox("Blue", true, 0, 255, 100);
	alpha = new LabeledSpinbox("Alpha", true, 0, 255, 100);

	updateChanges = new QPushButton("Update Texture", this);

	mainLayout->addWidget(dimensions);
	mainLayout->addWidget(red);
	mainLayout->addWidget(green);
	mainLayout->addWidget(blue);
	mainLayout->addWidget(alpha);
	mainLayout->addWidget(updateChanges);

	setLayout(mainLayout);
	show();

	connect(updateChanges, SIGNAL(clicked()), this, SLOT(update()));

	dmns = dimensions->getSpinboxValue();
	r = red->getSpinboxValue();
	g = green->getSpinboxValue();
	b = blue->getSpinboxValue();
	a = alpha->getSpinboxValue();

	rTexture = -1;
}

void RoomFloorTextureEditor::update()
{
	dmns = dimensions->getSpinboxValue();
	r = red->getSpinboxValue();
	g = green->getSpinboxValue();
	b = blue->getSpinboxValue();
	a = alpha->getSpinboxValue();
	FloorPattern();
}

void RoomFloorTextureEditor::FloorPattern()
{
	QImage newImage(dmns, dmns, QImage::Format::Format_RGB32);
	
	for(int x = 0; x < dmns; x++)
	{
		for(int y = 0; y < dmns; y++)
		{
			int mod = (x * y);
			int gray = qGray(r, g, b);
			int color = gray * mod % a;
			newImage.setPixel(x, y, QColor(color, color, color, color).rgba());
		}
	}

	rTexture = RENDERER.addTexture(newImage);
	//return newImage;
}

int RoomFloorTextureEditor::getTexture()
{
	return rTexture;
}

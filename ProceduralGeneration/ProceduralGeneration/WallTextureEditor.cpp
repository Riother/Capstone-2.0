#include "WallTextureEditor.h"

WallTextureEditor::WallTextureEditor()
{
	mainLayout = new QVBoxLayout;

	dimensions = new LabeledSpinbox("Image Size", true, 50, 250, 100);
	red = new LabeledSpinbox("Red", true, 0, 255, 100);
	green = new LabeledSpinbox("Green", true, 0, 255, 100);
	blue = new LabeledSpinbox("Blue", true, 0, 255, 100);
	alpha = new LabeledSpinbox("Alpha", true, 0, 255, 100);

	woodFrequency = new LabeledSpinbox("Frequency", true, 1, 100, 10);
	nRings = new LabeledSpinbox("Rings", true, 1, 100, 15);
	turbulence = new LabeledSpinbox("Turbulence", true, 1, 200, 10);

	updateChanges = new QPushButton("Update Texture", this);

	mainLayout->addWidget(dimensions);
	mainLayout->addWidget(red);
	mainLayout->addWidget(green);
	mainLayout->addWidget(blue);
	mainLayout->addWidget(alpha);
	mainLayout->addWidget(woodFrequency);
	mainLayout->addWidget(nRings);
	mainLayout->addWidget(turbulence);
	mainLayout->addWidget(updateChanges);

	setLayout(mainLayout);
	show();

	connect(updateChanges, SIGNAL(clicked()), this, SLOT(update()));

	dmns = dimensions->getSpinboxValue();
	r = red->getSpinboxValue();
	g = green->getSpinboxValue();
	b = blue->getSpinboxValue();
	a = alpha->getSpinboxValue();

	wFrequency = woodFrequency->getSpinboxValue();
	rings = nRings->getSpinboxValue();
	turbPow = turbulence->getSpinboxValue() / 100;

	wTexture = -1;
}

void WallTextureEditor::update()
{
	dmns = dimensions->getSpinboxValue();
	r = red->getSpinboxValue();
	g = green->getSpinboxValue();
	b = blue->getSpinboxValue();
	a = alpha->getSpinboxValue();

	wFrequency = woodFrequency->getSpinboxValue() / 100.0f;
	rings = nRings->getSpinboxValue();
	turbPow = turbulence->getSpinboxValue() / 100.0f;

	Wood();
}

void WallTextureEditor::Marble()
{
	
}

void WallTextureEditor::Wood()
{
	noise::module::Perlin noiseGenerator;
	noise::module::Turbulence turbulenceGenerator;
	
	turbulenceGenerator.SetSourceModule(0, noiseGenerator);
	turbulenceGenerator.SetFrequency(wFrequency);
	turbulenceGenerator.SetPower(turbPow);


	QImage newImage(dmns, dmns, QImage::Format::Format_RGB32);
	

	for(int x = 0; x < dmns; x++)
	{
		for(int y = 0; y < dmns; y++)
		{
			double xValue = (x - dmns / 2) / double(dmns);
			double yValue = (y - dmns / 2) / double(dmns);
			double distValue = sqrt(xValue * xValue + yValue * yValue) + turbPow * turbulenceGenerator.GetValue(x, y, wFrequency) / 256.0;
			double sineValue = 128.0 * fabs(sin(2 * rings * distValue * 3.14159));
			int red = UINT8(r + sineValue);
			int green = UINT8(g + sineValue);
			int blue = b;

			//double value1 = (double)x / (double)woodFrequency;
			//double value2 = (double)y / (double)woodFrequency;
			//double value3 = (double)(x +  y) / (double)woodFrequency;
			//double noiseValue = noiseGenerator.GetValue(value1, value2, value3);
			//
			//double mod = (double)x / woodFrequency;
			//double floored = floor(0.5f + mod);
			//int sinValue = 2.0 * (mod - floored);
			//int gray = qGray(sinValue, sinValue, sinValue);
			newImage.setPixel(x, y, QColor(red, green, blue, a).rgba());
		}
	}

	wTexture = RENDERER.addTexture(newImage);
}

int WallTextureEditor::getTexture()
{
	return wTexture;
}

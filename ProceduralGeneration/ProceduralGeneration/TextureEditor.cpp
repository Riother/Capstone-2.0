#include "TextureEditor.h"

TextureEditor::TextureEditor()
{
	mainLayout = new QHBoxLayout;
	mainWidget = new QWidget;

	red = new LabeledSpinbox("Red", true, 0, 255, 1);
	green = new LabeledSpinbox("Green", true, 0, 255, 1);
	blue = new LabeledSpinbox("Blue", true, 0, 255, 1);
	alpha = new LabeledSpinbox("Alpha", true, 1, 255, 1);
	sinFrequency = new LabeledSpinbox("Frequency", true, 1, 10, 1);
	marbleFrequency = new LabeledSpinbox("Marble Frequency", true, 10, 100, 1);

	rendererLayout = new QVBoxLayout;
	guiLayout = new QVBoxLayout;

	mainLayout->addLayout(guiLayout);
	mainLayout->addLayout(rendererLayout);

	guiLayout->addWidget(red);
	guiLayout->addWidget(green);
	guiLayout->addWidget(blue);
	guiLayout->addWidget(alpha);
	guiLayout->addWidget(sinFrequency);
	guiLayout->addWidget(marbleFrequency);

	rendererLayout->addWidget(&RENDERER);
	RENDERER.setMinimumSize(700, 600);
	mainWidget->setLayout(mainLayout);

	setCentralWidget(mainWidget);
	show();
	
	connect(red, SIGNAL(valueChanged()), this, SLOT(updateColors()));
	connect(green, SIGNAL(valueChanged()), this, SLOT(updateColors()));
	connect(blue, SIGNAL(valueChanged()), this, SLOT(updateColors()));
	connect(alpha, SIGNAL(valueChanged()), this, SLOT(updateColors()));
	connect(sinFrequency, SIGNAL(valueChanged()), this, SLOT(updateColors()));
	connect(marbleFrequency, SIGNAL(valueChanged()), this, SLOT(updateColors()));

	Plane plane;
	GeometryInfo* planeInfo = RENDERER.addGeometry(plane.vertices, plane.SIZE * sizeof(Vertex), plane.indices, plane.AMOUNT_OF_VERTICES, GL_TRIANGLES);

	ShaderInfo* shaderInfo = RENDERER.createShaderInfo("SimpleVertexShaderCode.glsl", "SimpleFragmentShaderCode.glsl");
	Matrix4 position = glm::translate(Vector3(0, 0, 0)) * glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));

	RENDERER.addShaderStreamedParameter(planeInfo, 0, ParameterType::PT_VECTOR3, Vertex::POSITION_OFFSET, Vertex::STRIDE);
	RENDERER.addShaderStreamedParameter(planeInfo, 1, ParameterType::PT_VECTOR3, Vertex::COLOR_OFFSET,    Vertex::STRIDE);
	RENDERER.addShaderStreamedParameter(planeInfo, 2, ParameterType::PT_VECTOR3, Vertex::NORMAL_OFFSET,   Vertex::STRIDE);
	RENDERER.addShaderStreamedParameter(planeInfo, 3, ParameterType::PT_VECTOR3, Vertex::UV_OFFSET,       Vertex::STRIDE);

	bool isVisible = true;
	
	testPlane = RENDERER.addRenderable(planeInfo, position, shaderInfo, isVisible, Vector4(1, 1, 1, 1.0f), RENDERER.addTexture(GenerateBasePerlinNoise()), false);
}

void TextureEditor::updateColors()
{
	testPlane->textureID = RENDERER.addTexture(MarbleType2(255, 255, red->getSpinboxValue(), green->getSpinboxValue(), blue->getSpinboxValue(), alpha->getSpinboxValue(), marbleFrequency->getSpinboxValue(), sinFrequency->getSpinboxValue()));
	//testPlane->textureID = RENDERER.addTexture(Sin(255, 255, red->getSpinboxValue(), green->getSpinboxValue(), blue->getSpinboxValue(), alpha->getSpinboxValue(), sinFrequency->getSpinboxValue()));
	//testPlane->textureID = RENDERER.addTexture(TiledPatterOne(255, 255, red->getSpinboxValue(), green->getSpinboxValue(), blue->getSpinboxValue(), alpha->getSpinboxValue()));

	float x = (float)red->getSpinboxValue() / (float)255;
	float y = (float)green->getSpinboxValue() / (float)255;
	float z = (float)blue->getSpinboxValue() / (float)255;
	float w = (float)alpha->getSpinboxValue() / (float)255;
	testPlane->color = Vector4(x, y, z, w);
}

QImage TextureEditor::UtilImageToQImage(noise::utils::Image image)
{
	
	int width = image.GetWidth(), height = image.GetHeight();
	QImage newImage(width, height, QImage::Format::Format_RGB32);

	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			newImage.setPixel(x, y, UtilColorToQColor(image.GetValue(x, y)).rgba());
		}
	}

	return newImage;
}

QColor TextureEditor::UtilColorToQColor(noise::utils::Color color)
{
	QColor newColor(color.red, color.green, color.blue, color.alpha);

	return newColor;
}

QColor TextureEditor::UtilColorToQColor(noise::utils::Color color, int mod)
{
	QColor newColor(color.red * mod % 255, color.green * mod % 255, color.blue * mod % 255, color.alpha * mod % 255);

	return newColor;
}

QImage TextureEditor::Sin(int width, int height, int red, int green, int blue, int alpha, int frequency)
{
	QImage newImage(width, height, QImage::Format::Format_RGB32);

	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			int mod = (x * frequency);
			int sinValue = (1 + sin(mod)) / 2 * 255;
			int gray = qGray(sinValue, sinValue, sinValue);
			newImage.setPixel(x, y, QColor(gray, gray, gray, gray).rgba());
		}
	}

	return newImage;
}

QImage TextureEditor::TiledPatterOne(int width, int height, int red, int green, int blue, int alpha)
{
	QImage newImage(width, height, QImage::Format::Format_RGB32);

	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			int mod = (x * y);
			int gray = qGray(red, green, blue);
			int color = gray * mod % alpha;
			newImage.setPixel(x, y, QColor(color, color, color, color).rgba());
		}
	}

	return newImage;
}

QImage TextureEditor::GenerateBasePerlinNoise()
{
	noise::module::Perlin myModule;
	noise::utils::NoiseMap heightMap;
	noise::utils::NoiseMapBuilderPlane heightMapBuilder;
	heightMapBuilder.SetSourceModule(myModule);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(256, 256);
	heightMapBuilder.SetBounds(2.0, 6.0, 1.0, 5.0);
	heightMapBuilder.Build();

	noise::utils::RendererImage imageRenderer;
	noise::utils::Image image;
	imageRenderer.SetSourceNoiseMap(heightMap);
	imageRenderer.SetDestImage(image);
	/**
	imageRenderer.ClearGradient ();
	imageRenderer.AddGradientPoint (-1.0000, noise::utils::Color (  0,   0, 128, 255)); // deeps
	imageRenderer.AddGradientPoint (-0.2500, noise::utils::Color (  0,   0, 255, 255)); // shallow
	imageRenderer.AddGradientPoint ( 0.0000, noise::utils::Color (  0, 128, 255, 255)); // shore
	imageRenderer.AddGradientPoint ( 0.0625, noise::utils::Color (240, 240,  64, 255)); // sand
	imageRenderer.AddGradientPoint ( 0.1250, noise::utils::Color ( 32, 160,   0, 255)); // grass
	imageRenderer.AddGradientPoint ( 0.3750, noise::utils::Color (224, 224,   0, 255)); // dirt
	imageRenderer.AddGradientPoint ( 0.7500, noise::utils::Color (128, 128, 128, 255)); // rock
	imageRenderer.AddGradientPoint ( 1.0000, noise::utils::Color (255, 255, 255, 255)); // snow
	imageRenderer.EnableLight();
	imageRenderer.SetLightContrast(3.0);
	imageRenderer.SetLightBrightness(2.0);
	/**/
	imageRenderer.Render();
	QImage texture = UtilImageToQImage(image);
	//QImage texture = TiledPatterOne(image.GetWidth(), image.GetHeight(), 100, 50, 100, 1);
	return texture;
}

QImage TextureEditor::MarbleType1(int width, int height, int red, int green, int blue, int alpha, int marbleFrequency)
{
	noise::module::Perlin noiseGenerator;

	QImage newImage(width, height, QImage::Format::Format_RGB32);

	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			double value1 = (double)x / (double)marbleFrequency;
			double value2 = (double)y / (double)marbleFrequency;
			double value3 = (double)(x +  y) / (double)marbleFrequency;
			double noiseValue = noiseGenerator.GetValue(value1, value2, value3);

			double mod = ((x + noiseValue) / 2) * marbleFrequency;
			int sinValue = (1 + sin(mod)) / 2 * 255;
			int gray = qGray(sinValue, sinValue, sinValue);
			newImage.setPixel(x, y, QColor(gray, gray, gray, gray).rgba());
		}
	}

	return newImage;
}

QImage TextureEditor::MarbleType2(int width, int height, int red, int green, int blue, int alpha, int marbleFrequency, int sinFrequency)
{
	noise::module::Perlin noiseGenerator;
	noise::module::Turbulence turbulenceGenerator;
	
	turbulenceGenerator.SetSourceModule(0, noiseGenerator);
	turbulenceGenerator.SetFrequency(sinFrequency * 2);
	turbulenceGenerator.SetPower(0.125);

	QImage newImage(width, height, QImage::Format::Format_RGB32);

	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			double value1 = (double)x / (double)marbleFrequency;
			double value2 = (double)y / (double)marbleFrequency;
			double value3 = (double)(x +  y) / (double)marbleFrequency;
			//double noiseValue = noiseGenerator.GetValue(value1, value2, value3);
			double noiseValue = turbulenceGenerator.GetValue(value1, value2, value3);

			double mod = ((x + noiseValue) / 2) * marbleFrequency;
			int sinValue = (1 + sin(mod)) / 2 * 255;
			int gray = qGray(sinValue, sinValue, sinValue);
			newImage.setPixel(x, y, QColor(gray, gray, gray, gray).rgba());
		}
	}

	return newImage;
}

QImage TextureEditor::WoodType1(int width, int height, int red, int green, int blue, int alpha, int woodFrequency)
{
	noise::module::Perlin noiseGenerator;

	QImage newImage(width, height, QImage::Format::Format_RGB32);

	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			double value1 = (double)x / (double)woodFrequency;
			double value2 = (double)y / (double)woodFrequency;
			double value3 = (double)(x +  y) / (double)woodFrequency;
			double noiseValue = noiseGenerator.GetValue(value1, value2, value3);

			double mod = x / woodFrequency;
			int sinValue = 2 * (mod - floor(0.5 + mod));
			int gray = qGray(sinValue, sinValue, sinValue);
			newImage.setPixel(x, y, QColor(gray, gray, gray, gray).rgba());
		}
	}

	return newImage;
}
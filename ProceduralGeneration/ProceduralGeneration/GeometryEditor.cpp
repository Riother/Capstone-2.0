#include "GeometryEditor.h"

GeometryEditor::GeometryEditor()
{
	mainLayout = new QHBoxLayout;
	mainWidget = new QWidget;

	roomSize = new LabeledSpinbox("Shape Size", true, 1, 10, 1);
	divisions = new LabeledSpinbox("Shape Detail", true, 1,  100, 10);
	showDome = new LabeledCheckBox("Show Dome", true, false);
	drawRoom = new QPushButton("Draw Room", this);
	drawDome = new QPushButton("Draw Dome", this);
	drawSphere = new QPushButton("Draw Sphere", this);
	drawColumn = new QPushButton("Draw Column", this);

	rendererLayout = new QVBoxLayout;
	guiLayout = new QVBoxLayout;

	mainLayout->addLayout(guiLayout);
	mainLayout->addLayout(rendererLayout);

	guiLayout->addWidget(roomSize);
	guiLayout->addWidget(divisions);
	guiLayout->addWidget(showDome);
	guiLayout->addWidget(drawRoom);
	guiLayout->addWidget(drawDome);
	guiLayout->addWidget(drawSphere);
	guiLayout->addWidget(drawColumn);

	rendererLayout->addWidget(&RENDERER);
	RENDERER.setMinimumSize(700, 600);
	mainWidget->setLayout(mainLayout);

	setCentralWidget(mainWidget);
	show();

	connect(roomSize, SIGNAL(valueChanged()), this, SLOT(updateValues()));
	connect(divisions, SIGNAL(valueChanged()), this, SLOT(updateValues()));
	connect(showDome, SIGNAL(stateChanged()), this, SLOT(updateValues()));
	connect(drawRoom, SIGNAL(clicked()), this, SLOT(MakeRoom()));
	connect(drawDome, SIGNAL(clicked()), this, SLOT(MakeDome()));
	connect(drawSphere, SIGNAL(clicked()), this, SLOT(MakeSphere()));
	connect(drawColumn, SIGNAL(clicked()), this, SLOT(MakeColumn()));

	/*Cube cube;
	GeometryInfo* info = RENDERER.addGeometry(cube.vertices, cube.SIZE * sizeof(Vertex), cube.indices, cube.AMOUNT_OF_VERTICES, GL_TRIANGLES);
	ShaderInfo* shader = RENDERER.createShaderInfo("SimpleVertexShaderCode.glsl", "LightFragmentShaderCode.glsl");
	Matrix4 position = glm::translate(Vector3(0, 0, 0)) * glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	bool isVisible = true;
	AddShaderStreamedParameters(info);
	int text = -2;
	RENDERER.addRenderable(info, position, shader, isVisible, glm::vec4(0, 1, 0, 1), -2);*/
	RENDERER.updateCameraSpeed(0.01f);
}

void GeometryEditor::updateValues()
{
	
}

void GeometryEditor::MakeRoom()
{
	CubeBuilder cube(roomSize->getSpinboxValue(), divisions->getSpinboxValue());
	ShaderInfo* shader = RENDERER.createShaderInfo("SimpleVertexShaderCode.glsl", "SimpleFragmentShaderCode.glsl");

	Matrix4 position = glm::translate(glm::vec3(0, 0, 0));
	bool isVisible = true;
	AddShaderStreamedParameters(cube.GetCube());
	textureID = RENDERER.addTexture("teepo.png");
	RENDERER.addRenderable(cube.GetCube(), position, shader, isVisible, glm::vec4(1, 1, 1, 1), textureID);

	////float size = roomSize->getSpinboxValue();
	//float size = 1;
	////float subdivisions = divisions->getSpinboxValue();
	//float subdivisions = 1;
	//
	//int amountOfVertices = (subdivisions + 1) * (subdivisions + 1);
	//int amountOfFaces    = 2 * (subdivisions * subdivisions);
	//int amountOfIndices  = 3 * amountOfFaces;
	//std::mt19937 rng(size * subdivisions);
	//std::uniform_int_distribution<int> gen(0, subdivisions - 1);
	//int randomColumn = gen(rng);
	//
	///std::vector<Vertex> vertices;
	//std::vector<ushort> indices;
	//
	////Top
	//float halfSize = size / 2;
	//float halfSizeX = -halfSize;
	//float halfSizeY = halfSize;
	//float halfSizeZ = halfSize;
	//float increment = size / subdivisions;
	//int nextDivision = subdivisions;
	//for(int currentVert = 0; currentVert < amountOfVertices; currentVert++)
	//{
	//	Vertex newVertex;
	//	newVertex.position = Vector3(halfSizeX, halfSizeY, halfSizeZ);
	//
	//	halfSizeX += increment;
	//	if(currentVert == nextDivision) {
	//		nextDivision += (subdivisions + 1);
	//		halfSizeZ -= increment;
	//		halfSizeX = -halfSize;
	//	}
	//	vertices.push_back(newVertex);
	//}
	//
	//ushort index1 = 0;
	//ushort index2 = index1 + 1;
	//ushort index3 = index2 + subdivisions;
	//ushort index4 = index3 + 1;
	//int maxVert = subdivisions * subdivisions;
	//int currentRow = 1;
	//int currentColumn = 0;
	//int endVert = currentRow * subdivisions - 1;
	//for(int currentVert = 0; currentVert < maxVert; currentVert++)
	//{
	//	if(currentRow <= subdivisions - 2 || currentColumn != randomColumn)
	//	{
	//		indices.push_back(index1);
	//		indices.push_back(index2);
	//		indices.push_back(index3);
	//
	//		indices.push_back(index2);
	//		indices.push_back(index3);
	//		indices.push_back(index4);
	//	}
	//
	//	currentColumn++;
	//	if(currentColumn > subdivisions - 1)
	//		currentColumn = 0;
	//
	//	if(currentVert == endVert) 
	//	{
	//		index1 += 2;
	//		currentRow++;
	//		endVert = currentRow * subdivisions - 1;;
	//
	//	}
	//	else
	//		index1++;
	//	index2 = index1 + 1;
	//	index3 = index2 + subdivisions;
	//	index4 = index3 + 1;
	//}
	//
	//////Top
	////vertices[0].position = Vector3(-size / 2, +size / 2, +size / 2);        // 0
	////vertices[0].color    = Vector4(+1.0f, +0.0f, +0.0f, +0.0f); // Color
	////vertices[0].normal   = Vector3(+0.0f, +1.0f, +0.0f);        // Normal
	////vertices[0].uv       = Vector2(+0.0f, +1.0f);               // UV
	////vertices[1].position = Vector3(+size / 2, +size / 2, +size / 2);        // 1
	////vertices[1].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	////vertices[1].normal   = Vector3(+0.0f, +1.0f, +0.0f);        // Normal
	////vertices[1].uv       = Vector2(+1.0f, +1.0f);               // UV
	////vertices[2].position = Vector3(+size / 2, +size / 2, -size / 2);		// 2
	////vertices[2].color    = Vector4(+0.0f, +0.0f, +1.0f, +0.0f); // Color
	////vertices[2].normal   = Vector3(+0.0f, +1.0f, +0.0f);		// Normal
	////vertices[2].uv       = Vector2(+1.0f, +0.0f);				// UV
	////vertices[3].position = Vector3(-size / 2, +size / 2, -size / 2);		// 3
	////vertices[3].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	////vertices[3].normal   = Vector3(+0.0f, +1.0f, +0.0f);		// Normal
	////vertices[3].uv       = Vector2(+0.0f, +0.0f);				// UV
	////
	//////Front
	////vertices[4].position = Vector3(-size / 2, +size / 2, -size / 2);		// 4
	////vertices[4].color    = Vector4(+1.0f, +0.0f, +0.0f, +0.0f); // Color
	////vertices[4].normal   = Vector3(+0.0f, +0.0f, +1.0f);		// Normal
	////vertices[4].uv       = Vector2(+0.0f, +1.0f);				// UV
	////vertices[5].position = Vector3(+size / 2, +size / 2, -size / 2);		// 5
	////vertices[5].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	////vertices[5].normal   = Vector3(+0.0f, +0.0f, +1.0f);		// Normal
	////vertices[5].uv       = Vector2(+1.0f, +1.0f);				// UV
	////vertices[6].position = Vector3(+size / 2, -size / 2, -size / 2);		// 6
	////vertices[6].color    = Vector4(+0.0f, +0.0f, +1.0f, +0.0f); // Color
	////vertices[6].normal   = Vector3(+0.0f, +0.0f, +1.0f);		// Normal
	////vertices[6].uv       = Vector2(+1.0f, +0.0f);				// UV
	////vertices[7].position = Vector3(-size / 2, -size / 2, -size / 2);		// 7
	////vertices[7].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	////vertices[7].normal   = Vector3(+0.0f, +0.0f, +1.0f);		// Normal
	////vertices[7].uv       = Vector2(+0.0f, +0.0f);				// UV
	////
	//////Right
	////vertices[8].position  = Vector3(+size / 2, +size / 2, -size / 2);        // 8
	////vertices[8].color     = Vector4(+1.0f, +0.0f, +0.0f, +0.0f); // Color
	////vertices[8].normal    = Vector3(+1.0f, +0.0f, +0.0f);		 // Normal
	////vertices[8].uv        = Vector2(+0.0f, +1.0f);				 // UV
	////vertices[9].position  = Vector3(+size / 2, +size / 2, +size / 2);		 // 9
	////vertices[9].color     = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	////vertices[9].normal    = Vector3(+1.0f, +0.0f, +0.0f);		 // Normal
	////vertices[9].uv        = Vector2(+1.0f, +1.0f);				 // UV
	////vertices[10].position = Vector3(+size / 2, -size / 2, +size / 2);		 // 10
	////vertices[10].color    = Vector4(+0.0f, +0.0f, +1.0f, +0.0f); // Color
	////vertices[10].normal   = Vector3(+1.0f, +0.0f, +0.0f);		 // Normal
	////vertices[10].uv       = Vector2(+1.0f, +0.0f);				 // UV
	////vertices[11].position = Vector3(+size / 2, -size / 2, -size / 2);		 // 11
	////vertices[11].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	////vertices[11].normal   = Vector3(+1.0f, +0.0f, +0.0f);		 // Normal
	////vertices[11].uv       = Vector2(+0.0f, +0.0f);				 // UV
	////
	//////Left
	////vertices[12].position = Vector3(-size / 2, +size / 2, +size / 2);		 // 12
	////vertices[12].color    = Vector4(+1.0f, +0.0f, +0.0f, +0.0f); // Color
	////vertices[12].normal   = Vector3(-1.0f, +0.0f, +0.0f);		 // Normal
	////vertices[12].uv       = Vector2(+0.0f, +1.0f);				 // UV
	////vertices[13].position = Vector3(-size / 2, +size / 2, -size / 2);		 // 13
	////vertices[13].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	////vertices[13].normal   = Vector3(-1.0f, +0.0f, +0.0f);		 // Normal
	////vertices[13].uv       = Vector2(+1.0f, +1.0f);				 // UV
	////vertices[14].position = Vector3(-size / 2, -size / 2, -size / 2);		 // 14
	////vertices[14].color    = Vector4(+0.0f, +0.0f, +1.0f, +0.0f); // Color
	////vertices[14].normal   = Vector3(-1.0f, +0.0f, +0.0f);		 // Normal
	////vertices[14].uv       = Vector2(+1.0f, +0.0f);				 // UV
	////vertices[15].position = Vector3(-size / 2, -size / 2, +size / 2);		 // 15
	////vertices[15].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	////vertices[15].normal   = Vector3(-1.0f, +0.0f, +0.0f);		 // Normal
	////vertices[15].uv       = Vector2(+0.0f, +0.0f);				 // UV
	////
	//////Back
	////vertices[16].position = Vector3(+size / 2, +size / 2, +size / 2);		 // 16
	////vertices[16].color    = Vector4(+1.0f, +0.0f, +0.0f, +0.0f); // Color
	////vertices[16].normal   = Vector3(+0.0f, +0.0f, -1.0f);		 // Normal
	////vertices[16].uv       = Vector2(+0.0f, +1.0f);				 // UV
	////vertices[17].position = Vector3(-size / 2, +size / 2, +size / 2);		 // 17
	////vertices[17].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	////vertices[17].normal   = Vector3(+0.0f, +0.0f, -1.0f);		 // Normal
	////vertices[17].uv       = Vector2(+1.0f, +1.0f);				 // UV
	////vertices[18].position = Vector3(-size / 2, -size / 2, +size / 2);		 // 18
	////vertices[18].color    = Vector4(+0.0f, +0.0f, +1.0f, +0.0f); // Color
	////vertices[18].normal   = Vector3(+0.0f, +0.0f, -1.0f);		 // Normal
	////vertices[18].uv       = Vector2(+1.0f, +0.0f);				 // UV
	////vertices[19].position = Vector3(+size / 2, -size / 2, +size / 2);		 // 19
	////vertices[19].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	////vertices[19].normal   = Vector3(+0.0f, +0.0f, -1.0f);		 // Normal
	////vertices[19].uv       = Vector2(+0.0f, +0.0f);				 // UV
	////
	//////Bottom
	////vertices[20].position = Vector3(+size / 2, -size / 2, -size / 2);		 // 20
	////vertices[20].color    = Vector4(+1.0f, +0.0f, +0.0f, +0.0f); // Color
	////vertices[20].normal   = Vector3(+0.0f, -1.0f, +0.0f);		 // Normal
	////vertices[20].uv       = Vector2(+0.0f, +1.0f);				 // UV
	////vertices[21].position = Vector3(-size / 2, -size / 2, -size / 2);		 // 21
	////vertices[21].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	////vertices[21].normal   = Vector3(+0.0f, -1.0f, +0.0f);		 // Normal
	////vertices[21].uv       = Vector2(+1.0f, +1.0f);				 // UV
	////vertices[22].position = Vector3(-size / 2, -size / 2, +size / 2);		 // 22
	////vertices[22].color    = Vector4(+0.0f, +0.0f, +1.0f, +0.0f); // Color
	////vertices[22].normal   = Vector3(+0.0f, -1.0f, +0.0f);		 // Normal
	////vertices[22].uv       = Vector2(+1.0f, +0.0f);				 // UV
	////vertices[23].position = Vector3(+size / 2, -size / 2, +size / 2);		 // 23
	////vertices[23].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	////vertices[23].normal   = Vector3(+0.0f, -1.0f, +0.0f);		 // Normal
	////vertices[23].uv       = Vector2(+0.0f, +0.0f);				 // UV
	//
	//std::vector<GeometryInfo*> walls;
	//RENDERER.addGeometry(&vertices[0], vertices.size() * sizeof(Vertex), &indices[0], indices.size(), GL_TRIANGLES);
	////rooms.push_back(DungeonRoom(walls, true));
	////RENDERER.addShaderStreamedParameter(cubeInfo, 0, ParameterType::PT_VECTOR3, Vertex::POSITION_OFFSET, Vertex::STRIDE);
	////RENDERER.addShaderStreamedParameter(cubeInfo, 1, ParameterType::PT_VECTOR3, Vertex::COLOR_OFFSET,    Vertex::STRIDE);
	////RENDERER.addShaderStreamedParameter(cubeInfo, 2, ParameterType::PT_VECTOR3, Vertex::NORMAL_OFFSET,   Vertex::STRIDE);
	////RENDERER.addShaderStreamedParameter(cubeInfo, 3, ParameterType::PT_VECTOR3, Vertex::UV_OFFSET,       Vertex::STRIDE);
	////
	////ShaderInfo* shaderInfo = RENDERER.createShaderInfo("SimpleVertexShaderCode.glsl", "SimpleFragmentShaderCode.glsl");
	////Matrix4 position = glm::translate(Vector3(0, 0, 0));// * glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	////RENDERER.addRenderable(cubeInfo, position, shaderInfo, isVisible, Vector4(1, 1, 1, 1.0f), -1, false);
}

void GeometryEditor::MakeDome()
{
	DomeBuilder dome(roomSize->getSpinboxValue(), divisions->getSpinboxValue());
	ShaderInfo* shader = RENDERER.createShaderInfo("SimpleVertexShaderCode.glsl", "SimpleFragmentShaderCode.glsl");
	Matrix4 position = glm::translate(glm::vec3(0, 0, 0));
	bool isVisible = true;
	AddShaderStreamedParameters(dome.GetDome());
	textureID = RENDERER.addTexture("teepo.png");
	RENDERER.addRenderable(dome.GetDome(), position, shader, isVisible, glm::vec4(1, 1, 1, 1), textureID);
#pragma region Comment
	//float size = roomSize->getSpinboxValue();
	//float subdivisions = divisions->getSpinboxValue();
	//int amountOfVertices = (subdivisions + 1) * (subdivisions + 1);
	//int amountOfFaces    = 2 * (subdivisions * subdivisions);
	//int amountOfIndices  = 3 * amountOfFaces;
	//
	//std::vector<Vertex> vertices;
	//std::vector<ushort> indices;
	//
	//float radius = size / 2;
	//
	//Vertex sphereTopPole;
	//Vector3 topPole(0, radius, 0);
	//sphereTopPole.position = topPole;
	//sphereTopPole.color = Vector4(0, 1, 0, 1);
	//vertices.push_back(sphereTopPole);
	//
	//float upDownAngle;
	//for(int row = 0; row < subdivisions; row ++)
	//{
	//	upDownAngle = 90 / subdivisions * (row + 1);
	//	for(int column = 0; column < subdivisions; column++)
	//	{
	//		Vertex newVertex;
	//		float leftRightAngle = 360 / subdivisions * column;
	//		Vector4 newPosition = (glm::vec4(topPole, 1) * glm::rotate(upDownAngle, glm::vec3(1, 0, 0))) * glm::rotate(leftRightAngle, glm::vec3(0, 1, 0));
	//		newVertex.position = glm::vec3(newPosition.x, newPosition.y, newPosition.z);
	//		vertices.push_back(newVertex);
	//	}
	//}
	//
	//Vertex sphereBotPole;
	//Vector3 botPole(0, 0, 0);
	//sphereBotPole.position = botPole;
	//vertices.push_back(sphereBotPole);
	//
	//ushort index1 = 0;
	//ushort index2 = index1 + 1;
	//ushort index3 = index2 + 1;
	//for(int currentVert = 0; currentVert < subdivisions; currentVert++)
	//{
	//	indices.push_back(index1);
	//	indices.push_back(index2);
	//	indices.push_back(index3);
	//
	//	index2++;
	//	if(index2 == subdivisions)
	//		index3 = 1;
	//	else
	//		index3 = index2 + 1;
	//}
	//
	//index1 = 1;
	//index2 = index1 + subdivisions;
	//index3 = index2 + 1;
	//ushort index4 = index1 + 1;
	//int currentRow = 1;
	//for(int currentVert = 0; currentVert < subdivisions * subdivisions - subdivisions; currentVert++)
	//{
	//	indices.push_back(index1);
	//	indices.push_back(index2);
	//	indices.push_back(index3);
	//
	//	indices.push_back(index1);
	//	indices.push_back(index3);
	//	indices.push_back(index4);
	//
	//	index1++;
	//	index2 = index1 + subdivisions;
	//	if(index1 == subdivisions * currentRow)
	//	{
	//		index3 = index1 + 1;
	//		index4 = index3 - subdivisions;
	//		currentRow++;
	//	}
	//	else
	//	{
	//		index3 = index2 + 1;
	//		index4 = index1 + 1;
	//	}
	//}
	//
	//index1 = vertices.size() - 1;
	//index2 = index1 - subdivisions;
	//index3 = index2 + 1;
	//for(int currentVert = 0; currentVert < subdivisions; currentVert++)
	//{
	//	indices.push_back(index1);
	//	indices.push_back(index2);
	//	indices.push_back(index3);
	//
	//	index2++;
	//	if(index2 == index1 - 1)
	//		index3 = index1 - subdivisions;
	//	else
	//		index3 = index2 + 1;
	//}
	//
	////RENDERER.addGeometry(&vertices[0], vertices.size() * sizeof(Vertex), &indices[0], indices.size(), GL_TRIANGLES);
	////rooms.push_back(DungeonRoom(walls));
	//RENDERER.updateCameraSpeed(0.01f);
#pragma endregion Comment
}

void GeometryEditor::MakeSphere()
{
	SphereBuilder sphere(roomSize->getSpinboxValue(), divisions->getSpinboxValue());
	ShaderInfo* shader = RENDERER.createShaderInfo("SimpleVertexShaderCode.glsl", "SimpleFragmentShaderCode.glsl");
	Matrix4 position = glm::translate(glm::vec3(0, 0, 0));
	bool isVisible = true;
	AddShaderStreamedParameters(sphere.GetSphere());
	textureID = RENDERER.addTexture("teepo.png");
	RENDERER.addRenderable(sphere.GetSphere(), position, shader, isVisible, glm::vec4(1, 1, 1, 1), textureID);
}

void GeometryEditor::MakeColumn()
{
	CylinderBuilder cylinder(roomSize->getSpinboxValue(), divisions->getSpinboxValue());
	ShaderInfo* shader = RENDERER.createShaderInfo("SimpleVertexShaderCode.glsl", "SimpleFragmentShaderCode.glsl");
	Matrix4 position = glm::translate(glm::vec3(0, 0, 0));
	bool isVisible = true;
	AddShaderStreamedParameters(cylinder.GetCylinder());
	textureID = RENDERER.addTexture("teepo.png");
	RENDERER.addRenderable(cylinder.GetCylinder(), position, shader, isVisible, glm::vec4(1, 1, 1, 1), textureID);
}

Vector2 GeometryEditor::CartesianToCylindrical(Vector3 cartesianVector, float radius)
{
	float x = cartesianVector.x;
	float y = cartesianVector.y;
	float z = abs(cartesianVector.z);

	Vector2 cylindricalVector;
	//float r = sqrt((x * x)+(y * y));
	float theta = abs(atan2(y, x));

	//cylindricalVector.x = r;
	cylindricalVector.x = theta;
	cylindricalVector.y = z;

	qDebug()<<theta<<", "<<z;

	return cylindricalVector;
}

void GeometryEditor::AddShaderStreamedParameters(GeometryInfo* info)
{
	RENDERER.addShaderStreamedParameter(info, 0, ParameterType::PT_VECTOR3, Vertex::POSITION_OFFSET, Vertex::STRIDE);
	RENDERER.addShaderStreamedParameter(info, 1, ParameterType::PT_VECTOR3, Vertex::COLOR_OFFSET,    Vertex::STRIDE);
	RENDERER.addShaderStreamedParameter(info, 2, ParameterType::PT_VECTOR3, Vertex::NORMAL_OFFSET,   Vertex::STRIDE);
	RENDERER.addShaderStreamedParameter(info, 3, ParameterType::PT_VECTOR3, Vertex::UV_OFFSET,       Vertex::STRIDE);
}
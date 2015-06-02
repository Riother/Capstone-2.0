#include "DungeonGraph.h"

DungeonGraph::DungeonGraph()
{
	mainLayout = new QVBoxLayout;

	dungeonLength = new LabeledSpinbox("Dungeon Length", true, 1, 100, 50);
	dungeonWidth = new LabeledSpinbox("Dungeon Width", true, 1, 100, 50);
	dungeonHeight = new LabeledSpinbox("Dungeon Height", true, 1, 1, 1);
	numberOfRooms = new LabeledSpinbox("Amount of Rooms", true, 1, 100, 10);
	placeAttempts = new LabeledSpinbox("Place Attempts", true, 1, 100, 10);
	minRoomLength = new LabeledSpinbox("Min Room Length", true, 1, 10, 3);
	maxRoomLength = new LabeledSpinbox("Max Room Length", true, 1, 10, 6);
	minRoomWidth = new LabeledSpinbox("Min Room Width", true, 1, 10, 4);
	maxRoomWidth = new LabeledSpinbox("Max Room Width", true, 1, 10, 6);
	hallways = new LabeledSpinbox("Amount of Halls", true, 1, 100, 50);

	showRoofs = new LabeledCheckBox("Show Roofs", true, false);
	showRooms = new LabeledCheckBox("Show Rooms", true, false);
	showHalls = new LabeledCheckBox("Show Halls", true, false);

	updateDimensions = new QPushButton("Update Dimensions", this);

	mainLayout->addWidget(dungeonLength);
	mainLayout->addWidget(dungeonWidth);
	//guiLayout->addWidget(dungeonHeight);
	
	mainLayout->addWidget(numberOfRooms);
	mainLayout->addWidget(placeAttempts);
	mainLayout->addWidget(minRoomLength);
	mainLayout->addWidget(maxRoomLength);
	mainLayout->addWidget(minRoomWidth);
	mainLayout->addWidget(maxRoomWidth);
	//guiLayout->addWidget(hallways);
	
	//guiLayout->addWidget(showRoofs);
	mainLayout->addWidget(showRooms);
	mainLayout->addWidget(showHalls);

	mainLayout->addWidget(updateDimensions);

	setLayout(mainLayout);
	show();

	//connect(dungeonLength, SIGNAL(valueChanged()), this, SLOT(updateValues()));
	//connect(dungeonWidth, SIGNAL(valueChanged()), this, SLOT(updateValues()));
	////connect(dungeonHeight, SIGNAL(valueChanged()), this, SLOT(updateValues()));

	//connect(numberOfRooms, SIGNAL(valueChanged()), this, SLOT(updateDungeon()));
	//connect(minRoomLength, SIGNAL(valueChanged()), this, SLOT(updateDungeon()));
	//connect(maxRoomLength, SIGNAL(valueChanged()), this, SLOT(updateDungeon()));
	//connect(minRoomWidth, SIGNAL(valueChanged()), this, SLOT(updateDungeon()));
	//connect(maxRoomWidth, SIGNAL(valueChanged()), this, SLOT(updateDungeon()));

	//connect(showRoofs, SIGNAL(stateChanged()), this, SLOT(updateSettings()));
	connect(showRooms, SIGNAL(stateChanged()), this, SLOT(updateSettings()));
	connect(showHalls, SIGNAL(stateChanged()), this, SLOT(updateSettings()));
	connect(updateDimensions, SIGNAL(clicked()), this, SLOT(updateDungeon()));

	isLoaded = false;
	corridorTexture = -1;
	roomTexture = -1;
	noTexture = -1;
	
}

void DungeonGraph::updateDungeon()
{
	ClearGraph();
	PrepareGraph();
	CreateRooms();
	CreateHalls();
	DrawDungeon();
}

void DungeonGraph::updateSettings()
{

}

void DungeonGraph::ClearGraph()
{
	if(isLoaded)
	{
		for(int i = 0; i < width; i++)
		{
			delete [] dungeon[i];
		}
		delete [] dungeon;

		isLoaded = false;
	}

	width = dungeonWidth->getSpinboxValue();
	length = dungeonLength->getSpinboxValue();
}

void DungeonGraph::PrepareGraph()
{
	dungeon = new DungeonNode*[width];

	for(int i = 0; i < width; i++)
	{
		dungeon[i] = new DungeonNode[length];
		for(int j = 0; j < length; j++)
		{
			dungeon[i][j].floorType = DungeonNode::FloorType::Wall;
			dungeon[i][j].isVisited = false;
		}
	}

	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < length; j++)
		{
			SetLeftNeighbor(i, j);
			SetTopNeighbor(i, j);
			SetRightNeighbor(i, j);
			SetBotNeighbor(i, j);
		}
	}
	PrintDungeon("Empty.txt");
}

void DungeonGraph::CreateRooms()
{
	int rooms = 0;

	std::mt19937 rng(length * width + numberOfRooms->getSpinboxValue());
	std::uniform_int_distribution<int> randomX(0, width - 1);
	std::uniform_int_distribution<int> randomY(0, length - 1);

	int attempts = 0;
	while(rooms < numberOfRooms->getSpinboxValue() && attempts < placeAttempts->getSpinboxValue())
	{
		if(PlaceRoom(randomX(rng), randomY(rng), rooms))
		{
			rooms++;
			roomDoors.push_back(false);
			qDebug()<<"Room "<<rooms<<" placed.";
		}
		else
			attempts++;
		//PrintDungeon("Room " + std::to_string(rooms) + ".txt");
	}
	qDebug()<<"Rooms Placed";
	PrintDungeon("AllRooms.txt");
}

bool DungeonGraph::PlaceRoom(int locationX, int locationY, int roomNumber)
{
	bool placed = true;

	std::mt19937 rng(minRoomLength->getSpinboxValue() * maxRoomLength->getSpinboxValue() * minRoomWidth->getSpinboxValue() * maxRoomWidth->getSpinboxValue() + locationX + locationY);
	std::uniform_int_distribution<int> randomWidth(minRoomWidth->getSpinboxValue(), maxRoomWidth->getSpinboxValue());
	std::uniform_int_distribution<int> randomLength(minRoomLength->getSpinboxValue(), maxRoomLength->getSpinboxValue());

	int roomWidth = randomWidth(rng);
	int roomLength = randomLength(rng);

	for(int i = 0; i <= roomWidth + 1 && placed; i++)
	{
		for(int j = 0; j <= roomLength + 1 && placed; j++)
		{
			int x;
			if(locationX - i > 0)
				x = locationX - i;
			else
			{
				placed = false;
				break;
			}

			int y;
			if(locationY - j > 0)
				y = locationY - j;
			else
			{
				placed = false;
				break;
			}

			if(dungeon[x][y].floorType != DungeonNode::FloorType::Wall)
			{
				placed = false;
			}
			
		}
	}

	if(placed)
	{
		for(int i = 0; i <= roomWidth + 1 && placed; i++)
		{
			for(int j = 0; j <= roomLength + 1 && placed; j++)
			{
				int x;
				if(locationX - i > 0)
					x = locationX - i;

				int y;
				if(locationY - j > 0)
					y = locationY - j;

				if(x == 33 && y == 10)
					qDebug()<<"Here";

				if((i > 0 && i < roomWidth + 1) && (j > 0 && j < roomLength + 1))
				{
					dungeon[x][y].floorType = DungeonNode::FloorType::Room;
					dungeon[x][y].isVisited = true;
				}
				else {
					dungeon[x][y].floorType = DungeonNode::FloorType::Wall;
					dungeon[x][y].isVisited = true;
					dungeon[x][y].roomNumber = roomNumber;
				}
			}
		}
	}

	return placed;
}

void DungeonGraph::CreateHalls()
{
	std::mt19937 rng(numberOfRooms->getSpinboxValue() * placeAttempts->getSpinboxValue());
	std::uniform_int_distribution<int> rndW(0, width - 1);
	std::uniform_int_distribution<int> rndL(0, length - 1);

	//while(!AllCellsVisited())
	//{
		int x = rndW(rng);
		int y = rndL(rng);

		while(dungeon[x][y].isVisited) {
			x = rndW(rng);
			y = rndL(rng);
		}
		
		std::mt19937 direction(x*y + 1);
		std::uniform_int_distribution<int> rngDir(0, 3);
		
		std::stack<DungeonNode*> nextCell;
		nextCell.push(&dungeon[x][y]);

		DungeonNode* temp;
		bool hasSpace = true;
		while(!nextCell.empty())
		{
			temp = nextCell.top();
			nextCell.pop();

			if(!temp->isVisited)
			{
				temp->floorType = DungeonNode::FloorType::Hall;
				if(HasValidNeighbors(temp)) 
				{
					std::vector<DungeonNode*> possibleDirections;

					if(temp->leftNeighbor)
					{
						if(IsValidNeighbor(temp->leftNeighbor))
						{
							possibleDirections.push_back(temp->leftNeighbor);
						}
					}

					if(temp->topNeighbor)
					{
						if(IsValidNeighbor(temp->topNeighbor))
						{
							possibleDirections.push_back(temp->topNeighbor);
						}
					}

					if(temp->rightNeighbor)
					{
						if(IsValidNeighbor(temp->rightNeighbor))
						{
							possibleDirections.push_back(temp->rightNeighbor);
						}
					}

					if(temp->botNeighbor)
					{
						if(IsValidNeighbor(temp->botNeighbor))
						{
							possibleDirections.push_back(temp->botNeighbor);
						}
					}

					if(possibleDirections.size() > 1)
					{
						std::uniform_int_distribution<int> rnd(0, possibleDirections.size() - 1);

						int random = rnd(rng);
						nextCell.push(temp);
						nextCell.push(possibleDirections[random]);
					}
					else if(possibleDirections.size() == 1)
					{
						nextCell.push(temp);
						nextCell.push(possibleDirections[0]);
					}
					else
						temp->isVisited = true;
				}
				else
					temp->isVisited = true;
			}
		}
	//}

	qDebug()<<"Done Generating Halls";
	PrintDungeon("Completed Dungeon.txt");
}

bool DungeonGraph::HasValidNeighbors(DungeonNode* node)
{
	bool valid = false;

	if(node->leftNeighbor)
	{
		if(IsValidNeighbor(node->leftNeighbor))
			valid = true;
	}

	if(node->topNeighbor)
	{
		if(IsValidNeighbor(node->topNeighbor))
			valid = true;
	}

	if(node->rightNeighbor)
	{
		if(IsValidNeighbor(node->rightNeighbor))
			valid = true;
	}

	if(node->botNeighbor)
	{
		if(IsValidNeighbor(node->botNeighbor))
			valid = true;
	}

	return valid;
}

bool DungeonGraph::IsValidNeighbor(DungeonNode* node)
{
	bool valid = false;

	if(!node->isVisited && node->floorType == DungeonNode::FloorType::Wall && HasMoreThanTwoWalls(node))
		valid = true;

	return valid;
}

bool DungeonGraph::HasMoreThanTwoWalls(DungeonNode* node)
{
	int wallCount = 0;

	if(node->leftNeighbor)
	{
		if(node->leftNeighbor->floorType == DungeonNode::FloorType::Wall)
			wallCount++;
	}

	if(node->topNeighbor)
	{
		if(node->topNeighbor->floorType == DungeonNode::FloorType::Wall)
			wallCount++;
	}

	if(node->rightNeighbor)
	{
		if(node->rightNeighbor->floorType == DungeonNode::FloorType::Wall)
			wallCount++;
	}

	if(node->botNeighbor)
	{
		if(node->botNeighbor->floorType == DungeonNode::FloorType::Wall)
			wallCount++;
	}

	bool valid = false;
	if(wallCount > 2)
		valid = true;

	return valid;
}

bool DungeonGraph::IsValidWall(DungeonNode* node)
{
	bool valid = false;

	if(node->leftNeighbor)
	{
		if(node->leftNeighbor->floorType == DungeonNode::FloorType::Hall || node->leftNeighbor->floorType == DungeonNode::FloorType::Room)
			valid = true;
	}

	if(node->topNeighbor)
	{
		if(node->topNeighbor->floorType == DungeonNode::FloorType::Hall || node->topNeighbor->floorType == DungeonNode::FloorType::Room)
			valid = true;
	}

	if(node->rightNeighbor)
	{
		if(node->rightNeighbor->floorType == DungeonNode::FloorType::Hall || node->rightNeighbor->floorType == DungeonNode::FloorType::Room)
			valid = true;
	}

	if(node->botNeighbor)
	{
		if(node->botNeighbor->floorType == DungeonNode::FloorType::Hall || node->botNeighbor->floorType == DungeonNode::FloorType::Room)
			valid = true;
	}

	return valid;
}

bool DungeonGraph::IsValidDoor(DungeonNode* node)
{
	bool hasRoom = false;
	bool hasHall = false;

	if(node->leftNeighbor)
	{
		if(node->leftNeighbor->floorType == DungeonNode::FloorType::Hall)
			hasHall = true;
		else if(node->leftNeighbor->floorType == DungeonNode::FloorType::Room)
			hasRoom = true;
	}

	if(node->topNeighbor)
	{
		if(node->topNeighbor->floorType == DungeonNode::FloorType::Hall)
			hasHall = true;
		else if(node->topNeighbor->floorType == DungeonNode::FloorType::Room)
			hasRoom = true;
	}

	if(node->rightNeighbor)
	{
		if(node->rightNeighbor->floorType == DungeonNode::FloorType::Hall)
			hasHall = true;
		else if(node->rightNeighbor->floorType == DungeonNode::FloorType::Room)
			hasRoom = true;
	}

	if(node->botNeighbor)
	{
		if(node->botNeighbor->floorType == DungeonNode::FloorType::Hall)
			hasHall = true;
		else if(node->botNeighbor->floorType == DungeonNode::FloorType::Room)
			hasRoom = true;
	}

	return hasRoom && hasHall && !roomDoors[node->roomNumber];
}

void DungeonGraph::SetLeftNeighbor(int x, int y)
{
	if(x > 0)
		dungeon[x][y].leftNeighbor = &dungeon[x - 1][y];
	else 
		dungeon[x][y].leftNeighbor = nullptr;
}

void DungeonGraph::SetTopNeighbor(int x, int y)
{
	if(y > 0)
		dungeon[x][y].topNeighbor = &dungeon[x][y - 1];
	else 
		dungeon[x][y].topNeighbor = nullptr;
}

void DungeonGraph::SetRightNeighbor(int x, int y)
{
	if(x < width - 1)
		dungeon[x][y].rightNeighbor = &dungeon[x + 1][y];
	else 
		dungeon[x][y].rightNeighbor = nullptr;
}

void DungeonGraph::SetBotNeighbor(int x, int y)
{
	if(y < length - 1)
		dungeon[x][y].botNeighbor = &dungeon[x][y + 1];
	else 
		dungeon[x][y].botNeighbor = nullptr;
}

void DungeonGraph::PrintDungeon(std::string filename)
{
	ClearDoors();
	std::ofstream out(filename);
	//QDebug debug = qDebug();
	for(int i = 0; i < dungeonWidth->getSpinboxValue(); i++)
	{
		for(int j = 0; j < dungeonLength->getSpinboxValue(); j++)
		{
			if(dungeon[i][j].floorType == DungeonNode::FloorType::Wall)
			{
				if(IsValidDoor(&dungeon[i][j]))
				{
					out<<" ";
					dungeon[i][j].floorType = DungeonNode::FloorType::Hall;
					roomDoors[dungeon[i][j].roomNumber] = true;
				}
				else
				{
					out<<"#";
				}
				//debug<<"|";
			}
			else if(dungeon[i][j].floorType == DungeonNode::FloorType::Hall)
			{
				out<<" ";
			}
			else if(dungeon[i][j].floorType == DungeonNode::FloorType::Room)
			{
				out<<" ";
				//debug<<" ";
			}
			else if(dungeon[i][j].floorType == DungeonNode::FloorType::Empty)
			{
				out<<"X";
				//debug<<"X";
			}
		}
		out<<"\r\n";
		//debug<<endl;
	}
	out<<"\r\n";
	out.close();
}

void DungeonGraph::ClearDoors()
{
	for(int i = 0; i < roomDoors.size(); i++)
	{
		roomDoors[i] = false;
	}
}

void DungeonGraph::DrawDungeon()
{
	RENDERER.clearGeometries();
	RENDERER.clearRenderables();
	RENDERER.clearShaders();
	ShaderInfo* shader = RENDERER.createShaderInfo("SimpleVertexShaderCode.glsl", "SimpleFragmentShaderCode.glsl");
	Plane plane;
	GeometryInfo* planeInfo = RENDERER.addGeometry(plane.vertices, plane.SIZE * sizeof(Vertex), plane.indices, plane.AMOUNT_OF_VERTICES, GL_TRIANGLES);
	GeometryInfo* cubeInfo = RENDERER.addGeometry(cube.vertices, cube.SIZE * sizeof(Vertex), cube.indices, cube.AMOUNT_OF_VERTICES, GL_TRIANGLES);
	AddShaderStreamedParameters(planeInfo);
	AddShaderStreamedParameters(cubeInfo);
	Matrix4 position = glm::translate(Vector3(0, 0, 0));// * glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	bool isVisible = true;

	for(int i = 0; i < dungeonWidth->getSpinboxValue(); i++)
	{
		for(int j = 0; j < dungeonLength->getSpinboxValue(); j++)
		{
			if(dungeon[i][j].floorType == DungeonNode::FloorType::Hall)
			{
				position = glm::translate(i, 0, j);
				corridors.push_back(RENDERER.addRenderable(planeInfo, position, shader, isVisible, Vector4(1, 1, 1, 1.0f), corridorTexture, false));
			}
			else if(dungeon[i][j].floorType == DungeonNode::FloorType::Room)
			{
				position = glm::translate(i, 0, j);
				rooms.push_back(RENDERER.addRenderable(planeInfo, position, shader, isVisible, Vector4(1, 1, 1, 1.0f), roomTexture, false));
			}
			else if(dungeon[i][j].floorType == DungeonNode::FloorType::Wall)
			{
				if(IsValidDoor(&dungeon[i][j]))
				{
					position = glm::translate(i, 0, j);
					RENDERER.addRenderable(planeInfo, position, shader, isVisible, Vector4(0, 1, 0, 1.0f), noTexture, false);
					roomDoors[dungeon[i][j].roomNumber] = true;
				}
				else if(IsValidWall(&dungeon[i][j]))
				{
					position = glm::translate(i, 1, j);
					walls.push_back(RENDERER.addRenderable(cubeInfo, position, shader, isVisible, Vector4(0.5f, 0.5f, 0.5f, 1.f), wallTexture, false));
				}
			}
		}
	}
	qDebug()<<"Finished drawing dungeon.";
}

void DungeonGraph::AddShaderStreamedParameters(GeometryInfo* info)
{
	RENDERER.addShaderStreamedParameter(info, 0, ParameterType::PT_VECTOR3, Vertex::POSITION_OFFSET, Vertex::STRIDE);
	RENDERER.addShaderStreamedParameter(info, 1, ParameterType::PT_VECTOR3, Vertex::COLOR_OFFSET,    Vertex::STRIDE);
	RENDERER.addShaderStreamedParameter(info, 2, ParameterType::PT_VECTOR3, Vertex::NORMAL_OFFSET,   Vertex::STRIDE);
	RENDERER.addShaderStreamedParameter(info, 3, ParameterType::PT_VECTOR3, Vertex::UV_OFFSET,       Vertex::STRIDE);
}

void DungeonGraph::setCorridorFloorTexture(int cTexture)
{
	corridorTexture = cTexture;

	/*for(int i = 0; i < corridors.size(); i++)
	{
		corridors.at(i)->textureID = corridorTexture;
	}*/
}

void DungeonGraph::setRoomFloorTexture(int rTexture)
{
	roomTexture = rTexture;

	/*for(int i = 0; i < rooms.size(); i++)
	{
		rooms.at(i)->textureID = roomTexture;
	}*/
}

void DungeonGraph::setWallTexture(int wTexture)
{
	wallTexture = wTexture;
}


void DungeonGraph::updateTextures()
{
	

	
}
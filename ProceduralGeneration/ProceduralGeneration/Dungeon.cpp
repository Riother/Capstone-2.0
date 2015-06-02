#include "Dungeon.h"

Dungeon::Dungeon()
{
	mainLayout = new QHBoxLayout;
	mainWidget = new QWidget;

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

	rendererLayout = new QVBoxLayout;
	guiLayout = new QVBoxLayout;

	mainLayout->addLayout(guiLayout);
	mainLayout->addLayout(rendererLayout);

	guiLayout->addWidget(dungeonLength);
	guiLayout->addWidget(dungeonWidth);
	//guiLayout->addWidget(dungeonHeight);
	
	guiLayout->addWidget(numberOfRooms);
	guiLayout->addWidget(placeAttempts);
	guiLayout->addWidget(minRoomLength);
	guiLayout->addWidget(maxRoomLength);
	guiLayout->addWidget(minRoomWidth);
	guiLayout->addWidget(maxRoomWidth);
	//guiLayout->addWidget(hallways);
	
	//guiLayout->addWidget(showRoofs);
	guiLayout->addWidget(showRooms);
	guiLayout->addWidget(showHalls);

	guiLayout->addWidget(updateDimensions);

	rendererLayout->addWidget(&RENDERER);
	RENDERER.setMinimumSize(700, 600);
	mainWidget->setLayout(mainLayout);

	setCentralWidget(mainWidget);
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

	prevLength = dungeonLength->getSpinboxValue();
	prevWidth = dungeonWidth->getSpinboxValue();
	prevHeight = dungeonHeight->getSpinboxValue();

	loadedDungeon = false;
}

void Dungeon::updateDungeon()
{
	ClearDungeon();
	PrepareDungeon();
}

void Dungeon::updateSettings()
{

}

void Dungeon::ClearDungeon()
{
	if(loadedDungeon)
	{
		for(int i = 0; i < prevWidth; i ++)
		{
			delete [] cells[i];
		}
		delete [] cells;
	}

	prevWidth = dungeonWidth->getSpinboxValue();
	prevLength = dungeonLength->getSpinboxValue();
	prevHeight = dungeonHeight->getSpinboxValue();
}

void Dungeon::PrepareDungeon()
{
	cells = new Cell*[dungeonWidth->getSpinboxValue()];

	for(int i = 0; i < dungeonWidth->getSpinboxValue(); i++)
	{
		cells[i] = new Cell[dungeonLength->getSpinboxValue()];
		for(int j = 0; j < dungeonLength->getSpinboxValue(); j++)
		{
			if(i == 0 || i == dungeonWidth->getSpinboxValue() - 1)
				cells[i][j] = Cell(Cell::Type::Wall, i, j, true);
			else if(j == 0 || j == dungeonLength->getSpinboxValue() - 1)
				cells[i][j] = Cell(Cell::Type::Wall, i, j, true);
			else
				cells[i][j] = Cell(Cell::Type::None, i, j, false);
		}
	}

	PrintDungeon("Empty.txt");
	CreateDungeon();
}

void Dungeon::CreateDungeon()
{
	//Place Rooms
	int rooms = 0;

	std::mt19937 rng(prevLength * prevWidth * dungeonHeight->getSpinboxValue() + numberOfRooms->getSpinboxValue());
	std::uniform_int_distribution<int> randomWidth(1, prevWidth - 1);
	std::uniform_int_distribution<int> randomLength(1, prevLength - 1);

	//int attempts = 0;
	//while(rooms < numberOfRooms->getSpinboxValue() && attempts < placeAttempts->getSpinboxValue())
	//{
	//	

	//	if(CreateRoom(randomWidth(rng), randomLength(rng), 0))
	//	{
	//		rooms++;
	//		qDebug()<<rooms;
	//	}
	//	else
	//		attempts++;
	//	//PrintDungeon("Room " + std::to_string(rooms) + ".txt");
	//}
	PrintDungeon("AllRooms.txt");

	CreateHalls();

	PrintDungeon("Dungeon.txt");

	DrawDungeon();
}

bool Dungeon::CreateRoom(int width, int length, int height)
{
	bool placed = true;
	std::mt19937 rng(minRoomLength->getSpinboxValue() * maxRoomLength->getSpinboxValue() * minRoomWidth->getSpinboxValue() * maxRoomWidth->getSpinboxValue() + width + length + height);
	std::uniform_int_distribution<int> randomWidth(minRoomWidth->getSpinboxValue(), maxRoomWidth->getSpinboxValue());
	std::uniform_int_distribution<int> randomLength(minRoomLength->getSpinboxValue(), maxRoomLength->getSpinboxValue());

	int roomWidth = randomWidth(rng);
	int roomLength = randomLength(rng);

	for(int i = 0; i <= roomWidth + 1 && placed; i++)
	{
		for(int j = 0; j <= roomLength + 1 && placed; j++)
		{
			int x;
			if(width - i > 0)
				x = width - i;
			/*else if(width + i < dungeonWidth->getSpinboxValue() - 1)
				x = width + i;*/
			else
			{
				placed = false;
				break;
			}

			int y;
			if(length - j > 0)
				y = length - j;
			/*else if(length + j < dungeonLength->getSpinboxValue() - 1)
				y = length + j;*/
			else
			{
				placed = false;
				break;
			}

		
			if(cells[x][y].isEdgeCell || cells[x][y].spaceType != Cell::Type::None)
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
				if(width - i > 0)
					x = width - i;
				/*else if(width + i < dungeonWidth->getSpinboxValue() - 1)
					x = width + i;*/

				int y;
				if(length - j > 0)
					y = length - j;
			/*	else if(length + j < dungeonLength->getSpinboxValue() - 1)
					y = length + j;*/

				if((i > 0 && i < roomWidth + 1) && (j > 0 && j < roomLength + 1))
				{
					cells[x][y].spaceType = Cell::Type::Room;
					cells[x][y].isVisited = true;
				}
				else {
					cells[x][y].spaceType = Cell::Type::Wall;
					cells[x][y].isVisited = true;
				}
			}
		}
	}

	/*if(!cells[width][length].isEdgeCell && !cells[width][length].None)
	{
		cells[width][length].spaceType = Cell::Type::Room;
	}*/

	return placed;
}

void Dungeon::CreateHalls()
{
	std::mt19937 rng(numberOfRooms->getSpinboxValue() * placeAttempts->getSpinboxValue());
	std::uniform_int_distribution<int> rndW(1, prevWidth - 1);
	std::uniform_int_distribution<int> rndL(1, prevLength - 1);

	//while(!AllCellsVisited())
	//{
		int x = rndW(rng);
		int y = rndL(rng);

		while(!cells[x][y].isEmpty()) {
			x = rndW(rng);
			y = rndL(rng);
		}
		
		std::mt19937 direction(x*y);
		std::uniform_int_distribution<int> rngDir(0, 3);
		
		std::stack<Cell*> nextCell;
		std::stack<int> prev;
		nextCell.push(&cells[x][y]);
		prev.push(5);
		
		Cell* temp;
		bool hasSpace = true;
		while(!nextCell.empty())
		{
			temp = nextCell.top();
			nextCell.pop();

			if(!temp->isVisited && CheckForSpaces(temp->x, temp->y) <= 1)
			{
				int left = temp->x - 1;
				int top = temp->y - 1;
				int right = temp->x + 1;
				int bot = temp->y + 1;
				if((left > 0 && right < prevWidth) && (top > 0 && bot < prevLength))
				{
					temp->isVisited = true;
					if(temp->isEmpty())// && ((cells[left][temp->y].isEmpty() && cells[right][temp->y].isEmpty()) 	|| (cells[temp->x][top].isEmpty() && cells[temp->x][bot].isEmpty())))
					{
						if(ConnectedToBlank(temp->x, temp->y, prev.top()))
							temp->spaceType = Cell::Type::Hall;

						prev.pop();

						std::vector<glm::vec3> possibleDirections;

						if(cells[temp->x][top].isEmpty() && !cells[temp->x][top].isVisited && ConnectedToBlank(temp->x, top, 0))
							possibleDirections.push_back(glm::vec3(temp->x, top, 0));

						if(cells[right][temp->y].isEmpty() && !cells[right][temp->y].isVisited && ConnectedToBlank(right, temp->y, 1))
							possibleDirections.push_back(glm::vec3(right, temp->y, 1));

						if(cells[temp->x][bot].isEmpty() && !cells[temp->x][bot].isVisited && ConnectedToBlank(temp->x, bot, 2))
							possibleDirections.push_back(glm::vec3(temp->x, bot, 2));

						if(cells[left][temp->y].isEmpty() && !cells[left][temp->y].isVisited && ConnectedToBlank(left, temp->y, 3))
							possibleDirections.push_back(glm::vec3(left, temp->y, 3));

						if(possibleDirections.size() > 1)
						{
							std::uniform_int_distribution<int> rnd(0, possibleDirections.size() - 1);

							int random = rnd(rng);
							std::random_shuffle(possibleDirections.begin(), possibleDirections.end());
						}

						if(possibleDirections.size() > 0)
						{
							for(int i = 0; i < possibleDirections.size(); i++)
							{
								int nextX = possibleDirections[i].x;
								int nextY = possibleDirections[i].y;
								int nextZ = possibleDirections[i].z;
								nextCell.push(&cells[nextX][nextY]);
								prev.push(nextZ);
							}
						}
					}
				}
			}
		}
	//}
	qDebug()<<"Done Generating Halls";
}

glm::vec2 Dungeon::PickDirection(int x, int y)
{
	std::vector<glm::vec2> possibleDirections;

	if(cells[x][y - 1].isEmptyOrWall() && !cells[x][y - 1].isVisited)
		possibleDirections.push_back(glm::vec2(x, y - 1));

	if(cells[x + 1][y].isEmptyOrWall() && !cells[x + 1][y].isVisited)
			possibleDirections.push_back(glm::vec2(x + 1, y));

	if(cells[x][y + 1].isEmptyOrWall() && !cells[x][y + 1].isVisited)
			possibleDirections.push_back(glm::vec2(x, y + 1));

	if(cells[x - 1][y].isEmptyOrWall() && !cells[x - 1][y].isVisited)
			possibleDirections.push_back(glm::vec2(x - 1, y));

	std::mt19937 rng(x * y);
	std::uniform_int_distribution<int> rnd(0, possibleDirections.size() - 1);

	return possibleDirections.at(rnd(rng));
}

bool Dungeon::AllCellsVisited()
{
	for(int i = 0; i < prevWidth; i++)
	{
		for(int j = 0; j < prevLength; j++)
		{
			if(!cells[i][j].isVisited)
				return false;
		}
	}
	return true;
}

bool Dungeon::ConnectedToBlank(int x, int y, int previousDirection)
{
	if(y + 1 < prevLength && previousDirection != 0)
	{
		if(!cells[x][y + 1].isEmpty())
			return false;
	}
	if(x + 1 < prevWidth && previousDirection != 3)
	{
		if(!cells[x + 1][y].isEmpty())
			return false;
	}

	if(y - 1 > 0 && previousDirection != 2)
	{
		if(!cells[x][y - 1].isEmpty())
			return false;
	}

	if(x - 1 > 0 && previousDirection != 1)
	{
		if(!cells[x - 1][y].isEmpty())
			return false;
	}

	return true;
}

int Dungeon::CheckForSpaces(int x, int y)
{
	int count = 0;
	if(y + 1 < prevLength)
	{
		if(!cells[x][y + 1].isEmpty())
			count++;
	}
	if(x + 1 < prevWidth)
	{
		if(!cells[x + 1][y].isEmpty())
			count++;
	}

	if(y - 1 > 0)
	{
		if(!cells[x][y - 1].isEmpty())
			count++;
	}

	if(x - 1 > 0)
	{
		if(!cells[x - 1][y].isEmpty())
			count++;
	}
	return count;
}

void Dungeon::PrintDungeon(std::string fileName)
{
	std::ofstream out(fileName);
	//qDebug() << dungeonWidth->getSpinboxValue() << " " << dungeonLength->getSpinboxValue();
	//QDebug debug = qDebug();
	for(int i = 0; i < dungeonWidth->getSpinboxValue(); i++)
	{
		for(int j = 0; j < dungeonLength->getSpinboxValue(); j++)
		{
			if(cells[i][j].spaceType == Cell::Type::Wall)
			{
				out<<"|";
				//debug<<"|";
			}
			else if(cells[i][j].spaceType == Cell::Type::Hall)
			{
				out<<" ";
			}
			else if(cells[i][j].spaceType == Cell::Type::Room)
			{
				out<<" ";
				//debug<<" ";
			}
			else if(cells[i][j].spaceType == Cell::Type::None)
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

void Dungeon::DrawDungeon()
{
	ShaderInfo* shader = RENDERER.createShaderInfo("SimpleVertexShaderCode.glsl", "SimpleFragmentShaderCode.glsl");
	Plane plane;
	GeometryInfo* planeInfo = RENDERER.addGeometry(plane.vertices, plane.SIZE * sizeof(Vertex), plane.indices, plane.AMOUNT_OF_VERTICES, GL_TRIANGLES);
	AddShaderStreamedParameters(planeInfo);
	Matrix4 position = glm::translate(Vector3(0, 0, 0));// * glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	bool isVisible = true;
	int text = -1;
	for(int i = 0; i < dungeonWidth->getSpinboxValue(); i++)
	{
		for(int j = 0; j < dungeonLength->getSpinboxValue(); j++)
		{
			if(cells[i][j].spaceType == Cell::Type::Hall)
			{
				position = glm::translate(i, 0, j);
				RENDERER.addRenderable(planeInfo, position, shader, isVisible, Vector4(0, 0, 0, 1.0f), text, false);
			}
			else if(cells[i][j].spaceType == Cell::Type::Room)
			{
				position = glm::translate(i, 0, j);
				RENDERER.addRenderable(planeInfo, position, shader, isVisible, Vector4(0, 0, 0, 1.0f), text, false);
			}
		}
	}
}

void Dungeon::AddShaderStreamedParameters(GeometryInfo* info)
{
	RENDERER.addShaderStreamedParameter(info, 0, ParameterType::PT_VECTOR3, Vertex::POSITION_OFFSET, Vertex::STRIDE);
	RENDERER.addShaderStreamedParameter(info, 1, ParameterType::PT_VECTOR3, Vertex::COLOR_OFFSET,    Vertex::STRIDE);
	RENDERER.addShaderStreamedParameter(info, 2, ParameterType::PT_VECTOR3, Vertex::NORMAL_OFFSET,   Vertex::STRIDE);
	RENDERER.addShaderStreamedParameter(info, 3, ParameterType::PT_VECTOR3, Vertex::UV_OFFSET,       Vertex::STRIDE);
}
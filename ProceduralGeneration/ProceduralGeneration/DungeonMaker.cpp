#include "DungeonMaker.h"

DungeonMaker::DungeonMaker()
{
	mainWidget = new QWidget;
	dungeon = new DungeonGraph;
	cFloor = new CorridorFloorTextureEditor;
	rFloor = new RoomFloorTextureEditor;
	walls = new WallTextureEditor;
	
	tabs = new QTabWidget;
	tabs->addTab(dungeon, "Dungeon Editor");
	tabs->addTab(cFloor, "Corridor Floor Editor");
	tabs->addTab(rFloor, "Room Floor Editor");
	tabs->addTab(walls, "Walls Editor");

	mainLayout = new QHBoxLayout;

	tabsLayout = new QVBoxLayout;
	tabsLayout->addWidget(tabs);

	rendererLayout = new QVBoxLayout;
	rendererLayout->addWidget(&RENDERER);
	RENDERER.setMinimumSize(700, 600);
	
	mainLayout->addLayout(tabsLayout);
	mainLayout->addLayout(rendererLayout);

	mainWidget->setLayout(mainLayout);
	setCentralWidget(mainWidget);
	show();

	connect(&updateTimer, SIGNAL(timeout()), this, SLOT(update()));
	updateTimer.start(0);
}

void DungeonMaker::update()
{
	///qDebug()<<cFloor->getTexture()<<", "<<rFloor->getTexture();
	dungeon->setCorridorFloorTexture(cFloor->getTexture());
	dungeon->setRoomFloorTexture(rFloor->getTexture());
	dungeon->setWallTexture(walls->getTexture());
}
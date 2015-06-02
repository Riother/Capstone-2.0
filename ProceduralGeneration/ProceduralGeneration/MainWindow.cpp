#include <Qt\qapplication.h>
#include "TextureEditor.h"
#include "GeometryEditor.h"
#include "DungeonMaker.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	DungeonMaker widg;
	//Dungeon widg;
	//DungeonGraph widg;
	//GeometryEditor widg;
	//TextureEditor widg;

	return app.exec();
}
#include <Qt\qapplication.h>
#include "TextureEditor.h"
#include "GeometryEditor.h"
#include "RendererWindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	GeometryEditor widg;

	return app.exec();
}
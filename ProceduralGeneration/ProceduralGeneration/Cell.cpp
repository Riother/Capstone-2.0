#include "Cell.h"

Cell::Cell()
{
	isEdgeCell = false;
	isVisited = false;
}

Cell::Cell(Type type, int x, int y, bool isEdge)
{
	spaceType = type;
	isEdgeCell = isEdge;
	isVisited = false;
	this->x = x;
	this->y = y;
}

bool Cell::isEmpty()
{
	if(spaceType == Type::None)
		return true;
	else
		return false;
}

bool Cell::isEmptyOrWall()
{
	if(isEmpty() || spaceType == Type::Wall)
		return true;
	else 
		return false;
}
#include "RenderableInfo.h"

RenderableInfo::RenderableInfo()
{
	isAvailable = true;
}

RenderableInfo::RenderableInfo(GeometryInfo* whatGeometry, Matrix4 whereMatrix, ShaderInfo* howShaders, bool isVisible, int textureID, Vector4 color, bool useMap)
{
	this->whatGeometry = whatGeometry;
	this->whereMatrix = whereMatrix;
	this->howShaders = howShaders;
	this->isVisible = isVisible;
	this->textureID = textureID;
	this->color = color;
	this->useMap = useMap;
}
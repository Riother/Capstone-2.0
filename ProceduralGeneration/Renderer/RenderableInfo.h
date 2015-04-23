#ifndef RENDERABLE_INFO_H
#define RENDERABLE_INFO_H

#include <GL\glew.h>
#include <Qt\qglobal.h>
#include <glm\glm.hpp>
#include "GeometryInfo.h"
#include "ShaderInfo.h"

typedef glm::mat4 Matrix4;
typedef glm::vec4 Vector4;

struct RenderableInfo
{
	GeometryInfo* whatGeometry;
	Matrix4 whereMatrix;
	Vector4 color;
	ShaderInfo* howShaders;
	int textureID;
	bool isVisible;
	bool isAvailable;
	bool useMap;
	RenderableInfo();
	RenderableInfo(GeometryInfo* whatGeometry, Matrix4 whatMatrix, ShaderInfo* howShaders, bool isVisible, int textureID, Vector4 color, bool useMap);
};

#endif
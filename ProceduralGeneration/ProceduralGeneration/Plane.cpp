#include "Plane.h"

Plane::Plane()
{
	createPlaneVerticesAndColor();
	createPlaneIndices();
}

void Plane::createPlaneVerticesAndColor()
{
	//Top
	vertices[0].position = Vector3(-0.5f, +0.5f, +0.5f);        // 0
	vertices[0].color    = Vector4(+1.0f, +0.0f, +0.0f, +0.0f); // Color
	vertices[0].normal   = Vector3(+0.0f, +1.0f, +0.0f);        // Normal
	vertices[0].uv       = Vector2(+0.0f, +1.0f);               // UV
	vertices[1].position = Vector3(+0.5f, +0.5f, +0.5f);        // 1
	vertices[1].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	vertices[1].normal   = Vector3(+0.0f, +1.0f, +0.0f);        // Normal
	vertices[1].uv       = Vector2(+1.0f, +1.0f);               // UV
	vertices[2].position = Vector3(+0.5f, +0.5f, -0.5f);		// 2
	vertices[2].color    = Vector4(+0.0f, +0.0f, +1.0f, +0.0f); // Color
	vertices[2].normal   = Vector3(+0.0f, +1.0f, +0.0f);		// Normal
	vertices[2].uv       = Vector2(+1.0f, +0.0f);				// UV
	vertices[3].position = Vector3(-0.5f, +0.5f, -0.5f);		// 3
	vertices[3].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	vertices[3].normal   = Vector3(+0.0f, +1.0f, +0.0f);		// Normal
	vertices[3].uv       = Vector2(+0.0f, +0.0f);				// UV
}

void Plane::createPlaneIndices()
{
	//Top
	indices[0]  = 0;
	indices[1]  = 1;
	indices[2]  = 2;
	indices[3]  = 0;
	indices[4]  = 2;
	indices[5]  = 3;
}
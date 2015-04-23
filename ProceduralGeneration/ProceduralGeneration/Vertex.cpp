#include "Vertex.h"


Vertex::Vertex()
{
	position = Vector3(0, 0, 0);
	color = Vector4(0, 0, 0, 0);
	normal = Vector3(0, 0, 0);
	uv = Vector2(0, 0);
}

bool Vertex::compare(Vertex v)
{
	bool theSame = false;
	if(position == v.position && normal == v.normal && uv == v.uv)
		theSame = true;

	return theSame;
}
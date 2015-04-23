#ifndef VERTEX_H
#define VERTEX_H

#include <glm\glm.hpp>
typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;

struct Vertex
{
	Vector3 position;
	Vector4 color;
	Vector3 normal;
	Vector2 uv;
	static const glm::uint POSITION_OFFSET = 0;
	static const glm::uint COLOR_OFFSET = sizeof(Vector3);
	static const glm::uint NORMAL_OFFSET = COLOR_OFFSET + sizeof(Vector4);
	static const glm::uint UV_OFFSET = NORMAL_OFFSET + sizeof(Vector3);
	static const glm::uint STRIDE = UV_OFFSET + sizeof(Vector2);
	Vertex();
	bool compare(Vertex v);
};

#endif
#include "DungeonRoom.h"

const glm::mat4 TOP_WALL_TRANSFORM   = glm::translate(glm::vec3(0, 0, 0)) * glm::rotate(180.0f, glm::vec3(0, 1, 0));
const glm::mat4 LEFT_WALL_TRANSFORM  = glm::translate(glm::vec3(0, 0, 0)) * glm::rotate(90.0f, glm::vec3(0, 0, 1)) * glm::rotate(90.0f, glm::vec3(0, 1, 0));
const glm::mat4 RIGHT_WALL_TRANSFORM = glm::translate(glm::vec3(0, 0, 0)) * glm::rotate(-90.0f, glm::vec3(0, 0, 1)) * glm::rotate(-90.0f, glm::vec3(0, 1, 0));
const glm::mat4 BOT_WALL_TRANSFORM   = glm::translate(glm::vec3(0, 0, 0)) * glm::rotate(180.0f, glm::vec3(0, 0, 1));
const glm::mat4 FRONT_WALL_TRANSFORM = glm::translate(glm::vec3(0, 0, 0)) * glm::rotate(90.0f, glm::vec3(1, 0, 0)) * glm::rotate(180.0f, glm::vec3(0, 1, 0));
const glm::mat4 BACK_WALL_TRANSFORM  = glm::translate(glm::vec3(0, 0, 0)) * glm::rotate(-90.0f, glm::vec3(1, 0, 0));

DungeonRoom::DungeonRoom(bool showRoof)
{
	this->showRoof = showRoof;
}

DungeonRoom::DungeonRoom(std::vector<GeometryInfo*> walls, bool showRoof)
{
	this->walls = walls;
	this->showRoof = showRoof;
	CreateSquareRoom();
}

DungeonRoom::DungeonRoom(std::vector<GeometryInfo*> walls)
{
	this->walls = walls;
	CreateDomeRoom();
}

void DungeonRoom::CreateSquareRoom()
{
	ShaderInfo* shader = RENDERER.createShaderInfo("SimpleVertexShaderCode.glsl", "SimpleFragmentShaderCode.glsl");
	bool showWalls = true;

	topWall   = walls[0];
	AddShaderStreamedParameters(topWall);
	top = RENDERER.addRenderable(topWall, TOP_WALL_TRANSFORM, shader, showRoof, Vector4(1, 0, 0, 1), -1, false);

	leftWall  = walls[1];
	AddShaderStreamedParameters(leftWall);
	left = RENDERER.addRenderable(leftWall, LEFT_WALL_TRANSFORM, shader, showWalls, Vector4(0, 1, 0, 1), -1, false);

	rightWall = walls[2];
	AddShaderStreamedParameters(rightWall);
	right = RENDERER.addRenderable(rightWall, RIGHT_WALL_TRANSFORM, shader, showWalls, Vector4(1, 0, 1, 1), -1, false);

	botWall   = walls[3];
	AddShaderStreamedParameters(botWall);
	bot = RENDERER.addRenderable(botWall, BOT_WALL_TRANSFORM, shader, showWalls, Vector4(0, 1, 1, 1), -1, false);

	frontWall = walls[4];
	AddShaderStreamedParameters(frontWall);
	front = RENDERER.addRenderable(frontWall, FRONT_WALL_TRANSFORM, shader, showWalls, Vector4(0, 0, 1, 1), -1, false);

	backWall  = walls[5];
	AddShaderStreamedParameters(backWall);
	back = RENDERER.addRenderable(backWall, BACK_WALL_TRANSFORM, shader, showWalls, Vector4(1, 1, 0, 1), -1, false);
}

void DungeonRoom::CreateDomeRoom()
{
	ShaderInfo* shader = RENDERER.createShaderInfo("SimpleVertexShaderCode.glsl", "SimpleFragmentShaderCode.glsl");
	bool showWalls = true;

	topWall   = walls[0];
	AddShaderStreamedParameters(topWall);
	top = RENDERER.addRenderable(topWall, TOP_WALL_TRANSFORM, shader, showRoof, Vector4(1, 0, 0, 1), -1, false);

	botWall   = walls[1];
	AddShaderStreamedParameters(botWall);
	bot = RENDERER.addRenderable(botWall, BOT_WALL_TRANSFORM, shader, showWalls, Vector4(0, 1, 1, 1), -1, false);
}

void DungeonRoom::AddShaderStreamedParameters(GeometryInfo* info)
{
	RENDERER.addShaderStreamedParameter(info, 0, ParameterType::PT_VECTOR3, Vertex::POSITION_OFFSET, Vertex::STRIDE);
	RENDERER.addShaderStreamedParameter(info, 1, ParameterType::PT_VECTOR3, Vertex::COLOR_OFFSET,    Vertex::STRIDE);
	RENDERER.addShaderStreamedParameter(info, 2, ParameterType::PT_VECTOR3, Vertex::NORMAL_OFFSET,   Vertex::STRIDE);
	RENDERER.addShaderStreamedParameter(info, 3, ParameterType::PT_VECTOR3, Vertex::UV_OFFSET,       Vertex::STRIDE);
}
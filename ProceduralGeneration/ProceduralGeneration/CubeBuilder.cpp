#include "CubeBuilder.h"

CubeBuilder::CubeBuilder()
{
	cubeSize = 1;
	divisions = 1;
	isCreated = false;
}

CubeBuilder::CubeBuilder(int size, int subdivisions)
{
	cubeSize = size;
	divisions = subdivisions;
	isCreated = false;
}

GeometryInfo* CubeBuilder::GetCube()
{
	if(!isCreated)
	{
		CreatePositions();
		PlaceTempIndices();
		PlacePositions();
		isCreated = true;
		geometry = RENDERER.addGeometry(&vertices[0], vertices.size() * sizeof(Vertex), &actualIndices[0], actualIndices.size(), GL_TRIANGLES);
	}
	return geometry;
}

void CubeBuilder::CreatePositions() 
{
	int amountOfVertices = (divisions + 1) * (divisions + 1);
	int amountOfFaces    = 2 * (divisions * divisions);
	int amountOfIndices  = 3 * amountOfFaces;
	//std::mt19937 rng(size * subdivisions);
	//std::uniform_int_distribution<int> gen(0, subdivisions - 1);
	//int randomColumn = gen(rng);
#pragma region Top
	float halfSize = cubeSize / 2;
	float halfSizeX = -halfSize;
	float halfSizeY = halfSize;
	float halfSizeZ = halfSize;
	float increment = cubeSize / divisions;
	int nextDivision = divisions;

	for(int currentVert = 0; currentVert < amountOfVertices; currentVert++)
	{
		Vector3 newVertex = Vector3(halfSizeX, halfSizeY, halfSizeZ);

		halfSizeX += increment;
		if(currentVert == nextDivision) {
			nextDivision += (divisions + 1);
			halfSizeZ -= increment;
			halfSizeX = -halfSize;
		}
		//qDebug()<<newVertex.x<<", "<<newVertex.y<<", "<<newVertex.z;
		positions.push_back(newVertex);
	}
#pragma endregion Top

#pragma region Bot
	halfSizeX = -halfSize;
	halfSizeY = -halfSize;
	halfSizeZ = halfSize;
	increment = cubeSize / divisions;
	nextDivision = divisions;

	for(int currentVert = 0; currentVert < amountOfVertices; currentVert++)
	{
		Vector3 newVertex = Vector3(halfSizeX, halfSizeY, halfSizeZ);

		halfSizeX += increment;
		if(currentVert == nextDivision) {
			nextDivision += (divisions + 1);
			halfSizeZ -= increment;
			halfSizeX = -halfSize;
		}
		//qDebug()<<newVertex.x<<", "<<newVertex.y<<", "<<newVertex.z;
		positions.push_back(newVertex);
	}
#pragma endregion Bot

#pragma region Left
	halfSizeX = -halfSize;
	halfSizeY = halfSize;
	halfSizeZ = -halfSize;
	increment = cubeSize / divisions;
	nextDivision = divisions;

	for(int currentVert = 0; currentVert < amountOfVertices; currentVert++)
	{
		Vector3 newVertex = Vector3(halfSizeX, halfSizeY, halfSizeZ);

		halfSizeZ += increment;
		if(currentVert == nextDivision) {
			nextDivision += (divisions + 1);
			halfSizeY -= increment;
			halfSizeZ = -halfSize;
		}
		//qDebug()<<newVertex.x<<", "<<newVertex.y<<", "<<newVertex.z;
		positions.push_back(newVertex);
	}
#pragma endregion Left

#pragma region Right
	halfSizeX = halfSize;
	halfSizeY = halfSize;
	halfSizeZ = -halfSize;
	increment = cubeSize / divisions;
	nextDivision = divisions;

	for(int currentVert = 0; currentVert < amountOfVertices; currentVert++)
	{
		Vector3 newVertex = Vector3(halfSizeX, halfSizeY, halfSizeZ);

		halfSizeZ += increment;
		if(currentVert == nextDivision) {
			nextDivision += (divisions + 1);
			halfSizeY -= increment;
			halfSizeZ = -halfSize;
		}
		//qDebug()<<newVertex.x<<", "<<newVertex.y<<", "<<newVertex.z;
		positions.push_back(newVertex);
	}
#pragma endregion Right

#pragma region Front
	halfSizeX = -halfSize;
	halfSizeY = halfSize;
	halfSizeZ = -halfSize;
	increment = cubeSize / divisions;
	nextDivision = divisions;

	for(int currentVert = 0; currentVert < amountOfVertices; currentVert++)
	{
		Vector3 newVertex = Vector3(halfSizeX, halfSizeY, halfSizeZ);

		halfSizeX += increment;
		if(currentVert == nextDivision) {
			nextDivision += (divisions + 1);
			halfSizeY -= increment;
			halfSizeX = -halfSize;
		}
		//qDebug()<<newVertex.x<<", "<<newVertex.y<<", "<<newVertex.z;
		positions.push_back(newVertex);
	}
#pragma endregion Front

#pragma region Back
	halfSizeX = -halfSize;
	halfSizeY = halfSize;
	halfSizeZ = halfSize;
	increment = cubeSize / divisions;
	nextDivision = divisions;

	for(int currentVert = 0; currentVert < amountOfVertices; currentVert++)
	{
		Vector3 newVertex = Vector3(halfSizeX, halfSizeY, halfSizeZ);

		halfSizeX += increment;
		if(currentVert == nextDivision) {
			nextDivision += (divisions + 1);
			halfSizeY -= increment;
			halfSizeX = -halfSize;
		}
		//qDebug()<<newVertex.x<<", "<<newVertex.y<<", "<<newVertex.z;
		positions.push_back(newVertex);
	}
#pragma endregion Back
}

void CubeBuilder::PlaceTempIndices()
{
	int amountOfVertices = (divisions + 1) * (divisions + 1);
	int maxVert = divisions * divisions;

	for(int i = 0; i < 1; i++)
	{
		int temp = i * amountOfVertices;
		ushort index1 = temp;
		ushort index2 = index1 + 1;
		ushort index3 = index2 + divisions;
		ushort index4 = index3 + 1;

		int currentRow = 1;
		int currentColumn = 0;
		int endVert = currentRow * divisions - 1 + temp;
		for(int currentVert = 0; currentVert < maxVert; currentVert++)
		{
			if(currentRow <= divisions - 2 || divisions == 1/* || currentColumn != randomColumn*/)
			{
				tempIndices.push_back(index1);
				tempIndices.push_back(index2);
				tempIndices.push_back(index3);

				tempIndices.push_back(index2);
				tempIndices.push_back(index3);
				tempIndices.push_back(index4);
			}

			currentColumn++;
			if(currentColumn > divisions - 1)
				currentColumn = 0;

			if(currentVert == endVert) 
			{
				index1 += 2;
				currentRow++;
				endVert = currentRow * divisions - 1;;

			}
			else
				index1++;
			index2 = index1 + 1;
			index3 = index2 + divisions;
			index4 = index3 + 1;
		}
	}
}

void CubeBuilder::PlaceActualIndices()
{
	
}

void CubeBuilder::PlacePositions()
{	
	//Calculate Normals
	for(int i = 0; i < tempIndices.size(); i+=3)
	{
		Vertex newVertex1;
		newVertex1.position = positions[tempIndices[i]];

		Vertex newVertex2;
		newVertex2.position = positions[tempIndices[i+1]];

		Vertex newVertex3;
		newVertex3.position = positions[tempIndices[i+2]];

		Vector3 normal = glm::normalize(glm::cross(newVertex2.position - newVertex1.position, newVertex3.position - newVertex1.position));
		newVertex1.normal = -normal;
		newVertex2.normal = -normal;
		newVertex3.normal = -normal;

		vertices.push_back(newVertex1);
		vertices.push_back(newVertex2);
		vertices.push_back(newVertex3);

		if(newVertex1.position.y && newVertex2.position.y && newVertex3.position.y)
		{
			//newVertex1.uv = Vector2(newVertex1.position.x * 
		}

		actualIndices.push_back(i);
		actualIndices.push_back(i+1);
		actualIndices.push_back(i+2);
	}
}

void CubeBuilder::PlaceNormals()
{

}

void CubeBuilder::PlaceUVs()
{

}

#include "CylinderBuilder.h"

CylinderBuilder::CylinderBuilder()
{
	columnSize = 1;
	divisions = 1;
	isCreated = false;
}

CylinderBuilder::CylinderBuilder(int size, int subdivisions)
{
	columnSize = size;
	divisions = subdivisions;
	isCreated = false;
}

GeometryInfo* CylinderBuilder::GetCylinder()
{
	if(!isCreated)
	{
		//CreatePositions();
		//PlaceTempIndices();
		//PlacePositions();
		PlaceActualIndices();
		isCreated = true;
		geometry = RENDERER.addGeometry(&vertices[0], vertices.size() * sizeof(Vertex), &actualIndices[0], actualIndices.size(), GL_TRIANGLES);
	}
	return geometry;
}

void CylinderBuilder::CreatePositions() 
{
	int amountOfVertices = (divisions + 1) * (divisions + 1);
	int amountOfFaces    = 2 * (divisions * divisions);
	int amountOfIndices  = 3 * amountOfFaces;
	float radius = columnSize / 2;

	Vector3 topPole(0, radius, 0);
	positions.push_back(topPole);

	float upDownIncrement = columnSize / divisions;
	for(int row = 0; row <= divisions; row ++)
	{
		float upDown = -(upDownIncrement * row);
		for(int column = 0; column < divisions; column++)
		{
			Vector3 newVertex;
			float leftRightAngle = 360 / divisions * column;
			Vector4 newPosition = (glm::translate(glm::vec3(radius, upDown, 0)) * glm::vec4(topPole, 1)) * glm::rotate(leftRightAngle, glm::vec3(0, 1, 0));
			newVertex = glm::vec3(newPosition.x, newPosition.y, newPosition.z);
			positions.push_back(newVertex);
		}
	}

	Vector3 botPole(0, -radius, 0);
	positions.push_back(botPole);
}

void CylinderBuilder::PlaceTempIndices()
{
	//Top Circle
	ushort index1 = 0;
	ushort index2 = index1 + 1;
	ushort index3 = index2 + 1;
	for(int currentVert = 0; currentVert < divisions; currentVert++)
	{
		tempIndices.push_back(index1);
		tempIndices.push_back(index2);
		tempIndices.push_back(index3);

		index2++;
		if(index2 == divisions)
			index3 = 1;
		else
			index3 = index2 + 1;
	}

	//Body
	index1 = 1;
	index2 = index1 + divisions;
	index3 = index2 + 1;
	ushort index4 = index1 + 1;
	int currentRow = 1;
	for(int currentVert = 0; currentVert < divisions * divisions; currentVert++)
	{
		tempIndices.push_back(index1);
		tempIndices.push_back(index2);
		tempIndices.push_back(index3);

		tempIndices.push_back(index1);
		tempIndices.push_back(index3);
		tempIndices.push_back(index4);

		index1++;
		index2 = index1 + divisions;
		if(index1 == divisions * currentRow)
		{
			index3 = index1 + 1;
			index4 = index3 - divisions;
			currentRow++;
		}
		else
		{
			index3 = index2 + 1;
			index4 = index1 + 1;
		}
	}

	//Bot Circle
	index1 = positions.size() - 1;
	index2 = index1 - divisions;
	index3 = index2 + 1;
	for(int currentVert = 0; currentVert < divisions; currentVert++)
	{
		tempIndices.push_back(index1);
		tempIndices.push_back(index2);
		tempIndices.push_back(index3);

		index2++;
		if(index2 == index1 - 1)
			index3 = index1 - divisions;
		else
			index3 = index2 + 1;
	}
}

void CylinderBuilder::PlaceActualIndices()
{
	float R = 1./(float)(divisions - 1);
	float S = 1./(float)(divisions - 1);
	float radius = columnSize / 2;
	int r, s;

	//Bottom
	r = 0;
	for(s = 0; s < divisions; s++)
	{
		float y = sin(-M_PI_2 + M_PI * r * R);
		float x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
		float z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);
		qDebug()<<r<<", "<<s<<", "<<x<<", "<<y<<", "<<z;
		Vertex temp;
		temp.uv = Vector2(s*S, r*R);
		temp.position = Vector3(x * radius, y * radius, z * radius);
		temp.normal = Vector3(-x, -y, -z);
		float tc = 0.1f * r;
		temp.color = Vector4(tc, tc, tc, tc);
		vertices.push_back(temp);
	}

	r = divisions / 2;
	for(int i = 1; i < divisions - 1; i++) for(s = 0; s < divisions; s++)
	{
		float y = sin(-M_PI_2 + M_PI * i * R);
		float x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
		float z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);
		qDebug()<<r<<", "<<s<<", "<<x<<", "<<y<<", "<<z;
		Vertex temp;
		temp.uv = Vector2(s*S, r*R);
		temp.position = Vector3(x * radius, y * radius, z * radius);
		temp.normal = Vector3(-x, -y, -z);
		float tc = 0.1f * r;
		temp.color = Vector4(tc, tc, tc, tc);
		vertices.push_back(temp);
	}

	//Top
	r = divisions - 1;
	for(s = 0; s < divisions; s++)
	{
		float y = sin(-M_PI_2 + M_PI * r * R);
		float x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
		float z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);
		qDebug()<<r<<", "<<s<<", "<<x<<", "<<y<<", "<<z;
		Vertex temp;
		temp.uv = Vector2(s*S, r*R);
		temp.position = Vector3(x * radius, y * radius, z * radius);
		temp.normal = Vector3(-x, -y, -z);
		float tc = 0.1f * r;
		temp.color = Vector4(tc, tc, tc, tc);
		vertices.push_back(temp);
	}

	for(r = 0; r < divisions-1; r++) for(s = 0; s < divisions-1; s++) {
		actualIndices.push_back(r * divisions + s);
		actualIndices.push_back(r * divisions + (s+1));
		actualIndices.push_back((r+1) * divisions + (s+1));

		actualIndices.push_back(r * divisions + s);
		actualIndices.push_back((r+1) * divisions + (s+1));
		actualIndices.push_back((r+1) * divisions + s);
	}
}

void CylinderBuilder::PlacePositions()
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

		newVertex1.uv = CalculateUV(newVertex1.position, columnSize / 2);
		newVertex2.uv = CalculateUV(newVertex2.position, columnSize / 2);
		newVertex3.uv = CalculateUV(newVertex3.position, columnSize / 2);

		vertices.push_back(newVertex1);
		vertices.push_back(newVertex2);
		vertices.push_back(newVertex3);

		actualIndices.push_back(i);
		actualIndices.push_back(i+1);
		actualIndices.push_back(i+2);
	}
}

void CylinderBuilder::PlaceNormals()
{

}

Vector2 CylinderBuilder::CalculateUV(Vector3 position, float radius)
{

	float p = sqrt((position.x * position.x) + (position.y * position.y));
	float a = 0;
	if(position.x == 0 && position.y == 0)
		a = 0;
	else if(position.x >= 0)
		a = asin(position.y / p) / M_PI;
	else if(position.x < 0)
		a = - asin(position.y / p) + M_PI;

	float z = position.z;

	qDebug()<<a<<", "<<z;
	return Vector2(a, z);
}

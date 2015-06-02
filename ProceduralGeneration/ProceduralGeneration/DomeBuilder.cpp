#include "DomeBuilder.h"

DomeBuilder::DomeBuilder()
{
	domeSize = 1;
	divisions = 1;
	isCreated = false;
}

DomeBuilder::DomeBuilder(int size, int subdivisions)
{
	domeSize = size;
	divisions = subdivisions;
	isCreated = false;
}

GeometryInfo* DomeBuilder::GetDome()
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

void DomeBuilder::CreatePositions() 
{
	int amountOfVertices = (divisions + 1) * (divisions + 1);
	int amountOfFaces    = 2 * (divisions * divisions);
	int amountOfIndices  = 3 * amountOfFaces;

	float radius = domeSize / 2;

	Vector3 topPole(0, radius, 0);
	positions.push_back(topPole);

	float upDownAngle;
	for(int row = 0; row < divisions; row ++)
	{
		upDownAngle = 90 / divisions * (row + 1);
		for(int column = 0; column < divisions; column++)
		{
			float leftRightAngle = (360 / divisions) * column;
			Vector4 newPosition = (glm::vec4(topPole, 1) * glm::rotate(upDownAngle, glm::vec3(1, 0, 0))) * glm::rotate(leftRightAngle, glm::vec3(0, 1, 0));
			Vector3 tempPos = glm::vec3(newPosition.x, newPosition.y, newPosition.z);
			positions.push_back(tempPos);
		}
	}

	Vector3 botPole(0, 0, 0);
	positions.push_back(botPole);
}

void DomeBuilder::PlaceTempIndices()
{
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

	index1 = 1;
	index2 = index1 + divisions;
	index3 = index2 + 1;
	ushort index4 = index1 + 1;
	int currentRow = 1;
	for(int currentVert = 0; currentVert < divisions * divisions - divisions; currentVert++)
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

void DomeBuilder::PlaceActualIndices()
{	
	float i = 1.0f/ (divisions - 1);
	float radius = domeSize / 2;
	int r, s;

	Vector4 colors[3] = 
	{
		Vector4(1, 0, 0, 0), 
		Vector4(0, 1, 0, 0),
		Vector4(0, 0, 1, 0)
	};

	//Bottom
	r = divisions / 2;
	for(s = 0; s < divisions; s++)
	{
		float y = sin(-M_PI_2 + M_PI * r * i);
		float x = cos(2 * M_PI * s * i) * sin(M_PI * 0 * i);
		float z = sin(2 * M_PI * s * i) * sin(M_PI * 0 * i);
		qDebug()<<r<<", "<<s<<", "<<x<<", "<<y<<", "<<z;
		Vertex temp;
		temp.uv = Vector2(s*i, r*i);
		temp.position = Vector3(x * radius, y * radius, z * radius);
		temp.normal = Vector3(-x, -y, -z);
		float tc = 0.1f * r;
		temp.color = Vector4(tc, tc, tc, tc);
		vertices.push_back(temp);
	}

	for(r = divisions / 2; r < divisions; r++) for(s = 0; s < divisions; s++)
	{
		float y = sin(-M_PI_2 + M_PI * r * i);
		float x = cos(2 * M_PI * s * i) * sin(M_PI * r * i);
		float z = sin(2 * M_PI * s * i) * sin(M_PI * r * i);
		qDebug()<<r<<", "<<s<<", "<<x<<", "<<y<<", "<<z;
		Vertex temp;
		temp.uv = Vector2(s*i, r*i);
		temp.position = Vector3(x * radius, y * radius, z * radius);
		temp.normal = Vector3(-x, -y, -z);
		//float tc = 0.1f * r;
		if(r % 2 == 0)
			temp.color = colors[0];
		else
			temp.color = colors[s % 2 + 1];
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

void DomeBuilder::PlacePositions()
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

		newVertex1.uv = CalculateUV(newVertex1.position);
		newVertex2.uv = CalculateUV(newVertex2.position);
		newVertex3.uv = CalculateUV(newVertex3.position);
		qDebug()<<newVertex1.uv.x<<", "<<newVertex1.uv.y<<" | "<<newVertex2.uv.x<<", "<<newVertex2.uv.y<<" | "<<newVertex3.uv.x<<", "<<newVertex3.uv.y;

		vertices.push_back(newVertex1);
		vertices.push_back(newVertex2);
		vertices.push_back(newVertex3);

		actualIndices.push_back(i);
		actualIndices.push_back(i+1);
		actualIndices.push_back(i+2);
	}
}

void DomeBuilder::PlaceNormals()
{
	
}

Vector2 DomeBuilder::CalculateUV(Vector3 position)
{
	Vector3 target(0, domeSize / 4, 0);
	Vector3 temp = glm::normalize(target - position);
	float u = 0.5 + (atan2(temp.z, temp.x) / (2 * M_PI));
	float v = 0.5 - (asin(temp.y) / M_PI);
	//qDebug()<<u<<", "<<v;
	//Vector2(Mathf.Atan2(vertices[i].z,vertices[i].x)/Mathf.Pi/2,Mathf.Acos(vertices[i].y/r)/Mathf.Pi);
	return Vector2(u, v);
}

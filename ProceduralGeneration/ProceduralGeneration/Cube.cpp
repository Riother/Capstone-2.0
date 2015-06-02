#include "Cube.h"

Cube::Cube()
{
	createCubeVerticesAndColor();
	createCubeIndices();
}

void Cube::createCubeVerticesAndColor()
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
	
	//Front
	vertices[4].position = Vector3(-0.5f, +0.5f, -0.5f);		// 4
	vertices[4].color    = Vector4(+1.0f, +0.0f, +0.0f, +0.0f); // Color
	vertices[4].normal   = Vector3(+0.0f, +0.0f, +1.0f);		// Normal
	vertices[4].uv       = Vector2(+0.0f, +1.0f);				// UV
	vertices[5].position = Vector3(+0.5f, +0.5f, -0.5f);		// 5
	vertices[5].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	vertices[5].normal   = Vector3(+0.0f, +0.0f, +1.0f);		// Normal
	vertices[5].uv       = Vector2(+1.0f, +1.0f);				// UV
	vertices[6].position = Vector3(+0.5f, -0.5f, -0.5f);		// 6
	vertices[6].color    = Vector4(+0.0f, +0.0f, +1.0f, +0.0f); // Color
	vertices[6].normal   = Vector3(+0.0f, +0.0f, +1.0f);		// Normal
	vertices[6].uv       = Vector2(+1.0f, +0.0f);				// UV
	vertices[7].position = Vector3(-0.5f, -0.5f, -0.5f);		// 7
	vertices[7].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	vertices[7].normal   = Vector3(+0.0f, +0.0f, +1.0f);		// Normal
	vertices[7].uv       = Vector2(+0.0f, +0.0f);				// UV
	
	//Right
	vertices[8].position  = Vector3(+0.5f, +0.5f, -0.5f);        // 8
	vertices[8].color     = Vector4(+1.0f, +0.0f, +0.0f, +0.0f); // Color
	vertices[8].normal    = Vector3(+1.0f, +0.0f, +0.0f);		 // Normal
	vertices[8].uv        = Vector2(+0.0f, +1.0f);				 // UV
	vertices[9].position  = Vector3(+0.5f, +0.5f, +0.5f);		 // 9
	vertices[9].color     = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	vertices[9].normal    = Vector3(+1.0f, +0.0f, +0.0f);		 // Normal
	vertices[9].uv        = Vector2(+1.0f, +1.0f);				 // UV
	vertices[10].position = Vector3(+0.5f, -0.5f, +0.5f);		 // 10
	vertices[10].color    = Vector4(+0.0f, +0.0f, +1.0f, +0.0f); // Color
	vertices[10].normal   = Vector3(+1.0f, +0.0f, +0.0f);		 // Normal
	vertices[10].uv       = Vector2(+1.0f, +0.0f);				 // UV
	vertices[11].position = Vector3(+0.5f, -0.5f, -0.5f);		 // 11
	vertices[11].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	vertices[11].normal   = Vector3(+1.0f, +0.0f, +0.0f);		 // Normal
	vertices[11].uv       = Vector2(+0.0f, +0.0f);				 // UV
	
	//Left
	vertices[12].position = Vector3(-0.5f, +0.5f, +0.5f);		 // 12
	vertices[12].color    = Vector4(+1.0f, +0.0f, +0.0f, +0.0f); // Color
	vertices[12].normal   = Vector3(-1.0f, +0.0f, +0.0f);		 // Normal
	vertices[12].uv       = Vector2(+0.0f, +1.0f);				 // UV
	vertices[13].position = Vector3(-0.5f, +0.5f, -0.5f);		 // 13
	vertices[13].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	vertices[13].normal   = Vector3(-1.0f, +0.0f, +0.0f);		 // Normal
	vertices[13].uv       = Vector2(+1.0f, +1.0f);				 // UV
	vertices[14].position = Vector3(-0.5f, -0.5f, -0.5f);		 // 14
	vertices[14].color    = Vector4(+0.0f, +0.0f, +1.0f, +0.0f); // Color
	vertices[14].normal   = Vector3(-1.0f, +0.0f, +0.0f);		 // Normal
	vertices[14].uv       = Vector2(+1.0f, +0.0f);				 // UV
	vertices[15].position = Vector3(-0.5f, -0.5f, +0.5f);		 // 15
	vertices[15].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	vertices[15].normal   = Vector3(-1.0f, +0.0f, +0.0f);		 // Normal
	vertices[15].uv       = Vector2(+0.0f, +0.0f);				 // UV
	
	//Back
	vertices[16].position = Vector3(+0.5f, +0.5f, +0.5f);		 // 16
	vertices[16].color    = Vector4(+1.0f, +0.0f, +0.0f, +0.0f); // Color
	vertices[16].normal   = Vector3(+0.0f, +0.0f, -1.0f);		 // Normal
	vertices[16].uv       = Vector2(+0.0f, +1.0f);				 // UV
	vertices[17].position = Vector3(-0.5f, +0.5f, +0.5f);		 // 17
	vertices[17].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	vertices[17].normal   = Vector3(+0.0f, +0.0f, -1.0f);		 // Normal
	vertices[17].uv       = Vector2(+1.0f, +1.0f);				 // UV
	vertices[18].position = Vector3(-0.5f, -0.5f, +0.5f);		 // 18
	vertices[18].color    = Vector4(+0.0f, +0.0f, +1.0f, +0.0f); // Color
	vertices[18].normal   = Vector3(+0.0f, +0.0f, -1.0f);		 // Normal
	vertices[18].uv       = Vector2(+1.0f, +0.0f);				 // UV
	vertices[19].position = Vector3(+0.5f, -0.5f, +0.5f);		 // 19
	vertices[19].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	vertices[19].normal   = Vector3(+0.0f, +0.0f, -1.0f);		 // Normal
	vertices[19].uv       = Vector2(+0.0f, +0.0f);				 // UV
	
	//Bottom
	vertices[20].position = Vector3(+0.5f, -0.5f, -0.5f);		 // 20
	vertices[20].color    = Vector4(+1.0f, +0.0f, +0.0f, +0.0f); // Color
	vertices[20].normal   = Vector3(+0.0f, -1.0f, +0.0f);		 // Normal
	vertices[20].uv       = Vector2(+0.0f, +1.0f);				 // UV
	vertices[21].position = Vector3(-0.5f, -0.5f, -0.5f);		 // 21
	vertices[21].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	vertices[21].normal   = Vector3(+0.0f, -1.0f, +0.0f);		 // Normal
	vertices[21].uv       = Vector2(+1.0f, +1.0f);				 // UV
	vertices[22].position = Vector3(-0.5f, -0.5f, +0.5f);		 // 22
	vertices[22].color    = Vector4(+0.0f, +0.0f, +1.0f, +0.0f); // Color
	vertices[22].normal   = Vector3(+0.0f, -1.0f, +0.0f);		 // Normal
	vertices[22].uv       = Vector2(+1.0f, +0.0f);				 // UV
	vertices[23].position = Vector3(+0.5f, -0.5f, +0.5f);		 // 23
	vertices[23].color    = Vector4(+0.0f, +1.0f, +0.0f, +0.0f); // Color
	vertices[23].normal   = Vector3(+0.0f, -1.0f, +0.0f);		 // Normal
	vertices[23].uv       = Vector2(+0.0f, +0.0f);				 // UV
}

void Cube::createCubeIndices()
{
	//Top
	indices[0]  = 0;
	indices[1]  = 1;
	indices[2]  = 2;
	indices[3]  = 0;
	indices[4]  = 2;
	indices[5]  = 3;
		
	//Front
	indices[6]  = 4;
	indices[7]  = 5;
	indices[8]  = 6;
	indices[9]  = 4;
	indices[10] = 6;
	indices[11] = 7;
		
	//Right
	indices[12] = 8;
	indices[13] = 9;
	indices[14] = 10;
	indices[15] = 8;
	indices[16] = 10;
	indices[17] = 11;
		
	//Left
	indices[18] = 12;
	indices[19] = 13;
	indices[20] = 14;
	indices[21] = 12;
	indices[22] = 14;
	indices[23] = 15;
		
	//Back
	indices[24] = 16;
	indices[25] = 17;
	indices[26] = 18;
	indices[27] = 16;
	indices[28] = 18;
	indices[29] = 19;
		
	//Bottom
	indices[30] = 20;
	indices[31] = 21;
	indices[32] = 22;
	indices[33] = 20;
	indices[34] = 22;
	indices[35] = 23;
}
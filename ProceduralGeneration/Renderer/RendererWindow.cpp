#include "RendererWindow.h"

const int MAX_INFOS = 3000;
const int MAX_RENDERABLES = 3000;
const int MEGABYTE = 1048576;

RendererWindow * RendererWindow::rendererInstance;
RendererWindow& RendererWindow::getRenderer()
{
	if(rendererInstance == NULL)
		rendererInstance = new RendererWindow();
	return *rendererInstance;
}

void RendererWindow::initializeGL()
{
	glewInit();

	cubeCount = 0;
	renderableCount = 0;
	lightCount = 0;
	geometryCount = 0;
	shaderCount = 0;
	cameraSpeed = 0.01f;
	perspectiveMatrix = glm::perspective(90.0f, (float)(width())/height(), 0.1f, 1000.0f);
	highlightedColor = Vector4(0, 0, 1, 1);

	setVisibility = true;

	for(int i = 0; i < MAX_INFOS; i++)
	{
		buffers[i].remainingSize = MEGABYTE;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

	connect(&updateTimer, SIGNAL(timeout()), this, SLOT(Update()));
	updateTimer.start(0);
	//setupFrameBuffer();
	leftClick = false;
	setMouseTracking(false);
}

void RendererWindow::paintGL()
{
	glViewport(0, 0, width(), height());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawStuff();
	//drawMap();
}

RendererWindow::RendererWindow()
{
}

GeometryInfo* RendererWindow::addGeometry(const void* verts, GLuint vertexDataSize, ushort* indices, uint numIndices, GLuint indexingMode)
{
	int counter = 0;
	while(buffers[counter].remainingSize < vertexDataSize + (numIndices * sizeof(ushort *)))
	{
		counter++;
	}

	if(buffers[counter].remainingSize == MEGABYTE)
	{
		glGenBuffers(1, &buffers[counter].glBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[counter].glBufferID);
		glBufferData(GL_ARRAY_BUFFER, MEGABYTE, 0, GL_STATIC_DRAW);
	}
	
	GLuint offset = (MEGABYTE) - buffers[counter].remainingSize;
	GLuint indexOffset = vertexDataSize + offset;
	unsigned int bufferID = buffers[counter].glBufferID;
	geometryInfos[geometryCount] = GeometryInfo(offset, numIndices, indexOffset, indexingMode, indices, bufferID);
	buffers[counter].remainingSize -= (vertexDataSize + (numIndices * sizeof(ushort)));

	glBindBuffer(GL_ARRAY_BUFFER, buffers[counter].glBufferID);
	glBufferSubData(GL_ARRAY_BUFFER, geometryInfos[geometryCount].offset, vertexDataSize, verts);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[counter].glBufferID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, geometryInfos[geometryCount].indexOffset, numIndices* sizeof(ushort), indices);
	
	glGenVertexArrays(1, &geometryInfos[geometryCount].vertexArrayID);
	glBindVertexArray(geometryInfos[geometryCount].vertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[counter].glBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[counter].glBufferID);

	return &geometryInfos[geometryCount++];
}

ShaderInfo* RendererWindow::createShaderInfo(const char* vertexShaderCode, const char* fragmentShaderCode, const char* geometryShaderCode)
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint geoShaderID = geometryShaderCode ? glCreateShader(GL_GEOMETRY_SHADER) : 0;
	
	//string tempShaderCode = readShaderCode(vertexShaderCode);
	//const char* adapter[1];
	//adapter[0] = tempShaderCode.c_str();
	//glShaderSource(vertexShaderID, 1, adapter, 0);
	//tempShaderCode = readShaderCode(fragmentShaderCode);
	//adapter[0] = tempShaderCode.c_str();
	//glShaderSource(fragShaderID, 1, adapter, 0);

	compileShader(vertexShaderCode, vertexShaderID);
	compileShader(fragmentShaderCode, fragShaderID);
	
	if(geoShaderID)
	{
		compileShader(geometryShaderCode, geoShaderID);
	}


	shaderInfos[shaderCount] = ShaderInfo(glCreateProgram());
	glAttachShader(shaderInfos[shaderCount].programID, vertexShaderID);
	glAttachShader(shaderInfos[shaderCount].programID, fragShaderID);

	if(geoShaderID)
	{
		glAttachShader(shaderInfos[shaderCount].programID, geoShaderID);
	}

	glLinkProgram(shaderInfos[shaderCount].programID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragShaderID);
	glDeleteShader(geoShaderID);

	return &shaderInfos[shaderCount++];
}

void RendererWindow::compileShader(const char* shaderCode, GLuint shaderID)
{
	string tempShaderCode = readShaderCode(shaderCode);
	const char* adapter[1];
	adapter[0] = tempShaderCode.c_str();
	glShaderSource(shaderID, 1, adapter, 0);

	glCompileShader(shaderID);

	GLint compileStatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
	if(compileStatus != GL_TRUE)
	{
		GLint logLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		char* buffer = new char[logLength];
		GLsizei happyGL;
		glGetShaderInfoLog(shaderID, logLength, &happyGL, buffer);
		qDebug() << buffer;
		delete[] buffer;
	}
}

RenderableInfo* RendererWindow::addRenderable(GeometryInfo* whatGeometry, const Matrix4& whereMatrix, ShaderInfo* howShaders, bool& isVisible, Vector4 color, int& texture, bool useMap)
{
	renderableInfos[renderableCount] = RenderableInfo(whatGeometry, whereMatrix, howShaders, isVisible, texture, color, useMap);
	
	return &renderableInfos[renderableCount++];
}

RenderableInfo* RendererWindow::addLight(GeometryInfo* whatGeometry, const Matrix4& whereMatrix, ShaderInfo* howShaders, bool& isVisible, Vector4 color)
{
	int temp = -1;
	lightInfos[lightCount] = RenderableInfo(whatGeometry, whereMatrix, howShaders, isVisible, temp, color, false);
	
	return &renderableInfos[lightCount++];
}

void RendererWindow::addShaderStreamedParameter(GeometryInfo* geometry, uint layoutLocation, ParameterType parameterType, uint bufferOffset, uint bufferStride)
{
	glBindVertexArray(geometry->vertexArrayID);
	glEnableVertexAttribArray(layoutLocation);

	glVertexAttribPointer(layoutLocation, parameterType/ sizeof(float), GL_FLOAT, GL_FALSE, bufferStride, (void*)(geometry->offset + bufferOffset));
}

void RendererWindow::addRenderableUniformParameter(RenderableInfo* renderable, const char* name, ParameterType parameterType, const float* value)
{
	glUseProgram(renderable->howShaders->programID);
	GLuint location = glGetUniformLocation(renderable->howShaders->programID, name);

	switch(parameterType)
	{
	case ParameterType::PT_FLOAT:
		{
			glUniform1f(location, *value);
			//break;
		}
	case ParameterType::PT_VECTOR2:
		{
			glUniform2fv(location, 1, value);
			//break;
		}
	case ParameterType::PT_VECTOR3:
		{
			glUniform3fv(location, 1, value);
			//break;
		}
	case ParameterType::PT_VECTOR4:
		{
			glUniform4fv(location, 1, value);
			//break;
		}
	case ParameterType::PT_MATRIX3:
		{
			glUniformMatrix3fv(location, 1, GL_FALSE, value);
			//break;
		}
	case ParameterType::PT_MATRIX4:
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, value);
			//break;
		}
	}
}

int RendererWindow::addTexture(const char* fileName)
{
	QImage image;

	image.load(fileName);

	if(!image.load(fileName))
	{
		std::cerr<<"Could not load image "<<fileName<<".";
		return -1;
	}

	image = QGLWidget::convertToGLFormat(image);
	int w = image.width();
	int h = image.height();

	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

	return textureID;
}

int RendererWindow::addTexture(QImage image)
{
	image = QGLWidget::convertToGLFormat(image);
	int w = image.width();
	int h = image.height();

	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

	return textureID;
}

QImage RendererWindow::loadImage(const char* fileName)
{
	QImage image;
	image.load(fileName);

	if(!image.load(fileName))
	{
		std::cerr<<"Could not load image"<<fileName<<".";
	}

	return image;
}

void RendererWindow::prepareTexture(QImage image, GLuint type)
{
	image = QGLWidget::convertToGLFormat(image);
	int w = image.width();
	int h = image.height();

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexImage2D(type, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
}

void RendererWindow::setupFrameBuffer()
{
	glGenFramebuffers(1, &frameBufferID);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBufferID);

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &colorTextureID);
	glBindTexture(GL_TEXTURE_2D, colorTextureID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 255, 255, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTextureID, 0);
	glGenTextures(1, &depthTextureID);
	glBindTexture(GL_TEXTURE_2D, depthTextureID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, 255, 255, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTextureID, 0);

	GLuint status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if(status != GL_FRAMEBUFFER_COMPLETE)
		qDebug()<<"Frame buffer not complete...";
}

string RendererWindow::readShaderCode(const char* fileName)
{
	ifstream input(fileName);
	if(! input.good())
	{
		cout<<"File failed to load: "<<fileName;
		exit(1);
	}
	return string(istreambuf_iterator<char>(input), istreambuf_iterator<char>());
}

void RendererWindow::drawStuff()
{
	for(int i = 0; i < renderableCount; i++)
	{
		RenderableInfo temp = renderableInfos[i];
		if(temp.isVisible)
		{
			glUseProgram(temp.howShaders->programID);


			addRenderableUniformParameter(&temp, "transformation", ParameterType::PT_MATRIX4, &(perspectiveMatrix * camera.getWorldToViewMatrix() * temp.whereMatrix)[0][0]);
			addRenderableUniformParameter(&temp, "cameraPosition", ParameterType::PT_VECTOR3, &camera.getPosition()[0]);

			//addRenderableUniformParameter(&renderableInfos[i], "pureTrans", ParameterType::PT_MATRIX4, &(renderableInfos[i].whereMatrix)[0][0]);
			if(temp.lightLocation != -1)
				addRenderableUniformParameter(&temp, "lightPosition", ParameterType::PT_VECTOR3, &lightInfos[temp.lightLocation].position[0]);
			//addRenderableUniformParameter(&renderableInfos[i], "lightColor", ParameterType::PT_VECTOR3, &lightPosition[0]);
			//addRenderableUniformParameter(&renderableInfos[i], "specularLight", ParameterType::PT_VECTOR3, &specularLight[0]);
			//addRenderableUniformParameter(&renderableInfos[i], "diffuseLight", ParameterType::PT_VECTOR3, &diffuseLight[0]);
			//addRenderableUniformParameter(&renderableInfos[i], "ambientLight", ParameterType::PT_VECTOR3, &ambientLight[0]);
			//addRenderableUniformParameter(&renderableInfos[i], "specularExponent", ParameterType::PT_FLOAT, &specularExponent);
			addRenderableUniformParameter(&temp, "color", ParameterType::PT_VECTOR3, &temp.color[0]);
			addRenderableUniformParameter(&temp, "modelToWorld", ParameterType::PT_MATRIX4, &temp.whereMatrix[0][0]);
			//addRenderableUniformParameter(&renderableInfos[i], "octave", ParameterType::PT_FLOAT, &octave);
			//addRenderableUniformParameter(&renderableInfos[i], "meltingRange", ParameterType::PT_FLOAT, &meltingRange);

			if(*temp.textureID == -1)
			{
				//dont use image
				float useImage = 0;
				addRenderableUniformParameter(&temp, "useImage", ParameterType::PT_FLOAT, &useImage);
			}
			else
			{
				//use image
				float useImage = 1;
				addRenderableUniformParameter(&temp, "useImage", ParameterType::PT_FLOAT, &useImage);
				glActiveTexture(*temp.textureID);
				glBindTexture(GL_TEXTURE_2D, *temp.textureID);
			}

			glBindVertexArray(temp.whatGeometry->vertexArrayID);

			glDrawElements(temp.whatGeometry->indexingMode, temp.whatGeometry->numIndices, GL_UNSIGNED_SHORT, (void*)(temp.whatGeometry->indexOffset));
		}
	}
}

void RendererWindow::drawMap()
{
}

void RendererWindow::Update()
{
	if(leftClick)
		camera.update();
	repaint();

	

	//camera.updateCameraSpeed(cameraSpeed);

	/*if(GetAsyncKeyState(VK_UP))
	{
		lightPosition.z -= 0.01f;
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		lightPosition.z += 0.01f;
	}

	if(GetAsyncKeyState(VK_LEFT))
	{
		lightPosition.x -= 0.01f;
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		lightPosition.x += 0.01f;
	}

	if(GetAsyncKeyState(VK_BROWSER_BACK))
	{
		lightPosition.y -= 0.01f;
	}
	else if(GetAsyncKeyState(VK_BROWSER_FORWARD))
	{
		lightPosition.y += 0.01f;
	}*/
}

void RendererWindow::mouseMoveEvent(QMouseEvent* e)
{
	camera.mouseUpdate(Vector2(e->x(), e->y()));
	repaint();
}

void RendererWindow::mousePressEvent(QMouseEvent* e)
{
	if(e->button() == Qt::RightButton)
	{

	}
		


	if(e->button() == Qt::LeftButton)
	{
		leftClick = true;
	}
}

//void RendererWindow::movementSelection(int x, int y)
//{
//	GLbyte color[4];
//	GLfloat depth;
//	GLuint index;
//
//	glReadPixels(x, height() - y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
//	glReadPixels(x, height() - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
//	glReadPixels(x, height() - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
//
//	Vector4 viewport = Vector4(0, 0, width(), height());
//	Vector3 wincoord = Vector3(x, height() - y - 1, depth);
//	Vector3 objcoord = glm::unProject(wincoord, camera.getWorldToViewMatrix(), perspectiveMatrix, viewport);
//
//	selectedX = static_cast<int>(objcoord.x + 0.5);
//	selectedY = static_cast<int>(objcoord.y + 0.5);
//	selectedZ = static_cast<int>(objcoord.z + 0.5);
//
//	if(selectedX >= 0 && selectedX < mapSizeX && selectedY >= 0 && selectedY < mapSizeY && selectedZ >= 0 && selectedZ < mapSizeZ)
//	{
//		if(MAP.cubes[selectedX][0][selectedZ].IsHighlighted)
//		{
//			isMovement = false;
//			emit moveMade();
//		}
//		//Cubes[selectedX][0][selectedZ].IsHighlighted = true;
//	}
//
//	//qDebug()<<objcoord.x<<", "<<objcoord.y<<", "<<objcoord.z;
//}

//void RendererWindow::characterSelection(int x, int y)
//{
//	Vector3 rayDirection, origin, planeNormal, planeTail;
//	createRay(x, y, rayDirection, origin, planeNormal, planeTail);
//
//	int index = getIntersectingSphere(rayDirection, origin);
//	if(index != -1) 
//	{
//		if(isAttack)
//		{
//			GAME.targetCharacter = GAME.currentPlayer ? GAME.player2.at(index) : GAME.player1.at(index);
//			GAME.targetIndex = index;
//			isAttack = false;
//			emit attacked();
//		}
//
//		if(isCharSelection)
//		{
//			GAME.selectedCharacter = GAME.currentPlayer ? GAME.player1.at(index) : GAME.player2.at(index);
//			GAME.selectedIndex = index;
//			isCharSelection = false;
//			emit characterSelected();
//		}
//	}
//}

//int RendererWindow::getIntersectingSphere(const Vector3 &rayDirection, const Vector3 &rayOrigin)
//{
//	Vector3 spherePosition;			  //p
//	Vector3 rayToNodeVector;
//	float rayToNodeLength;			  //c
//	float nodeRadius = 1;			  //r
//	float ray;						  //e = projection of c to rayDirection
//	float a;						  //a = sqrt(r^2 - c^2 + e^2)
//	float b;						  //b = sqrt(c^2 - e^2)
//	float pointOfIntersection;
//	bool intersection = false;
//
//	int index = -1;
//	int size = GAME.currentPlayer ? GAME.player1.size() : GAME.player2.size();
//	for(int i = 0; i < size && !intersection; i++)
//	{
//		Character temp;
//		if(GAME.currentPlayer)
//		{
//			if(isAttack)
//				temp = GAME.player2.at(i);
//			else
//				temp = GAME.player1.at(i);
//		}
//		else
//		{
//			if(isAttack)
//				temp = GAME.player1.at(i);
//			else
//				temp = GAME.player2.at(i);
//
//		}
//
//		spherePosition = Vector3(temp.position); 
//		rayToNodeVector = spherePosition - rayOrigin;
//		rayToNodeLength = glm::length(rayToNodeVector);
//		ray = glm::dot(rayToNodeVector, rayDirection);
//		a = glm::sqrt((nodeRadius * nodeRadius) - (rayToNodeLength * rayToNodeLength) + (ray * ray));
//		b = glm::sqrt((rayToNodeLength * rayToNodeLength) - (ray * ray));
//		pointOfIntersection = ray - a;
//
//		if((b * b) < (nodeRadius * nodeRadius))
//		{
//			intersection = true;
//			index = i;
//		}
//	}
//	
//	//Vector3 C = glm::length(wspherePosition - rayOrigin);
//	//sphere position from ray origin = vector then get length to get C
//	//we know p
//	//we know r
//	//e = c * d (project C to D) 
//	//b^2 = c^2 - e^2
//	//a = sqrt of r^2 - c^2 + e^2
//	//e - a = point of intersection
//	//b^2 > r^2 then no intersection
//	return index;
//}
//
//void RendererWindow::createRay(float x, float y, Vector3 &rayDirection, Vector3 &origin, Vector3 &planeNormal, Vector3 &planeTail)
//{
//	const float menuBarSize = 21;
//	float percentage = 1 - (y  / this->height());
//	float yOffset = menuBarSize * percentage;
//
//	//step 1
//	float mouseX = (2.0f * x) /this->width() - 1.0f;
//	float mouseY = 1.0f -  (2.0f * (y - yOffset)) / this->height();
//	float mouseZ = 1.0f;
//
//	//qDebug()<<"X: "<<e->x()<<" Y: "<<e->y();
//	//qDebug()<<"X: "<<mouseX * 900<<" Y: "<<mouseY * 900<<endl;
//
//	Vector3 normalRay(mouseX, mouseY, mouseZ);
//
//	//step 2
//	Vector4 forwardRay(normalRay.x, normalRay.y, -1, 1);
//
//	//step 3
//	Vector4 depthRay = glm::inverse(perspectiveMatrix) * forwardRay;
//	depthRay = Vector4(depthRay.x, depthRay.y, -1, 0); 
//
//	//step 4
//	Vector4 rayDirection4 = glm::inverse(this->camera.getWorldToViewMatrix()) * depthRay;
//	rayDirection = Vector3(rayDirection4.x, rayDirection4.y, rayDirection4.z);
//	rayDirection = glm::normalize(rayDirection);//l
//
//	origin = this->camera.getPosition();//lo
//
//	planeNormal = Vector3(0, -1, 0);//n
//	planeTail   = Vector3(0, 0, 0);//po
//}

void RendererWindow::mouseReleaseEvent(QMouseEvent* e)
{
	if(e->button() == Qt::LeftButton)
	{
		leftClick = false;
	}
}

void RendererWindow::updateCameraSpeed(float newSpeed)
{
	camera.updateCameraSpeed(newSpeed);
}

int RendererWindow::getMaxRenderables()
{
	return MAX_RENDERABLES;
}

void RendererWindow::clearRenderables()
{
	renderableCount = 0;
}

void RendererWindow::clearGeometries()
{
	geometryCount = 0;
}

void RendererWindow::clearShaders()
{
	shaderCount = 0;
}
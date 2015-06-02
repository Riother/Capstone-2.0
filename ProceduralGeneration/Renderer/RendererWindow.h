#ifndef RENDERER_WINDOW_H
#define RENDERER_WINDOW_H

#include <GL\glew.h>
#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>
#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <Qt\qdebug.h>
#include <iostream>
#include <fstream>
#include "ParameterType.h"
#include "BufferInfo.h"
#include "GeometryInfo.h"
#include "ShaderInfo.h"
#include "RenderableInfo.h"
#include "Camera.h"

using std::string;
using std::istreambuf_iterator;
using std::ifstream;
using std::cout;

typedef glm::mat4 Matrix4;

#define RENDERER RendererWindow::getRenderer()

class RendererWindow : public QGLWidget
{
	Q_OBJECT

	static const int MAX_INFOS = 30;
	static const int MAX_RENDERABLES = 3000;
	static const int MAX_DIMENSION_VALUE = 25;
	//Voxel Cubes[MAX_DIMENSION_VALUE][MAX_DIMENSION_VALUE][MAX_DIMENSION_VALUE];
	QList<RenderableInfo> characters;
	int cubeCount;
	int mapLength;
	int mapWidth;
	int mapHeight;
	int lightLocation;
	float cameraSpeed;
	bool leftClick;
	//glm::vec3 lightPosition;
	Vector4 highlightedColor;
	
private:
	//Singleton
	RendererWindow(const RendererWindow&);
	RendererWindow& operator=(const RendererWindow&);
	static RendererWindow* rendererInstance;
	//Singleton
public:
	//Singleton
	static RendererWindow& getRenderer();
	//Singleton
	RendererWindow();
	Camera camera;
	bool setVisibility;
	int renderableCount;
	int lightCount;
	int geometryCount;
	int shaderCount;
	void initializeGL();
	void paintGL();
	Matrix4 perspectiveMatrix;
	QTimer updateTimer;
	BufferInfo buffers[MAX_INFOS];
	GeometryInfo geometryInfos[MAX_INFOS];
	ShaderInfo shaderInfos[MAX_INFOS];
	RenderableInfo renderableInfos[MAX_RENDERABLES];
	RenderableInfo lightInfos[MAX_RENDERABLES];
	GLuint frameBufferID;
	GLuint colorTextureID;
	GLuint depthTextureID;

	GeometryInfo* addGeometry(const void* verts, GLuint vertexDataSize, ushort* indices, glm::uint numIndices, GLuint indexingMode);
	ShaderInfo* createShaderInfo(const char* vertexShaderCode, const char* fragmentShaderCode, const char* geometryShaderCode = nullptr);
	void compileShader(const char* shaderCode, GLuint shaderID);
	RenderableInfo* addRenderable(GeometryInfo* whatGeometry, const Matrix4& whereMatrix, ShaderInfo* howShaders, bool& isVisible, Vector4 color, int& texture, bool useMap = false);
	RenderableInfo* addLight(GeometryInfo* whatGeometry, const Matrix4& whereMatrix, ShaderInfo* howShaders, bool& isVisible, Vector4 color);
	void addShaderStreamedParameter(GeometryInfo* geometry,	glm::uint layoutLocation, ParameterType parameterType, glm::uint bufferOffset, glm:: uint bufferStride);
	void addRenderableUniformParameter(RenderableInfo* renderable, const char* name, ParameterType parameterType, const float* value);
	int addTexture(const char* fileName);
	int addTexture(QImage image);
	QImage loadImage(const char* fileName);
	void prepareTexture(QImage image, GLuint type);
	void setupFrameBuffer();

	string readShaderCode(const char* fileName);
	void drawStuff();
	void drawMap();
//Mouse & Keyboard Inputs
	void mouseMoveEvent(QMouseEvent* e);
	//void createRay(float x, float y, Vector3 &rayDirection, Vector3 &origin, Vector3 &planeNormal, Vector3 &planeTail);
	//int getIntersectingSphere(const Vector3 &rayDirection, const Vector3 &rayOrigin);
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void updateCameraSpeed(float newSpeed);
	int getMaxRenderables();
	void clearRenderables();
	void clearGeometries();
	void clearShaders();
private slots:
	void Update();
};

#endif
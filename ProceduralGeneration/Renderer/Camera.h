#ifndef CAMERA_H
#define CAMERA_H
#include <glm\glm.hpp>
#include <QtOpenGL\qglwidget>
#include <glm\gtx\transform.hpp>
#include <Qt\qdebug.h>

typedef glm::mat4 Matrix4;
typedef glm::mat3 Matrix3;
typedef glm::vec3 Vector3;
typedef glm::vec2 Vector2;

class Camera
{
	Vector3 up;
	Vector3 viewDirection;
	Vector3 moveDirection;
	Vector3 position;
	Vector2 oldMousePosition;
	float Speed;
	bool is3D;
public:
	Camera();
	Matrix4 getWorldToViewMatrix() const;
	void mouseUpdate(const Vector2 newMousePosition);
	void updateCameraSpeed(float newSpeed);
	void update();
	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	Vector3 getPosition();
	void change2D3D(bool newD, Vector3 dimensions);
	void set2DPosition(Vector3 dimensions);
};
#endif
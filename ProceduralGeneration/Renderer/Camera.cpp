#include "Camera.h"



Camera::Camera(void) :
	viewDirection(0.0f, 0.0f, -1.0f),
	position(0.0f, 1.0f, 1.0f),
	up(0.0f, 1.0f, 0.0)
{
	moveDirection = glm::cross(viewDirection, up);
	Speed = 0.01f;
	is3D = true;
}

Matrix4 Camera:: getWorldToViewMatrix() const
{
	return glm::lookAt(position, position + viewDirection, up);
}

void Camera::mouseUpdate(const Vector2 newMousePosition)
{
	if(is3D)
	{
		Vector2 mouseDelta = newMousePosition - oldMousePosition;
		if(glm::length(mouseDelta) > 50.0f)
		{
			oldMousePosition = newMousePosition;
		}
		else
		{
			moveDirection = glm::cross(viewDirection, up);

			Matrix4 rotations = glm::rotate(-mouseDelta.x, up) * glm::rotate(-mouseDelta.y, moveDirection);

			viewDirection = Matrix3(rotations) * viewDirection;

			oldMousePosition = newMousePosition;
		}
	}
}

void Camera::updateCameraSpeed(float newSpeed)
{
	Speed = newSpeed;
}

void Camera::update()
{
	if(GetAsyncKeyState('W'))
	{
		moveForward();
	}
	else if(GetAsyncKeyState('S'))
	{
		moveBackward();
	}

	if(GetAsyncKeyState('A'))
	{
		moveLeft();
	}
	else if(GetAsyncKeyState('D'))
	{
		moveRight();
	}

	if(GetAsyncKeyState('Q'))
	{
		moveUp();
	}
	else if(GetAsyncKeyState('E'))
	{
		moveDown();
	}

	//qDebug()<<"Camera Position: "<<position.x<<", "<<position.y<<", "<<position.z;
	//qDebug()<<"Look Direction: "<<viewDirection.x<<", "<<viewDirection.y<<", "<<viewDirection.z<<endl;
}

void Camera::moveForward()
{
	position += Speed * viewDirection;
}

void Camera::moveBackward()
{
	position -= Speed * viewDirection;
}

void Camera::moveLeft()
{
	position -= Speed * moveDirection;
}

void Camera::moveRight()
{
	position += Speed * moveDirection;
}

void Camera::moveUp()
{
	position += Speed * up;
}

void Camera::moveDown()
{
	position -= Speed * up;
}

Vector3 Camera::getPosition()
{
	return position;
}

void Camera::change2D3D(bool newD, Vector3 dimensions)
{
	is3D = newD;

	if(is3D)
	{
		viewDirection = Vector3(0.0f, 0.0f, -1.0f);
		position = Vector3(5.0f, 5.0f, 12.0f);
		up = Vector3(0.0f, 1.0f, 0.0);
	}
	else
	{
		set2DPosition(dimensions);
	}
}

void Camera::set2DPosition(Vector3 dimensions)
{
	position = Vector3(dimensions.x / 2, dimensions.y * 10, dimensions.z / 2);
	up = Vector3(0, 0, -1);
	viewDirection = Vector3(0, -1, 0);
	moveDirection = glm::cross(viewDirection, up);
}
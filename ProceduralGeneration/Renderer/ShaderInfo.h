#ifndef SHADER_INFO_H
#define SHADER_INFO_H

#include <GL\glew.h>
#include <Qt\qglobal.h>

struct ShaderInfo
{
	GLuint programID;
	bool isAvailable;
	ShaderInfo();
	ShaderInfo(GLuint programID);
};

#endif
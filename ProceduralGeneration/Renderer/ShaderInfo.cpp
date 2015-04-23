#include "ShaderInfo.h"

ShaderInfo::ShaderInfo()
{
	isAvailable = true;
}

ShaderInfo::ShaderInfo(GLuint programID)
{
	this->programID = programID;
	this->isAvailable = false;
}
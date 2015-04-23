#ifndef BUFFER_INFO_H
#define BUFFER_INFO_H

#include <GL\glew.h>

struct BufferInfo
{
	GLuint glBufferID;
	GLuint remainingSize;
};

#endif
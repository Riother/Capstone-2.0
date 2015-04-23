#ifndef PARAMETERTYPE_H
#define PARAMETERTYPE_H

enum ParameterType
{
	PT_BOOL    = sizeof(bool),
	PT_FLOAT   = sizeof(float),
	PT_VECTOR2 = sizeof(float) * 2,
	PT_VECTOR3 = sizeof(float) * 3,
	PT_VECTOR4 = sizeof(float) * 4,
	PT_MATRIX3 = sizeof(float) * 9,
	PT_MATRIX4 = sizeof(float) * 16,
};

#endif
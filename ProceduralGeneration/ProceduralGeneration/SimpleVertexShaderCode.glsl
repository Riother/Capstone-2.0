#version 400

in layout(location=0) vec3 position;
in layout(location=1) vec4 color;
in layout(location=2) vec3 normal;
in layout(location=3) vec2 uv;

uniform mat4 transformation;

out vec3 thePosition;
out vec4 theColor;
out vec3 theNormal;
out vec2 theUV;

void main()
{
	gl_Position = transformation * vec4(position, 1);

	thePosition = position;
	theColor = color;
	theNormal = normal;
	theUV = uv;
}
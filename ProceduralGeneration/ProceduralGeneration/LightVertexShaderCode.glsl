#version 400

in layout(location=0) vec3 position;
in layout(location=1) vec4 color;
in layout(location=2) vec3 normal;
in layout(location=3) vec2 uv;

uniform mat4 trans;

out vec4 deColor;
out vec2 deUV;
out vec3 deNormal;
out vec3 dePosition;

void main()
{
	gl_Position = trans * vec4(position, 1.0);
	deNormal = normal;
	dePosition = position;
	deColor = color;
	deUV = uv;
}
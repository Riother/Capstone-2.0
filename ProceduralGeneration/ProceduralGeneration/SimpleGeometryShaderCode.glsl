#version 400

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in there
{
	vec3 theNormal;
}here[];

void main()
{
	for(int i=0; i<3; i++)
	{
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}  
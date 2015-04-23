#version 400

in vec3 thePosition;
in vec4 theColor;
in vec3 theNormal;
in vec2 theUV;


uniform vec4 color;
uniform vec4 highlightColor;
uniform bool useImage;
uniform bool isHighlighted;
uniform sampler2D image;

out vec4 theFinalColor;

void main()
{
	vec2 flippedUV = vec2(theUV.x, 1 - theUV.y);

	if(useImage)
		theFinalColor = texture(image, flippedUV).rgba * color;
	else
		theFinalColor = color;

	if(isHighlighted)
		theFinalColor = highlightColor;

	//if(theColor.x  < 0.05 || theColor.z < 0.05)
		//theFinalColor = vec4(1, 1, 1, 1);

	float gradient1 = 0.1;
	float gradient2 = 0.3;
	float gradient3 = 0.6;
	float gradient4 = 1;

	theFinalColor = vec4(thePosition, 1);
	//if(theFinalColor.x <= gradient1 && theFinalColor.y <= gradient1 && theFinalColor.z <= gradient1)
	//	theFinalColor = vec4(color.x * 0.25, color.y * 0.25, color.z * 0.25, 1);
	//else if(theFinalColor.x <= gradient2 && theFinalColor.y <= gradient2 && theFinalColor.z <= gradient2)
	//	theFinalColor = vec4(color.x / 2, color.y / 2, color.z / 2, 1);
	//else if(theFinalColor.x <= gradient3 && theFinalColor.y <= gradient3 && theFinalColor.z <= gradient3)
	//	theFinalColor = vec4(color.x * 0.75, color.y * 0.75, color.z * 0.75, 1);
	//else if(theFinalColor.x <= gradient4 && theFinalColor.y <= gradient4 && theFinalColor.z <= gradient4)
	//	theFinalColor = color;
};
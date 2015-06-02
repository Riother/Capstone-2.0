#version 400

in vec3 thePosition;
in vec4 theColor;
in vec3 theNormal;
in vec2 theUV;

uniform mat4 modelToWorld;
uniform vec3 cameraPosition;
uniform vec3 lightPosition;
uniform vec4 color;
uniform bool useImage;
uniform sampler2D image;

out vec4 theFinalColor;

void main()
{
	vec3 diffuseLight  = vec3(1, 1, 1);
	vec3 specularLight = vec3(1, 1, 1);
	vec3 ambientLight  = vec3(1, 1, 1);
	float specularExponent = 50;

	vec4 newNormal = modelToWorld * vec4(theNormal, 0);

	vec3 transformedNormal = vec3( normalize(newNormal));
	vec3 lightVector = normalize(lightPosition - vec3(modelToWorld * vec4(thePosition, 1)));
	
	float diffuseBrightness = dot(lightVector, transformedNormal);
	
	vec3 finalDiffuseLight = diffuseLight * diffuseBrightness;
	
	vec3 reflectionSpecular = reflect(lightVector, transformedNormal);
	vec3 normalizedEyeVector = normalize(cameraPosition - vec3(modelToWorld * vec4(thePosition, 1)));
	float specularBrightness = dot(-reflectionSpecular, normalizedEyeVector);
	specularBrightness = pow(specularBrightness, specularExponent);
	
	vec3 finalSpecularColor = specularLight * specularBrightness;
	
	vec3 ambientDiffuse = clamp(ambientLight, 0, 1) + clamp(finalDiffuseLight, 0, 1);
	
	vec3 tempColor = vec3(color.x, color.y, color.z);
	theFinalColor = vec4((ambientDiffuse * tempColor) + clamp(finalSpecularColor, 0, 1), 1);

	//-----------------------------------------------------------------------------------------
	vec2 flippedUV = vec2(theUV.x, theUV.y);
	
	if(useImage)
		theFinalColor = texture(image, flippedUV).rgba;
	//else
	//	theFinalColor *= color;

	float gradient1 = 0.1;
	float gradient2 = 0.3;
	float gradient3 = 0.6;
	float gradient4 = 1;

	//theFinalColor = vec4(thePosition, 1);
	//if(theFinalColor.x <= gradient1 && theFinalColor.y <= gradient1 && theFinalColor.z <= gradient1)
	//	theFinalColor = vec4(color.x * 0.25, color.y * 0.25, color.z * 0.25, 1);
	//else if(theFinalColor.x <= gradient2 && theFinalColor.y <= gradient2 && theFinalColor.z <= gradient2)
	//	theFinalColor = vec4(color.x / 2, color.y / 2, color.z / 2, 1);
	//else if(theFinalColor.x <= gradient3 && theFinalColor.y <= gradient3 && theFinalColor.z <= gradient3)
	//	theFinalColor = vec4(color.x * 0.75, color.y * 0.75, color.z * 0.75, 1);
	//else if(theFinalColor.x <= gradient4 && theFinalColor.y <= gradient4 && theFinalColor.z <= gradient4)
	//	theFinalColor = color;

	//theFinalColor = theColor;
	//if(theColor.x == 0 && theColor.y == 0 && theColor.z == 0)
	//	theFinalColor =  texture(image, flippedUV).rgba;
	//theFinalColor += vec4(0.25f, 0.25f, 0.25f, 1);
};
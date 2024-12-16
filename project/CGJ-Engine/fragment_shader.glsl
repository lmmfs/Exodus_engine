#version 330 core

in vec2 ex_TexCoord;
in vec3 ex_Normal;
in vec4 ex_Color;
in vec3 FragPos;
in vec4 FragPosLightSpace;

in float zDepth;

out vec4 out_Color;

struct Material {
    float ambientStrength;
	float specularStrength;
    float shininess;
	float transparency;
	int type;
};

vec3 lightColor = vec3(1);

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D shadowMap;
  
uniform Material material;
uniform sampler2D ourSampler;
uniform float pi = 3.14159;
uniform float powerSlide = 1;

vec4 marble(float x, float y, float turbulence, vec4 color, float transparency) {
	vec4 newColor = vec4(transparency);
	color.x = color.x * 255;
	color.y = color.y * 255;
	color.z = color.z * 255;
	color.x = color.x - color.z;
	color.y = color.y - color.z;

	//xPeriod and yPeriod together define the angle of the lines both 0 ==> it becomes a normal turbulence pattern
	float xPeriod = 5.0; //defines repetition of marble lines in x direction
	float yPeriod = 10.0; //defines repetition of marble lines in y direction
	//turbPower = 0 ==> it becomes a normal sine pattern

	float turbPower = 5.0 * powerSlide; //makes twists

	float xyValue = x * xPeriod + y * yPeriod + turbPower * turbulence;
	float sineValue = color.z * abs(sin(xyValue * pi));
	newColor.x = ( color.x + sineValue )/255;
	newColor.y = ( color.y + sineValue )/255;
	newColor.z = ( sineValue )/255;
	return newColor;
}

vec4 wood(float x, float y, float turbulence, vec4 color, float transparency) {
	float xyPeriod = 24.0; //number of rings
	float turbPower = 0.1  * powerSlide; //makes twists
	float turbSize = 32.0; //initial size of the turbulence
	
	vec4 newColor = vec4(transparency);

	color.x = color.x * 255;
	color.y = color.y * 255;

	float xValue = (x - 1 / 2);
    float yValue = (y - 1 / 2);
    float distValue = sqrt(xValue * xValue + yValue * yValue) + turbPower * turbulence;
    float sineValue = 128.0 * abs(sin(2 * xyPeriod * distValue * 3.14159));
   
	newColor.x = ( color.x + sineValue )/255;
	newColor.y = ( color.y + sineValue )/255;
	newColor.z = color.z;
	return newColor;
}

vec4 melon(float x, float y, float turbulence, vec4 color, float transparency) {
	float turbPower = 1  * powerSlide;

	vec4 newColor = vec4(transparency);

	color.x = color.x * 255;
	color.y = color.y * 255;
	color.z = color.z * 255;

	float xyPeriod = 10.0; 

	float xValue = (x - 1 / 2) + turbPower * turbulence;
    float yValue = (y - 1 / 2) + turbPower * turbulence;
    float sineValue = 33.0 * abs(sin(xyPeriod * xValue * pi) + sin(xyPeriod * yValue * pi));

	newColor.x = ( color.x + sineValue )/255;
	newColor.y = ( color.y + sineValue )/255;
	newColor.z = ( sineValue )/255;
	return newColor;
}

vec4 squareTexture(float x, float y, float turbulenceX, float turbulenceY, vec4 color, float transparency) {
	float turbPower = 0.002  * powerSlide;
	vec4 newColor = vec4(transparency);

	color.x = color.x * 255;
	color.y = color.y * 255;
	color.z = color.z * 255;

	float xyPeriod = 15.0;
	float xValue = (x - 1 / 2) + turbPower * turbulenceX;
    float yValue = (y - 1 / 2) + turbPower * turbulenceY;

    float sineValue = 22.0 * abs(sin(xyPeriod * xValue * pi) + sin(xyPeriod * yValue * pi));
	sineValue = sineValue / 60;
	float r = abs(mod(sineValue, 2) - 1); 
	r = 1 * ( 1 - r );
	
	newColor.x = 1;
	newColor.y = r;
	newColor.z = 0;
	if(r < 0.2){
		newColor.w = 1;
	}
	
	return newColor;
}

float colorToFloat(vec4 color){
	return (color.x + color.y + color.z)/3;
}

float ShadowCalculation(vec4 fragPosLightSpace) {
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    float currentDepth = projCoords.z;
	
	vec3 lightDir = normalize(lightPos - FragPos);
	float cosTheta = clamp(dot(ex_Normal, lightDir), 0, 1); 
	float bias = 0.005 * tan(acos(cosTheta)); 
	bias = clamp(bias, 0, 0.01); 
	 
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0; 
	 
	if(currentDepth > 1.0) 
        shadow = 0.0;

    return shadow;
}

void main(void) {

	vec2 texCoord = ex_TexCoord; 

	float ambientStrength = material.ambientStrength;
	float specularStrength = material.specularStrength;
	float transparency = material.transparency;

	//Texture
	vec4 color = texture(ourSampler, texCoord);
	if(material.type == 1) {
		color = marble(texCoord.x, texCoord.y, colorToFloat(color), ex_Color, transparency);
	}
	if(material.type == 2) {
		color = wood(texCoord.x, texCoord.y, colorToFloat(color), ex_Color, transparency);
	}
	if(material.type == 3) {
		vec2 invCoord = vec2(1 - texCoord.x, 1 - texCoord.y);
		vec4 invColor = texture(ourSampler, invCoord);
		color = squareTexture(texCoord.x, texCoord.y, colorToFloat(color), colorToFloat(invColor), ex_Color, transparency);
	}
	if(material.type == 4) {
		color = melon(texCoord.x, texCoord.y, colorToFloat(color), ex_Color, transparency);
	} else {
		color.w = transparency;
	}
	
	//phong
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(ex_Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	float shadow = 0.0f;
	shadow = ShadowCalculation(FragPosLightSpace);
	
	//final color
	vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular));
	
	out_Color = vec4(result, 1.0) * color;
}
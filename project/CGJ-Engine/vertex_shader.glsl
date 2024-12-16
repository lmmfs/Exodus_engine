#version 330 core

in vec3 in_Position;
in vec2 in_TexCoord;
in vec3 in_Normal;


out float zDepth;
out vec2 ex_TexCoord;
out vec4 ex_Color;
out vec3 ex_Normal;
out vec3 FragPos;
out vec4 FragPosLightSpace;

uniform vec4 Color;

uniform mat4 ModelMatrix;

uniform SharedMatrices {
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

uniform mat4 lightSpaceMatrix;

void main(void) {
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_Position, 1);
	ex_TexCoord = in_TexCoord;
	ex_Color = Color;

	FragPos = vec3(ModelMatrix * vec4(in_Position, 1));
	ex_Normal = mat3(transpose(inverse(ModelMatrix))) * in_Normal;

	FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
}
#version 330 core
in vec3 in_Position;

out vec3 TexCoords;

uniform mat4 model = mat4(1.0f);

uniform SharedMatrices {
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main()
{
    gl_Position = ProjectionMatrix * ViewMatrix * vec4(in_Position, 1.0);
    TexCoords = in_Position;
}  
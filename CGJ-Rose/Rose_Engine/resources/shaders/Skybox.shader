#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

out vec3 TexCoords;

uniform SharedMatrices
{
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
};

void main()
{
    vec4 pos = ProjectionMatrix * ViewMatrix * vec4(position, 1.0);
    gl_Position = pos.xyww;
    TexCoords = position;
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{
    FragColor = texture(skybox, TexCoords);
}
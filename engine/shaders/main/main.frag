#version 460 core
out vec4 FragColor;
in vec2 TexCoords;
uniform vec3 objectColor;
uniform sampler2D sprite;
void main()
{
    FragColor = vec4(0,0,0, 1.0);
}

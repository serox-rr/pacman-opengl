#version 460 core
layout (location = 0) in vec4 aPos;
uniform mat4 transpose;
uniform mat4 model;
out vec2 TexCoords;
void main()
{
    gl_PointSize = 15.0;
    TexCoords = aPos.zw;
    gl_Position = transpose * model * vec4(aPos.xy, 0.0, 1.0);
}
//

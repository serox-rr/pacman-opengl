#version 460 core
layout (location = 0) in vec2 aPos;
uniform mat4 transpose;
uniform mat4 model;

void main()
{
    gl_PointSize = 15.0;
    gl_Position = transpose * model * vec4(aPos.xy, 0.0, 1.0);
}
//

#version 410 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 vertexColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform float u_Time;

void main()
{
    mat4 rotation = mat4(cos(u_Time), -sin(u_Time), 0.0, 0.0, sin(u_Time), cos(u_Time), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
                         0.0, 0.0, 0.0, 1.0);
    mat4 modelTransform = rotation * model;

    gl_Position = projection * view * modelTransform * vec4(aPos, 1.0);
    vertexColor = aColor;
}
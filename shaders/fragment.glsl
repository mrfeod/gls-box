#version 410 core

in vec3 vertexColor;
out vec4 FragColor;

uniform float u_Time;

vec3 rotateColor(vec3 color, float angle)
{
    float cosA          = cos(angle);
    float sinA          = sin(angle);
    mat3 rotationMatrix = mat3(cosA, -sinA, 0.0, sinA, cosA, 0.0, 0.0, 0.0, 1.0);
    return rotationMatrix * color;
}

void main()
{
    vec3 rotatedColor = 1.0 - rotateColor(vertexColor, u_Time);
    FragColor         = vec4(rotatedColor, 1.0);
}
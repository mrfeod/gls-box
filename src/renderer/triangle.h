#pragma once

#include "shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

class Triangle
{
public:
    Triangle();
    ~Triangle();

    void render(const Shader& shader, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const;

private:
    GLuint VAO;
    GLuint VBO;
};

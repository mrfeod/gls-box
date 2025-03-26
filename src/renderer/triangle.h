#pragma once

#include "shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

class Triangle
{
private:
    GLuint VAO_{};
    GLuint VBO_{};

public:
    Triangle();
    ~Triangle();

    void render(const Shader& shader, const glm::mat4& model, const glm::mat4& view,
                const glm::mat4& projection) const;
};

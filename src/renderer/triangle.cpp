#include "triangle.h"

#include <array>

namespace {

// Define triangle vertices and colors separately
const std::array<GLfloat, 9> k_Positions{
    -0.5F, -0.2887F, 0.0F,  // bottom left
    0.5F,  -0.2887F, 0.0F,  // bottom right
    0.0F,  0.5774F,  0.0F   // top
};

const std::array<GLfloat, 9> k_Colors{
    1.0F, 0.0F, 0.0F,  // red (bottom left)
    0.0F, 1.0F, 0.0F,  // green (bottom right)
    0.0F, 0.0F, 1.0F   // blue (top)
};

}  // namespace

Triangle::Triangle()
{
    // Create vertex array object and vertex buffers
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &colorVBO_);

    // Bind vertex array object first
    glBindVertexArray(VAO_);

    // Set up position buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(k_Positions), k_Positions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    // Set up color buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(k_Colors), k_Colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(1);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Triangle::~Triangle()
{
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
    glDeleteBuffers(1, &colorVBO_);
}

void Triangle::render(const Shader& shader, const glm::mat4& model, const glm::mat4& view,
                      const glm::mat4& projection) const
{
    // Set shader uniforms
    shader.use();
    shader.setUniform("model", model);
    shader.setUniform("view", view);
    shader.setUniform("projection", projection);

    // Draw triangle
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

#include "triangle.h"

namespace {
// Define triangle vertices (position and color)
constexpr float vertices[] = {
    // positions         // colors
    -0.5F, -0.2887F, 0.0F, 1.0F, 0.0F, 0.0F,  // bottom left
    0.5F,  -0.2887F, 0.0F, 0.0F, 1.0F, 0.0F,  // bottom right
    0.0F,  0.5774F,  0.0F, 0.0F, 0.0F, 1.0F   // top
};
}  // namespace

Triangle::Triangle() : VAO(0), VBO(0)
{
    // Create vertex array object and vertex buffer
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind vertex array object first, then vertex buffer
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    constexpr int stride = 6 * sizeof(float);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, nullptr);
    glEnableVertexAttribArray(0);

    // Color attribute
    const std::uintptr_t bufferOffset = 3 * sizeof(float);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
                          reinterpret_cast<const void*>(bufferOffset));
    glEnableVertexAttribArray(1);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Triangle::~Triangle()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
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
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

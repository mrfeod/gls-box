#include "triangle.h"

#include <array>

namespace {

// Define triangle vertices (position and color)
const std::array<GLfloat, 18> k_Vertices{
    // positions         // colors
    -0.5F, -0.2887F, 0.0F, 1.0F, 0.0F, 0.0F,  // bottom left
    0.5F,  -0.2887F, 0.0F, 0.0F, 1.0F, 0.0F,  // bottom right
    0.0F,  0.5774F,  0.0F, 0.0F, 0.0F, 1.0F   // top
};

}  // namespace

Triangle::Triangle()
{
    // Create vertex array object and vertex buffer
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);

    // Bind vertex array object first, then vertex buffer
    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(k_Vertices), k_Vertices.data(), GL_STATIC_DRAW);

    constexpr int stride = 6 * sizeof(float);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, nullptr);
    glEnableVertexAttribArray(0);

    // Color attribute
    const void* bufferOffset = reinterpret_cast<const void*>(3 * sizeof(GLfloat));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, bufferOffset);
    glEnableVertexAttribArray(1);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Triangle::~Triangle()
{
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
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

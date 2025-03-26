#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
private:
    GLuint programID_{};
    GLuint vertexShaderID_{};
    GLuint fragmentShaderID_{};

public:
    ~Shader();

    void loadFromFile(const std::string& vertexPath, const std::string& fragmentPath);
    void use() const;
    void setUniform(const std::string& name, float value) const;
    void setUniform(const std::string& name, int value) const;
    void setUniform(const std::string& name, const glm::vec3& value) const;
    void setUniform(const std::string& name, const glm::mat4& value) const;

private:
    GLuint compileShader(GLenum type, const std::string& source);
    void linkProgram();
};

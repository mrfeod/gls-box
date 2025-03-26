#include "shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace {
constexpr int k_InfoLogSize = 512;
}

Shader::~Shader()
{
    if (programID_ != 0) {
        glDeleteProgram(programID_);
        programID_ = 0;
    }
}

void Shader::loadFromFile(const std::string& vertexPath, const std::string& fragmentPath)
{
    // Read vertex shader code from file
    std::ifstream vertexFile(vertexPath);
    if (!vertexFile.is_open()) {
        throw std::runtime_error("Failed to open vertex shader file: " + vertexPath);
    }

    std::stringstream vertexStream;
    vertexStream << vertexFile.rdbuf();
    std::string vertexCode = vertexStream.str();
    vertexFile.close();

    // Read fragment shader code from file
    std::ifstream fragmentFile(fragmentPath);
    if (!fragmentFile.is_open()) {
        throw std::runtime_error("Failed to open fragment shader file: " + fragmentPath);
    }

    std::stringstream fragmentStream;
    fragmentStream << fragmentFile.rdbuf();
    std::string fragmentCode = fragmentStream.str();
    fragmentFile.close();

    // Compile shaders
    const char* vertexSource   = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Create and compile vertex shader
    vertexShaderID_ = glCreateShader(GL_VERTEX_SHADER);
    if (vertexShaderID_ == 0) {
        throw std::runtime_error("Failed to create vertex shader");
    }

    glShaderSource(vertexShaderID_, 1, &vertexSource, nullptr);
    glCompileShader(vertexShaderID_);

    // Check for vertex shader compile errors
    GLint success = 0;
    std::array<GLchar, k_InfoLogSize> infoLog{};
    glGetShaderiv(vertexShaderID_, GL_COMPILE_STATUS, &success);
    if (success == 0) {
        glGetShaderInfoLog(vertexShaderID_, k_InfoLogSize, nullptr, infoLog.data());
        glDeleteShader(vertexShaderID_);
        throw std::runtime_error("Vertex shader compilation failed: " +
                                 std::string(infoLog.data()));
    }

    // Create and compile fragment shader
    fragmentShaderID_ = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragmentShaderID_ == 0) {
        glDeleteShader(vertexShaderID_);
        throw std::runtime_error("Failed to create fragment shader");
    }

    glShaderSource(fragmentShaderID_, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShaderID_);

    // Check for fragment shader compile errors
    glGetShaderiv(fragmentShaderID_, GL_COMPILE_STATUS, &success);
    if (success == 0) {
        glGetShaderInfoLog(fragmentShaderID_, k_InfoLogSize, nullptr, infoLog.data());
        glDeleteShader(vertexShaderID_);
        glDeleteShader(fragmentShaderID_);
        throw std::runtime_error("Fragment shader compilation failed: " +
                                 std::string(infoLog.data()));
    }

    // Link shaders into a program
    programID_ = glCreateProgram();
    if (programID_ == 0) {
        glDeleteShader(vertexShaderID_);
        glDeleteShader(fragmentShaderID_);
        throw std::runtime_error("Failed to create shader program");
    }

    glAttachShader(programID_, vertexShaderID_);
    glAttachShader(programID_, fragmentShaderID_);
    glLinkProgram(programID_);

    // Check for linking errors
    glGetProgramiv(programID_, GL_LINK_STATUS, &success);
    if (success == 0) {
        glGetProgramInfoLog(programID_, k_InfoLogSize, nullptr, infoLog.data());
        glDeleteShader(vertexShaderID_);
        glDeleteShader(fragmentShaderID_);
        glDeleteProgram(programID_);
        programID_ = 0;
        throw std::runtime_error("Shader program linking failed: " + std::string(infoLog.data()));
    }

    // Clean up shaders as they're no longer needed after linking
    glDeleteShader(vertexShaderID_);
    glDeleteShader(fragmentShaderID_);
    vertexShaderID_   = 0;
    fragmentShaderID_ = 0;
}

void Shader::use() const
{
    if (programID_ == 0) {
        throw std::runtime_error("Attempting to use an invalid shader program");
    }
    glUseProgram(programID_);
}

void Shader::setUniform(const std::string& name, float value) const
{
    if (programID_ == 0) {
        throw std::runtime_error("Shader program not initialized");
    }
    GLint location = glGetUniformLocation(programID_, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader program." << "\n";
        return;
    }
    glUniform1f(location, value);
}

void Shader::setUniform(const std::string& name, int value) const
{
    if (programID_ == 0) {
        throw std::runtime_error("Shader program not initialized");
    }
    GLint location = glGetUniformLocation(programID_, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader program." << "\n";
        return;
    }
    glUniform1i(location, value);
}

void Shader::setUniform(const std::string& name, const glm::vec3& value) const
{
    if (programID_ == 0) {
        throw std::runtime_error("Shader program not initialized");
    }
    GLint location = glGetUniformLocation(programID_, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader program." << "\n";
        return;
    }
    glUniform3fv(location, 1, &value[0]);
}

void Shader::setUniform(const std::string& name, const glm::mat4& value) const
{
    if (programID_ == 0) {
        throw std::runtime_error("Shader program not initialized");
    }
    GLint location = glGetUniformLocation(programID_, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader program." << "\n";
        return;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

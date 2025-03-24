#include "shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::~Shader()
{
    if (programID != 0) {
        glDeleteProgram(programID);
        programID = 0;
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
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (vertexShaderID == 0) {
        throw std::runtime_error("Failed to create vertex shader");
    }

    glShaderSource(vertexShaderID, 1, &vertexSource, nullptr);
    glCompileShader(vertexShaderID);

    // Check for vertex shader compile errors
    GLint success = 0;
    GLchar infoLog[512];
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShaderID, 512, nullptr, infoLog);
        glDeleteShader(vertexShaderID);
        throw std::runtime_error("Vertex shader compilation failed: " + std::string(infoLog));
    }

    // Create and compile fragment shader
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragmentShaderID == 0) {
        glDeleteShader(vertexShaderID);
        throw std::runtime_error("Failed to create fragment shader");
    }

    glShaderSource(fragmentShaderID, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShaderID);

    // Check for fragment shader compile errors
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
    if (success == 0) {
        glGetShaderInfoLog(fragmentShaderID, 512, nullptr, infoLog);
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
        throw std::runtime_error("Fragment shader compilation failed: " + std::string(infoLog));
    }

    // Link shaders into a program
    programID = glCreateProgram();
    if (programID == 0) {
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
        throw std::runtime_error("Failed to create shader program");
    }

    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    // Check for linking errors
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (success == 0) {
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
        glDeleteProgram(programID);
        programID = 0;
        throw std::runtime_error("Shader program linking failed: " + std::string(infoLog));
    }

    // Clean up shaders as they're no longer needed after linking
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    vertexShaderID   = 0;
    fragmentShaderID = 0;
}

void Shader::use() const
{
    if (programID == 0) {
        throw std::runtime_error("Attempting to use an invalid shader program");
    }
    glUseProgram(programID);
}

void Shader::setUniform(const std::string& name, float value) const
{
    if (programID == 0) {
        throw std::runtime_error("Shader program not initialized");
    }
    GLint location = glGetUniformLocation(programID, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader program." << "\n";
        return;
    }
    glUniform1f(location, value);
}

void Shader::setUniform(const std::string& name, int value) const
{
    if (programID == 0) {
        throw std::runtime_error("Shader program not initialized");
    }
    GLint location = glGetUniformLocation(programID, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader program." << "\n";
        return;
    }
    glUniform1i(location, value);
}

void Shader::setUniform(const std::string& name, const glm::vec3& value) const
{
    if (programID == 0) {
        throw std::runtime_error("Shader program not initialized");
    }
    GLint location = glGetUniformLocation(programID, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader program." << "\n";
        return;
    }
    glUniform3fv(location, 1, &value[0]);
}

void Shader::setUniform(const std::string& name, const glm::mat4& value) const
{
    if (programID == 0) {
        throw std::runtime_error("Shader program not initialized");
    }
    GLint location = glGetUniformLocation(programID, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader program." << "\n";
        return;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

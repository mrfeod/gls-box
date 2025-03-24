#include "renderer.h"
#include "triangle.h"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <iostream>

bool Renderer::init()
{
    // Initialize GLAD - MUST happen after context is current
    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0) {
        std::cerr << "Failed to initialize GLAD" << "\n";
        return false;
    }

    // Add after successful GLAD initialization
    const GLubyte* renderer    = glGetString(GL_RENDERER);
    const GLubyte* version     = glGetString(GL_VERSION);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    std::cout << "Renderer: " << renderer << "\n";
    std::cout << "OpenGL version supported: " << version << "\n";
    std::cout << "GLSL version supported: " << glslVersion << "\n";

    // You can also check if specific extensions are available
    GLint numExtensions = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
    std::cout << "Number of extensions: " << numExtensions << "\n";

    // Initialize OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0F, 0.0F, 0.0F, 1.0F);

    // Load shaders
    shader_.loadFromFile("./shaders/vertex.glsl", "./shaders/fragment.glsl");
    return true;
}

void Renderer::setViewport(int width, int height)
{
    width_  = width;
    height_ = height;
    glViewport(0, 0, width, height);
}

void Renderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set a uniform variable (example: time)
    auto timeValue = static_cast<float>(glfwGetTime());
    shader_.setUniform("u_Time", timeValue);

    // Add rendering code here
    Triangle triangle;

    const float aspectRatio = static_cast<float>(width_) / static_cast<float>(height_);

    constexpr float fov       = 45.0F;
    constexpr float nearPlane = 0.1F;
    constexpr float farPlane  = 100.0F;
    glm::mat4 projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

    // Camera/view transformation
    constexpr float cameraDistance = 3.0F;
    glm::mat4 view = glm::lookAt(glm::vec3(0.0F, 0.0F, cameraDistance), glm::vec3(0.0F, 0.0F, 0.0F),
                                 glm::vec3(0.0F, 1.0F, 0.0F));

    // Pass the adjusted view matrix to the triangle's render method
    triangle.render(shader_, glm::mat4(1.0F), view, projection);
}
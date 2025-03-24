#include "window.h"

#include <iostream>

Window::Window(int width, int height, const char* title)
{
    if (glfwInit() == 0) {
        std::cerr << "Failed to initialize GLFW." << "\n";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    windowHandle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (windowHandle == nullptr) {
        glfwTerminate();
        std::cerr << "Failed to create window" << "\n";
    }

    glfwMakeContextCurrent(windowHandle);
}

Window::~Window()
{
    glfwDestroyWindow(windowHandle);
    glfwTerminate();
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::close()
{
    glfwSetWindowShouldClose(windowHandle, GLFW_TRUE);
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(windowHandle) != 0;
}

void Window::swapBuffers()
{
    glfwSwapBuffers(windowHandle);
}

void Window::registerFramebufferSizeCallback(GLFWframebuffersizefun callback) const
{
    glfwSetFramebufferSizeCallback(windowHandle, callback);
}

void Window::getFramebufferSize(int* width, int* height) const
{
    glfwGetFramebufferSize(windowHandle, width, height);
}

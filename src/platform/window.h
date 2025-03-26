#pragma once

#include <GLFW/glfw3.h>

class Window
{
private:
    GLFWwindow* windowHandle_{};

public:
    Window(int width, int height, const char* title);
    ~Window();

    bool init();

    void pollEvents();
    void close();

    void swapBuffers();

    bool shouldClose() const;

    void registerFramebufferSizeCallback(GLFWframebuffersizefun callback) const;

    void getFramebufferSize(int* width, int* height) const;
};
#ifndef APPLICATION_H
#define APPLICATION_H

#include "renderer/renderer.h"
#include "platform/window.h"

class Application
{
private:
    Window window_;
    Renderer renderer_;

public:
    Application();

    bool initialize();
    void run();

private:
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};

#endif  // APPLICATION_H
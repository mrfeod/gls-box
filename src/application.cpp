#include "application.h"

#include <functional>

namespace {

constexpr int k_InitWidth  = 800;
constexpr int k_InitHeight = 600;

namespace CallbackRegistry {
std::function<void(int, int)> g_framebufferSizeCallback;

// Static C-compatible function that GLFW will call
void FramebufferSizeCallbackBridge(GLFWwindow*, int width, int height)
{
    if (g_framebufferSizeCallback) {
        g_framebufferSizeCallback(width, height);
    }
}

}  // namespace CallbackRegistry

}  // namespace

Application::Application() : window_(k_InitWidth, k_InitHeight, "OpenGL Application")
{
    CallbackRegistry::g_framebufferSizeCallback = [this](int width, int height) {
        renderer_.setViewport(width, height);
    };
    window_.registerFramebufferSizeCallback(CallbackRegistry::FramebufferSizeCallbackBridge);
}

bool Application::initialize()
{
    if (!renderer_.init()) {
        return false;
    }

    // Set initial viewport size
    int width  = 0;
    int height = 0;
    window_.getFramebufferSize(&width, &height);
    renderer_.setViewport(width, height);

    return true;
}

void Application::run()
{
    // Main application loop
    while (!window_.shouldClose()) {
        window_.pollEvents();

        // Rendering code
        renderer_.render();
        window_.swapBuffers();
    }
}

void Application::framebufferSizeCallback(GLFWwindow*, int width, int height)
{
    renderer_.setViewport(width, height);
}

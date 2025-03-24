#pragma once

#include "shader.h"

class Renderer
{
public:
    bool init();
    void render();
    void setViewport(int width, int height);

private:
    Shader shader_;
    int width_;
    int height_;
};
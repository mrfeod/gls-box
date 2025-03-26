#pragma once

#include "shader.h"

class Renderer
{
private:
    Shader shader_;
    int width_{};
    int height_{};

public:
    bool init();
    void render();
    void setViewport(int width, int height);
};
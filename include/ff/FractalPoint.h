#pragma once
#include "glm/vec3.hpp"

struct FractalPoint
{
    glm::vec3 pos;
    FractalPoint(glm::vec3 pos) : pos{pos} {}
    virtual ~FractalPoint() {}
};
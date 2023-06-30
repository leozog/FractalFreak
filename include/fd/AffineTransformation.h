#pragma once

#include "glm/glm.hpp"
#include "glm/ext.hpp"

// TODO(?): #include "fd/AffineTransformation.h" in FractalsDefinitions.h

struct AffineTransformation
{
    AffineTransformation(float pick_probability = 0.) : pick_probability(pick_probability) {}

    // returns a copy of itself in a new unique_ptr of a derived type
    // virtual std::unique_ptr<AffineTransformation> copy() = 0;

    float pick_probability; // probability of this transformation being chosen
};


struct AffineTransformation_2D : public AffineTransformation
{
    AffineTransformation_2D(float a = 0, float b = 0, float c = 0, float d = 0, float dx = 0, float dy = 0) : matrix(a, c, b, d), vector(dx, dy) {}

    // std::unique_ptr<AffineTransformation> copy() { return std::make_unique<AffineTransformation_2D>(*this); }

    glm::mat2 matrix; // transformation matrix: {{A, C}, {B, D}}
    glm::vec2 vector; // translation vector: {dx, dy} or {E, F}
};

struct AffineTransformation_3D : public AffineTransformation
{
    AffineTransformation_3D(float a = 0, float b = 0, float c = 0, float d = 0, float e = 0, float f = 0, float g = 0, float h = 0, float i = 0, float dx = 0, float dy = 0, float dz = 0) : matrix(a, d, g, b, e, h, c, f, i), vector(dx, dy, dz) {}

    // std::unique_ptr<AffineTransformation> copy() { return std::make_unique<AffineTransformation_2D>(*this); }

    glm::mat3 matrix; // transformation matrix: {{A, C}, {B, D}}
    glm::vec3 vector; // translation vector: {dx, dy} or {E, F}
};
#pragma once

#include "glm/glm.hpp"
#include "glm/ext.hpp"

struct AffineTransformation_3D
{
    AffineTransformation_3D(float a = 0, float b = 0, float c = 0, float d = 0, float e = 0, float f = 0, float g = 0, float h = 0, float i = 0, float dx = 0, float dy = 0, float dz = 0)
        : matrix(a, d, g, b, e, h, c, f, i),
          vector(dx, dy, dz),
          pick_probability(0)
    {
    }

    glm::mat3 matrix;       // transformation matrix: {{A, D, G}, {B, E, H}, {C, F, I}}
    glm::vec3 vector;       // translation vector: {dx, dy, dz} or {J, K, L}
    float pick_probability; // probability of this transformation being chosen
};

struct AffineTransformation_2D : public AffineTransformation_3D
{
    AffineTransformation_2D(float a = 0, float b = 0, float c = 0, float d = 0, float dx = 0, float dy = 0)
        : AffineTransformation_3D{a, b, 0, c, d, 0, 0, 0, 1, dx, dy, 0}
    {
    }
};
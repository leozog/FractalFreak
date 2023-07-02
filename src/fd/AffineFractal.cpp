#include "fd/AffineFractal.h"
#include <cmath>

namespace AffineFractal
{
    std::unique_ptr<FractalParameters> Parameters::copy() const
    {
        return std::make_unique<Parameters>(*this);
    }

    void Parameters::add(FractalParameters &a)
    {
        AffineFractal::Parameters &A = dynamic_cast<AffineFractal::Parameters &>(a);

        while (A.transformations.size() > transformations.size())
            transformations.push_back(AffineTransformation_3D());

        while (A.transformations.size() < transformations.size())
            A.transformations.push_back(AffineTransformation_3D());

        for (int i = 0; i < transformations.size(); i++)
        {
            transformations[i].matrix += A.transformations[i].matrix;
            transformations[i].vector += A.transformations[i].vector;
        }

        cam_pos += A.cam_pos;
    }

    void Parameters::mul(const double b)
    {
        for (int i = 0; i < transformations.size(); i++)
        {
            transformations[i].matrix *= b;
            transformations[i].vector *= b;
        }

        cam_pos *= b;
    }

#define GLM_FORCE_RADIANS

    glm::mat4 Parameters::get_transformation_matrix()
    {
        glm::mat4 mTranslate = glm::translate(glm::mat4(1.0f), -cam_pos);
        glm::mat4 mRotation = lookAt(glm::vec3(0, 0, 0), -cam_pos, glm::vec3(0, 1, 0));
        glm::mat4 mPerspective = glm::perspectiveFov(glm::radians(30.0f), 2.0f, 2.0f, 0.001f, 100.0f);
        return mPerspective * mRotation * mTranslate;
    }
}
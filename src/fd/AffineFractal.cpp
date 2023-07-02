#include "fd/AffineFractal.h"

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
    }

    void Parameters::mul(const double b)
    {
        for (int i = 0; i < transformations.size(); i++)
        {
            transformations[i].matrix *= b;
            transformations[i].vector *= b;
        }
    }
}
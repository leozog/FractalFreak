#include "fd/Parameters.h"

namespace fractal_factory
{
    std::unique_ptr<FractalParameters> Parameters2D::copy() const
    {
        return std::make_unique<Parameters2D>(*this);
    }

    void Parameters2D::add(FractalParameters& a)
    {
        Parameters2D& A = dynamic_cast<Parameters2D&>(a);

        while (A.transformations.size() > transformations.size())
            transformations.push_back(AffineTransformation_2D(0, 0, 0, 0, 0, 0));

        while (A.transformations.size() < transformations.size())
            A.transformations.push_back(AffineTransformation_2D(0, 0, 0, 0, 0, 0));

        for (int i = 0; i < transformations.size(); i++)
        {
            transformations[i].matrix += A.transformations[i].matrix;
            transformations[i].vector += A.transformations[i].vector;
        }
    }

    void Parameters2D::mul(const double b)
    {
        for (int i = 0; i < transformations.size(); i++)
        {
            transformations[i].matrix *= b;
            transformations[i].vector *= b;
        }
    }


    std::unique_ptr<FractalParameters> Parameters3D::copy() const
    {
        return std::make_unique<Parameters3D>(*this);
    }

    void Parameters3D::add(FractalParameters& a)
    {
        Parameters3D& A = dynamic_cast<Parameters3D&>(a);

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

    void Parameters3D::mul(const double b)
    {
        for (int i = 0; i < transformations.size(); i++)
        {
            transformations[i].matrix *= b;
            transformations[i].vector *= b;
        }
    }
}
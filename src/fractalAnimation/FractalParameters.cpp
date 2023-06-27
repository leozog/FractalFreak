#include "fractalAnimation/FractalParameters.h"

std::unique_ptr<FractalParameters> operator*(const std::unique_ptr<FractalParameters> &a, const double b)
{
    std::unique_ptr<FractalParameters> c = a->copy();
    c->mul(b);
    return c;
}

std::unique_ptr<FractalParameters> operator*(const double b, const std::unique_ptr<FractalParameters> &a)
{
    return operator*(a, b);
}

std::unique_ptr<FractalParameters> operator+(const std::unique_ptr<FractalParameters> &a, const std::unique_ptr<FractalParameters> &b)
{
    std::unique_ptr<FractalParameters> c = a->copy();
    c->add(*b);
    return c;
}

std::unique_ptr<FractalParameters> operator-(const std::unique_ptr<FractalParameters> &a, const std::unique_ptr<FractalParameters> &b)
{
    std::unique_ptr<FractalParameters> c = b->copy();
    c->mul(-1);
    c->add(*a);
    return c;
}
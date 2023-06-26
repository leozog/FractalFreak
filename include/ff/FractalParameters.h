#pragma once
#include <memory>

class FractalParameters
{
private:
public:
    virtual std::unique_ptr<FractalParameters> copy() const { return 0; };
    virtual void add(const FractalParameters &b){};
    virtual void mul(const double b){};
};

std::unique_ptr<FractalParameters> operator*(const std::unique_ptr<FractalParameters> &a, const double b);
std::unique_ptr<FractalParameters> operator*(const double b, const std::unique_ptr<FractalParameters> &a);
std::unique_ptr<FractalParameters> operator+(const std::unique_ptr<FractalParameters> &a, const std::unique_ptr<FractalParameters> &b);
std::unique_ptr<FractalParameters> operator-(const std::unique_ptr<FractalParameters> &a, const std::unique_ptr<FractalParameters> &b);
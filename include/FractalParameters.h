#pragma once

class FractalParameters
{
private:
public:
    virtual void add(const FractalParameters &b) = 0;
    virtual void mul(const double b) = 0;
};

std::unique_ptr<FractalParameters> operator*(const std::unique_ptr<FractalParameters> &a, const double b);
std::unique_ptr<FractalParameters> operator*(const double b, const std::unique_ptr<FractalParameters> &a);
std::unique_ptr<FractalParameters> operator+(const std::unique_ptr<FractalParameters> &a, const std::unique_ptr<FractalParameters> &b);
std::unique_ptr<FractalParameters> operator-(const std::unique_ptr<FractalParameters> &a, const std::unique_ptr<FractalParameters> &b);
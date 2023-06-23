#pragma once
#include "FractalParameters.h"
#include "Point.h"

namespace FractalGenerator
{
    class Points
    {
    private:
    public:
        virtual std::vector<std::unique_ptr<Point>> calculate(const std::unique_ptr<FractalParameters> &param) = 0;
    };

    class Pixels
    {
    private:
    public:
        virtual void calculate(std::vector<std::unique_ptr<Point>> &points, wxImage color, wxImage depth, uint32_t W, uint32_t H) = 0;
    };
}
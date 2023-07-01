#pragma once
#include "ff/FractalParameters.h"
#include "ff/FractalPoint.h"

#include <wx/image.h>

namespace FractalGenerator
{
    class Points
    {
    public:
        virtual std::vector<std::unique_ptr<FractalPoint>> calculate(const std::unique_ptr<FractalParameters> &param) const = 0;
    };

    class Pixels
    {
    public:
        virtual void render(const std::vector<std::unique_ptr<FractalPoint>> &points, wxImage &color, wxImage &depth, uint32_t W, uint32_t H) const = 0;
    };
}
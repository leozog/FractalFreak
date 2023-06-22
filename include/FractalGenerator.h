#pragma once

namespace FractalGenerator
{
    class Point
    {
    private:
    public:
        virtual void calculate(const FractalParameters &param, wxImage &img);
    };

    class Img
    {
    private:
    public:
        virtual void calculate(wxImage &color, wxImage &depth);
    };
}
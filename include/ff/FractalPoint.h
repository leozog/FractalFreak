#pragma once

struct FractalPoint
{
    double x, y, z;
    FractalPoint(double x, double y, double z) : x{x}, y{y}, z{z} {}
    virtual ~FractalPoint() {}
};
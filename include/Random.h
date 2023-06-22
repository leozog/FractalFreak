#pragma once
#include <cstdlib>

double rand_d(double low, double high)
{
    return ((double)rand() * (high - low)) / (double)RAND_MAX + low;
}
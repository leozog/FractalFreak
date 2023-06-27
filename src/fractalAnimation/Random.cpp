#include "fractalAnimation/Random.h"

namespace Random
{
    int32_t rand_i(int32_t low, int32_t high)
    {
        return rand() % (high - low) + low;
    }

    double rand_d(double low, double high)
    {
        return ((double)rand() * (high - low)) / (double)RAND_MAX + low;
    }
}

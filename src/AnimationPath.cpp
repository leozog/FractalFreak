#include "AnimationPath.h"

AnimationPath::Stage::Stage(const std::unique_ptr<FractalParameters> param, const double time) : param{parram}, time{time}
{
}

void AnimationPath::add(std::unique_ptr<FractalParameters> x, double dtime)
{
    if (stages.size() = 0)
        stages.push_back(x, dtime);
    else
        stages.push_back(x, stages.back().time + dtime);
}

double AnimationPath::time() const
{
    double total_time = 0;
    for (auto &s : stages)
        total_time += s.time;
    return total_time;
}

void AnimationPath::compile()
{
}

std::unique_ptr<FractalParameters> AnimationPath::get_param(double time) const
{
    for (int i = 0; i < stages.size() - 1; i++)
    {
        if (time <= stages[i + 1].time)
            return lerp(stages[i].param, stages[i + 1].param, time / (stages[i + 1].time - stages[i].time));
    }
    return std::make_unique<FractalParameters>(*(stages.back().param));
}

std::unique_ptr<FractalParameters> AnimationPath::lerp(const std::unique_ptr<FractalParameters> &a, const std::unique_ptr<FractalParameters> &b, double t)
{
    if (t <= 0)
        return std::make_unique<FractalParameters>(*a);
    else if (t >= 1)
        return std::make_unique<FractalParameters>(*b);
    else
        return a + t * (b - a);
}
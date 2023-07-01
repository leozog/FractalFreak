#include "ff/AnimationPath.h"

AnimationPath::Stage::Stage(std::unique_ptr<FractalParameters> &&param, const double time) : param{std::move(param)}, time{time}
{
}

AnimationPath::Stage::Stage(const Stage &other) : param{other.param->copy()}, time{other.time}
{
}

AnimationPath::Stage::Stage(Stage &&other) : param{std::move(other.param)}, time{other.time}
{
}

void AnimationPath::add(std::unique_ptr<FractalParameters> &&x, double dtime)
{
    if (stages.size() == 0)
        stages.push_back(Stage(std::move(x), dtime));
    else
        stages.push_back(Stage(std::move(x), stages.back().time + dtime));
}

double AnimationPath::time() const
{
    return stages.back().time;
}

void AnimationPath::compile()
{
}

std::unique_ptr<FractalParameters> AnimationPath::get_param(double time) const
{
    for (int i = 0; i < stages.size() - 1; i++)
    {
        if (time <= stages[i + 1].time)
        {
            time = smoothstep(0, 1, (time - stages[i].time) / (stages[i + 1].time - stages[i].time));
            return lerp(stages[i].param, stages[i + 1].param, time);
        }
    }
    return stages.back().param->copy();
}

std::unique_ptr<FractalParameters> AnimationPath::lerp(const std::unique_ptr<FractalParameters> &a, const std::unique_ptr<FractalParameters> &b, double t) const
{
    if (t <= 0)
        return a->copy();
    else if (t >= 1)
        return b->copy();
    else
        return a + t * (b - a);
}

double AnimationPath::smoothstep(double a, double b, double t) const
{
    if (t <= 0)
        return a;
    else if (t >= 1)
        return b;
    return t * t * (3.0 - 2.0 * t) * (b - a) + a;
}

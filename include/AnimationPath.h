#pragma once
#include <vector>

class AnimationPath
{
private:
    struct stage
    {
        const std::unique_ptr<FractalParameters> param;
        const double time;
        stage(param, time) : param{param}, time{time} {}
    };
    std::vector<stage> stages; // stores the parameters of each stage and the time of its appearance [seconds]

public:
    void add(std::unique_ptr<FractalParameters> x, double dtime);    // Adds a Fractal parameters stage. dtime is a time from the previous stage
    template <typename T>                                            //
    void add(const T &x, double dtime);                              //
    double time() const;                                             // Calculates the time of entire path
    void compile();                                                  // Performs additional calculations after the whole path is assembled
    std::unique_ptr<FractalParameters> get_param(double time) const; // Returns a set of parameters necessary for generating a fractal for a given time

private:
    // linear interpolation
    std::unique_ptr<FractalParameters> lerp(const std::unique_ptr<FractalParameters> &a, const std::unique_ptr<FractalParameters> &b, float t)
};

template <typename T>
void AnimationPath::add(const T &x, double dtime)
{
    add(std::make_unique<T>(x), dtime);
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

std::unique_ptr<FractalParameters> AnimationPath::lerp(const std::unique_ptr<FractalParameters> &a, const std::unique_ptr<FractalParameters> &b, float t)
{
    if (t <= 0)
        return std::make_unique<FractalParameters>(*a);
    else if (t >= 1)
        return std::make_unique<FractalParameters>(*b);
    else
        return a + t * (b - a);
}
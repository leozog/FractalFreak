#pragma once
#include <vector>

class AnimationPath
{
private:
    struct Stage
    {
        const std::unique_ptr<FractalParameters> param;
        const double time;
        Stage(const std::unique_ptr<FractalParameters> param, const double time);
    };
    std::vector<Stage> stages; // stores the parameters of each stage and the time of its appearance [seconds]

public:
    void add(std::unique_ptr<FractalParameters> x, double dtime); // Adds a Fractal parameters stage. dtime is a time from the previous stage
    template <typename T>
    void add(const T &x, double dtime)
    {
        add(std::make_unique<T>(x), dtime);
    }
    double time() const;                                             // Calculates the time of entire path
    void compile();                                                  // Performs additional calculations after the whole path is assembled
    std::unique_ptr<FractalParameters> get_param(double time) const; // Returns a set of parameters necessary for generating a fractal for a given time

private:
    // linear interpolation
    std::unique_ptr<FractalParameters> lerp(const std::unique_ptr<FractalParameters> &a, const std::unique_ptr<FractalParameters> &b, double t);
};

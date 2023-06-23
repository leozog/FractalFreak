#pragma once
#include "Task.h"
#include "FractalGenerator.h"
// #include "PostProcess.h"

class Frame : public Task
{
private:
    const uint32_t W, H;
    const std::unique_ptr<FractalParameters> param;
    const FractalGenerator::Points &points_generator;
    const FractalGenerator::Pixels &pixels_generator;
    // const std::vector<&PostProcess> &post_process_stack;

    wxImage color;

public:
    Frame(
        const std::unique_ptr<FractalParameters> param,
        const FractalGenerator::Points &points_generator,
        const FractalGenerator::Pixels &pixels_generator,
        // const std::vector<&PostProcess> &post_process_stack;
        uint32_t W, uint32_t H);
    void process() override; // renders the frame
    wxImage get_img() const; // returns a wxwidgets wxImage (copy of color)
};
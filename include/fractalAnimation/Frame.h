#pragma once
#include "fractalAnimation/Task.h"
#include "fractalAnimation/FractalGenerator.h"
#include "fractalAnimation/FractalPoint.h"
// #include "PostProcess.h"

#include <wx/image.h>

class Frame : public Task
{
private:
    const uint32_t W, H;
    const std::unique_ptr<FractalParameters> param;
    const std::unique_ptr<const FractalGenerator::Points> &points_generator;
    const std::unique_ptr<const FractalGenerator::Pixels> &pixels_generator;
    // const std::vector<&PostProcess> &post_process_stack;

    wxImage color;

public:
    Frame(
        std::unique_ptr<FractalParameters> &&param,
        const std::unique_ptr<const FractalGenerator::Points> &points_generator,
        const std::unique_ptr<const FractalGenerator::Pixels> &pixels_generator,
        // const std::vector<&PostProcess> &post_process_stack;
        uint32_t W, uint32_t H);
    void process() override; // renders the frame
    wxImage get_img() const; // returns a wxwidgets wxImage (copy of color)
};
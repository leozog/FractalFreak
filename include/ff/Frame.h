#pragma once
#include "ff/Task.h"
#include "ff/FractalGenerator.h"
#include "ff/FractalPoint.h"
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

    std::shared_ptr<wxImage> color;

public:
    Frame(
        std::unique_ptr<FractalParameters> &&param,
        const std::unique_ptr<const FractalGenerator::Points> &points_generator,
        const std::unique_ptr<const FractalGenerator::Pixels> &pixels_generator,
        // const std::vector<&PostProcess> &post_process_stack;
        uint32_t W, uint32_t H);
    void process() override;                  // renders the frame
    std::shared_ptr<wxImage> get_img() const; // returns a wxwidgets wxImage (copy of color)
private:
    std::vector<float> generate_depth(uint32_t W, uint32_t H);
};
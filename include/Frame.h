#pragma once
#include "Task.h"

class Frame : public Task
{
private:
    const std::unique_ptr<FractalParameters> param;
    const FractalGenerator::Points &point;
    const FractalGenerator::Pixel &pixel;

    wxImage color;

public:
    Frame(const FractalGenerator &fractal, const std::unique_ptr<FractalParameters> param, uint32_t W, uint32_t H);
    void process() override;        // renders the frame
    const wxImage &get_img() const; // returns a wxwidgets wxImage
};
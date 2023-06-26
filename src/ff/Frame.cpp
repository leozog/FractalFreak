#include "ff/Frame.h"

Frame::Frame(
    std::unique_ptr<FractalParameters> &&param,
    const std::unique_ptr<const FractalGenerator::Points> &points_generator,
    const std::unique_ptr<const FractalGenerator::Pixels> &pixels_generator,
    // const std::vector<&PostProcess> &post_process_stack,
    uint32_t W, uint32_t H)
    : param{std::move(param)}, points_generator{points_generator}, pixels_generator{pixels_generator}, color{(int)W, (int)H}, W{W}, H{H}
{
}

void Frame::process()
{
    std::vector<std::unique_ptr<FractalPoint>> points = points_generator->calculate(param);
    wxImage depth(W, H);
    pixels_generator->render(points, color, depth, W, H);
    /*for (auto &pp : post_process_stack)
        pp(color, depth);*/
}

wxImage Frame::get_img() const
{
    return color;
}
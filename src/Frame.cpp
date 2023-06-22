#include "Frame.h"

Frame::Frame(const FractalGenerator &fractal, const std::unique_ptr<FractalParameters> param, uint32_t W, uint32_t H) : fractal{fractal}, param{param}, img{W, H}
{
}

void Frame::process() override
{
    point.calculate(param, img);
    pixel.render(point, img, )
}

const wxImage &Frame::get_img() const
{
    return color;
}
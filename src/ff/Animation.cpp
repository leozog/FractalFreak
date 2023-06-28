#include "ff/Animation.h"

Animation::Animation(
    std::unique_ptr<AnimationPath> &&path,
    std::unique_ptr<FractalGenerator::Points> &&points_generator,
    std::unique_ptr<FractalGenerator::Pixels> &&pixels_generator /*,
    const std::vector<std::unique_ptr<PostProcess>> post_process_stack*/
    )
    : path{std::move(path)}, points_generator{std::move(points_generator)}, pixels_generator{std::move(pixels_generator)} //, post_process_stack{post_process_stack}
{
    path->compile(); // Performs additional calculations after the whole path is assembled
}

void Animation::render(double fps, int32_t n_threads, uint32_t W, uint32_t H)
{
    frames.clear();
    uint32_t n_frames = path->time() * fps;
    for (uint32_t i = 0; i < n_frames; i++) // creation of every frame, alacation of memory, setting of parameters for this point in time
        frames.add(std::make_unique<Frame>(
            path->get_param(static_cast<double>(i) / fps),
            points_generator,
            pixels_generator,
            // post_process_stack,
            W, H));

    frames.process(n_threads); // the actuall calculation of frames (async)
}

std::shared_ptr<wxImage> Animation::get_frame_latest() const
{
    for (int i = frames.size() - 1; i >= 0; i--)
    {
        if (frames[i].is_ready())
            return dynamic_cast<const Frame &>(frames[i]).get_img();
    }
    return std::make_shared<wxImage>(0, 0); // placeholder
}

std::shared_ptr<wxImage> Animation::get_frame_x(uint32_t x) const
{
    if (frames[x].is_ready())
        return dynamic_cast<const Frame &>(frames[x]).get_img();
    return std::make_shared<wxImage>(0, 0);
}

uint32_t Animation::n_frames() const
{
    return frames.size();
}

uint32_t Animation::n_frames_ready() const
{
    uint32_t n_ready = 0;
    for (uint32_t i = 0; i < frames.size(); i++)
    {
        if (frames[i].is_ready())
            n_ready++;
    }
    return n_ready;
}
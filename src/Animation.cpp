#include "Animation.h"

Animation::Animation(
    AnimationPath path,
    const std::shared_ptr<FractalGenerator::Points> points_generator,
    const std::shared_ptr<FractalGenerator::Pixels> pixels_generator,
    //const std::vector<std::shared_ptr<PostProcess>> post_process_stack)
    : path{path}, points_generator{points_generator}, pixels_generator{pixels_generator}//, post_process_stack{post_process_stack}
{
    path.compile(); // Performs additional calculations after the whole path is assembled
}

void Animation::render(double fps, uint32_t n_threads)
{
    frames.clear();
    uint32_t n_frames = path.time() * fps;
    for (uint32_t i = 0; i < n_frames; i++) // creation of every frame, alacation of memory, setting of parameters for this point in time
        frames.add(Frame(
            path.get_param(static_cast<double>(i) / fps),
            *points_generator,
            *pixels_generator,
            //*post_process_stack,
            W, H));

    frames.process(n_threads); // the actuall calculation of frames (async)
}

wxImage Animation::get_frame_latest() const;
{
    for (int i = frames.size() - 1; i >= 0; i--)
    {
        if (frames[i].is_ready())
            return frames[i].get_img();
    }
    return wxImage(16, 16);
}

wxImage Animation::get_frame_x(uint32_t x) const
{
    if (frames[x].is_ready())
        return frames[x].get_img();
    return wxImage(16, 16);
}
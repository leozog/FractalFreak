#include "Animation.h"

Animation::Animation(double fps, uint32_t n_threads, AnimationPath path) : fps{fps}, n_frames{path.time() * fps}, n_threads{n_threads}
{
    path.compile();
}

void Animation::render()
{
    frames.clear();
    for (int i = 0; i < n_frames; i++) // creation of every frame, alacation of memory, setting of parameters for this point in time
        frames.add(Frame(fractal, path.get_param(static_cast<double>(i) / fps), W, H));

    frames.process(n_threads);
}

wxImage *Animation::get_frame_latest() const;
{
    for (int i = frames.size() - 1; i >= 0; i--)
    {
        if (frames[i].is_ready())
            return frames[i].get_img();
    }
    return nullptr;
}

wxImage *Animation::get_frame_x(uint32_t x) const
{
    if (frames[x].is_ready())
        return frames[x].get_img();
    return nullptr;
}
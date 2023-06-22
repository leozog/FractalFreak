#pragma once
#include "Task.h"
#include "Frame.h"
#include "Path.h"

class Animation
{
public:
    const double fps;         // frames per second
    const uint32_t n_frames;  // frames per second
    const uint32_t n_threads; // number of threads used to render the animation
private:
    Tast_list frames;                // frames of the animation
    const FractalGenerator &fractal; // class used to generate the frames
    AnimationPath &path;             // path of animation describing the state of paramethers in every frame

public:
    Animation(double fps, uint32_t n_threads, Path path);
    void render();

    wxImage *get_frame_latest() const; // returns latest ready frame
    wxImage *get_frame_x() const;      // returns frame number x
private:
};
#pragma once
#include "ff/Task.h"
#include "ff/Frame.h"
#include "ff/AnimationPath.h"
#include "ff/FractalGenerator.h"

#include <wx/image.h>

class Animation
{
private:
    const std::unique_ptr<AnimationPath> path;                              // path of animation describing the state of parameters in every frame
    const std::unique_ptr<const FractalGenerator::Points> points_generator; // class used to generate the points of the fractal
    const std::unique_ptr<const FractalGenerator::Pixels> pixels_generator; // class used to generate the color and depth img from points
    // const std::vector<std::shared_ptr<PostProcess>> post_process_stack; // post processing effects applied to img

    Task_list frames; // frames of the animation (its important for it to be declared last because of multithreading. basically it needs to be destroyed first)

public:
    Animation() {}
    Animation(
        std::unique_ptr<AnimationPath> &&path,
        std::unique_ptr<FractalGenerator::Points> &&points_generator,
        std::unique_ptr<FractalGenerator::Pixels> &&pixels_generator /*,
        const std::vector<std::unique_ptr<PostProcess>> post_process_stack*/
    );
    void render(double fps, int32_t n_threads, uint32_t W, uint32_t H);

    std::shared_ptr<wxImage> get_frame_latest() const;      // returns latest ready frame img
    std::shared_ptr<wxImage> get_frame_x(uint32_t x) const; // returns frame img number x

    uint32_t n_frames() const;
    uint32_t n_frames_ready() const;
};
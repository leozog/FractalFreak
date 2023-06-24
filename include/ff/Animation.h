#pragma once
#include "Task.h"
#include "Frame.h"
#include "AnimationPath.h"
#include "FractalGenerator.h"

class Animation
{
private:
    AnimationPath path;                                               // path of animation describing the state of parameters in every frame
    const std::shared_ptr<FractalGenerator::Points> points_generator; // class used to generate the points of the fractal
    const std::shared_ptr<FractalGenerator::Pixels> pixels_generator; // class used to generate the color and depth img from points
    // const std::vector<std::shared_ptr<PostProcess>> post_process_stack; // post processing effects applied to img

    Task_list frames; // frames of the animation (its important for it to be declared last because of multithreading. basically it needs to be destroyed first)

public:
    Animation() {}
    Animation(
        AnimationPath path,
        const std::shared_ptr<FractalGenerator::Points> points_generator,
        const std::shared_ptr<FractalGenerator::Pixels> pixels_generator /*,
         const std::vector<std::shared_ptr<PostProcess>> post_process_stack*/
    );
    void render(double fps, uint32_t n_threads);

    wxImage get_frame_latest() const; // returns latest ready frame img
    wxImage get_frame_x() const;      // returns frame img number x
private:
};
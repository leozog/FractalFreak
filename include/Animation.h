#pragma once
#include "Task.h"
#include "Frame.h"
#include "AnimationPath.h"
#include "FractalGenerator.h"

class Animation
{
private:
    Task_list frames;                                                 // frames of the animation
    AnimationPath path;                                               // path of animation describing the state of parameters in every frame
    const std::shared_ptr<FractalGenerator::Points> points_generator; // class used to generate the points of the fractal
    const std::shared_ptr<FractalGenerator::Pixels> pixels_generator; // class used to generate the color and depth img from points
    // const std::vector<std::shared_ptr<PostProcess>> post_process_stack; // post processing effects applied to img

public:
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
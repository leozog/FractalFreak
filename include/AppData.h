#pragma once
#include "ff/Animation.h"
#include "ff/FractalParameters.h"
#include "ff/FractalGenerator.h"
#include "FractalsDefinitions.h"

class AppData
{
public:
    Animation animation;
    AppData()
    {
        AnimationPath path;
        path.add(
            {std::make_shared<Transform_2D>(0.5, 0., 0., 0.5, 0., 0.),
             std::make_shared<Transform_2D>(0.5, 0., 0., 0.5, 0.5, 0.),
             std::make_shared<Transform_2D>(0.5, 0., 0., 0.5, 0., 0.5)},
            0.0);
        path.add(
            {std::make_shared<Transform_2D>(0.5, 0.0, 0.0, 0.8, 0.0, 50),
             std::make_shared<Transform_2D>(0.5, 0.2, -0.2, 0.5, -100, -100),
             std::make_shared<Transform_2D>(0.5, -0.2, 0.2, 0.5, 100, -100)},
            1.0);
        animation = animation(
            path,                                                                      // AnimationPath
            std::make_unique<simple_fractal::points_generator>(/*iterations*/ 100000), // Inheritance of FractalGenerator::Points
            std::make_unique<simple_fractal::pixels_generator>()                       // Inheritance of FractalGenerator::Pixels
            // TODO: post_process_stack
        );
    }
};
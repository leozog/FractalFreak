#pragma once
#include "ff/Animation.h"
#include "ff/FractalParameters.h"
#include "ff/FractalGenerator.h"
#include "FractalsDefinitions.h"

class AppData
{
public:
    std::unique_ptr<Animation> animation;
    AppData()
    {
        // inicjalizajca sciezki animacji
        std::unique_ptr<AnimationPath> path = std::make_unique<AnimationPath>();

        // dodawanie stage'y
        path->add(
            std::make_unique<simple_fractal::Parameters>(simple_fractal::Parameters({Transform_2D(0.5, 0., 0., 0.5, 0., 0.),
                                                                                     Transform_2D(0.5, 0., 0., 0.5, 0.5, 0.),
                                                                                     Transform_2D(0.5, 0., 0., 0.5, 0., 0.5)})),
            0.0); // czas w sekundach od poprzedniego stage'a
        path->add(
            std::make_unique<simple_fractal::Parameters>(simple_fractal::Parameters({Transform_2D(0.5, 0.0, 0.0, 0.8, 0.0, 50),
                                                                                     Transform_2D(0.5, 0.2, -0.2, 0.5, -100, -100),
                                                                                     Transform_2D(0.5, -0.2, 0.2, 0.5, 100, -100)})),
            2.0);

        // inicjalizacja funkcji renderujacych
        std::unique_ptr<FractalGenerator::Points> points = std::make_unique<simple_fractal::points_generator>(1000000); // w tym wypadku argumentem jest ilosc iteracji
        std::unique_ptr<FractalGenerator::Pixels> pixels = std::make_unique<simple_fractal::pixels_generator>();

        // inicjalizacja animacji
        animation = std::make_unique<Animation>(
            std::move(path),   // AnimationPath
            std::move(points), // Inheritance of FractalGenerator::Points
            std::move(pixels)  // Inheritance of FractalGenerator::Pixels
            // TODO: post_process_stack
        );
    }
};
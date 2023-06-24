#pragma once
#include "ff/FractalParameters.h"
#include "ff/FractalGenerator.h"
#include "ff/FractalPoint.h"
#include "ff/Random.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <wx/dcbuffer.h>
#include <vector>
#include <memory>

// TODO(?): Move to another file "AffineTransformation.h" and include the file both hire and in FractalsDefinitions.h
struct AffineTransformation
{
    AffineTransformation(float probability = 0.) : probability(probability) {}

    // returns a copy of itself in a new shared_ptr of a derived type
    virtual std::shared_ptr<AffineTransformation> copy() = 0;

    // probability of this transformation being chosen to move the drawing pixel in an interation
    float probability;
};

// 2D affine transformation
struct Transform_2D : public AffineTransformation
{
    Transform_2D(float a = 0, float b = 0, float c = 0, float d = 0, float dx = 0, float dy = 0) : matrix({a, b}, {c, d}), vector(dx, dy) {}

    std::shared_ptr<AffineTransformation> copy() { return std::make_shared<Transform_2D>(*this); }

    glm::mat2 matrix; // transformation matrix: {{A, B}, {C, D}}
    glm::vec2 vector; // translation vector: {dx, dy} or {E, F}
};

// name is wip. TODO: give appropriate name
namespace simple_fractal // made by Ola!
{

    struct Parameters : public FractalParameters
    {
        std::vector<std::shared_ptr<AffineTransformation>> transformations;
        Parameters(std::initializer_list<Transform_2D> ilist) transformations{ilist}
        {
        }
        void add(const FractalParameters &b) override
        {
            for (int i = 0; i < transformations.size(); i++)
            {
                std::dynamic_pointer_cast<Transform_2D>(transformations[i])->matrix[0][0] += std::dynamic_pointer_cast<Transform_2D>(b.transformations[i])->matrix[0][0];
                std::dynamic_pointer_cast<Transform_2D>(transformations[i])->matrix[0][1] += std::dynamic_pointer_cast<Transform_2D>(b.transformations[i])->matrix[0][1];
                std::dynamic_pointer_cast<Transform_2D>(transformations[i])->matrix[1][0] += std::dynamic_pointer_cast<Transform_2D>(b.transformations[i])->matrix[1][0];
                std::dynamic_pointer_cast<Transform_2D>(transformations[i])->matrix[1][1] += std::dynamic_pointer_cast<Transform_2D>(b.transformations[i])->matrix[1][1];
                std::dynamic_pointer_cast<Transform_2D>(transformations[i])->vector[0] += std::dynamic_pointer_cast<Transform_2D>(b.transformations[i])->vector[0];
                std::dynamic_pointer_cast<Transform_2D>(transformations[i])->vector[1] += std::dynamic_pointer_cast<Transform_2D>(b.transformations[i])->vector[1];
            }
        }
        void mul(const double b) override
        {
            for (int i = 0; i < transformations.size(); i++)
            {
                std::dynamic_pointer_cast<Transform_2D>(transformations[i])->matrix[0][0] *= b;
                std::dynamic_pointer_cast<Transform_2D>(transformations[i])->matrix[0][1] *= b;
                std::dynamic_pointer_cast<Transform_2D>(transformations[i])->matrix[1][0] *= b;
                std::dynamic_pointer_cast<Transform_2D>(transformations[i])->matrix[1][1] *= b;
                std::dynamic_pointer_cast<Transform_2D>(transformations[i])->vector[0] *= b;
                std::dynamic_pointer_cast<Transform_2D>(transformations[i])->vector[1] *= b;
            }
        }
    };

    struct Point : public FractalPoint
    {
        uint32_t leaf;
        Point(double x, double y, double z, uint32_t leaf) FractalPoint{x, y, z}, leaf{leaf} {}
    }

    class points_generator : public FractalGenerator::Points
    {
        uint32_t iterations_amount;

    public:
        points_generator(uint32_t iterations_amount) : iterations_amount{iterations_amount} {}

        std::vector<std::unique_ptr<FractalPoint>> calculate(const std::unique_ptr<FractalParameters> &param) const override
        {
            // dynamic cast (for speed and legibility)
            std::vector<std::shared_ptr<Transform_2D>> transformations;
            for (auto transformation : std::dynamic_pointer_cast<simple_fractal::Parameters>(param).transformations)
                transformations.push_back(std::dynamic_pointer_cast<Transform_2D>(transformation));

            // calculate probabilities and sum them { transformations[0]->probability, transformations[0]->probability + transformations[1]->probability, ... }
            std::vector<float> prob_sum = calcProbabilities(transformations);

            // calculate points
            float x_pixel, y_pixel, random_val, x = 0., y = 0., x_old = 0., y_old = 0.;

            /* randomize a value and pick a transformation to apply based on it (with accordance to the probabilities calculated earlier)
             * then position and draw the pixel with a color based on the chosen transformation
             */
            std::vector<std::unique_ptr<FractalPoint>> points;
            for (int i = 0; i < iterations_amount; i++)
            {
                random_val = static_cast<float>(std::rand()) / RAND_MAX; // random value from 0. to 1.
                x_old = x;
                y_old = y;

                for (int j = 0; j < prob_sum.size(); j++)
                {
                    if (random_val < prob_sum[j])
                    {
                        x = transformations[j]->matrix[0][0] * x_old + transformations[j]->matrix[0][1] * y_old + transformations[j]->vector[0];
                        y = transformations[j]->matrix[1][0] * x_old + transformations[j]->matrix[1][1] * y_old + transformations[j]->vector[1];
                        points.push_back(std::make_unique<simple_fractal::Point>(x, y, 0, j));
                    }
                }
            }
            return points;
        }

    private:
        std::vector<float> calcProbabilities(const std::vector<std::shared_ptr<Transform_2D>> &transformations) const
        {
            // sum determinants of all matrices
            float det_sum = 0.;
            for (auto transformation : transformations)
                det_sum += std::abs(glm::determinant(transformation->matrix));

            // calculate probabilities for each transformation: prob_i = det_i / det_sum
            for (auto transformation : transformations)
                transformation->probability = std::abs(glm::determinant(transformation->matrix)) / det_sum;

            // calculate and return sums of probabilities { prob_0, prob_0 + prob_1, ... }
            std::vector<float> prob_sum(5);

            prob_sum[0] = (transformations_amount > 0) ? transformations[0]->probability : 0.;
            for (int i = 1; i < 5; i++)
                prob_sum[i] = (transformations_amount > i) ? prob_sum[i - 1] + transformations[i]->probability : 0.;

            return prob_sum;
        }
    };
    class pixels_generator : public FractalGenerator::Pixels
    {
    public:
        void render(const std::vector<std::unique_ptr<FractalPoint>> &points, wxImage &color, wxImage &depth, uint32_t W, uint32_t H) const override
        {
            double x_min = points[0]->x;
            double x_max = points[0]->x;
            double y_min = points[0]->y;
            double y_max = points[0]->y;
            for (const auto &fpoint : points)
            {
                if (x < x_min)
                    x_min = x;
                if (x > x_max)
                    x_max = x;
                if (y < y_min)
                    y_min = y;
                if (y > y_max)
                    y_max = y;
            }

            for (const auto &fpoint : points)
            {
                const simple_fractal::Point point = *fpoint;

                // set color
                uint8_t red = 0, green = 0, blue = 0;
                if (point.leaf == 0) // red pixel
                {
                    red = 255;
                    green = 0;
                    blue = 0;
                }
                else if (point.leaf == 1) // green pixel
                {
                    red = 0;
                    green = 255;
                    blue = 0;
                }
                else if (point.leaf == 2) // blue pixel
                {
                    red = 0;
                    green = 0;
                    blue = 255;
                }
                else if (point.leaf == 3) // purple pixel
                {
                    red = 255;
                    green = 0;
                    blue = 255;
                }
                else if (point.leaf == 4) // yellow pixel
                {
                    red = 255;
                    green = 255;
                    blue = 0;
                }

                // if the pixel is inside the bitmap, draw it
                if (0 <= point.x && point.x < W && 0 <= point.y && point.y < H)
                {
                    double screenX = (point.x - x_min) / (x_max - x_min) * W;
                    double screenY = (point.y - y_min) / (y_max - y_min) * H;
                    color.SetRGB(screenX, screenY, red, green, blue);
                }
            }
        }
    };
}
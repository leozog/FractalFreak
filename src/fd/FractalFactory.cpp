#include "fd/FractalFactory.h"

namespace fractal_factory
{
    std::unique_ptr<FractalParameters> Parameters::copy() const 
    {
        return std::make_unique<Parameters>(*this);
    }

    void Parameters::add(FractalParameters& a)
    {
        Parameters& A = dynamic_cast<Parameters&>(a);

        while (A.transformations.size() > transformations.size())
            transformations.push_back(AffineTransformation_2D(0, 0, 0, 0, 0, 0));

        while (A.transformations.size() < transformations.size())
            A.transformations.push_back(AffineTransformation_2D(0, 0, 0, 0, 0, 0));

        for (int i = 0; i < transformations.size(); i++)
        {
            // dynamic_cast<Transform_2D &>(*transformations[i]).matrix[0][0] += dynamic_cast<Transform_2D &>(*(B.transformations[i])).matrix[0][0];
            transformations[i].matrix += A.transformations[i].matrix;
            transformations[i].vector += A.transformations[i].vector;
        }
    }

    void Parameters::mul(const double b)
    {
        for (int i = 0; i < transformations.size(); i++)
        {
            transformations[i].matrix *= b;
            transformations[i].vector *= b;
        }
    }

    std::vector<std::unique_ptr<FractalPoint>> PointsGenerator::calculate(const std::unique_ptr<FractalParameters>& param) const
    {
        // dynamic_cast for speed and legibility //TODO(!): ochrona przed zlym castem. zeby wywalalo exception
        std::vector<AffineTransformation_2D>& transformations = dynamic_cast<Parameters*>(param.get())->getTransformations();

        std::vector<float> prob_sum = calcProbabilities(transformations);


        glm::vec2 p(0., 0.);
        std::vector<std::unique_ptr<FractalPoint>> generated_points;
        generated_points.reserve(points_per_frame);

        // randomly pick transformations to apply to p (based on probability)
        // save all points created this way to a vector
        for (int i = 0; i < points_per_frame; i++)
        {
            double random_val = Random::rand_d(0., 1.);

            for (int j = 0; j < prob_sum.size(); j++)
            {
                if (random_val <= prob_sum[j])
                {
                    p = transformations[j].matrix * p + transformations[j].vector;
                    generated_points.push_back(std::make_unique<Point>(p.x, p.y, 0, j));
                    break;
                }
            }
        }

        return generated_points;
    }

    std::vector<float> PointsGenerator::calcProbabilities(std::vector<AffineTransformation_2D>& transformations) const
    {
        // sum determinants of all matrices
        float det_sum = 0.;
        for (auto& transformation : transformations)
            det_sum += std::abs(glm::determinant(transformation.matrix));

        // calculate probabilities for each transformation: prob_i = det_i / det_sum
        for (auto& transformation : transformations)
            transformation.pick_probability = std::abs(glm::determinant(transformation.matrix)) / det_sum;

        // calculate sums { prob_0, prob_0 + prob_1, ... }
        std::vector<float> prob_sum(transformations.size());

        prob_sum[0] = (transformations.size() > 0) ? transformations[0].pick_probability : 0.;
        for (int i = 1; i < prob_sum.size(); i++)
            prob_sum[i] = (transformations.size() > i) ? prob_sum[i - 1] + transformations[i].pick_probability : 0.;

        return prob_sum;
    }

	void PixelsGenerator::render(const std::vector<std::unique_ptr<FractalPoint>>& points, wxImage& bitmap, wxImage& depth, uint32_t bitmapWidth, uint32_t bitmapHeight) const
    {
        // find max and min values of x and y
        double x_min = points[0]->x;
        double x_max = points[0]->x;
        double y_min = points[0]->y;
        double y_max = points[0]->y;

        for (const auto& fpoint : points)
        {
            if (x_min > fpoint->x)
                x_min = fpoint->x;
            if (x_max < fpoint->x)
                x_max = fpoint->x;
            if (y_min > fpoint->y)
                y_min = fpoint->y;
            if (y_max < fpoint->y)
                y_max = fpoint->y;
        }

        // draw pixels on bitmap
        for (auto& fpoint : points)
        {
            fractal_factory::Point* point = dynamic_cast<Point*>(fpoint.get());

            // set point color
            uint8_t red = 0, green = 0, blue = 0;

            if (point->transformation_id == 0) // red 
            {
                red = 255;
                green = 0;
                blue = 0;
            }
            else if (point->transformation_id == 1) // green 
            {
                red = 0;
                green = 255;
                blue = 0;
            }
            else if (point->transformation_id == 2) // blue 
            {
                red = 0;
                green = 0;
                blue = 255;
            }
            else if (point->transformation_id == 3) // purple 
            {
                red = 255;
                green = 0;
                blue = 255;
            }
            else if (point->transformation_id == 4) // yellow 
            {
                red = 255;
                green = 255;
                blue = 0;
            }

            // calc coordinates
            int bitmapX = (point->x - x_min) / (x_max - x_min) * bitmapWidth;
            int bitmapY = bitmapHeight - (point->y - y_min) / (y_max - y_min) * bitmapHeight;

            // if the pixel is inside the bitmap, draw it
            if (0 <= bitmapX && bitmapX < bitmapWidth && 0 <= bitmapY && bitmapY < bitmapHeight)
                bitmap.SetRGB(bitmapX, bitmapY, red, green, blue);
        }
    }
}
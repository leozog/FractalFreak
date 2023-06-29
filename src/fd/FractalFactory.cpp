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
        // dynamic_cast for speed and legibility
        try
        {
            std::vector<AffineTransformation_2D>& transformations = dynamic_cast<Parameters*>(param.get())->getTransformations();
        }
        catch (const std::bad_cast& e)
        {
            std::cout << "in PointsGenerator::calculate:\n" << e.what() << std::endl;
        }

        std::vector<AffineTransformation_2D>& transformations = dynamic_cast<Parameters*>(param.get())->getTransformations();

        std::vector<float> prob_sum = calcProbabilities(transformations);


        glm::vec2 p(0., 0.);
        std::vector<std::unique_ptr<FractalPoint>> generated_points;
        generated_points.reserve(points_per_frame);

        // loop 100 times first to avoid stutter
        for (int i = 0; i < 100; i++)
        {
            double random_val = Random::rand_d(0., 1.); // random value from 0. to 1.
            for (int j = 0; j < prob_sum.size(); j++)
            {
                if (random_val <= prob_sum[j])
                {
                    p = transformations[j].matrix * p + transformations[j].vector;
                    break;
                }
            }
        }

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
        if (transformations.empty())
            return std::vector<float>(0);

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

    void PixelsGenerator::hslToRgb(uint8_t& red, uint8_t& green, uint8_t& blue, float h, float s, float l) const
    {
        while (h > 1.)
        {
            h -= 1.;
            l -= 0.2;
        }

        if (s == 0.)
        {
            red = green = blue = l * 255.;
            return;
        }

        float var2 = (l < 0.5) ? var2 = l * (1 + s) : var2 = (l + s) - (s * l);
        float var1 = 2 * l - var2;

        

        red = 255. * hueToRgb(var1, var2, h + 0.3333333f);
        green = 255. * hueToRgb(var1, var2, h);
        blue = 255. * hueToRgb(var1, var2, h - 0.3333333f);
    }

    float PixelsGenerator::hueToRgb(float var1, float var2, float hue) const
    {
        if (hue < 0) hue += 1;
        if (hue > 1) hue -= 1;
        if (6 * hue < 1) return var1 + (var2 - var1) * 6 * hue;
        if (2 * hue < 1) return var2;
        if (3 * hue < 2) return var1 + (var2 - var1) * (0.6666666f - hue) * 6;
        return var1;
    }

	void PixelsGenerator::render(const std::vector<std::unique_ptr<FractalPoint>>& points, wxImage& bitmap, wxImage& depth, uint32_t bitmapWidth, uint32_t bitmapHeight) const
    {
        if (points.empty() || !bitmap.IsOk())
            return;

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

        std::vector<Color> pixelColors;

        // draw pixels on bitmap
        for (auto& fpoint : points)
        {
            Point* point = dynamic_cast<Point*>(fpoint.get());

            // create new colors if there isn't enough
            while (point->transformation_id >= pixelColors.size())
            {
                uint8_t red, green, blue;
                hslToRgb(red, green, blue, 50. / 360. * pixelColors.size());

                pixelColors.emplace_back(red, green, blue);
            }

            // calc coordinates
            int bitmapX = (point->x - x_min) / (x_max - x_min) * bitmapWidth;
            int bitmapY = bitmapHeight - (point->y - y_min) / (y_max - y_min) * bitmapHeight;

            // if the pixel is inside the bitmap, draw it
            if (0 <= bitmapX && bitmapX < bitmapWidth && 0 <= bitmapY && bitmapY < bitmapHeight)
                bitmap.SetRGB(bitmapX, bitmapY, pixelColors[point->transformation_id].red, pixelColors[point->transformation_id].green, pixelColors[point->transformation_id].blue);
        }
    }
}
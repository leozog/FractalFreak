#include "fd/FractalFactory.h"

namespace fractal_factory
{
    std::unique_ptr<FractalParameters> Parameters2D::copy() const 
    {
        return std::make_unique<Parameters2D>(*this);
    }

    std::unique_ptr<FractalParameters> Parameters3D::copy() const
    {
        return std::make_unique<Parameters3D>(*this);
    }

    void Parameters2D::add(FractalParameters& a)
    {
        Parameters2D& A = dynamic_cast<Parameters2D&>(a);

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

    void Parameters2D::mul(const double b)
    {
        for (int i = 0; i < transformations.size(); i++)
        {
            transformations[i].matrix *= b;
            transformations[i].vector *= b;
        }
    }

    void Parameters3D::add(FractalParameters& a)
    {
        Parameters3D& A = dynamic_cast<Parameters3D&>(a);

        while (A.transformations.size() > transformations.size())
            transformations.push_back(AffineTransformation_3D());

        while (A.transformations.size() < transformations.size())
            A.transformations.push_back(AffineTransformation_3D());

        for (int i = 0; i < transformations.size(); i++)
        {
            // dynamic_cast<Transform_2D &>(*transformations[i]).matrix[0][0] += dynamic_cast<Transform_2D &>(*(B.transformations[i])).matrix[0][0];
            transformations[i].matrix += A.transformations[i].matrix;
            transformations[i].vector += A.transformations[i].vector;
        }
    }

    void Parameters3D::mul(const double b)
    {
        for (int i = 0; i < transformations.size(); i++)
        {
            transformations[i].matrix *= b;
            transformations[i].vector *= b;
        }
    }

    std::vector<std::unique_ptr<FractalPoint>> PointsGenerator2D::calculate(const std::unique_ptr<FractalParameters>& param) const
    {
        // dynamic_cast for speed and legibility
        try
        {
            std::vector<AffineTransformation_2D>& transformations = dynamic_cast<Parameters2D*>(param.get())->getTransformations();
        }
        catch (const std::bad_cast& e)
        {
            std::cout << "in PointsGenerator::calculate:\n" << e.what() << std::endl;
        }

        std::vector<AffineTransformation_2D>& transformations = dynamic_cast<Parameters2D*>(param.get())->getTransformations();

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

    std::vector<std::unique_ptr<FractalPoint>> PointsGenerator3D::calculate(const std::unique_ptr<FractalParameters>& param) const
    {
        // dynamic_cast for speed and legibility
        try
        {
            std::vector<AffineTransformation_3D>& transformations = dynamic_cast<Parameters3D*>(param.get())->getTransformations();
        }
        catch (const std::bad_cast& e)
        {
            std::cout << "in PointsGenerator::calculate:\n" << e.what() << std::endl;
        }

        std::vector<AffineTransformation_3D>& transformations = dynamic_cast<Parameters3D*>(param.get())->getTransformations();

        // std::vector<float> prob_sum = calcProbabilities(transformations);


        glm::vec3 p(1., 1., 1.);
        std::vector<std::unique_ptr<FractalPoint>> generated_points;
        generated_points.reserve(points_per_frame);

        // loop 100 times first to avoid stutter
        for (int i = 0; i < 1000; i++)
        {
            int random_val = Random::rand_i(0, transformations.size() - 1);
            p = transformations[random_val].matrix * p + transformations[random_val].vector;

        }

        // randomly pick transformations to apply to p (based on probability)
        // save all points created this way to a vector
        for (int i = 0; i < points_per_frame; i++)
        {
            int random_val = Random::rand_i(0, transformations.size() - 1);
            p = transformations[random_val].matrix * p + transformations[random_val].vector;
            generated_points.push_back(std::make_unique<Point>(p.x, p.y, p.z, random_val));
        }

        return generated_points;
    }


    std::vector<float> PointsGenerator2D::calcProbabilities(std::vector<AffineTransformation_2D>& transformations) const
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

    std::vector<float> PointsGenerator3D::calcProbabilities(std::vector<AffineTransformation_3D>& transformations) const
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

    void hslToRgb(uint8_t& red, uint8_t& green, uint8_t& blue, float h, float s, float l)
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

    float hueToRgb(float var1, float var2, float hue)
    {
        if (hue < 0) hue += 1;
        if (hue > 1) hue -= 1;
        if (6 * hue < 1) return var1 + (var2 - var1) * 6 * hue;
        if (2 * hue < 1) return var2;
        if (3 * hue < 2) return var1 + (var2 - var1) * (0.6666666f - hue) * 6;
        return var1;
    }

	void PixelsGenerator2D::render(const std::vector<std::unique_ptr<FractalPoint>>& points, wxImage& bitmap, wxImage& depth, uint32_t bitmapWidth, uint32_t bitmapHeight) const
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

    void PixelsGenerator3D::render(const std::vector<std::unique_ptr<FractalPoint>>& points, wxImage& bitmap, wxImage& depth, uint32_t bitmapWidth, uint32_t bitmapHeight) const
    {
        if (points.empty() || !bitmap.IsOk())
            return;

        // find max and min values of x and y
        

        std::vector<Color> pixelColors;

        // Make the matrix for casting

        double n, r, l, t, b, f;


        t = 1;
        b = -1;

        l = -1;
        r = 1;

        f = 3;
        n = 1;

        // na cele tego projektu nie wiemy o istnieniu glm::perspective!

        glm::mat4 ortho_cast(n/4, 0, 0, 0, 0, n/b, 0, 0, 0, 0, f/(f-n), 1, 0, 0, -f * n / (f - n), 0);
        glm::mat4 scale(2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2);

        ortho_cast = ortho_cast * scale; //* inversion * rotation

        std::vector<glm::vec4> drawablePoints;
        drawablePoints.reserve(points.size());
     
        // First we need to perform math on the points
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

            // We need to cast the stuff!
            // First make a civilised 4 vector
            glm::vec4 glm_point(point->x - _x, point->y - _y, point->z - _z, 1);

            // https://static.wikia.nocookie.net/afbe0a28-af5a-4073-9579-1b56c0a33e22

            // Then we apply math wizardry (often confused with Algebra)

            glm_point = ortho_cast * glm_point;

            drawablePoints.push_back(glm_point);
            
        }

        double z_max = drawablePoints[0].z;

        double x_min = drawablePoints[0].x;
        double x_max = drawablePoints[0].x;
        double y_min = drawablePoints[0].y;
        double y_max = drawablePoints[0].y;

        for (int i = 0; i < points.size(); i++)
        {
            if (drawablePoints[i].z > z_max)
            {
                z_max = drawablePoints[i].z;
            }

            if (x_min > drawablePoints[i].x)
                x_min = drawablePoints[i].x;
            if (x_max < drawablePoints[i].x)
                x_max = drawablePoints[i].x;
            if (y_min > drawablePoints[i].y)
                y_min = drawablePoints[i].y;
            if (y_max < drawablePoints[i].y)
                y_max = drawablePoints[i].y;

            drawablePoints[i].w = dynamic_cast<const Point&>(*points[i]).transformation_id;
        }
        
        std::sort(drawablePoints.begin(), drawablePoints.end(), [](const glm::vec4& a, const glm::vec4& b) -> bool {return a.z > b.z; });


        // Z sorting goes here

        for (auto& point : drawablePoints)
        {
            if (point.z <= 0 || point.x > 1 || point.x < -1 || point.y > 1 || point.y < -1) continue; // nie rysujemy tego czego nie widaæ


            int bitmapX = (bitmapWidth / 2) + point.x * bitmapWidth / 2;
            int bitmapY = (bitmapHeight / 2) + point.y  * bitmapHeight / 2;

            float lightness = 1 - (point.z / z_max);

            // if the pixel is inside the bitmap, draw it
            if (0 <= bitmapX && bitmapX < bitmapWidth && 0 <= bitmapY && bitmapY < bitmapHeight)
                bitmap.SetRGB(bitmapX, bitmapY, lightness * pixelColors[point.w].red, lightness * pixelColors[point.w].green, lightness * pixelColors[point.w].blue);

        }

       
    }
}
#pragma once
#include "ff/FractalParameters.h"
#include "ff/FractalGenerator.h"
#include "ff/FractalPoint.h"
#include "ff/Random.h"

#include "fd/AffineTransformation.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <wx/image.h>
#include <vector>
#include <initializer_list>
#include <memory>

#include <typeinfo>
#include <typeindex>
#include <iostream>


namespace fractal_factory
{

// TODO: Add camera
class Parameters : public FractalParameters
{
	private:
        std::vector<AffineTransformation_2D> transformations;

	public:
	    Parameters(const std::initializer_list<AffineTransformation_2D> &transformations_ilist) : transformations{transformations_ilist} {}
	    Parameters(const std::vector<AffineTransformation_2D>& transformations_ilist) : transformations( transformations_ilist ) {}

		std::vector<AffineTransformation_2D>& getTransformations() { return transformations; }

		std::unique_ptr<FractalParameters> copy() const override;

		// add a's matrices and vectors to this object's
		void add(FractalParameters& a) override;

		// multiply all matrices and vectors by b
		void mul(const double b) override;
};

struct Point : public FractalPoint
{
    uint32_t transformation_id;

    Point(double x, double y, double z, uint32_t transformation_id) : FractalPoint{x, y, z}, transformation_id{ transformation_id } {}
};

class PointsGenerator : public FractalGenerator::Points
{
	private:
	    uint32_t points_per_frame;

	public:
	    PointsGenerator(uint32_t points_per_frame) : points_per_frame{ points_per_frame } {}

		// generate a set of points creating a fractal based on given parameters
        std::vector<std::unique_ptr<FractalPoint>> calculate(const std::unique_ptr<FractalParameters>& param) const override;

	private:
		// calculate probabilities for given transformations and return a vector of sums { prob_0, prob_0 + prob_1, ... }
		std::vector<float> calcProbabilities(std::vector<AffineTransformation_2D>& transformations) const;
};

class PixelsGenerator : public FractalGenerator::Pixels
{
	public:
		// draw points on bitmap
	    void render(const std::vector<std::unique_ptr<FractalPoint>>& points, wxImage& bitmap, wxImage& depth, uint32_t bitmapWidth, uint32_t bitmapHeight) const override;
};

}
#pragma once
#include "ff/FractalGenerator.h"

#include "fd/FractalFactory.h"
#include "fd/AffineTransformation.h"
#include "fd/Parameters.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <vector>
#include <memory>
#include <initializer_list>
#include <typeinfo>
#include <typeindex>
#include <iostream>

namespace fractal_factory
{
	class PointsGenerator2D : public FractalGenerator::Points
	{
	private:
		uint32_t points_per_frame;

	public:
		PointsGenerator2D(uint32_t points_per_frame) : points_per_frame{points_per_frame} {}

		// generate a set of points creating a fractal based on given parameters
		std::vector<std::unique_ptr<FractalPoint>> calculate(const std::unique_ptr<FractalParameters> &param) const override;

	private:
		// calculate probabilities for given transformations and return a vector of sums { prob_0, prob_0 + prob_1, ... }
		std::vector<float> calcProbabilities(std::vector<AffineTransformation_2D> &transformations) const;
	};

	class PointsGenerator3D : public FractalGenerator::Points
	{
	private:
		uint32_t points_per_frame;

	public:
		PointsGenerator3D(uint32_t points_per_frame) : points_per_frame{points_per_frame} {}

		// generate a set of points creating a fractal based on given parameters
		std::vector<std::unique_ptr<FractalPoint>> calculate(const std::unique_ptr<FractalParameters> &param) const override;

	private:
		// calculate probabilities for given transformations and return a vector of sums { prob_0, prob_0 + prob_1, ... }
		std::vector<float> calcProbabilities(std::vector<AffineTransformation_3D> &transformations) const;
	};
}
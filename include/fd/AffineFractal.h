#pragma once
#include "ff/FractalParameters.h"
#include "ff/FractalGenerator.h"
#include "ff/Random.h"
#include "fd/AffineTransformation.h"
#include "fd/PointScatter.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <initializer_list>
#include <vector>
#include <memory>

namespace AffineFractal
{
	class Parameters : public FractalParameters
	{
	private:
		std::vector<AffineTransformation_3D> transformations;
		glm::vec3 cam_pos;

	public:
		Parameters(glm::vec3 cam_pos, const std::initializer_list<AffineTransformation_3D> &transformations_ilist) : cam_pos{cam_pos}, transformations{transformations_ilist} {}
		Parameters(glm::vec3 cam_pos, const std::vector<AffineTransformation_3D> &transformations_ilist) : cam_pos{cam_pos}, transformations(transformations_ilist) {}

		std::vector<AffineTransformation_3D> &get_transformations() { return transformations; }

		glm::mat4 get_transformation_matrix(glm::vec3 target);

		// return copy of self
		std::unique_ptr<FractalParameters> copy() const override;

		// add a's matrices and vectors to this object's
		void add(FractalParameters &a) override;

		// multiply all matrices and vectors by b
		void mul(const double b) override;
	};

	class PointsGenerator : public FractalGenerator::Points
	{
	private:
		uint32_t points_per_frame;

	public:
		PointsGenerator(uint32_t points_per_frame) : points_per_frame{points_per_frame} {}

		// generate a set of points creating a fractal based on given parameters
		std::vector<std::unique_ptr<FractalPoint>> calculate(const std::unique_ptr<FractalParameters> &param) const override;

	private:
		// calculate probabilities for given transformations and return a vector of sums { prob_0, prob_0 + prob_1, ... }
		std::vector<float> calcProbabilities(std::vector<AffineTransformation_3D> &transformations) const;
	};
}
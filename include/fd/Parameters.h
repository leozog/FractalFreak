#pragma once
#include "ff/FractalParameters.h"
#include "fd/AffineTransformation.h"

#include <vector>

namespace fractal_factory
{
	class Parameters2D : public FractalParameters
	{
	private:
		std::vector<AffineTransformation_2D> transformations;

	public:
		Parameters2D(const std::initializer_list<AffineTransformation_2D> &transformations_ilist) : transformations{transformations_ilist} {}
		Parameters2D(const std::vector<AffineTransformation_2D> &transformations_ilist) : transformations(transformations_ilist) {}

		std::vector<AffineTransformation_2D> &getTransformations() { return transformations; }

		// return copy of self
		std::unique_ptr<FractalParameters> copy() const override;

		// add a's matrices and vectors to this object's
		void add(FractalParameters &a) override;

		// multiply all matrices and vectors by b
		void mul(const double b) override;
	};

	class Parameters3D : public FractalParameters
	{
	private:
		std::vector<AffineTransformation_3D> transformations;

	public:
		Parameters3D(const std::initializer_list<AffineTransformation_3D> &transformations_ilist) : transformations{transformations_ilist} {}
		Parameters3D(const std::vector<AffineTransformation_3D> &transformations_ilist) : transformations(transformations_ilist) {}

		std::vector<AffineTransformation_3D> &getTransformations() { return transformations; }

		// return copy of self
		std::unique_ptr<FractalParameters> copy() const override;

		// add a's matrices and vectors to this object's
		void add(FractalParameters &a) override;

		// multiply all matrices and vectors by b
		void mul(const double b) override;
	};
}
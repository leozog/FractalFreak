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
class Parameters2D : public FractalParameters
{
	private:
        std::vector<AffineTransformation_2D> transformations;

	public:
	    Parameters2D(const std::initializer_list<AffineTransformation_2D> &transformations_ilist) : transformations{transformations_ilist} {}
	    Parameters2D(const std::vector<AffineTransformation_2D>& transformations_ilist) : transformations( transformations_ilist ) {}

		std::vector<AffineTransformation_2D>& getTransformations() { return transformations; }

		std::unique_ptr<FractalParameters> copy() const override;

		// add a's matrices and vectors to this object's
		void add(FractalParameters& a) override;

		// multiply all matrices and vectors by b
		void mul(const double b) override;
};

class Parameters3D : public FractalParameters
{
private:
	std::vector<AffineTransformation_3D> transformations;

public:
	Parameters3D(const std::initializer_list<AffineTransformation_3D>& transformations_ilist) : transformations{ transformations_ilist } {}
	Parameters3D(const std::vector<AffineTransformation_3D>& transformations_ilist) : transformations(transformations_ilist) {}

	std::vector<AffineTransformation_3D>& getTransformations() { return transformations; }

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

class PointsGenerator2D : public FractalGenerator::Points
{
	private:
	    uint32_t points_per_frame;

	public:
	    PointsGenerator2D(uint32_t points_per_frame) : points_per_frame{ points_per_frame } {}

		// generate a set of points creating a fractal based on given parameters
        std::vector<std::unique_ptr<FractalPoint>> calculate(const std::unique_ptr<FractalParameters>& param) const override;

	private:
		// calculate probabilities for given transformations and return a vector of sums { prob_0, prob_0 + prob_1, ... }
		std::vector<float> calcProbabilities(std::vector<AffineTransformation_2D>& transformations) const;
};

class PointsGenerator3D : public FractalGenerator::Points
{
	private:
		uint32_t points_per_frame;

	public:
		PointsGenerator3D(uint32_t points_per_frame) : points_per_frame{ points_per_frame } {}

		// generate a set of points creating a fractal based on given parameters
		std::vector<std::unique_ptr<FractalPoint>> calculate(const std::unique_ptr<FractalParameters>& param) const override;

	private:
		// calculate probabilities for given transformations and return a vector of sums { prob_0, prob_0 + prob_1, ... }
		std::vector<float> calcProbabilities(std::vector<AffineTransformation_3D>& transformations) const;
};

// Why would you put this in a class?
void hslToRgb(uint8_t& red, uint8_t& green, uint8_t& blue, float h, float s = 1., float l = 0.5);
float hueToRgb(float var1, float var2, float hue);

class PixelsGenerator2D : public FractalGenerator::Pixels
{
	private:
		struct Color
		{
			uint8_t red, green, blue;
			Color(uint8_t red, uint8_t green, uint8_t blue): red(red), green(green), blue(blue) {}
		};

	public:
		// draw points on bitmap
	    void render(const std::vector<std::unique_ptr<FractalPoint>>& points, wxImage& bitmap, wxImage& depth, uint32_t bitmapWidth, uint32_t bitmapHeight) const override;
};

class PixelsGenerator3D : public FractalGenerator::Pixels
{
private:
	struct Color
	{
		uint8_t red, green, blue;
		Color(uint8_t red, uint8_t green, uint8_t blue) : red(red), green(green), blue(blue) {}
	};

	float _x, _y, _z;



public:
	// draw points on bitmap
	PixelsGenerator3D(float x, float y, float z) : _x(x), _y(y), _z(z) {}
	void render(const std::vector<std::unique_ptr<FractalPoint>>& points, wxImage& bitmap, wxImage& depth, uint32_t bitmapWidth, uint32_t bitmapHeight) const override;
};

}
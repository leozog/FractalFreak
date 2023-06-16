#pragma once

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include <cstdlib>
#include <vector>
#include <memory>
#include <wx/dcbuffer.h>

/* affine transformation abstract base class
 * classes derived from it should contain a transformation matrix and a translation vector */
struct AffineTransformation
{
	AffineTransformation(float p = 0.) : probability(p) {}

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

// all variables needed to describe and draw a fractal
struct Fractal
{
	// all transformations describing a fractal, max 5
	std::vector<std::shared_ptr<AffineTransformation>> transformations;

	float x_offset;				// how far, in pixels, should the LEFT-most pixel of a fractal be from the LEFT side of a bitmap it's drawn on
	float y_offset;				// how far, in pixels, should the LOWEST pixel or a fractal be from the TOP of a bitmap it's drawn on
	float stretch_y, stretch_x; // width and height of a fractal (NOT IN PIXELS - but in mathematical terms, like the floats in AffineTransformation classes)
};

// class implementing all fractal calculations
class FractalCalculations
{
protected:
	std::vector<Fractal> base_frc; // fractals supplied by user (beginning and end fractals in the animation)
	Fractal work_frc;			   // current fractal to be drawn
	Fractal change_frc;			   // contains values of a unit change from work_frc(t) to work_frc(t+1). add all values to work_frc to get the next fractal to be drawn

	int bitmap_width, bitmap_height;	// bitap (wxImage frame) dimensions in pixels
	int iterations_amount;				// amount of pixels calculated and drawn every frame
	int dimensions_amount;				//  2 for 2D, 3 for 3D, (4 for 4D?)
	int frames_amount;					// number of frames of the animation showing base_frc[0] morphing into base_frc[1]
	int transformations_amount;			// number of transformations used by any calculated fractal in an animation (the bigger number between the amount of transformations describing base_frc[0] and base_frc[1])
	float camera_x, camera_y, camera_z; // camera coordinates for 3D viewing

	// calculate probabilities for given transformations and sum them { transformations[0]->probability, transformations[0]->probability + transformations[1]->probability, ... }
	std::vector<float> calcProbabilities(const std::vector<std::shared_ptr<Transform_2D>> &transformations);

public:
	wxImage frame; // bitmap with a calculated fractal to be drawn on screen TODO should be private but copying the whole image... and i don't want to deal with references and shit at 5:39 AM

	FractalCalculations();

	int get_frames_amount() const { return frames_amount; }

	// draws work_frc on wxImage frame
	void createBitmap();

	// calculates dimensions (x/y offset, x/y stretch) of a chosen base_frc
	void calcSize(int frc_num);

	// calculates values of change_frc
	void calcChange();

	// adds change_frc values to work_frc variables
	void updateTransformations();
};
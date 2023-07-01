#pragma once
#include "ff/FractalGenerator.h"
#include "ff/Random.h"

#include "fd/FractalFactory.h"
#include "fd/AffineTransformation.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <wx/image.h>
#include <vector>
#include <memory>
#include <initializer_list>
#include <typeinfo>
#include <typeindex>
#include <iostream>

namespace fractal_factory
{
	struct Color
	{
		uint8_t red, green, blue;
		Color(uint8_t red, uint8_t green, uint8_t blue) : red(red), green(green), blue(blue) {}
	};

	void hslToRgb(uint8_t &red, uint8_t &green, uint8_t &blue, float h, float s = 1., float l = 0.5);
	float hueToRgb(float var1, float var2, float hue);

	class PixelsGenerator2D : public FractalGenerator::Pixels
	{
	public:
		// draw points on bitmap
		void render(const std::vector<std::unique_ptr<FractalPoint>> &points, wxImage &bitmap, wxImage &depth, uint32_t bitmapWidth, uint32_t bitmapHeight) const override;
	};

	class PixelsGenerator3D : public FractalGenerator::Pixels
	{
	private:
		float cameraX, cameraY, cameraZ;

	public:
		PixelsGenerator3D(float cameraX, float cameraY, float cameraZ) : cameraX(cameraX), cameraY(cameraY), cameraZ(cameraZ) {}

		// draw points on bitmap
		void render(const std::vector<std::unique_ptr<FractalPoint>> &points, wxImage &bitmap, wxImage &depth, uint32_t bitmapWidth, uint32_t bitmapHeight) const override;
	};
}
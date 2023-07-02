#pragma once
#include "ff/FractalGenerator.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <wx/image.h>
#include <vector>
#include <memory>

class PointScatter : public FractalGenerator::Pixels
{
public:
	struct Point : public FractalPoint
	{
		uint32_t color;

		Point(glm::vec3 pos, uint32_t color) : FractalPoint{pos}, color{color} {}
	};

private:
	struct Color
	{
		uint8_t red, green, blue;
		Color(uint8_t red, uint8_t green, uint8_t blue) : red(red), green(green), blue(blue) {}
	};

	uint32_t colors;
	double z_shadow;
	bool fit;

public:
	PointScatter(uint32_t colors, double z_shadow, double fit) : colors{colors}, z_shadow{z_shadow}, fit{fit} {}
	// draw points on bitmap
	void render(const std::vector<std::unique_ptr<FractalPoint>> &points, wxImage &color, std::vector<float> &depth, uint32_t bitmapWidth, uint32_t bitmapHeight) const override;

private:
	void put_pixel(wxImage &color, std::vector<float> &depth, uint32_t x, uint32_t y, float z, PointScatter::Color c) const;
	void hslToRgb(uint8_t &red, uint8_t &green, uint8_t &blue, float h, float s = 1., float l = 0.5) const;
	float hueToRgb(float var1, float var2, float hue) const;
};
#include "fd/PointScatter.h"

#include <iostream> //usunac

void PointScatter::render(const std::vector<std::unique_ptr<FractalPoint>> &points, wxImage &color, std::vector<float> &depth, uint32_t bitmapWidth, uint32_t bitmapHeight) const
{
	if (points.empty() || !color.IsOk())
		return;

	// find max and min values of x, y, z

	double x_min = points[0]->pos.x;
	double x_max = points[0]->pos.x;
	double y_min = points[0]->pos.y;
	double y_max = points[0]->pos.y;
	double z_min = points[0]->pos.z;
	double z_max = points[0]->pos.z;
	uint32_t color_max = 0;

	for (auto &point : points)
	{
		if (point->pos.z < 0)
			continue;

		if (x_min > point->pos.x)
			x_min = point->pos.x;
		if (x_max < point->pos.x)
			x_max = point->pos.x;
		if (y_min > point->pos.y)
			y_min = point->pos.y;
		if (y_max < point->pos.y)
			y_max = point->pos.y;
		if (z_min > point->pos.z)
			z_min = point->pos.z;
		if (z_max < point->pos.z)
			z_max = point->pos.z;

		auto drawablePoint = dynamic_cast<PointScatter::Point *>(point.get());
		if (drawablePoint->color > color_max)
			color_max = drawablePoint->color;
	}

	for (auto &point : points)
	{
		if (point->pos.z < 0)
			continue;

		auto drawablePoint = dynamic_cast<PointScatter::Point *>(point.get());

		int bitmapX = (drawablePoint->pos.x - x_min) / (x_max - x_min) * bitmapWidth / 1.5 + bitmapWidth / 6;
		int bitmapY = (1 - ((drawablePoint->pos.y - y_min) / (y_max - y_min))) * bitmapHeight / 1.5 + bitmapHeight / 6;

		// if pixel is inside bitmap, draw it
		if (0 <= bitmapX && bitmapX < bitmapWidth && 0 <= bitmapY && bitmapY < bitmapHeight)
		{
			uint8_t red, green, blue;
			hslToRgb(red, green, blue, 1. / (color_max + 1) * drawablePoint->color, 1., std::max(0., 1. - (drawablePoint->pos.z - z_min) / (z_max - z_min) * z_shadow));

			put_pixel(color, depth, bitmapX, bitmapY, drawablePoint->pos.z, PointScatter::Color(red, green, blue));
		}
	}
}

void PointScatter::put_pixel(wxImage &color, std::vector<float> &depth, uint32_t x, uint32_t y, float z, PointScatter::Color c) const
{
	uint32_t d = x + y * color.GetWidth();
	if (depth[d] > z)
	{
		depth[d] = z;
		unsigned char *p = color.GetData();
		p += d * 3;
		p[0] = c.red;
		p[1] = c.green;
		p[2] = c.blue;
	}
}

void PointScatter::hslToRgb(uint8_t &red, uint8_t &green, uint8_t &blue, float h, float s, float l) const
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

float PointScatter::hueToRgb(float var1, float var2, float hue) const
{
	if (hue < 0)
		hue += 1;
	if (hue > 1)
		hue -= 1;
	if (6 * hue < 1)
		return var1 + (var2 - var1) * 6 * hue;
	if (2 * hue < 1)
		return var2;
	if (3 * hue < 2)
		return var1 + (var2 - var1) * (0.6666666f - hue) * 6;
	return var1;
}
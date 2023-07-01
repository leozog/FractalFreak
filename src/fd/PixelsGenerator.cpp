#include "fd/PixelsGenerator.h"

namespace fractal_factory
{
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

		std::vector<Color> pixelColors;

		// Make the matrix for casting

		double n, r, l, t, b, f;

		t = 1; // top
		b = -1; // bottom

		l = -1; // left
		r = 1; // right

		f = 3; // far plane
		n = 1; // near plane

		// na cele tego projektu nie wiemy o istnieniu glm::perspective!

		glm::mat4 ortho_cast(n / 4, 0, 0, 0, 0, n / b, 0, 0, 0, 0, f / (f - n), 1, 0, 0, -f * n / (f - n), 0);
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
			glm::vec4 glm_point(point->x - cameraX, point->y - cameraY, point->z - cameraZ, 1);

			// https://static.wikia.nocookie.net/afbe0a28-af5a-4073-9579-1b56c0a33e22

			// Then we apply math wizardry (often confused with Algebra)

			glm_point = ortho_cast * glm_point;

			drawablePoints.push_back(glm_point);

		}

		// find max and min values of x, y, z
		double z_max = drawablePoints[0].z;

		//double x_min = drawablePoints[0].x;
		//double x_max = drawablePoints[0].x;
		//double y_min = drawablePoints[0].y;
		//double y_max = drawablePoints[0].y;

		for (int i = 0; i < points.size(); i++)
		{
			if (z_max < drawablePoints[i].z)
				z_max = drawablePoints[i].z;

			//if (x_min > drawablePoints[i].x)
			//	x_min = drawablePoints[i].x;
			//if (x_max < drawablePoints[i].x)
			//	x_max = drawablePoints[i].x;
			//if (y_min > drawablePoints[i].y)
			//	y_min = drawablePoints[i].y;
			//if (y_max < drawablePoints[i].y)
			//	y_max = drawablePoints[i].y;

			drawablePoints[i].w = dynamic_cast<const Point&>(*points[i]).transformation_id;
		}
		//TODO scaling?

		std::sort(drawablePoints.begin(), drawablePoints.end(), [](const glm::vec4& a, const glm::vec4& b) -> bool {return a.z > b.z; });


		for (auto& point : drawablePoints)
		{
			if (point.z <= 0 || point.x > 1 || point.x < -1 || point.y > 1 || point.y < -1) 
				continue; // nie rysujemy tego czego nie widac


			int bitmapX = (bitmapWidth / 2) + point.x * bitmapWidth / 2;
			int bitmapY = (bitmapHeight / 2) + point.y * bitmapHeight / 2;

			float lightness = 1 - (point.z / z_max);

			// if pixel is inside bitmap, draw it
			if (0 <= bitmapX && bitmapX < bitmapWidth && 0 <= bitmapY && bitmapY < bitmapHeight)
				bitmap.SetRGB(bitmapX, bitmapY, lightness * pixelColors[point.w].red, lightness * pixelColors[point.w].green, lightness * pixelColors[point.w].blue);

		}
	}
}

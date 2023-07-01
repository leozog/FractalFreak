#pragma once

#include "fd/Parameters.h"
#include "fd/PointsGenerator.h"
#include "fd/PixelsGenerator.h"

#include "ff/FractalPoint.h"


namespace fractal_factory
{
	struct Point : public FractalPoint
	{
		uint32_t transformation_id;

	    Point(double x, double y, double z, uint32_t transformation_id) : FractalPoint{x, y, z}, transformation_id{ transformation_id } {}
	};
}
#include "../include/FractalCalculations.h"

FractalCalculations::FractalCalculations()
{
	// describes all values since no input method has been implemented yet TODO implement user input and yeet this
	base_frc.resize(2);

	bitmap_width = 800;
	bitmap_height = 600;
	iterations_amount = 2000000; // 100000; // lags :( TODO speed optimization
	dimensions_amount = 2;
	frames_amount = 100;

	// start fractal

	// dywan sierpinskiego z zadania
	int transformations_amount_0 = 3;
	base_frc[0].transformations.resize(transformations_amount_0);
	base_frc[0].transformations[0] = std::make_shared<Transform_2D>(0.5, 0., 0., 0.5, 0., 0.);
	base_frc[0].transformations[1] = std::make_shared<Transform_2D>(0.5, 0., 0., 0.5, 0.5, 0.);
	base_frc[0].transformations[2] = std::make_shared<Transform_2D>(0.5, 0., 0., 0.5, 0., 0.5);

	// ten dziwny snowflake z tej stronki co kuba wyslal
	/*int transformations_amount_0 = 4;
	base_frc[0].transformations.resize(transformations_amount_0);
	base_frc[0].transformations[0] = std::make_shared<Transform_2D>(0.4, 0.0, 0.0, 0.4, -160, 0);
	base_frc[0].transformations[1] = std::make_shared<Transform_2D>(0.4, 0.0, 0.0, 0.4, 160, 0);
	base_frc[0].transformations[2] = std::make_shared<Transform_2D>(0.4, -0.5, 0.5, 0.4, 0, 0);
	base_frc[0].transformations[3] = std::make_shared<Transform_2D>(0.4, 0.5, -0.5, 0.4, 0, 0);*/

	// koch curve (nie caly snowflake)
	/*int transformations_amount_0 = 4;
	base_frc[0].transformations.resize(transformations_amount_0);
	base_frc[0].transformations[0] = std::make_shared<Transform_2D>(.3333, 0.0, 0.0, .3333, -200, 0);
	base_frc[0].transformations[1] = std::make_shared<Transform_2D>(.3333, 0.0, 0.0, .3333, 200, 0);
	base_frc[0].transformations[2] = std::make_shared<Transform_2D>(0.16667, -0.288675, 0.288675, 0.16667, -50, 86.6024);
	base_frc[0].transformations[3] = std::make_shared<Transform_2D>(0.16667, 0.288675, -0.288675, 0.16667, 50, 86.6024);*/

	// dragon fire
	/*int transformations_amount_0 = 3;
	base_frc[0].transformations.resize(transformations_amount_0);
	base_frc[0].transformations[0] = std::make_shared<Transform_2D>(0.5, 0.0, 0.0, 0.8, 0.0, 50);
	base_frc[0].transformations[1] = std::make_shared<Transform_2D>(0.5, 0.2, -0.2, 0.5, -100, -100);
	base_frc[0].transformations[2] = std::make_shared<Transform_2D>(0.5, -0.2, 0.2, 0.5, 100, -100);*/

	// pentagon
	/*int transformations_amount_0 = 5;
	base_frc[0].transformations.resize(transformations_amount_0);
	base_frc[0].transformations[0] = std::make_shared<Transform_2D>(0.38, 0.0, 0.0, 0.38, 100, 0);
	base_frc[0].transformations[1] = std::make_shared<Transform_2D>(0.38, 0.0, 0.0, 0.38, 30.9017, 95.1057);
	base_frc[0].transformations[2] = std::make_shared<Transform_2D>(0.38, 0.0, 0.0, 0.38, -80.9017, 58.7785);
	base_frc[0].transformations[3] = std::make_shared<Transform_2D>(0.38, 0.0, 0.0, 0.38, -80.9017, -58.7785);
	base_frc[0].transformations[4] = std::make_shared<Transform_2D>(0.38, 0.0, 0.0, 0.38, 30.9017, -95.1057);*/

	// end fractal

	// paprotka z zadania
	int transformations_amount_1 = 4;
	base_frc[1].transformations.resize(transformations_amount_1);
	base_frc[1].transformations[0] = std::make_shared<Transform_2D>(0.787, -0.14, 0.138, 0.787, 0.075, 0.21);
	base_frc[1].transformations[1] = std::make_shared<Transform_2D>(0.218, -0.24, 0.183, 0.287, 0.33, -0.045);
	base_frc[1].transformations[2] = std::make_shared<Transform_2D>(-0.22, 0.241, 0.183, 0.287, 0.605, 0.015);
	base_frc[1].transformations[3] = std::make_shared<Transform_2D>(0.019, 0, -0.03, 0.299, 0.451, 0.03);

	/* set transformations_amount to the biggest number of transformations used in any base_frc[i]
	 * and push empty transformations into base_frc[i] so every vector is of the same length*/
	if (transformations_amount_0 > transformations_amount_1)
	{
		transformations_amount = transformations_amount_0;
		for (int i = transformations_amount_1; i < transformations_amount; i++)
			base_frc[1].transformations.push_back(std::make_shared<Transform_2D>());
	}
	else
	{
		transformations_amount = transformations_amount_1;
		for (int i = transformations_amount_0; i < transformations_amount; i++)
			base_frc[0].transformations.push_back(std::make_shared<Transform_2D>());
	}
}

std::vector<float> FractalCalculations::calcProbabilities(const std::vector<std::shared_ptr<Transform_2D>> &transformations)
{
	// sum determinants of all matrices
	float det_sum = 0.;
	for (auto transformation : transformations)
		det_sum += std::abs(glm::determinant(transformation->matrix));

	// calculate probabilities for each transformation: prob_i = det_i / det_sum
	for (auto transformation : transformations)
		transformation->probability = std::abs(glm::determinant(transformation->matrix)) / det_sum;

	// calculate and return sums of probabilities { prob_0, prob_0 + prob_1, ... }
	std::vector<float> prob_sum(5);

	prob_sum[0] = (transformations_amount > 0) ? transformations[0]->probability : 0.;
	for (int i = 1; i < 5; i++)
		prob_sum[i] = (transformations_amount > i) ? prob_sum[i - 1] + transformations[i]->probability : 0.;

	return prob_sum;
}

void FractalCalculations::createBitmap()
{
	// dynamic cast (for speed and legibility)
	std::vector<std::shared_ptr<Transform_2D>> transformations;
	for (auto transformation : work_frc.transformations)
		transformations.push_back(std::dynamic_pointer_cast<Transform_2D>(transformation));

	// calculate probabilities and sum them { transformations[0]->probability, transformations[0]->probability + transformations[1]->probability, ... }
	std::vector<float> prob_sum = calcProbabilities(transformations);

	// clear bitmap
	frame.Create(bitmap_width, bitmap_height);

	// draw pixels
	char red = 0, green = 0, blue = 0;
	float x_pixel, y_pixel, random_val, x = 0., y = 0., x_old = 0., y_old = 0.;

	/* randomize a value and pick a transformation to apply based on it (with accordance to the probabilities calculated earlier)
	 * then position and draw the pixel with a color based on the chosen transformation
	 */
	for (int i = 0; i < iterations_amount; i++)
	{
		random_val = static_cast<float>(std::rand()) / RAND_MAX; // random value from 0. to 1.
		x_old = x;
		y_old = y;

		if (random_val < prob_sum[0]) // red pixel
		{
			x = transformations[0]->matrix[0][0] * x_old + transformations[0]->matrix[0][1] * y_old + transformations[0]->vector[0];
			y = transformations[0]->matrix[1][0] * x_old + transformations[0]->matrix[1][1] * y_old + transformations[0]->vector[1];
			red = 255;
			green = 0;
			blue = 0;
		}
		else if (random_val < prob_sum[1]) // green pixel
		{
			x = transformations[1]->matrix[0][0] * x_old + transformations[1]->matrix[0][1] * y_old + transformations[1]->vector[0];
			y = transformations[1]->matrix[1][0] * x_old + transformations[1]->matrix[1][1] * y_old + transformations[1]->vector[1];
			red = 0;
			green = 255;
			blue = 0;
		}
		else if (random_val < prob_sum[2]) // blue pixel
		{
			x = transformations[2]->matrix[0][0] * x_old + transformations[2]->matrix[0][1] * y_old + transformations[2]->vector[0];
			y = transformations[2]->matrix[1][0] * x_old + transformations[2]->matrix[1][1] * y_old + transformations[2]->vector[1];
			red = 0;
			green = 0;
			blue = 255;
		}
		else if (random_val <= prob_sum[3]) // purple pixel
		{
			x = transformations[3]->matrix[0][0] * x_old + transformations[3]->matrix[0][1] * y_old + transformations[3]->vector[0];
			y = transformations[3]->matrix[1][0] * x_old + transformations[3]->matrix[1][1] * y_old + transformations[3]->vector[1];
			red = 255;
			green = 0;
			blue = 255;
		}
		else if (random_val <= prob_sum[4]) // yellow pixel
		{
			x = transformations[4]->matrix[0][0] * x_old + transformations[4]->matrix[0][1] * y_old + transformations[4]->vector[0];
			y = transformations[4]->matrix[1][0] * x_old + transformations[4]->matrix[1][1] * y_old + transformations[4]->vector[1];
			red = 255;
			green = 255;
			blue = 0;
		}

		// calculate pixel position on the bitmap, scaling and centering the fractal
		x_pixel = work_frc.x_offset + x * static_cast<float>(bitmap_width) / work_frc.stretch_x;
		y_pixel = work_frc.y_offset - y * static_cast<float>(bitmap_height) / work_frc.stretch_y;

		// if the pixel is inside the bitmap, draw it
		if (0 <= x_pixel && x_pixel < bitmap_width && 0 <= y_pixel && y_pixel < bitmap_height)
			frame.SetRGB(x_pixel, y_pixel, red, green, blue);
	}
}

void FractalCalculations::calcSize(int frc_num)
{
	// dynamic cast (for speed and legibility)
	std::vector<std::shared_ptr<Transform_2D>> transformations;
	for (auto transformation : base_frc[frc_num].transformations)
		transformations.push_back(std::dynamic_pointer_cast<Transform_2D>(transformation));

	// calculate probabilities
	std::vector<float> prob_sum = calcProbabilities(transformations);

	// find x/y offset and x/y stretch
	float x = 0., y = 0., x_old = 0., y_old = 0.;
	float random_val, x_min = bitmap_width, x_max = 0, y_min = bitmap_height, y_max = 0;

	/* randomize a value and pick a transformation to apply based on it (with accordance to the probabilities calculated earlier)
	 * find the approximate min/max x/y values the fractal reaches (math values, not converted to pixels)
	 */
	for (int i = 0; i < 5000; i++) // only 5000 iterations! can be less but will give less consistent results
	{
		random_val = static_cast<float>(std::rand()) / RAND_MAX; // random value from 0. to 1.
		x_old = x;
		y_old = y;

		if (random_val < prob_sum[0]) // transformation 0
		{
			x = transformations[0]->matrix[0][0] * x_old + transformations[0]->matrix[0][1] * y_old + transformations[0]->vector[0];
			y = transformations[0]->matrix[1][0] * x_old + transformations[0]->matrix[1][1] * y_old + transformations[0]->vector[1];
		}
		else if (random_val < prob_sum[1]) // transformation 1
		{
			x = transformations[1]->matrix[0][0] * x_old + transformations[1]->matrix[0][1] * y_old + transformations[1]->vector[0];
			y = transformations[1]->matrix[1][0] * x_old + transformations[1]->matrix[1][1] * y_old + transformations[1]->vector[1];
		}
		else if (random_val < prob_sum[2]) // transformation 2
		{
			x = transformations[2]->matrix[0][0] * x_old + transformations[2]->matrix[0][1] * y_old + transformations[2]->vector[0];
			y = transformations[2]->matrix[1][0] * x_old + transformations[2]->matrix[1][1] * y_old + transformations[2]->vector[1];
		}
		else if (random_val <= prob_sum[3]) // transformation 3
		{
			x = transformations[3]->matrix[0][0] * x_old + transformations[3]->matrix[0][1] * y_old + transformations[3]->vector[0];
			y = transformations[3]->matrix[1][0] * x_old + transformations[3]->matrix[1][1] * y_old + transformations[3]->vector[1];
		}
		else if (random_val <= prob_sum[4]) // transformation 4
		{
			x = transformations[4]->matrix[0][0] * x_old + transformations[4]->matrix[0][1] * y_old + transformations[4]->vector[0];
			y = transformations[4]->matrix[1][0] * x_old + transformations[4]->matrix[1][1] * y_old + transformations[4]->vector[1];
		}

		// check if this pixel's coordinates aren't the approximate min/max x/y values
		if (x < x_min)
			x_min = x;
		if (x > x_max)
			x_max = x;
		if (y < y_min)
			y_min = y;
		if (y > y_max)
			y_max = y;
	}

	// set width/height of the fractal TODO make them a bit bigger maybe? so the fractal is a bit smaller when drawn and fits nicer into the bitmap
	base_frc[frc_num].stretch_y = y_max - y_min;
	base_frc[frc_num].stretch_x = x_max - x_min;

	// set x/y pixel offset
	base_frc[frc_num].x_offset = static_cast<float>(bitmap_width) / 2. - (x_max - x_min) / 2. * static_cast<float>(bitmap_width) / base_frc[frc_num].stretch_x - x_min * static_cast<float>(bitmap_width) / base_frc[frc_num].stretch_x;
	base_frc[frc_num].y_offset = static_cast<float>(bitmap_height) - (static_cast<float>(bitmap_height) / 2. - (y_max - y_min) / 2. * static_cast<float>(bitmap_height) / base_frc[frc_num].stretch_y - y_min * static_cast<float>(bitmap_height) / base_frc[frc_num].stretch_y);
}

void FractalCalculations::calcChange()
{
	// init and copy transformation matrices
	change_frc.transformations.clear();
	work_frc.transformations.clear();

	for (int i = 0; i < transformations_amount; i++)
	{
		work_frc.transformations.push_back(base_frc[0].transformations[i]->copy());
		change_frc.transformations.push_back(std::make_shared<Transform_2D>());
	}

	// set start values
	work_frc.x_offset = base_frc[0].x_offset;
	work_frc.y_offset = base_frc[0].y_offset;
	work_frc.stretch_x = base_frc[0].stretch_x;
	work_frc.stretch_y = base_frc[0].stretch_y;

	// calculate per-frame change of values used for scaling and centering (from base_frc[0] to base_frc[1])
	change_frc.x_offset = (base_frc[1].x_offset - base_frc[0].x_offset) / frames_amount;
	change_frc.y_offset = (base_frc[1].y_offset - base_frc[0].y_offset) / frames_amount;
	change_frc.stretch_x = (base_frc[1].stretch_x - base_frc[0].stretch_x) / frames_amount;
	change_frc.stretch_y = (base_frc[1].stretch_y - base_frc[0].stretch_y) / frames_amount;

	// calculate per-frame change of transformation values (from base_frc[0] to base_frc[1])
	for (int i = 0; i < transformations_amount; i++)
	{
		std::dynamic_pointer_cast<Transform_2D>(change_frc.transformations[i])->matrix[0][0] = (std::dynamic_pointer_cast<Transform_2D>(base_frc[1].transformations[i])->matrix[0][0] - std::dynamic_pointer_cast<Transform_2D>(base_frc[0].transformations[i])->matrix[0][0]) / frames_amount;
		std::dynamic_pointer_cast<Transform_2D>(change_frc.transformations[i])->matrix[0][1] = (std::dynamic_pointer_cast<Transform_2D>(base_frc[1].transformations[i])->matrix[0][1] - std::dynamic_pointer_cast<Transform_2D>(base_frc[0].transformations[i])->matrix[0][1]) / frames_amount;
		std::dynamic_pointer_cast<Transform_2D>(change_frc.transformations[i])->matrix[1][0] = (std::dynamic_pointer_cast<Transform_2D>(base_frc[1].transformations[i])->matrix[1][0] - std::dynamic_pointer_cast<Transform_2D>(base_frc[0].transformations[i])->matrix[1][0]) / frames_amount;
		std::dynamic_pointer_cast<Transform_2D>(change_frc.transformations[i])->matrix[1][1] = (std::dynamic_pointer_cast<Transform_2D>(base_frc[1].transformations[i])->matrix[1][1] - std::dynamic_pointer_cast<Transform_2D>(base_frc[0].transformations[i])->matrix[1][1]) / frames_amount;
		std::dynamic_pointer_cast<Transform_2D>(change_frc.transformations[i])->vector[0] = (std::dynamic_pointer_cast<Transform_2D>(base_frc[1].transformations[i])->vector[0] - std::dynamic_pointer_cast<Transform_2D>(base_frc[0].transformations[i])->vector[0]) / frames_amount;
		std::dynamic_pointer_cast<Transform_2D>(change_frc.transformations[i])->vector[1] = (std::dynamic_pointer_cast<Transform_2D>(base_frc[1].transformations[i])->vector[1] - std::dynamic_pointer_cast<Transform_2D>(base_frc[0].transformations[i])->vector[1]) / frames_amount;
	}
}

void FractalCalculations::updateTransformations()
{
	// add change_frc values to work_frc
	work_frc.x_offset += change_frc.x_offset;
	work_frc.y_offset += change_frc.y_offset;
	work_frc.stretch_x += change_frc.stretch_x;
	work_frc.stretch_y += change_frc.stretch_y;

	for (int i = 0; i < transformations_amount; i++)
	{
		std::dynamic_pointer_cast<Transform_2D>(work_frc.transformations[i])->matrix[0][0] += std::dynamic_pointer_cast<Transform_2D>(change_frc.transformations[i])->matrix[0][0];
		std::dynamic_pointer_cast<Transform_2D>(work_frc.transformations[i])->matrix[0][1] += std::dynamic_pointer_cast<Transform_2D>(change_frc.transformations[i])->matrix[0][1];
		std::dynamic_pointer_cast<Transform_2D>(work_frc.transformations[i])->matrix[1][0] += std::dynamic_pointer_cast<Transform_2D>(change_frc.transformations[i])->matrix[1][0];
		std::dynamic_pointer_cast<Transform_2D>(work_frc.transformations[i])->matrix[1][1] += std::dynamic_pointer_cast<Transform_2D>(change_frc.transformations[i])->matrix[1][1];
		std::dynamic_pointer_cast<Transform_2D>(work_frc.transformations[i])->vector[0] += std::dynamic_pointer_cast<Transform_2D>(change_frc.transformations[i])->vector[0];
		std::dynamic_pointer_cast<Transform_2D>(work_frc.transformations[i])->vector[1] += std::dynamic_pointer_cast<Transform_2D>(change_frc.transformations[i])->vector[1];
	}
}

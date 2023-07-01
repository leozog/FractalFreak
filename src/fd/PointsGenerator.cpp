#include "fd/PointsGenerator.h"

namespace fractal_factory
{

	std::vector<std::unique_ptr<FractalPoint>> PointsGenerator2D::calculate(const std::unique_ptr<FractalParameters>& param) const
	{
		try
		{
			std::vector<AffineTransformation_2D>& transformations = dynamic_cast<Parameters2D*>(param.get())->getTransformations();
		}
		catch (const std::bad_cast& e)
		{
			std::cout << "in PointsGenerator::calculate:\n" << e.what() << std::endl;
		}

		std::vector<AffineTransformation_2D>& transformations = dynamic_cast<Parameters2D*>(param.get())->getTransformations();

		std::vector<float> prob_sum = calcProbabilities(transformations);


		glm::vec2 p(0., 0.);
		std::vector<std::unique_ptr<FractalPoint>> generated_points;
		generated_points.reserve(points_per_frame);

		// loop 100 times first to avoid stutter
		for (int i = 0; i < 100; i++)
		{
			double random_val = Random::rand_d(0., 1.); // random value from 0. to 1.
			for (int j = 0; j < prob_sum.size(); j++)
			{
				if (random_val <= prob_sum[j])
				{
					p = transformations[j].matrix * p + transformations[j].vector;
					break;
				}
			}
		}

		// randomly pick transformations to apply to p (based on probability)
		// save all points created this way to a vector
		for (int i = 0; i < points_per_frame; i++)
		{
			double random_val = Random::rand_d(0., 1.);
			for (int j = 0; j < prob_sum.size(); j++)
			{
				if (random_val <= prob_sum[j])
				{
					p = transformations[j].matrix * p + transformations[j].vector;
					generated_points.push_back(std::make_unique<Point>(p.x, p.y, 0, j));
					break;
				}
			}
		}

		return generated_points;
	}

	std::vector<std::unique_ptr<FractalPoint>> PointsGenerator3D::calculate(const std::unique_ptr<FractalParameters>& param) const
	{
		try
		{
			std::vector<AffineTransformation_3D>& transformations = dynamic_cast<Parameters3D*>(param.get())->getTransformations();
		}
		catch (const std::bad_cast& e)
		{
			std::cout << "in PointsGenerator::calculate:\n" << e.what() << std::endl;
		}

		std::vector<AffineTransformation_3D>& transformations = dynamic_cast<Parameters3D*>(param.get())->getTransformations();

		std::vector<float> prob_sum = calcProbabilities(transformations);


		glm::vec3 p(0, 0, 0);
		std::vector<std::unique_ptr<FractalPoint>> generated_points;
		generated_points.reserve(points_per_frame);

		// loop 100 times first to avoid stutter
		for (int i = 0; i < 1000; i++)
		{
			double random_val = Random::rand_d(0., 1.); // random value from 0. to 1.
			for (int j = 0; j < prob_sum.size(); j++)
			{
				if (random_val <= prob_sum[j])
				{
					p = transformations[j].matrix * p + transformations[j].vector;
					break;
				}
			}
		}

		// randomly pick transformations to apply to p (based on probability)
		// save all points created this way to a vector
		for (int i = 0; i < points_per_frame; i++)
		{
			double random_val = Random::rand_d(0., 1.);
			for (int j = 0; j < prob_sum.size(); j++)
			{
				if (random_val <= prob_sum[j])
				{
					p = transformations[j].matrix * p + transformations[j].vector;
					generated_points.push_back(std::make_unique<Point>(p.x, p.y, p.z, j));
					break;
				}
			}
		}

		return generated_points;
	}

	std::vector<float> PointsGenerator2D::calcProbabilities(std::vector<AffineTransformation_2D>& transformations) const
	{
		if (transformations.empty())
			return std::vector<float>(0);

		// sum determinants of all matrices
		float det_sum = 0.;
		for (auto& transformation : transformations)
			det_sum += std::abs(glm::determinant(transformation.matrix));

		// calculate probabilities for each transformation: prob_i = det_i / det_sum
		for (auto& transformation : transformations)
			transformation.pick_probability = std::abs(glm::determinant(transformation.matrix)) / det_sum;

		// calculate sums { prob_0, prob_0 + prob_1, ... }
		std::vector<float> prob_sum(transformations.size());

		prob_sum[0] = (transformations.size() > 0) ? transformations[0].pick_probability : 0.;
		for (int i = 1; i < prob_sum.size(); i++)
			prob_sum[i] = (transformations.size() > i) ? prob_sum[i - 1] + transformations[i].pick_probability : 0.;

		return prob_sum;
	}

	std::vector<float> PointsGenerator3D::calcProbabilities(std::vector<AffineTransformation_3D>& transformations) const
	{
		if (transformations.empty())
			return std::vector<float>(0);

		// sum determinants of all matrices
		float det_sum = 0.;
		for (auto& transformation : transformations)
			det_sum += std::abs(glm::determinant(transformation.matrix));

		// calculate probabilities for each transformation: prob_i = det_i / det_sum
		for (auto& transformation : transformations)
			transformation.pick_probability = std::abs(glm::determinant(transformation.matrix)) / det_sum;

		// calculate sums { prob_0, prob_0 + prob_1, ... }
		std::vector<float> prob_sum(transformations.size());

		prob_sum[0] = (transformations.size() > 0) ? transformations[0].pick_probability : 0.;
		for (int i = 1; i < prob_sum.size(); i++)
			prob_sum[i] = (transformations.size() > i) ? prob_sum[i - 1] + transformations[i].pick_probability : 0.;

		return prob_sum;
	}
}
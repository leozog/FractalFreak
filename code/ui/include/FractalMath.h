#pragma once

// Represents a transformation for calculations
class Transformation {
public:
	Transformation(int dimension) : _dimension(dimension)
	{
		_coefficients = new double[dimension * (dimension + 1)];
	}

	// Hey it's not pretty but it should be fast
	inline void Apply(double& x, double& y) const
	{
		double tx = _coefficients[0] * x + _coefficients[1] * y + _coefficients[2];
		y = _coefficients[3] * x + _coefficients[4] * y + _coefficients[5];
		x = tx;
	}

	Transformation(const Transformation& other) : Transformation(other._dimension)
	{
		for (int i = 0; i < _dimension * (_dimension + 1); i++)
		{
			_coefficients[i] = other._coefficients[i];
		}
	}

	Transformation& operator=(const Transformation& other)
	{
		if (this == &other) return *this;

		this->~Transformation();

		for (int i = 0; i < _dimension * (_dimension + 1); i++)
		{
			_coefficients[i] = other._coefficients[i];
		}

		return *this;
	}

	Transformation(Transformation&& other) noexcept : Transformation(other._dimension)
	{
		for (int i = 0; i < _dimension * (_dimension + 1); i++)
		{
			_coefficients[i] = other._coefficients[i];
		}

		delete other._coefficients;
		other._coefficients = nullptr;
	}

	Transformation& operator=(Transformation&& other) noexcept
	{
		if (this == &other) return *this;

		this->~Transformation();

		for (int i = 0; i < _dimension * (_dimension + 1); i++)
		{
			_coefficients[i] = other._coefficients[i];
		}

		delete other._coefficients;
		other._coefficients = nullptr;

		return *this;
	}


	~Transformation()
	{
		if (_coefficients) delete _coefficients;
	}

	double* _coefficients;
	int _dimension;
};


class FractalGenerator
{
public:
	FractalGenerator()
	{

	}

	void addFractal(const std::vector<Transformation>& vect)
	{
		_Fractals.push_back(vect);
	}

	std::vector<double>& generateFrame()
	{
		std::vector<double>* toReturn = new std::vector<double>;

		return *toReturn;
	}

protected:
	std::vector<std::vector<Transformation>> _Fractals;
};
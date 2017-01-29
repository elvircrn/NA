#pragma once

#include <vector>
#include <utility>

#include "GMath.h"

class PolynomialInterpolator
{
	std::vector<GMath::Point2D> data;
	std::vector<double> newton;

	// Exceptions
	void SameXCheck(const std::vector<GMath::Point2D> &) const;
	void DataSizeCheck(const std::vector<GMath::Point2D> &) const;
	void SameXCheck() const;
	void DataSizeCheck() const;

	int GetDegree() const;

public:
	PolynomialInterpolator(std::vector<std::pair<double, double>>);
	double operator()(double) const;
	void AddPoint(GMath::Point2D);
	std::vector<double> GetCoefficients() const;
};


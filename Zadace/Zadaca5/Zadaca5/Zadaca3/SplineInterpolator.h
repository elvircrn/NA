#pragma once

#include <vector>
#include <utility>

#include "GMath.h"

class SplineInterpolator
{
	std::vector<double> x, p, q, r, s, y;

	void SameXCheck(const std::vector<GMath::Point2D> &) const;
	void DataSizeCheck(const std::vector<GMath::Point2D> &) const;

	int GetSize() const;

	mutable int cache;

public:
	SplineInterpolator(std::vector<GMath::Point2D>);
	double operator()(double) const;
};


#pragma once

#include <vector>
#include <utility>

#include "GMath.h"

class LinearInterpolator
{
private:
	mutable int cache;
	std::vector<GMath::Point2D> data;

	// Exceptions
	void SameXCheck() const;
	void DataSizeCheck() const;

	double calc(int ind, double x) const;
	
public:
	LinearInterpolator(std::vector<GMath::Point2D> _data);
	double operator()(double x) const;
};


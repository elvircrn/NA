#pragma once
#include <vector>

#include "GMath.h"

class BarycentricInterpolator
{
	void SameXCheck() const;
	void DataSizeCheck() const;
	void OrderCheck(int) const;
	int GetDegree() const;
	
	std::vector<GMath::Point2D> data;
	std::vector<double> w;

public:
	BarycentricInterpolator(std::vector<GMath::Point2D> data, int order);
	double operator()(double x) const;
	std::vector<double> GetWeights() const;
};


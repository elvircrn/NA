#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include <iomanip>

#include "GMath.h"
#include "BarycentricInterpolator.h"
#include "LinearInterpolator.h"
#include <fstream>
	using namespace std;

class TestUtil
{
public:
	static std::vector<GMath::Point2D> LinSpace(double(*f)(double), double lower, double upper, int space)
	{
		std::vector<GMath::Point2D> ret;
		double step = (upper - lower) / (space - 1);
		for (int i = 0; i < space; i++)
			ret.emplace_back(lower + i * step, f(lower + i * step));
		return ret;
	}

	template<class T>
	static T GetInterp(double(*f)(double), double lower, double upper, int space)
	{
		TestUtil::LinSpace(f, lower, upper, space);
		return T(TestUtil::LinSpace(f, lower, upper, space));
	}

	static BarycentricInterpolator GetBarInterp(double(*f)(double), double lower, double upper, int space, int bOrder)
	{
		TestUtil::LinSpace(f, lower, upper, space);
		return BarycentricInterpolator(TestUtil::LinSpace(f, lower, upper, space), bOrder);
	}

	static BarycentricInterpolator TestBarInterp(double(*f)(double), double lower, double upper, int space, int testSize, int bOrder, bool printRes = false, bool printFull = false)
	{
		std::pair<double, double> maxError = { 0.0, 0.0 };
		BarycentricInterpolator interp = GetBarInterp(f, lower, upper, space, bOrder);
		auto test = TestUtil::LinSpace(f, lower, upper, testSize);

		int ind = 0;
		for (auto& p : test)
		{
			if (printFull)
				//std::cout << std::abs(interp(p.first) - f(p.first)) << '\n';
				std::cout << std::setw(10) << p.first << ' ' << std::setw(10) << interp(p.first) << '\n';
			maxError = std::max(maxError, { std::abs(interp(p.first) - f(p.first)), p.first });
		}

		if (printRes)
			std::cout << "Maximum absolute error: " << maxError.first << " at " << maxError.second << '\n';

		return interp;
	}


	template<class T>
	static T TestInterp(double(*f)(double), double lower, double upper, int space, int testSize, bool printRes = false, bool printFull = false)
	{
		std::pair<double, double> maxError = { 0.0, 0.0 };
		T interp = GetInterp<T>(f, lower, upper, space);
		auto test = TestUtil::LinSpace(f, lower, upper, testSize);

		int ind = 0;
		for (auto& p : test)
		{
			if (printFull)
				//std::cout << std::abs(interp(p.first) - f(p.first)) << '\n';
				std::cout << std::setw(10) << p.first << ' ' << std::setw(10) << interp(p.first) << '\n';
			maxError = std::max(maxError, { std::abs(interp(p.first) - f(p.first)), p.first });
		}
		
		if (printRes)
			std::cout << "Maximum absolute error: " << maxError.first << " at " << maxError.second << '\n';

		return interp;
	}
};

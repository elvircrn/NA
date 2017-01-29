#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <fstream>

#include "GMath.h"

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

	template<class F>
	static double FCompare(F f, const std::vector<GMath::Point2D> &sample, bool full = false)
	{
		double absMax = 0.0;
		for (auto& pt : sample)
		{
			double diff = std::abs(pt.second - f(pt.first));
			absMax = std::max(absMax, diff);
			if (full)
				std::cout << "Diff at " << pt.first << " " << diff << '\n';
		}
		return absMax;
	}
};

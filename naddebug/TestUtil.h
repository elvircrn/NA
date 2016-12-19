#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>

#include "GMath.h"
#include "LinearInterpolator.h"

class TestUtil
{
public:
    static std::vector<GMath::Point2D> LinSpace(double (*f)(double), double lower, double upper, int space)
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

    template<class T>
    static void TestInterp(double(*f)(double), double lower, double upper, int space, int testSize)
    {
        T interp = GetInterp<T>(f, lower, upper, space);
        auto test = TestUtil::LinSpace(f, lower, upper, testSize);

        std::cout << "Absolute error per point:\n";
        for (auto& p : test)
            std::cout << std::abs(interp(p.first) - f(p.first)) << '\n';
    }
};

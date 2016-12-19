#define _USE_MATH_DEFINES // msvc
#undef __STRICT_ANSI__


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <functional>
#include <vector>
#include <math.h>

#include "QRDecomposer.h"
#include "LUDecomposer.h"
#include "Matrix.h"
#include "Vector.h"
#include "PolynomialInterpolator.h"
#include "LinearInterpolator.h"
#include "TestUtil.h"

#pragma region Zadaca2


void test_1()
{
    //TestUtil::LinSpace(sin, 0, 1, 10);
	TestUtil::TestInterp<LinearInterpolator>(std::sin, 0, 2.0, 30, 6);
}

template <typename FunTip>
double Limit(FunTip f, double x0, double eps = 1e-8, double nmax = 20);


int main()
{
    test_1();

	char c = getchar();
	return 0;
}

template <typename FunTip>
double Limit(FunTip f, double x0, double eps, double nmax)
{
	double yOld = GMath::INF;
	std::vector<double> y(nmax);
	double h = 1e-3 - 1e-2;
	for (int i = 1; i <= nmax; i++)
	{
		y[i - 1] = f(x0 + h);
		double p = 2.0;
		for (int k = i - 1; k >= 1; k--)
		{
			y[k - 1] = (p * y[k] - y[k - 1]) / (p - 1.0);
			p = 2 * p;
		}
		if (std::abs(y[0] - yOld) < eps)
			return y[0];
		yOld = y[0];
		h /= 2.0;
	}
	return y[0];
}
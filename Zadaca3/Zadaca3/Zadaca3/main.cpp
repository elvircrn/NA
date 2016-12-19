#define _USE_MATH_DEFINES // msvc

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <functional>
#include <vector>
#include <cmath>

#include "QRDecomposer.h"
#include "LUDecomposer.h"
#include "Matrix.h"
#include "Vector.h"
#include "PolynomialInterpolator.h"
#include "LinearInterpolator.h"
#include "TestUtil.h"
#include "SplineInterpolator.h"

#pragma region Zadaca2

void generalTest()
{
	std::cout << "General tests\n";
	std::vector<GMath::Point2D> range = { { 0, 2 * M_PI }, { 0, 2 * M_PI }, { -0.5, 0.5 }, { -0.5, 0.5 }, { -10, 10 }, { -3, 3 } };
	std::vector<std::string> names = { "sin", "cos", "acos", "atan", "sigmoid", "runge" };

	std::vector<double(*)(double)> functions = {
		sin,
		cos,
		acos,
		atan,
		[](double x) -> double { return (1.0 / (1 + std::exp(-x))); },
		[](double x) -> double { return (1.0 / (1 + 25 * x * x));  }
	};


	int seedSize = 50, sampleSize = 30;

	for (int i = 0; i < names.size(); i++)
	{
		std::cout << "\n\nAnalysis of " + names[i] << '\n';
		std::cout << "Linear:\n";
		TestUtil::TestInterp<LinearInterpolator>(functions[i], range[i].first, range[i].second, seedSize, sampleSize, true);

		std::cout << "Polynomial:\n";
		TestUtil::TestInterp<PolynomialInterpolator>(functions[i], range[i].first, range[i].second, seedSize, sampleSize, true);

		std::cout << "Splyne:\n";
		TestUtil::TestInterp<SplineInterpolator>(functions[i], range[i].first, range[i].second, seedSize, sampleSize, true);
	}
}

double poly(double x)
{
	std::cout << "Poly tests\n";
	std::vector<double> a = { -8, -6, 3, 1.0 };
	double ret = 0, deg = 1.0;
	for (int i = 0; i < a.size(); i++)
	{
		ret += deg * a[i];
		deg *= x;
	}
	return ret;
}

double poly(std::vector<double> coeffs, double x)
{
	double deg = 1.0, ret = 0.0;

	for (double a : coeffs)
	{
		ret += deg * a;
		deg *= x;
	}

	return ret;
}

// Needs work
void polyTest()
{
	std::cout << "\n\PolyInterp on a polynomial test\n";
	PolynomialInterpolator pol({ { -5, poly(-5) }, { 2, poly(2) }, { 4, poly(4) } });
	//PolynomialInterpolator pol({ { -4, 0 }, { -1, 0 }, { 2, 0 } });

	std::vector<double> coeffs = pol.GetCoefficients();

	for (double x : coeffs)
		std::cout << x << ' ';
	std::cout << '\n';
}

void wTest()
{
	std::cout << "\n\nGetCoefficients() test; Passes if both values are the same.\n";
	PolynomialInterpolator polInter = TestUtil::TestInterp<PolynomialInterpolator>(sin, 0.0, 2 * M_PI, 20, 30);
	std::vector<double> w = polInter.GetCoefficients();
	std::cout << polInter(4 * M_PI / 3.0) << ' ' << poly(w, 4 * M_PI / 3.0) << '\n';
}

void argumentSizeTest()
{
	std::cout << "\n\nNot enough points passed; Passes if 3 exceptions are thrown.\n";

	std::vector<GMath::Point2D> v = { { 0.0, 0.0 } };

	try
	{
		auto l = LinearInterpolator(v);
	}
	catch (std::exception e)
	{
		std::cout << e.what() << '\n';
	}

	try
	{
		auto p = PolynomialInterpolator(v);
	}
	catch (std::exception e)
	{
		std::cout << e.what() << '\n';
	}

	try
	{
		auto s = SplineInterpolator(v);
	}
	catch (std::exception e)
	{
		std::cout << e.what() << '\n';
	}
}

void sameXTest()
{
	std::cout << "\n\nSame x-coordinate test; Passes if 3 exceptions are thrown.\n";
	std::vector<GMath::Point2D> v = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
	try
	{
		auto l = LinearInterpolator(v);
	}
	catch (std::exception e)
	{
		std::cout << e.what() << '\n';
	}

	try
	{
		auto p = PolynomialInterpolator(v);
	}
	catch (std::exception e)
	{
		std::cout << e.what() << '\n';
	}

	try
	{
		auto s = SplineInterpolator(v);
	}
	catch (std::exception e)
	{
		std::cout << e.what() << '\n';
	}
}

//void linInterpOutOfBoundsTest()
//{
//	std::cout << "\n\nPasses if all values are the same\n";
//	bool ok = true;
//
//	auto li = TestUtil::GetInterp<LinearInterpolator>(sin, 0, 2 * M_PI, 20);
//
//	std::vector<double> res;
//
//	for (int i = 0 )
//}

void addPointTest()
{
	std::cout << "\n\nAddPoint test; Passes if values from 2 instances of LinearInterpolation class are the same.\n";

	std::vector<GMath::Point2D> range = { { 0, 2 * M_PI }, { 0, 2 * M_PI }, { -0.5, 0.5 }, { -0.5, 0.5 }, { -10, 10 }, { -3, 3 } };
	std::vector<std::string> names = { "sin", "cos", "acos", "atan", "sigmoid", "runge" };
	std::vector<double(*)(double)> functions = {
		sin,
		cos,
		acos,
		atan,
		[](double x) -> double { return (1.0 / (1 + std::exp(-x))); },
		[](double x) -> double { return (1.0 / (1 + 25 * x * x));  }
	};

	for (int i = 0; i < 5; i++)
	{
		std::vector<GMath::Point2D> data = TestUtil::LinSpace(functions[i], range[i].first, range[i].second, 20);
		PolynomialInterpolator regular(data);

		auto dataCpy = data;
		data.resize(2);
		
		PolynomialInterpolator addInter(data);

		for (int i = 2; i < dataCpy.size(); i++)
			addInter.AddPoint(dataCpy[i]);
		
		std::cout << names[i] << " test: ";

		bool ok = true;

		for (int j = 0; j < addInter.GetCoefficients().size(); j++)
			if (!GMath::Equal(addInter.GetCoefficients()[j], regular.GetCoefficients()[j]))
				ok = false;

		if (ok)
			std::cout << "Test OK\n";
		else
			std::cout << "Not OK\n";
	}
}

void addPointExcTest()
{
	std::cout << "\n\nAdd point test; Passes if exception is thrown\n";
	bool ok = true;
	try
	{
		PolynomialInterpolator pi = TestUtil::GetInterp<PolynomialInterpolator>(sin, 0, 2 * M_PI, 10);
		pi.AddPoint({ 0.0, 0.0 });
		ok = false;
	}
	catch (std::domain_error d)
	{
		std::cout << d.what() << '\n';
	}

	if (ok)
		std::cout << "Test OK\n";
	else
		std::cout << "Not OK\n";
}

template <typename FunTip>
double Limit(FunTip f, double x0, double eps = 1e-8, double nmax = 20);

void basicLimitTest()
{
	std::cout << "\n\nBasic limit test, passes if maximum error is 'relatively' small.\n";
	std::vector<GMath::Point2D> range = { { 0, 2 * M_PI },{ 0, 2 * M_PI },{ -0.5, 0.5 },{ -0.5, 0.5 },{ -10, 10 },{ -3, 3 } };
	std::vector<std::string> names = { "sin", "cos", "acos", "atan", "sigmoid", "runge" };
	std::vector<double(*)(double)> functions = {
		sin,
		cos,
		acos,
		atan,
		[](double x) -> double { return (1.0 / (1 + std::exp(-x))); },
		[](double x) -> double { return (1.0 / (1 + 25 * x * x));  }
	};
	std::vector<int> testSizes = { 10, 10, 10, 10, 10, 10 };

	int testSize = 10;

	for (int i = 0; i < functions.size(); i++)
	{
		std::cout << names[i] << " test\n";
		double max = 0.0;

		double step = (range[i].second - range[i].first) / (testSizes[i] - 1);

		for (double j = range[i].first; j < range[i].second || GMath::Equal(j, range[i].second, 0.00001); j += step)
		{
			//std::cout << Limit(functions[i], j) << ' ' << functions[i](j) << '\n';
			max = std::max(std::abs(Limit(functions[i], j) - functions[i](j)), max);
		}

		std::cout << "Max error for " << names[i] << " is: " << max << '\n';
	}

	std::cout << "sin(x) / x, x -> 0 test\n";

	if (GMath::Equal(Limit([](double x) -> double { return std::sin(x) / x; }, 0.0), 1.0, 0.000001))
		std::cout << "Test OK\n";
	else
		std::cout << "Test NOT OK\n";
}

void testZadaca3()
{
	generalTest();
	polyTest();
	wTest();
	argumentSizeTest();
	sameXTest();
	addPointTest();
	addPointExcTest();
	basicLimitTest();
}

int main()
{
	testZadaca3();

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
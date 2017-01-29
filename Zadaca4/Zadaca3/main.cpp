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
#include "BarycentricInterpolator.h"
#include "main.h"

#pragma region Zadaca2

template <typename FunTip>
double RombergIntegration(FunTip f, double a, double b, double eps = 1e-8,
	int nmax = 1000000, int nmin = 50);

template <typename FunTip>
double AdaptiveIntegration(FunTip f, double a, double b, double eps = 1e-10,
	int maxdepth = 30, int nmin = 1);

template <typename FunTip>
double AdaptiveAux(FunTip f, double a, double b, double eps,
	double f1, double f2, double f3, int r);

double poly(double x)
{
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
	double deg = 1.0, ret = 0.0, c = 0;

	for (double a : coeffs)
	{
		double elem = deg * a;
		double y = elem - c;
		double t = ret + y;
		c = (t - ret) - y;
		ret = t;
		deg *= x;
	}

	return ret;
}

/* test functions */
double invsin(double x) { return std::sin(1 / x); }

double xinvsin(double x) { return x * invsin(x); }

double Sin(double x) { return std::sin(x); }

double Root(double x) { return std::sqrt(x); }

double RombergPoly(double x) { return poly({ 0, 1, 5, -2 }, x); }

double XSin(double x) { return x * std::sin(x); }

double runge(double x) { return (1.0 / (1 + 25 * x * x)); }

double sigmoid(double x) { return (1.0 / (1 + std::exp(-x))); }

/* derivatives */
double dinvsin(double x) { return -cos(1 / x) / (x * x); }

double dxinvsin(double x) { return invsin(x) + dinvsin(x); }

double dSin(double x) { return std::cos(x); }

double dRoot(double x) { return 1 / 2 * std::sqrt(x); }

double dXSin(double x) { return std::sin(x) + x * std::cos(x); }

double drunge(double x) { return -(50 * x) / (25 * x * x + 1) * (25 * x * x + 1); }

double dsigmoid(double x) { return (1.0 / (1 + std::exp(-x))); }


/* integrals */
double iSin(double x) { return -std::cos(x); }

double iXSin(double x) { return std::sin(x) + x * std::cos(x); }


bool TestRomberg()
{
	double sinpi = RombergIntegration(Sin, 0, M_PI);
	double sigmoid2pi = RombergIntegration(sigmoid, 0, 2 * M_PI);
	double root = RombergIntegration(Root, 1, 4);
	double poly = RombergIntegration(RombergPoly, -100, 100);

	return GMath::Equal(sinpi, 2, 0.001) &&
		GMath::Equal(sigmoid2pi, 5.5919, 0.001) &&
		GMath::Equal(root, 4.6667, 0.001) &&
		GMath::Equal(poly, 3333333, 0.001);
}

bool TestAdaptive()
{
	double sinpi = AdaptiveIntegration(Sin, 0, M_PI);
	double sigmoid2pi = AdaptiveIntegration(sigmoid, 0, 2 * M_PI);
	double root = AdaptiveIntegration(Root, 1, 4);
	double poly = AdaptiveIntegration(RombergPoly, -100, 100);
	double xsin = AdaptiveIntegration(XSin, -5, 5);

	return GMath::Equal(sinpi, 2, 0.001) &&
		GMath::Equal(sigmoid2pi, 5.5919, 0.001) &&
		GMath::Equal(root, 4.6667, 0.001) &&
		GMath::Equal(poly, 3333333, 0.001) &&
		GMath::Equal(xsin, -4.7545, 0.001);
}

bool TestIntChebyshev()
{
	return true;
}

bool TestBadM()
{
	ChebyshevApproximation c = ChebyshevApproximation(Sin, -20, 20, 100);
	try
	{
		c.set_m(-123);
	}
	catch(std::domain_error d)
	{
		std::string str = d.what();
		return (str == "Bad order");
	}
	return false;
}

bool TestBadParams()
{
	bool ok = true;
	try
	{
		ChebyshevApproximation c = ChebyshevApproximation(Sin, 20, -20, 100);
	}
	catch (std::domain_error d)
	{
		std::string str = d.what();
		ok &= (str == "Bad parameters");
	}

	try
	{
		ChebyshevApproximation c = ChebyshevApproximation(Sin, 20, 20, 100);
	}
	catch (std::domain_error d)
	{
		std::string str = d.what();
		ok &= (str == "Bad parameters");
	}

	try
	{
		ChebyshevApproximation c = ChebyshevApproximation(Sin, -20, 20, -100);
	}
	catch (std::domain_error d)
	{
		std::string str = d.what();
		ok &= (str == "Bad parameters");
	}

	return ok;
}

bool TestChebApprox()
{
	bool ok = true;
	std::cout << "sin:\n";
	ok &= GMath::IsZero(TestUtil::TestChebyshevInterp(Sin, 0, M_PI, 20, 10, true, true), 1e-12);
	std::cout << "runge:\n";
	ok &= GMath::IsZero(TestUtil::TestChebyshevInterp(runge, 0, M_PI, 200, 10, true, true), 1e-12);
	std::cout << "sigmoid:\n";
	ok &= GMath::IsZero(TestUtil::TestChebyshevInterp(sigmoid, 0, M_PI, 20, 10, true, true), 1e-12);
	std::cout << "polynomial:\n";
	ok &= GMath::IsZero(TestUtil::TestChebyshevInterp(poly, 0, M_PI, 20, 10, true, true), 1e-12);
	std::cout << "xsinx:\n";
	ok &= GMath::IsZero(TestUtil::TestChebyshevInterp(XSin, M_PI / 2, M_PI, 20, 10, true, true), 1e-12);
	std::cout << "xinvsin:\n";
	ok &= GMath::IsZero(TestUtil::TestChebyshevInterp(xinvsin, M_PI / 2, M_PI, 20, 10, true, true), 1e-5);
	return ok;
}

bool TestChebDerivative()
{
	bool ok = true;
	std::cout << "derivative test:\n";
	std::cout << "dsin:\n";
	ok &= GMath::IsZero(TestUtil::TestChebyshevDerivative(Sin, dSin, 0, M_PI, 20, 10, true, true), 1e-10);
	std::cout << "dxsinx:\n";
	ok &= GMath::IsZero(TestUtil::TestChebyshevDerivative(XSin, dXSin, M_PI / 2, M_PI, 20, 10, true, true), 1e-10);

	return ok;
}

bool TestChebDerivativeObj()
{
	bool ok = true;
	std::cout << "derivative test:\n";
	std::cout << "dsin:\n";
	ok &= GMath::IsZero(TestUtil::TestChebyshevDerivativeObj(Sin, dSin, 0, M_PI, 20, 10, true, true), 1e-10);
	std::cout << "dxsinx:\n";
	ok &= GMath::IsZero(TestUtil::TestChebyshevDerivativeObj(XSin, dXSin, M_PI / 2, M_PI, 20, 10, true, true), 1e-10);
	return ok;
}

bool TestChebInt()
{
	double sinpi = ChebyshevApproximation(Sin, 0, M_PI, 20).integrate();
	double sigmoid2pi = ChebyshevApproximation(sigmoid, 0, 2 * M_PI, 20).integrate();
	double root = ChebyshevApproximation(Root, 1, 4, 20).integrate();
	double poly = ChebyshevApproximation(RombergPoly, -100, 100, 20).integrate();
	double xsin = ChebyshevApproximation(XSin, -5, 5, 20).integrate();

	std::cout << sinpi << '\n';
	std::cout << sigmoid2pi << '\n';
	std::cout << root << '\n';
	std::cout << poly << '\n';
	std::cout << xsin << '\n';


	return GMath::Equal(sinpi, 2, 0.001) &&
		GMath::Equal(sigmoid2pi, 5.5919, 0.001) &&
		GMath::Equal(root, 4.6667, 0.001) &&
		GMath::Equal(poly, 3333333, 0.001) &&
		GMath::Equal(xsin, -4.7545, 0.001);
}

bool TestChebIntObj()
{
	double sinpi = ChebyshevApproximation(Sin, 0, M_PI, 20).antiderivative()(M_PI) - ChebyshevApproximation(Sin, 0, M_PI, 20).antiderivative()(0);
	double sigmoid2pi = ChebyshevApproximation(sigmoid, 0, 2 * M_PI, 20).antiderivative().integrate();
	double root = ChebyshevApproximation(Root, 1, 4, 20).antiderivative().integrate();
	double poly = ChebyshevApproximation(RombergPoly, -100, 100, 20).antiderivative().integrate();
	double xsin = ChebyshevApproximation(XSin, -5, 5, 20).antiderivative().integrate();

	std::cout << sinpi << '\n';
	std::cout << sigmoid2pi << '\n';
	std::cout << root << '\n';
	std::cout << poly << '\n';
	std::cout << xsin << '\n';

	return GMath::Equal(sinpi, 2, 0.001) &&
		GMath::Equal(sigmoid2pi, 5.5919, 0.001) &&
		GMath::Equal(root, 4.6667, 0.001) &&
		GMath::Equal(poly, 3333333, 0.001) &&
		GMath::Equal(xsin, -4.7545, 0.001);
}


void testZadaca4()
{
	if (TestRomberg())
		std::cout << "Romberg passed\n";
	else
		std::cout << "Romberg failed\n";

	if (TestAdaptive())
		std::cout << "Adaptive passed\n";
	else
		std::cout << "Adaptived failed\n";

	if (TestIntChebyshev())
		std::cout << "Chebyshev basic integration passsed\n";
	else
		std::cout << "Chebyshev basic integration failed\n";

	if (TestBadM())
		std::cout << "Test bad m Chebyshev passed\n";
	else
		std::cout << "Test bad m Chebyshev failed\n";

	if (TestBadParams())
		std::cout << "Test bad constructor params passed\n";
	else
		std::cout << "Test bad constructor params failed\n";
	
	if (TestChebApprox())
		std::cout << "Test Chebishev approx passed\n";
	else
		std::cout << "Test Chebishev approx failed\n";

	if (TestChebDerivative())
		std::cout << "Test Chebishev derivative passed\n";
	else
		std::cout << "Test Chebishev derivative failed\n";

	if (TestChebDerivativeObj())
		std::cout << "Test Chebishev derivative obj passed\n";
	else
		std::cout << "Test Chebishev derivative obj failed\n";

	if (TestChebInt())
		std::cout << "Test Chebishev integral passed\n";
	else
		std::cout << "Test Chebishev integral failed\n";

	if (TestChebIntObj())
		std::cout << "Test Chebishev integral obj passed\n";
	else
		std::cout << "Test Chebishev integral obj failed\n";

}

int main()
{
	testZadaca4();

	std::getchar();
	return 0;
}

template<typename FunTip>
double RombergIntegration(FunTip f, double a, double b, double eps, int nmax, int nmin)
{
	int n = 2;
	double h = (b - a) / n;
	double s = (f(a) + f(b)) / 2.0;
	double iold = s;
	std::vector<double> I(nmax + 1);
	for (int i = 1; i <= nmax; i++)
	{
		for (int j = 1; j <= n / 2; j++)
			s += f(a + (2 * j - 1) * h);

		I[i] = h * s;
		int p = 4;

		for (int k = i - 1; k >= 1; k--)
		{
			I[k] = (p * I[k + 1] - I[k]) / (p - 1);
			p *= 4;
		}

		if (n >= nmin && GMath::IsZero(I[1] - iold))
			return I[1];

		iold = I[1];
		h /= 2;
		n *= 2;
	}

	return iold;
}

template<typename FunTip>
double AdaptiveIntegration(FunTip f, double a, double b, double eps, int maxdepth, int nmin)
{
	double s = 0;
	double h = (b - a) / nmin;
	for (int i = 1; i <= nmin; i++)
	{
		s += AdaptiveAux(f, a, a + h, eps, f(a), f(a + h), f(a + h / 2), maxdepth);
		a += h;
	}
	return s;
}

template<typename FunTip>
double AdaptiveAux(FunTip f, double a, double b, double eps,
	double f1, double f2, double f3, int r)
{
	double c = (a + b) / 2.0;
	double i1 = (b - a) * (f1 + 4 * f3 + f2) / 6;
	double f4 = f((a + c) / 2.0);
	double f5 = f((c + b) / 2.0);

	double i2 = (b - a) * (f1 + 4 * f4 + 2 * f3 + 4 * f5 + f2) / 12;

	if (r <= 0 || std::abs(i1 - i2) < eps)
		return i2;

	return AdaptiveAux(f, a, c, eps, f1, f3, f4, r - 1) +
		AdaptiveAux(f, c, b, eps, f3, f2, f5, r - 1);
}



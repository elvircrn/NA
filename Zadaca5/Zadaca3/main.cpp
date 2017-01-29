#define _USE_MATH_DEFINES // msvc

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <functional>
#include <vector>
#include <cmath>
#include <complex>

#include "TestUtil.h"
#include "SplineInterpolator.h"
#include "BarycentricInterpolator.h"
#include "main.h"

#pragma region Zadaca2

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

double xmsinx2(double x) { return x - 2 * std::sin(x); }

/* derivatives */
double dinvsin(double x) { return -cos(1 / x) / (x * x); }

double dxinvsin(double x) { return invsin(x) + dinvsin(x); }

double dSin(double x) { return std::cos(x); }

double dRoot(double x) { return 1 / 2 * std::sqrt(x); }

double dXSin(double x) { return std::sin(x) + x * std::cos(x); }

double drunge(double x) { return -(50 * x) / (25 * x * x + 1) * (25 * x * x + 1); }

double dsigmoid(double x) { return (1.0 / (1 + std::exp(-x))); }

double dxmsinx2(double x) { return 1 - 2 * std::cos(x); }

/* integrals */
double iSin(double x) { return -std::cos(x); }

double iXSin(double x) { return std::sin(x) + x * std::cos(x); }

// OK
template <typename FunTip>
bool BracketRoot(FunTip f, double x0, double &a, double &b,
	double hinit = 1e-5, double hmax = 1e10, double lambda = 1.4);

// OK
template <typename FunTip>
double ModifiedRegulaFalsi(FunTip f, double a, double b, double eps = 1e-10,
	int maxiter = 100);

// OK
template <typename FunTip>
double Ridders(FunTip f, double a, double b, double eps = 1e-10,
	int maxiter = 100);

// OK
template <typename FunTip>
double NewtonRaphson(FunTip f, FunTip fprim, double x0, double eps = 1e-10,
	int maxiter = 100);

std::vector<std::complex<double>> PolyRoots(std::vector<std::complex<double>> coefficients,
	double eps = 1e-10, int maxiters = 100, int maxtrials = 10);

std::vector<std::complex<double>> PolyRoots(std::vector<double> coefficients,
	double eps = 1e-10, int maxiters = 100, int maxtrials = 10);

template <typename FunTip>
double FindMinimum(FunTip f, double x0, double eps = 1e-8,
	double hinit = 1e-5, double hmax = 1e10, double lambda = 1.4);

template <typename FunTip>
std::vector<std::pair<double, double>> RK4Integrator(FunTip f, double x0,
	double y0, double xmax, double h, double eps = 1e-8, bool adaptive = false);

bool BracketExc1()
{
	double a, b;
	try
	{
		BracketRoot(Sin, 0, a, b, -1, 1, 1);
	}
	catch (std::domain_error e)
	{
		return true;
	}
	return false;
}

bool BracketExc2()
{
	double a, b;
	try
	{
		BracketRoot(Sin, 0, a, b, 1, -1, 1);
	}
	catch (std::domain_error e)
	{
		return true;
	}
	return false;
}


bool BracketExc3()
{
	double a, b;
	try
	{
		BracketRoot(Sin, 0, a, b, -1, 1, -1);
	}
	catch (std::domain_error e)
	{
		return true;
	}
	return false;
}

bool BracketTest1()
{
	double a, b;
	auto f = [](double x) -> double { return x * x * x - x - 2; };
	bool res = BracketRoot(f, -100, a, b);
	return res && (f(a) * f(b) < 0);
}

bool BracketTest2()
{
	double a, b;
	auto f = [](double x) -> double { return x * x + 100; };
	bool res = BracketRoot(f, -100, a, b);
	return !res;
}

bool TestBracket()
{
	bool ok = true;

	ok &= BracketExc1();
	ok &= BracketExc2();
	ok &= BracketExc3();

	ok &= BracketTest1();
	ok &= BracketTest2();

	return ok;
}

bool TestRegulaExc1()
{
	try
	{
		ModifiedRegulaFalsi(Sin, 2, 1);
	}
	catch (std::range_error e)
	{
		return true;
	}
	return false;
}

bool TestRegulaExc2()
{
	try
	{
		ModifiedRegulaFalsi(Sin, 1, 2, -1);
	}
	catch (std::domain_error e)
	{
		return true;
	}
	return false;
}

bool TestRegulaExc3()
{
	try
	{
		ModifiedRegulaFalsi(Sin, 1, 2, 1, -1);
	}
	catch (std::domain_error e)
	{
		return true;
	}
	return false;
}

bool TestRegulaExc4()
{
	try
	{
		auto f = [](double x) -> double { return 1 / x; };
		double res = ModifiedRegulaFalsi(f, -1, 1, 1e-10, 2);
		return GMath::Equal(res, 1.0000, 0.0001);
	}
	catch (std::logic_error e)
	{
		return true;
	}
	return false;
}

bool RegulaTest1()
{
	auto f = [](double x) -> double { return std::exp(x * x + 7 * x - 30) - 1; };
	double res = ModifiedRegulaFalsi(f, 2.8, 3.1);
	return GMath::Equal(res, 3, 0.0001);
}

bool RegulaTest2()
{
	auto f = [](double x) -> double { return 1 / x - Sin(x) + 1; };
	double res = ModifiedRegulaFalsi(f, -1.3, -0.5);
	return GMath::Equal(res, -0.629446, 0.0001);
}

bool RegulaTest3()
{
	auto f = [](double x) -> double { return x * x * x - 2 * x - 5; };
	double res = ModifiedRegulaFalsi(f, 2, 3);
	return GMath::Equal(res, 2.0945, 0.0001);
}

bool TestRegula()
{
	bool ok = true;

	ok &= TestRegulaExc1();
	ok &= TestRegulaExc2();
	ok &= TestRegulaExc3();
	ok &= TestRegulaExc4();

	ok &= RegulaTest1();
	ok &= RegulaTest2();
	ok &= RegulaTest3();

	return ok;
}

bool RidersExc1()
{
	try
	{
		Ridders(Sin, 2, 1);
	}
	catch (std::range_error e)
	{
		return true;
	}
	return false;
}

bool RidersExc2()
{
	try
	{
		Ridders(Sin, 1, 2, -1);
	}
	catch (std::domain_error e)
	{
		return true;
	}
	return false;
}

bool RidersExc3()
{
	try
	{
		Ridders(Sin, 1, 2, 1, -1);
	}
	catch (std::domain_error e)
	{
		return true;
	}
	return false;
}

bool RidersExc4()
{
	try
	{
		auto f = [](double x) -> double { return 1 / x; };
		double res = Ridders(f, -1, 1, 1e-10, 2);
		return GMath::Equal(res, 1.0000, 0.0001);
	}
	catch (std::logic_error e)
	{
		return true;
	}
	return false;
}

bool RiddersTest1()
{
	auto f = [](double x) -> double { return x * std::exp(x) - 1; };
	double res = Ridders(f, -1, 1);
	return GMath::Equal(res, 0.567143, 0.0001);
}

bool RiddersTest2()
{
	auto f = [](double x) -> double { return 1 / x - Sin(x) + 1; };
	double res = Ridders(f, -1.3, -0.5);
	return GMath::Equal(res, -0.629446, 0.0001);
}

bool RiddersTest3()
{
	auto f = [](double x) -> double { return 1 / x - 1; };
	double res = Ridders(f, 0.5, 1.5);
	return GMath::Equal(res, 1.0000, 0.0001);
}

bool TestRidders()
{
	bool ok = true;

	ok &= RidersExc1();
	ok &= RidersExc2();
	ok &= RidersExc3();

	ok &= RiddersTest1();
	ok &= RiddersTest2();
	ok &= RiddersTest3();

	return ok;
}

bool NewtonRaphsonExcTest1()
{
	try
	{
		NewtonRaphson(Sin, dSin, 0, -1);
	}
	catch (std::domain_error e)
	{
		return true;
	}
	return false;
}

bool NewtonRaphsonExcTest2()
{
	try
	{
		NewtonRaphson(Sin, dSin, 0, 1, -1);
	}
	catch (std::domain_error e)
	{
		return true;
	}
	return false;
}

bool NewtonRaphsonExcTest3()
{
	try
	{
		NewtonRaphson(Sin, dSin, 100, 1, 1);
	}
	catch (std::logic_error e)
	{
		return true;
	}
	return false;
}

bool NewtonRaphsonExcTest4()
{
	try
	{
		double res = NewtonRaphson(xmsinx2, dxmsinx2, M_PI / 3);
	}
	catch (std::logic_error e)
	{
		return true;
	}
	return false;
}

bool NewtonRaphsonTest1()
{
	double res = NewtonRaphson(xmsinx2, dxmsinx2, 1.1);
	return GMath::IsZero(xmsinx2(res));
}

bool NewtonRaphsonTest2()
{
	double res = NewtonRaphson(xinvsin, dxinvsin, 1.1, 1e-18, 10000000);
	return GMath::IsZero(xinvsin(res), 1e-14);
}

// Patoloski slucaj
bool NewtonRaphsonTest3()
{
	try
	{
		double res = NewtonRaphson(sigmoid, dsigmoid, 1.1);
	}
	catch (std::logic_error e)
	{
		return true;
	}
	return false;
}

bool NewtonRaphsonTest4()
{
	try
	{
		double res = NewtonRaphson(Root, dRoot, 1.1);
	}
	catch (std::logic_error e)
	{
		return true;
	}
	return false;
}

bool NewtonRaphsonTest5()
{
	double res = NewtonRaphson(xmsinx2, dxmsinx2, 1.1);
	return GMath::IsZero(xmsinx2(res));
}

bool NewtonRaphsonTest6()
{
	double res = NewtonRaphson(Sin, dSin, 1.1);
	return GMath::IsZero(Sin(res));
}


bool TestNewtonRaphson()
{
	bool ok = true;

	ok &= NewtonRaphsonExcTest1();
	ok &= NewtonRaphsonExcTest2();
	ok &= NewtonRaphsonExcTest3();
	ok &= NewtonRaphsonExcTest4();

	ok &= NewtonRaphsonTest1();
	ok &= NewtonRaphsonTest2();
	ok &= NewtonRaphsonTest3();
	ok &= NewtonRaphsonTest4();
	ok &= NewtonRaphsonTest5();
	ok &= NewtonRaphsonTest6();

	return ok;
}

bool RK4ExcTest1()
{
	return true;
}

bool RK4Test1()
{
	double absMax;

	auto f = [](double x) -> double { return 0.25 * (-6 * x + 23 * std::exp(2 * x) - 3); };

	absMax = TestUtil::FCompare(f, RK4Integrator([](double x, double y) -> double
	{
		return 3 * x + 2 * y;
	}, 0, 5, 10, 0.25, 1e-8, false));

	std::cout << "Test 1 non-adaptive abs max: " << absMax << '\n';

	absMax = TestUtil::FCompare(f, RK4Integrator([](double x, double y) -> double
	{
		return 3 * x + 2 * y;
	}, 0, 5, 10, 0.25, 1e-8, true));

	std::cout << "Test 1 adaptive abs max: " << absMax << '\n';

	return true;
}

bool RK4Test2()
{
	double absMax;

	auto f = [](double x) -> double { return 0.25 * (-6 * x * x - 6 * x - 197 * std::exp(2 * x) - 3); };

	absMax = TestUtil::FCompare(f, RK4Integrator([](double x, double y) -> double
	{
		return 3 * x + 2 * y;
	}, 0, 5, 10, 0.25, 1e-8, false));

	std::cout << "Test 2 non-adaptive abs max: " << absMax << '\n';

	absMax = TestUtil::FCompare(f, RK4Integrator([](double x, double y) -> double
	{
		return 3 * x + 2 * y;
	}, 0, 5, 10, 0.25, 1e-8, true));

	std::cout << "Test 2 adaptive abs max: " << absMax << '\n';

	return true;
}

bool RK4Test3()
{
	double absMax;

	auto f = [](double x) -> double { return (-225 * x * x - 30 * x - 56248 * std::exp(15 * x) - 2) / 1125; };

	absMax = TestUtil::FCompare(f, RK4Integrator([](double x, double y) -> double
	{
		return 3 * x * x + 15 * y;
	}, 0, -50, 10, 0.25, 1e-8, false));

	std::cout << "Test 3 non-adaptive abs max: " << absMax << '\n';

	absMax = TestUtil::FCompare(f, RK4Integrator([](double x, double y) -> double
	{
		return 3 * x * x + 15 * y;
	}, 0, -50, 10, 5, 1e-8, true));

	std::cout << "Test 3 adaptive abs max: " << absMax << '\n';

	return true;
}


bool TestRK4()
{
	bool ok = true;
	ok &= RK4Test1();
	ok &= RK4Test2();
	//ok &= RK4Test3(); <- JAAAAKO sporo

	return ok;
}

bool TestMinimumExc1()
{
	try
	{
		auto f = [](double x) -> double { return 3 * x * x * x - 2 * x - 5; };
		FindMinimum(f, 5);
	}
	catch (std::logic_error e)
	{
		return true;
	}
	return false;
}

bool TestMinimumExc2()
{
	try
	{
		auto f = [](double x) -> double { return 3 * x * x * x - 2 * x - 5; };
		FindMinimum(f, 5);
	}
	catch (std::logic_error e)
	{
		return true;
	}
	return false;
}

bool MinimumTest1()
{
	auto f = [](double x) -> double { return std::abs(x - 2) + (x - 1) * (x - 1); };

	std::cout << "Minimum se nalazi u okolini tacke x = 1.5, a nadjeni minimum je: " << FindMinimum(f, 2) << '\n';

	return true;
}

bool MinimumTest2()
{
	auto f = [](double x) -> double { return 3 * x * x * x * x - 2 * x - 5; };

	std::cout << "Minimum se nalazi u okolini tacke x = 0.55(wolfram alpha), a nadjeni minimum je: " << FindMinimum(f, 1) << '\n';

	return true;
}

bool MinimumTest3()
{
	auto f = Sin;

	std::cout << "Minimum za sin, pocenta tacka je x = 0: " << FindMinimum(f, 0, 1e-15) << '\n';

	return true;
}

bool MinimumTest4()
{
	auto f = Sin;

	std::cout << "Minimum za sigmoidu(nema lokalni minimum), pocenta tacka je x = 0: " << FindMinimum(sigmoid, 0, 1e-12) << '\n';

	return true;
}

bool MinimumTest5()
{
	auto f = Sin;
	std::cout << "Minimum za x * sin(1 / x) - singularitet u 0, ali konvergira ka njemu(?); pocenta tacka je x = 10: " << FindMinimum(xinvsin, 10) << '\n';
	return true;
}

bool TestMinimum()
{
	bool ok = true;

	ok &= TestMinimumExc1();
	ok &= TestMinimumExc2();

	ok &= MinimumTest1();
	ok &= MinimumTest2();
	ok &= MinimumTest3();
	ok &= MinimumTest4();
	ok &= MinimumTest5();

	return ok;
}


int main()
{
	std::cout << "Started...\n";
	if (TestBracket())
		std::cout << "BracketRoot: OK\n";
	else
		std::cout << "BracketRoot: NOT OK\n";

	if (TestRegula())
		std::cout << "RegulaFalsi: OK\n";
	else
		std::cout << "RegulaFalis: NOT OK\n";

	if (TestRidders())
		std::cout << "Ridders: OK\n";
	else
		std::cout << "Ridders: NOT OK\n";

	if (TestNewtonRaphson())
		std::cout << "Newton Raphson: OK\n";
	else
		std::cout << "Newton Raphson: NOT OK\n";

	if (TestRK4())
		std::cout << "RK4: OK\n";
	else
		std::cout << "RK4: NOT OK\n";

	if (TestMinimum())
		std::cout << "Minimum: OK\n";
	else
		std::cout << "Minimum: NOT OK\n";

	std::cout << "Finished...\n";

	std::getchar();
	return 0;
}

template <typename FunTip>
double Ridders(FunTip f, double a, double b, double eps,
	int maxiter)
{
	if (a > b || GMath::Equal(a, b))
		throw std::range_error("Root must be bracketed");

	if (eps < 0 || maxiter < 0)
		throw std::domain_error("Invalid parameters");

	double f1 = f(a);
	double f2 = f(b);

	while (std::abs(b - a) > eps && maxiter--)
	{
		double c = (a + b) / 2;
		double f3 = f(c);
		if (GMath::IsZero(f3))
			return c;
		double d = c + f3 * (c - a) * GMath::sgn(f1 - f2) / std::sqrt(f3 * f3 - f1 * f2);
		double f4 = f(d);
		if (GMath::IsZero(f4))
			return d;
		if (f3 * f4 < 0 || GMath::IsZero(f3 * f4))
		{
			a = c;
			b = d;
			f1 = f3;
			f2 = f4;
		}
		else if (f1 * f4 < 0 || GMath::IsZero(f1 * f4))
		{
			b = d;
			f2 = f4;
		}
		else
		{
			a = d;
			f1 = f4;
		}
	}

	if (!maxiter)
		throw std::logic_error("Given accuracy has not achieved");

	return (a + b) / 2;
}

template <typename FunTip>
bool BracketRoot(FunTip f, double x0, double &a, double &b,
	double hinit, double hmax, double lambda)
{
	if (hinit < 0 || hmax < 0 || lambda < 0)
		throw std::domain_error("Invalid parameters");

	a = x0;
	double f1 = f(a);
	double h = hinit;
	while (std::abs(h) < hmax)
	{
		b = a + h;
		double f2 = f(b);
		if (f1 * f2 <= 0)
			return true;
		h *= lambda;
		a = b;
		f1 = f2;
	}

	return false;
}

template <typename FunTip>
double ModifiedRegulaFalsi(FunTip f, double a, double b, double eps,
	int maxiter)
{
	if (a > b || GMath::Equal(a, b))
		throw std::range_error("Root must be bracketed");

	if (eps < 0 || maxiter < 0)
		throw std::domain_error("Invalid parameters");

	double f1 = GMath::phi(f(a)), f2 = GMath::phi(f(b));
	double c = a, cold = b;

	while (std::abs(c - cold) > eps && maxiter--)
	{
		cold = c;
		c = (a * f2 - b * f1) / (f2 - f1);
		double f3 = GMath::phi(f(c));

		if (f3 == 0)
			return c;

		if (f1 * f3 <= 0)
		{
			b = c;
			f2 = f3;
		}
		else
		{
			a = c;
			f1 = f3;
		}
	}

	if (!maxiter)
		throw std::logic_error("Given accuracy has not achieved");

	return c;
}

template <typename FunTip>
double NewtonRaphson(FunTip f, FunTip fprim, double x0, double eps,
	int maxiter)
{
	if (eps <= 0 || maxiter <= 0)
		throw std::domain_error("Invalid parameters");

	double dx = std::numeric_limits<double>::max();
	double x = x0;

	while (std::abs(dx) > eps && maxiter--)
	{
		double v = f(x);

		if (GMath::IsZero(v))
			return x;

		double fp = fprim(x);

		if (GMath::IsZero(fp, 1e-12))
			throw std::logic_error("Convergence has not achieved");

		dx = v / fp;
		x -= dx;
	}

	if (maxiter == 0)
		throw std::logic_error("Convergence has not achieved");

	return x;
}

std::vector<std::complex<double>> ToComplexVector(const std::vector<double> &vec)
{
	std::vector<std::complex<double>> ret;
	for (auto &x : vec)
		ret.emplace_back(x, 0);
	return ret;
}

template<typename FunTip>
double FindMinimum(FunTip f, double x0, double eps, double hinit, double hmax, double lambda)
{
	if (eps < 0 || hinit < 0 || hmax < 0 || lambda < 0)
		throw std::domain_error("Invalid parameters");

	double k = (1 + std::sqrt(5)) / 2, a, b, c, d;
	double h = hinit;

	bool found = false;

	while (h <= hmax)
	{
		if (f(x0 + h) < f(x0))
			x0 += h;
		else if (f(x0 - h) < f(x0))
			x0 -= h;
		else
		{
			found = true;
			break;
		}
		h *= lambda;
	}

	if (!found)
		throw std::logic_error("Minimum has not found");

	a = x0 - h;
	c = x0;
	b = x0 + h;

	if (c - a < b - c)
		d = a + (b - a) / k;
	else
	{
		d = c;
		c = b - (b - a) / k;
	}

	double u = f(c);
	double v = f(d);

	while (b - a > eps)
	{
		if (u < v)
		{
			b = d;
			d = c;
			c = b - (b - a) / k;
			v = u;
			u = f(c);
		}
		else
		{
			a = c;
			c = d;
			d = a + (b - a) / k;
			u = v;
			v = f(d);
		}
	}

	return (a + b) / 2;
}

template<class F>
double RK4Step(F f, double x, double y, double h)
{
	double k1 = f(x, y);
	double k2 = f(x + h / 2, y + h * k1 / 2);
	double k3 = f(x + h / 2, y + h * k2 / 2);
	double k4 = f(x + h, y + h * k3);
	return y + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

template<typename FunTip>
std::vector<std::pair<double, double>> RK4Integrator(FunTip f, double x0, double y0, double xmax, double h, double eps, bool adaptive)
{
	std::vector<std::pair<double, double>> ret;

	double x = x0;
	double y = y0;

	if (adaptive)
	{
		ret.emplace_back(x, y);

		while ((h > 0 && x <= xmax) || (h < 0 && x >= xmax))
		{
			double u = RK4Step(f, x, y, h / 2);
			double v = RK4Step(f, x + h / 2, u, h / 2);
			double w = RK4Step(f, x, y, h);

			double delta = std::abs(w - v) / h;

			if (delta < eps)
			{
				x += h;
				y = v;
				ret.emplace_back(x, y);
			}

			h *= std::min(5.0, 0.9 * std::sqrt(std::sqrt((eps / delta))));
		}
	}
	else
	{
		while (x <= xmax + GMath::GEPS)
		{
			ret.emplace_back(x, y);
			y = RK4Step(f, x, y, h);
			x += h;
		}
	}

	return ret;
}


std::pair<std::complex<double>, bool> Laguer(const std::vector<std::complex<double>> &p, int n, double x, double eps, int itermax)
{
	double dx = std::numeric_limits<double>::max();
	while (std::abs(x) > eps && itermax--)
	{
		auto f = p[n];
		std::complex<double> s, d;
		for (int i = n - 1; i > -1; i--)
		{
			s = s * x + 2.0 * d;
			d = d * x + f;
			f = f * x + p[i];
		}
		//if (GMath::IsZero(std::norm(f)))
	}

	return std::pair<std::complex<double>, bool>();
}

std::vector<std::complex<double>> PolyRoots(std::vector<std::complex<double>> coefficients,
	double eps, int maxiters, int maxtrials)
{
	std::vector<std::complex<double>> ret;
	return ret;
}

std::vector<std::complex<double>> PolyRoots(std::vector<double> coefficients,
	double eps, int maxiters, int maxtrials)
{
	std::vector<std::complex<double>> ret;
	return ret;
}


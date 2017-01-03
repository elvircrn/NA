/*
Ovaj cpp file je u haoticnom stanju zato sto je sklopjen u
jedan file iz citavog visual studio projekta. Projekat je testiran
na sljedeci nacin:
Napravio sam klasu TestUtil koja je zaduzena za racunanju apsolutnih
gresaka za neku funkciju i interpolaciju na arbitrarnom skupu brojeva
bez muke i sa relativno malo koda. Ostale test metode testiraju specificne
funkcionalnosti za svaku interpolaciju, a autor ocekuje da je
code-coverage od 100%. :))
*/



#define _USE_MATH_DEFINES // msvc

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <functional>
#include <vector>
#include <cmath>
#include <utility>
class GMath
{
	static const double GEPS;

public:
	static const double INF;

	typedef std::pair<double, double> Point2D;

	static bool Equal(double x, double y, double Eps = GEPS);
	static bool ContainsX(const Point2D &a, const Point2D &b, double x);
	static bool Contains(double x1, double x2, double x);
	static bool IsZero(double x, double Eps = GEPS);
};


#pragma once

#include <vector>
#include <utility>


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

#pragma once

#include <vector>
#include <utility>


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

#pragma once
#include <vector>

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

#pragma once

#include <vector>
#include <utility>

class PolynomialInterpolator
{
	std::vector<GMath::Point2D> data;
	std::vector<double> newton;

	// Exceptions
	void SameXCheck(const std::vector<GMath::Point2D> &) const;
	void DataSizeCheck(const std::vector<GMath::Point2D> &) const;
	void SameXCheck() const;
	void DataSizeCheck() const;

	int GetDegree() const;

public:
	PolynomialInterpolator(std::vector<std::pair<double, double>>);
	double operator()(double) const;
	void AddPoint(GMath::Point2D);
	std::vector<double> GetCoefficients() const;
};



#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include <iomanip>

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


double runge(double x)
{
	return (1.0 / (1 + 25 * x * x));
}

double sigmoid(double x)
{
	return (1.0 / (1 + std::exp(-x)));
}

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

		std::cout << "Barycentric:\n";
		TestUtil::TestBarInterp(functions[i], range[i].first, range[i].second, seedSize, sampleSize, 4, true, false);
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
	double deg = 1.0, ret = 0.0, c = 0;

	for (double a : coeffs)
	{
		double elem = deg * a;
		double y = elem - c;
		double t = ret + y;
		c = (t - ret) - y;
		ret = t;



		//ret += deg * a;
		deg *= x;
	}

	return ret;
}

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


	polInter = TestUtil::TestInterp<PolynomialInterpolator>(cos, 0.0, 2 * M_PI, 20, 30);
	w = polInter.GetCoefficients();
	std::cout << polInter(4 * M_PI / 3.0) << ' ' << poly(w, 4 * M_PI / 3.0) << '\n';


	polInter = TestUtil::TestInterp<PolynomialInterpolator>(tan, 0.0, 2 * M_PI, 10, 30);
	w = polInter.GetCoefficients();
	std::cout << polInter(4 * M_PI / 3.0) << ' ' << poly(w, 4 * M_PI / 3.0) << '\n';

	polInter = TestUtil::TestInterp<PolynomialInterpolator>(runge, 0.0, 2 * M_PI, 10, 30);
	w = polInter.GetCoefficients();
	std::cout << polInter(4 * M_PI / 3.0) << ' ' << poly(w, 4 * M_PI / 3.0) << '\n';


	polInter = TestUtil::TestInterp<PolynomialInterpolator>(sqrt, 0.0, 2 * M_PI, 20, 30);
	w = polInter.GetCoefficients();
	std::cout << polInter(4 * M_PI / 3.0) << ' ' << poly(w, 4 * M_PI / 3.0) << '\n';

	polInter = TestUtil::TestInterp<PolynomialInterpolator>(sigmoid, 0.0, 2 * M_PI, 20, 30);
	w = polInter.GetCoefficients();
	std::cout << polInter(4 * M_PI / 3.0) << ' ' << poly(w, 4 * M_PI / 3.0) << '\n';

}

void argumentSizeTest()
{
	std::cout << "\n\nNot enough points passed; Passes if 4 exceptions are thrown.\n";

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

    try
	{
		auto s = BarycentricInterpolator(v, 4);
	}
	catch (std::exception e)
	{
		std::cout << e.what() << '\n';
	}
}

void sameXTest()
{
	std::cout << "\n\nSame x-coordinate test; Passes if 4 exceptions are thrown.\n";
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

    try
	{
		auto s = BarycentricInterpolator(v, 4);
	}
	catch (std::exception e)
	{
		std::cout << e.what() << '\n';
	}
}

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

double invsin(double x)
{
	return std::sin(1 / x);
}

double xinvsin(double x)
{
	return x * invsin(x);
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
	/*
	test sa predavanja. run-ati po potrebi

	PolynomialInterpolator pol({ { 1, 2 },{ 2, 4 },{ 3, 2.5 },{ 4, 3 },{ 5, 1 } });
	std::vector <double> v = pol.GetCoefficients();
	for (auto x : v) std::cout << x << std::endl;
	getchar();


	getchar();
	PolynomialInterpolator _pol({ { 1, 2 },{ 2, 4 },{ 3, 2.5 },{ 4, 3 },{ 5, 1 } });
	std::cout << _pol(2.7) << '\n';
	std::cout << _pol(2) << '\n';

	getchar();
	LinearInterpolator lin({ { 1, 2 },{ 2, 4 },{ 3, 2.5 },{ 4, 3 },{ 5, 1 } });
	std::cout << lin(2.7);
	getchar();
	*/

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

#include <algorithm>

void BarycentricInterpolator::SameXCheck() const
{
	for (size_t i = 1; i < data.size(); i++)
		if (GMath::Equal(data[i - 1].first, data[i].first))
			throw std::domain_error("Invalid data set");
}

void BarycentricInterpolator::DataSizeCheck() const
{
	if (data.size() <= 1)
		throw std::domain_error("Invalid data set");
}

void BarycentricInterpolator::OrderCheck(int order) const
{
	if (order < 0 || order > (int)data.size())
		throw std::domain_error("Invalid data set");
}

int BarycentricInterpolator::GetDegree() const
{
	return data.size();
}

BarycentricInterpolator::BarycentricInterpolator(std::vector<GMath::Point2D> _data, int order) : data(_data)
{
	DataSizeCheck();
	OrderCheck(order);
	sort(data.begin(), data.end(), [](const GMath::Point2D &a, const GMath::Point2D &b) -> bool{ return a.first < b.first; });
	SameXCheck();

	w.resize(data.size());

	for (int i = 1; i <= (int)data.size(); i++)
	{
		double p = 1.0;
		w[i - 1] = 0.0;
		for (int k = std::max(1, i - order); k <= std::min(i, (int)data.size() - order); k++)
		{
			p = 1.0;
			for (int j = k; j <= k + order; j++)
				if (i != j)
					p /= (data[i - 1].first - data[j - 1].first);
			p = (k % 2) ? p : -p;
		}
		w[i - 1] += p;
	}
}

double BarycentricInterpolator::operator()(double xx) const
{
	double p = 0.0, q = 0.0;
	for (int i = 0; i < (int)data.size(); i++)
	{
		if (GMath::Equal(xx, data[i].first))
			return data[i].second;
		double u = w[i] / (xx - data[i].first);
		p += u * data[i].second;
		q += u;
	}
	return p / q;
}

std::vector<double> BarycentricInterpolator::GetWeights() const
{
	return w;
}
#include <limits>

const double GMath::GEPS = std::numeric_limits<double>::epsilon();
const double GMath::INF = std::numeric_limits<double>::infinity();

bool GMath::Equal(double x, double y, double Eps)
{
	if (std::abs(x) < Eps)
		x = 0;
	if (std::abs(y) < Eps)
		y = 0;

	return std::fabs(x - y) <= Eps * (std::fabs(x) + std::fabs(y));

	return false;
}

bool GMath::ContainsX(const Point2D & a, const Point2D & b, double x)
{
	return (a.first < x && x < b.first);
}

bool GMath::Contains(double x1, double x2, double x)
{
	return (x1 < x && x < x2) || GMath::Equal(x1, x) || GMath::Equal(x2, x);
}

bool GMath::IsZero(double x, double Eps)
{
	return std::abs(x) < Eps;
}

#include <utility>
#include <algorithm>
#include <stdexcept>
#include <iterator>

void LinearInterpolator::SameXCheck() const
{
	for (size_t i = 1; i < data.size(); i++)
		if (GMath::Equal(data[i - 1].first, data[i].first))
			throw std::domain_error("Invalid data set");
}

void LinearInterpolator::DataSizeCheck() const
{
	if (data.size() <= 1)
		throw std::domain_error("Invalid data set");
}

#include <iostream>
double LinearInterpolator::calc(int ind, double x) const
{
	return ((data[ind + 1].first - x) / (data[ind + 1].first - data[ind].first)) * data[ind].second +
		((x - data[ind].first) / (data[ind + 1].first - data[ind].first)) * data[ind + 1].second;
}

LinearInterpolator::LinearInterpolator(std::vector<GMath::Point2D> _data) : data(_data),
																			cache(0)
{
	DataSizeCheck();
	std::sort(data.begin(), data.end());
	SameXCheck();
}

double LinearInterpolator::operator()(double x) const
{
	double helpX = (x < data[0].first) ? ((data[0].first + data[1].first) / 2.0) : x;
	helpX = (data[data.size() - 1].first < x) ? ((data[data.size() - 2].first + data[data.size() - 1].first) / 2.0) : helpX;

	if (!GMath::ContainsX(data[cache], data[cache + 1], helpX))
		cache = std::distance(data.begin(), std::lower_bound(data.begin(),
															 data.end(),
															 GMath::Point2D(helpX, 0))) - 1;

	cache = std::min((int)data.size() - 2, cache);
	cache = std::max(cache, 0);

	return calc(cache, x);
}


#include <iostream>
#include <algorithm>
#include <iomanip>

void PolynomialInterpolator::SameXCheck(const std::vector<GMath::Point2D> &_data) const
{
	for (size_t i = 1; i < _data.size(); i++)
		if (GMath::Equal(_data[i - 1].first, _data[i].first))
			throw std::domain_error("Invalid data set");
}

void PolynomialInterpolator::DataSizeCheck(const std::vector<GMath::Point2D> &_data) const
{
	if (_data.size() <= 1)
		throw std::domain_error("Invalid data set");
}

void PolynomialInterpolator::SameXCheck() const
{
	SameXCheck(data);
}

void PolynomialInterpolator::DataSizeCheck() const
{
	DataSizeCheck(data);
}

int PolynomialInterpolator::GetDegree() const
{
	return data.size();
}

PolynomialInterpolator::PolynomialInterpolator(std::vector<GMath::Point2D> _data) : data(_data)
{
	DataSizeCheck();
	std::sort(data.begin(), data.end());
	SameXCheck();

	newton.resize(data.size() - 1);

	for (int j = 0; j < GetDegree() - 1; j++)
	{
		newton[j] = data[GetDegree() - 1].second;
		for (int i = GetDegree() - 1; i > j; i--)
			data[i].second = (data[i].second - data[i - 1].second) / (data[i].first - data[i - j - 1].first);
	}
	newton.push_back(data.back().second);

}

double PolynomialInterpolator::operator()(double x) const
{
	double ret = 0.0;
	int n = GetDegree();

	double shlemielThePainter = 1.0;

	for (int i = 0; i < n; i++)
	{
		if (i > 0)
			shlemielThePainter *= (x - data[i - 1].first);
		ret += data[i].second * shlemielThePainter;
	}

	return ret;
}

void PolynomialInterpolator::AddPoint(GMath::Point2D p)
{
	int n = GetDegree();
	data.push_back(p);
	double current = p.second, prev;

	for (int i = 1; i <= n; i++)
	{
		prev = newton[i - 1];
		newton[i - 1] = current;

		double dX = (p.first - data[n - i].first);

		if (GMath::IsZero(std::abs(dX)))
			throw std::domain_error("Invalid data set");

		current = (current - prev) / dX;
	}

	data.back().second = current;
	newton.push_back(current);
}


std::vector<double> PolynomialInterpolator::GetCoefficients() const
{
	double ret = 0.0;
	std::vector<double> w(GetDegree() + 1, 0);
	std::vector<double> v(GetDegree() + 1);

	w[0] = 1;
	for (int i = 1; i <= GetDegree(); i++)
	{
		for (int j = 0; j <= i; j++)
			v[j] += data[i - 1].second * w[j];
		w[i] = w[i - 1];
		for (int j = i - 1; j > 0; j--)
			w[j] = w[j - 1] - data[i - 1].first * w[j];
		w[0] *= -data[i - 1].first;
	}

	double f = 1.0;

	return v;
}

#include <functional>
#include <algorithm>

void SplineInterpolator::SameXCheck(const std::vector<GMath::Point2D> &_data) const
{
	for (size_t i = 1; i < _data.size(); i++)
		if (GMath::Equal(_data[i - 1].first, _data[i].first))
			throw std::domain_error("Invalid data set");
}

void SplineInterpolator::DataSizeCheck(const std::vector<GMath::Point2D> &_data) const
{
	if (_data.size() <= 1)
		throw std::domain_error("Invalid data set");
}

int SplineInterpolator::GetSize() const
{
	return x.size();
}

double SplineInterpolator::operator()(double xx) const
{
	double helpX = (xx < x[0]) ? ((x[0] + x[1]) / 2.0) : xx;
	helpX = (x.back() < xx) ? ((x[x.size() - 2] + x.back()) / 2.0) : helpX;

	if (!GMath::Contains(x[cache], x[cache + 1], helpX))
		cache = std::distance(x.begin(), std::lower_bound(x.begin(),
			x.end(),
			helpX)) - 1;

	cache = std::min((int)x.size() - 2, cache);
	cache = std::max(0, cache);

	double t = xx - x[cache];
	return y[cache] + t * (q[cache] + t * (r[cache] + s[cache] * t));
}

SplineInterpolator::SplineInterpolator(std::vector<GMath::Point2D> data) : cache(0)
{
	DataSizeCheck(data);
	sort(data.begin(), data.end());
	for (auto& elem : data)
	{
		x.push_back(elem.first);
		y.push_back(elem.second);
	}

	SameXCheck(data);

	r.resize(data.size(), 0);
	s.resize(data.size(), 0);
	q.resize(data.size(), 0);

	int n = GetSize();

	for (int i = 1; i < n - 2; i++)
	{
		s[i] = 2 * (x[i + 1] - x[i - 1]);
		r[i] = 3 * ((y[i + 1] - y[i]) / (x[i + 1] - x[i]) - (y[i] - y[i - 1] / (x[i] - x[i - 1])));
	}

	for (int i = 1; i < n - 2; i++)
	{
		double mi = (x[i] - x[i - 1]) / s[i];
		s[i + 1] -= mi * (x[i] - x[i - 1]);
		r[i + 1] -= mi * r[i];
	}

	r[n - 2] /= s[n - 2];

	for (int i = n - 3; i > 0; i--)
		r[i] = (r[i] - (x[i] - x[i - 1]) * r[i + 1]) / s[i];

	for (int i = 0; i < n - 1; i++)
	{
		double dx = x[i + 1] - x[i];
		s[i] = (r[i + 1] - r[i]) / (3 * dx);
		q[i] = (y[i + 1] - y[i]) / dx - dx * (r[i + 1] + 2 * r[i]) / 3;
	}

}

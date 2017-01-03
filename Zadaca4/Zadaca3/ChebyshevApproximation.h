#include <stdexcept>
#include <vector>

#include "GMath.h"

#pragma once
class ChebyshevApproximation
{
	void CheckBadParameters(double _xmin, double _xmax, int n);
	void CheckM(int _m);
	void CheckBound(double x) const;
	void CheckBound(double a, double b) const;

	int m;
	double xmin, xmax;

	std::vector<double> c, w, v;

public:
	template <typename FunTip>
	ChebyshevApproximation(FunTip f, double _xmin, double _xmax, int n);
	void set_m(int m);
	void trunc(double eps); // Treba li baciti exception?
	double operator()(double x) const;
	double derivative(double x) const;
	ChebyshevApproximation derivative() const;
	ChebyshevApproximation antiderivative() const;
	double integrate(double a, double b) const;
	double integrate() const;
};

template<typename FunTip>
ChebyshevApproximation::ChebyshevApproximation(FunTip f, double _xmin, double _xmax, int n) : xmin(_xmin), xmax(_xmax), m(n)
{
	CheckBadParameters(xmin, xmax, n);

	std::vector<double>v(n + 1);
	std::vector<double>w(n + 1);

	set_m(n);
	
	for (int i = 0; i <= n; i++)
	{
		w[i] = M_PI * (2 * i + 1) / (2 * n + 2);
		v[i] = f((xmin + xmax + (xmax - xmin) * std::cos(w[i])) / 2.0);
	}

	for (int k = 0; k <= n; k++)
	{
		double s = 0;
		for (int i = 0; i <= n; i++)
			s += v[i] * cos(k * w[i]);
		c[k] = 2 * s / (n + 1);
	}
}













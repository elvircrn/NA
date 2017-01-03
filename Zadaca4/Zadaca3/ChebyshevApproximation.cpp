#include "ChebyshevApproximation.h"

void ChebyshevApproximation::CheckBadParameters(double xmin, double xmax, int n)
{
	if (xmin > xmax || GMath::Equal(xmax, xmin) || n < 1)
		throw std::domain_error("Bad parameters");
}

void ChebyshevApproximation::CheckM(int _m)
{
	if (_m < 1)
		throw std::domain_error("Bad order");
}

void ChebyshevApproximation::CheckBound(double x) const
{
	if (!GMath::Contains(xmin, xmax, x))
		throw std::domain_error("Bad argument");
}

void ChebyshevApproximation::CheckBound(double a, double b) const
{
	if (!GMath::Contains(xmin, xmax, a) || !GMath::Contains(xmin, xmax, b))
		throw std::domain_error("Bad interval");
}

void ChebyshevApproximation::set_m(int m)
{
	CheckM(m);
}

void ChebyshevApproximation::trunc(double eps)
{
	for (m = 0; m < c.size(); m++)
		if (std::abs(c[m]) > std::abs(eps))
			break;
	m--;
}

double ChebyshevApproximation::operator()(double x) const
{
	CheckBound(x);
	double t = (2 * x - xmin - xmax) / (xmax - xmin);
	double p = 1;
	double q = t;
	double s = c[0] / 2 + c[1] * t;
	for (int k = 2; k <= m; k++)
	{
		double r = 2 * t * q - p;
		s += c[k] * r;
		p = q;
		q = r;
	}
	return s;
}

double ChebyshevApproximation::derivative(double x) const
{
	double t = (2 * x - xmin - xmax) / (xmax - xmin);
	double p = 1;
	double q = 4 * t;
	double s = c[1] / 2 + c[2] * t;
	for (int k = 3; k <= m; k++)
	{
		double r = k * (2 * t * q / (k - 1) - p / (k - 2));
		s += c[k] * r;
		p = q;
		q = r;
	}
	return 2 * s / (xmax - xmin);
}

double ChebyshevApproximation::integrate(double a, double b) const
{
	CheckBound(a, b);

	return 0.0;
}

double ChebyshevApproximation::integrate() const
{
	return 0.0;
}

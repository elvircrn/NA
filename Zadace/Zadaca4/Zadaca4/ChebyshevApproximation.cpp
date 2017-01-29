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

void ChebyshevApproximation::set_m(int _m)
{
	CheckM(_m);
	m = _m;
}

void ChebyshevApproximation::trunc(double eps)
{
	for (int i = m; i >= 0; i--)
	{
		if (std::abs(c[i]) > std::abs(eps))
		{
			m = i;
			break;
		}
	}
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
	CheckBound(x);
	double t = (2 * x - xmin - xmax) / (xmax - xmin);
	double p = 1;
	double q = 4 * t;
	double s = c[1] + 4 * c[2] * t;
	for (int k = 3; k <= m; k++)
	{
		double r = k * (2 * t * q / (k - 1) - p / (k - 2));
		s += c[k] * r;
		p = q;
		q = r;
	}
	return 2 * s / (xmax - xmin);
}

ChebyshevApproximation ChebyshevApproximation::derivative() const
{
	double mi = 4 / (xmax - xmin);
	std::vector<double> cder(m);
	cder[m - 1] = mi * m * c[m];
	cder[m - 2] = mi * (m - 1) * c[m - 1];
	for (int j = m - 3; j >= 0; j--)
		cder[j] = cder[j + 2] + mi * (j + 1) * c[j + 1];
	return ChebyshevApproximation(cder, xmin, xmax);
}


double ChebyshevApproximation::integrate(double a, double b) const
{
	CheckBound(a, b);
	auto F = this->antiderivative();
	return F(b) - F(a);
}

double ChebyshevApproximation::integrate() const
{
	auto F = this->antiderivative();
	return F(xmax) - F(xmin);
}

ChebyshevApproximation ChebyshevApproximation::antiderivative() const
{
	double sum = 0.0, fac = 1.0, con;
	std::vector<double> cint(m);
	con = 0.25*(xmax - xmin);
	for (int j = 1; j < m - 1; j++) {
		cint[j] = con*(c[j - 1] - c[j + 1]) / j;
			sum += fac*cint[j];
			fac = -fac;
	}
	cint[m - 1] = con*c[m - 2] / (m - 1);
	sum += fac*cint[m - 1];
	cint[0] = 2.0*sum;
	return ChebyshevApproximation(cint, xmin, xmax);

}

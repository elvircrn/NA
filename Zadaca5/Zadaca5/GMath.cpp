#include "GMath.h"
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

int GMath::sgn(double x)
{
	return (x < 0) ? -1 : 1;
}

double GMath::phi(double x)
{
	return x / (1 + std::abs(x));
}

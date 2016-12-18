#pragma once
#include <utility>
class GMath
{
	static const double GEPS;
	static const double INF;
public:
	typedef std::pair<double, double> Point2D;

	static bool Equal(double x, double y, double Eps = GEPS);
	static bool ContainsX(const Point2D &a, const Point2D &b, double x);
	static bool Contains(double x1, double x2, double x);
	static bool IsZero(double x, double Eps = GEPS);
};


#include "PolynomialInterpolator.h"

#include <iostream>
#include <algorithm>
#include <iomanip>

#include "GMath.h"

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

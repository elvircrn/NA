#include "BarycentricInterpolator.h"

#include <algorithm>
#include <exception>
#include <stdexcept>

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
	//sort(data.begin(), data.end(), [](const GMath::Point2D &a, const GMath::Point2D &b) -> bool{ return a.first < b.first; });
	SameXCheck();

	w.resize(data.size());

	for (int i = 1; i <= (int)data.size(); i++)
	{
		double p;
		w[i - 1] = 0.0;
		for (int k = std::max(1, i - order); k <= std::min(i, (int)data.size() - order); k++)
		{
			p = 1.0;
			for (int j = k; j <= k + order; j++)
				if (i != j)
					p /= (data[i].first - data[j].first);
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

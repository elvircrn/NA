#include "SplineInterpolator.h"

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

	for (int i = 1; i < n - 1; i++)
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

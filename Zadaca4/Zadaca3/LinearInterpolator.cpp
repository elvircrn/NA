#include "LinearInterpolator.h"
#include "GMath.h"

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


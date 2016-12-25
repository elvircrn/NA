#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>

#include "GMath.h"
#include "LinearInterpolator.h"
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
				std::cout << p.first << ' ' << interp(p.first) << '\n';
			maxError = std::max(maxError, { std::abs(interp(p.first) - f(p.first)), p.first });
		}
		
		if (printRes)
			std::cout << "Maximum absolute error: " << maxError.first << " at " << maxError.second << '\n';

		return interp;
	}

	static void print_vector_to_file(const vector<double> &v, ofstream &o) {
		o << " [ ";
		for (auto t : v)
			o << t << " ";
		o << "]";
	}

	static void create_scilab(const vector<double>& xdata, const vector<double>& ydata,
		const vector<double>& xinterp, const vector<double>& yinterp,
		string type) {
		static char counter('a');
		ofstream output("interp" + string(1, counter++) + ".sci");
		output << "xdata = ";
		print_vector_to_file(xdata, output);
		output << ";" << endl;
		output << "ydata = ";
		print_vector_to_file(ydata, output);
		output << ";" << endl;
		output << "xinterp = ";
		print_vector_to_file(xinterp, output);
		output << ";" << endl;
		output << "yinterp = ";
		print_vector_to_file(yinterp, output);
		output << ";" << endl;
		output << "[yinterpsci] = interp1(xdata, ydata, xinterp, \"" << type << "\");" << endl;
		output << "subplot(311)\nplot(xdata, ydata);\nsubplot(312)\nplot(xinterp, yinterpsci);\nsubplot(313)\nplot(xinterp, yinterp);";
		output.close();
	}

};

#pragma once

#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <functional>

class Vector
{
	std::vector<double> elements;

	void PushBack(const double &elem);
	void DimCheck(const Vector &v1, const Vector &v2) const;
	void DimCheck(const Vector &v) const;
	void RangeCheck(int index) const;
	Vector& ForEach(const std::function<double(double)> &f);

public:
	Vector();
	
	explicit Vector(int n);
	Vector(std::initializer_list<double> l);
	int NElems() const;
	double &operator[](int i);
	double operator[](int i) const;
	double &operator()(int i);
	double operator()(int i) const;
	void Print(char separator = '\n') const;
	friend Vector operator +(const Vector &v1, const Vector &v2);
	Vector &operator +=(const Vector &v);
	friend Vector operator -(const Vector &v1, const Vector &v2);
	Vector &operator -=(const Vector &v);
	friend Vector operator *(double s, const Vector &v);
	friend Vector operator *(const Vector &v, double s);
	Vector &operator *=(double s);
	friend double operator *(const Vector &v1, const Vector &v2);
	friend Vector operator /(const Vector &v, double s);
	Vector &operator /=(double s);
	~Vector();
};


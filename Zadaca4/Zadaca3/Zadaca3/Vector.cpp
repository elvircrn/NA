#include <iostream>

#include "Vector.h"

void Vector::DimCheck(int n) const
{
	if (n <= 0)
		throw std::range_error("Bad dimension");
}

void Vector::CheckZero(double x) const
{
	if (JesuLiJednaki(x, 0))
		throw std::domain_error("Division by zero");
}

void Vector::PushBack(const double & elem)
{
	elements.push_back(elem);
}

void Vector::DimCheck(const Vector & v1, const Vector & v2) const
{
	if (v1.NElems() != v2.NElems())
		throw std::domain_error("Incompatible formats");
}

void Vector::DimCheck(const Vector &v) const
{
	if (NElems() != v.NElems())
		throw std::domain_error("Incompatible formats");
}

void Vector::RangeCheck(int index) const
{
	if (index < 0 || NElems() <= index)
		throw std::range_error("Invalid index");
}

Vector& Vector::ForEach(const std::function<double(double)>& f)
{
	for (auto &x : elements)
		x = f(x);
	return (*this);
}

Vector::Vector(int n)
{
	DimCheck(n);
	elements.resize(n, 0);
}

Vector::Vector(std::initializer_list<double> l)
{
	DimCheck(l.size());
	elements = l;
}

Vector::Vector(const std::vector<double>& v)
{
	DimCheck(v.size());
	elements = v;
}

int Vector::NElems() const
{
	return elements.size();
}

double & Vector::operator[](int i)
{
	RangeCheck(i);
	return elements[i];
}

double Vector::operator[](int i) const
{
	RangeCheck(i);
	return elements[i];
}

double & Vector::operator()(int i)
{
	i--;
	RangeCheck(i);
	return elements[i];
}

double Vector::operator()(int i) const
{
	i--;
	RangeCheck(i);
	return elements[i];
}

void Vector::Print(char separator) const
{
	bool first(true);
	for (auto x : elements)
	{
		if (!first)
			printf("%c", separator);
		std::cout << x;
		if (first)
			first = false;
	}
}

Vector & Vector::operator+=(const Vector & v)
{
	DimCheck(v);
	for (int i = 0; i < v.NElems(); i++)
		elements[i] += v[i];
	return (*this);
}

Vector & Vector::operator-=(const Vector & v)
{
	DimCheck(v);
	for (int i = 0; i < v.NElems(); i++)
		elements[i] -= v[i];

	return (*this);
}

Vector & Vector::operator*=(double s)
{
	return ForEach([&s](double x) { return x * s; });
}

Vector & Vector::operator/=(double s)
{
	CheckZero(s);
	ForEach([&s](double x) -> double { return x / s; });
	return (*this);
}

bool Vector::operator==(const Vector & v) const
{
	for (int i = 0; i < v.NElems(); i++)
		if (!JesuLiJednaki(elements[i], v[i], 1e-12))
			return false;
	return true;
}

bool Vector::operator!=(const Vector & v) const
{
	for (int i = 0; i < v.NElems(); i++)
		if (JesuLiJednaki(elements[i], v[i], 1e-12))
			return false;
	return true;
}

Vector::~Vector()
{
}

Vector operator+(const Vector & v1, const Vector & v2)
{
	v1.DimCheck(v2);
	Vector ret(v1.NElems());
	for (int i = 0; i < v1.NElems(); i++)
		ret[i] = (v1[i] + v2[i]);
	return ret;
}

Vector operator-(const Vector & v1, const Vector & v2)
{
	v1.DimCheck(v2);
	Vector ret(v1.NElems());
	for (int i = 0; i < v1.NElems(); i++)
		ret[i] = (v1[i] - v2[i]);
	return ret;
}

Vector operator*(double s, const Vector &v)
{
	Vector ret = v;
	return ret.ForEach([&s](double x) { return x * s; });
}

Vector operator*(const Vector & v, double s)
{
	Vector ret = v;
	return ret.ForEach([&s](double x) { return x * s; });
}

double operator*(const Vector & v1, const Vector & v2)
{
	v1.DimCheck(v2);
	double ret = 0.0;
	for (int i = 0; i < v1.NElems(); i++)
		ret += v1[i] * v2[i];
	return ret;
}

Vector operator/(const Vector & v, double s)
{
	v.CheckZero(s);
	Vector ret = v;
	ret.ForEach([&s](double x) -> double { return x / s; });
	return ret;
}

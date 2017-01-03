#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cmath>
#include <vector>
#include <functional>
#include <numeric>
#include <type_traits>

#define EPS std::numeric_limits<double>::epsilon()

class Vector
{
	std::vector<double> elements;

	void DimCheck(int n) const;
	void PushBack(const double &elem);
	void DimCheck(const Vector &v1, const Vector &v2) const;
	void DimCheck(const Vector &v) const;
	void RangeCheck(int index) const;
	Vector& ForEach(const std::function<double(double)> &f);
	void CheckZero(double x) const;

public:

	explicit Vector(int n);
	Vector(std::initializer_list<double> l);
	Vector(const std::vector<double> &v);
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
	bool operator== (const Vector &v) const;
	bool operator!= (const Vector &v) const;

	~Vector();

	bool JesuLiJednaki(double x, double y, double Eps = EPS) const
	{
		if (std::abs(x) < EPS)
			x = 0;
		if (std::abs(y) < EPS)
			y = 0;

		return std::fabs(x - y) <= Eps * (std::fabs(x) + std::fabs(y));
	}

	friend class Matrix;
	friend class LUDecomposer;
	friend class QRDecomposer;
};

#endif // !_VECTOR_H_
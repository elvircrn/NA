#pragma once

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>

#include "Matrix.h"

void Matrix::ListCheck(const std::initializer_list<std::vector<double>> &l) const
{
	if (!l.size())
		throw std::range_error("Bad dimension");
	int first = l.begin()->size();
	for (auto item : l)
		if (item.size() == 0)
			throw std::range_error("Bad dimension");
		else if (item.size() != first)
			throw std::logic_error("Bad matrix");
}

void Matrix::RangeCheck(int x) const
{
	if (mat.empty() || x < 0 || mat.size() <= x)
		throw std::range_error("Invalid index");
}

void Matrix::RangeCheck(int x, int y) const
{
	if (mat.empty() || mat.size() < x || mat[0].NElems() < y)
		throw std::range_error("Invalid index");
}

void Matrix::DimCheck(int n, int m) const
{
	if (n <= 0 || m <= 0)
		throw std::range_error("Bad dimension");
}

void Matrix::DimCheck(int n) const
{
	if (n < 0 || n >= NRows())
		throw std::range_error("Bad dimensions");
}

void Matrix::DimCheck(const Matrix & m) const
{
	if (NCols() != m.NRows())
		throw std::domain_error("Incompatible formats");
}

void Matrix::CheckZero(double x) const
{
	if (JesuLiJednaki(x, 0))
		throw std::domain_error("Division by zero");
}

// assumes matrix is not empty
void Matrix::SquareCheck() const
{
	if (NCols() != NRows())
		throw std::domain_error("Divisor matrix is singular");
}

Vector & Matrix::operator()(int i)
{
	return mat[i - 1];
}

Vector Matrix::operator()(int i) const
{
	return mat[i - 1];
}

void Matrix::DimCheck(const Matrix & m1, const Matrix & m2) const
{
	m1.DimCheck(m2);
}

void Matrix::DimCheck(const Vector & v1) const
{
	if (NCols() != v1.NElems())
		throw std::domain_error("Incompatible formats");
}

void Matrix::DimSameCheck(const Matrix & m1, const Matrix & m2) const
{
	if (m1.NRows() != m2.NRows() || m2.NCols() != m2.NCols())
		throw std::domain_error("Incompatible formats");
}

void Matrix::DimSameCheck(const Matrix & m1) const
{
	if (NRows() != m1.NRows() || NCols() != m1.NCols())
		throw std::domain_error("Incompatible formats");
}

Matrix::Matrix(int n, int m)
{
	DimCheck(n, m);
	mat.resize(n, Vector(m));
}

Matrix::Matrix(const Vector & v)
{
	mat.resize(v.NElems(), Vector(1));
	mat[0] = v;
}

Matrix::Matrix(std::initializer_list<std::vector<double>> l)
{
	ListCheck(l);
	for (auto item : l)
		mat.push_back(Vector(item));
}

int Matrix::NRows() const
{
	return mat.size();
}

int Matrix::NCols() const
{
	return mat[0].NElems();
}

double* Matrix::operator[](int i)
{
	RangeCheck(i);
	return mat[i].elements.data();
}

const double* Matrix::operator[](int i) const
{
	RangeCheck(i);
	return mat[i].elements.data();
}

double & Matrix::operator()(int i, int j)
{
	i--;
	j--;
	RangeCheck(i, j);
	return mat[i][j];
}

double Matrix::operator()(int i, int j) const
{
	i--;
	j--;
	RangeCheck(i, j);
	return mat[i][j];
}

void Matrix::Print(int width) const
{
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[i].NElems(); j++)
			std::cout << std::setw(width) << mat[i][j];
		if (i < mat.size() - 1)
			std::putchar('\n');
	}
}

Matrix & Matrix::operator+=(const Matrix & m)
{
	DimSameCheck(m);
	for (int i = 0; i < m.NRows(); i++)
		for (int j = 0; j < m.NCols(); j++)
			mat[i][j] += m[i][j];
	return (*this);
}

Matrix & Matrix::operator-=(const Matrix & m)
{
	DimSameCheck(m);
	for (int i = 0; i < m.NRows(); i++)
		for (int j = 0; j < m.NCols(); j++)
			mat[i][j] -= m[i][j];
	return (*this);
}

Matrix & Matrix::operator*=(double s)
{
	for (int i = 0; i < NRows(); i++)
		for (int j = 0; j < NCols(); j++)
			mat[i][j] *= s;
	return (*this);
}


void Matrix::Transpose()
{
	if (NCols() == NRows())
	{
		for (int i = 0; i < NRows() - 1; i++)
			for (int j = i + 1; j < NCols(); j++)
				std::swap(mat[i][j], mat[j][i]);
	}
	else
	{
		Matrix help = Matrix(NCols(), NRows());
		for (int i = 0; i < help.NRows(); i++)
			for (int j = 0; j < help.NCols(); j++)
				help[i][j] = mat[j][i];
		(*this) = help;
	}
}

bool Matrix::operator==(const Matrix & m) const
{
	for (int i = 0; i < m.NRows(); i++)
		for (int j = 0; j < m.NCols(); j++)
			if (!JesuLiJednaki(mat[i][j], m[i][j]))
				return false;
	return true;
}


Matrix::~Matrix()
{
}

Matrix Matrix::operator/=(double s)
{
	CheckZero(s);
	for (int i = 0; i < NRows(); i++)
		for (int j = 0; j < NCols(); j++)
			mat[i][j] /= s;
	return (*this);
}

Matrix Matrix::operator/=(Matrix B)
{
	Matrix &A = (*this);
	B.SquareCheck();
	A.DimCheck(B);

	int n = B.NRows();
	int m = A.NCols();

	for (int k = 1; k <= B.NCols(); k++)
	{
		int p = k;
		for (int i = k + 1; i <= n; i++)
			if (std::abs(B(k, i)) > std::abs(B(k, p)))
				p = i;

		if (std::abs(B(k, p)) <= EPS)
			throw std::domain_error("Divisor matrix is singular");

		if (p != k)
		{
			for (int j = 1; j <= n; j++)
				std::swap(B[j - 1][k - 1], B[j - 1][p - 1]);
			for (int j = 1; j <= A.NRows(); j++)
				std::swap(A[j - 1][k - 1], A[j - 1][p - 1]);
		}

		for (int i = k + 1; i <= B.NCols(); i++)
		{
			double mi = B(k, i) / B(k, k);

			for (int j = 1; j <= B.NRows(); j++)
				B[j - 1][i - 1] -= mi * B[j - 1][k - 1];

			for (int j = 1; j <= A.NRows(); j++)
				A[j - 1][i - 1] -= mi * A[j - 1][k - 1];
		}
	}


	Matrix X = Matrix(A.NRows(), B.NCols());

	for (int k = 1; k <= A.NRows(); k++)
	{
		for (int i = A.NCols(); i >= 1; i--)
		{
			double s = A(k, i);
			for (int j = i + 1; j <= A.NCols(); j++)
				s -= B(j, i) * X(k, j);
			X(k, i) = s / B(i, i);
		}
	}

	A = X;

	return X;
}

double Matrix::Det() const
{
	SquareCheck();
	double d = 1;
	int n = NRows();

	Matrix a(*this);

	for (int k = 0; k < n; k++)
	{
		int p = k;
		for (int i = k + 1; i < n; i++)
			if (std::abs(a[i][k]) > std::abs(a[p][k]))
				p = i;

		if (std::abs(a[p][k]) < EPS)
			return 0.0;

		if (p != k)
		{
			d *= -1.0;
			std::swap(a(k + 1), a(p + 1));
		}

		for (int i = k + 1; i < n; i++)
		{
			double mi = a[i][k] / a[k][k];
			for (int j = k + 1; j < n; j++)
				a[i][j] -= mi * a[k][j];
		}
	}

	for (int i = 0; i < n; i++)
		d *= a[i][i];

	return d;
}

void Matrix::Invert()
{
	Matrix& a = (*this);
	SquareCheck();
	int n = NRows();
	std::vector<int>w(n);
	for (int k = 1; k <= n; k++)
	{
		int p = k;
		for (int i = k + 1; i <= n; i++)
			if (std::abs(a[i - 1][k - 1]) > std::abs(a[p - 1][k - 1]))
				p = i;
		if (std::abs(a[p - 1][k - 1]) < EPS)
			throw std::domain_error("Matrix is singular");
		if (p != k)
			std::swap(a(k), a(p));

		w[k - 1] = p;
		double mi = a[k - 1][k - 1];
		a[k - 1][k - 1] = 1.0;

		a(k) /= mi;

		for (int i = 1; i <= n; i++)
		{
			if (i != k)
			{
				mi = a[i - 1][k - 1];
				a[i - 1][k - 1] = 0.0;
				for (int j = 1; j <= n; j++)
					a[i - 1][j - 1] -= mi * a[k - 1][j - 1];
			}
		}
	}

	for (int j = n; j >= 1; j--)
	{
		int p = w[j - 1];
		if (p != j)
			for (int i = 1; i <= n; i++)
				std::swap(a[i - 1][p - 1], a[i - 1][j - 1]);
	}
}

void Matrix::ReduceToRREF()
{
	int k = 0;
	int l = 0;
	int n = NRows();
	int m = NCols();
	std::vector<int>w(n, 0);

	Matrix &a = (*this);


	while (k <= m && l <= n)
	{
		l++;
		k++;
		double v = 0;
		int p = 0;

		while (v < EPS && l <= n)
		{
			p = k;
			for (int i = k; i <= m; i++)
			{
				if (std::abs(a[i - 1][l - 1]) > v)
				{
					v = std::abs(a[i - 1][l - 1]);
					p = i;
				}
			}
			if (v < EPS)
				l++;
		}

		if (l <= n)
		{
			w[l - 1] = true;
			if (p != k)
				std::swap(a(k), a(p));
			double mi = a[k - 1][l - 1];
			for (int j = l; j <= n; j++)
				a[k - 1][j - 1] /= mi;
			for (int i = 1; i <= m; i++)
			{
				if (i != k)
				{
					mi = a[i - 1][l - 1];
					for (int j = l; j <= n; j++)
						a[i - 1][j - 1] -= mi * a[k - 1][j - 1];
				}
			}
		}
	}

}

Matrix Matrix::RREF(Matrix m)
{
	m.ReduceToRREF();
	return m;
}

int Matrix::Rank() const
{
	int k = 0;
	int l = 0;
	int n = NRows();
	int m = NCols();
	std::vector<int>w(n, 0);

	Matrix a = (*this);

	while (k <= m && l <= n)
	{
		l++;
		k++;
		double v = 0;
		int p = 0;

		while (v < EPS && l <= n)
		{
			p = k;
			for (int i = k; i <= m; i++)
			{
				if (std::abs(a[i - 1][l - 1]) > v)
				{
					v = std::abs(a[i - 1][l - 1]);
					p = i;
				}
			}
			if (v < EPS)
				l++;
		}

		if (l <= n)
		{
			w[l - 1] = true;
			if (p != k)
				std::swap(a(k), a(p));
			double mi = a[k - 1][l - 1];
			for (int j = l; j <= n; j++)
				a[k - 1][j - 1] /= mi;
			for (int i = 1; i <= m; i++)
			{
				if (i != k)
				{
					mi = a[i - 1][l - 1];
					for (int j = l; j <= n; j++)
						a[i - 1][j - 1] -= mi * a[k - 1][j - 1];
				}
			}
		}
	}

	return k - 1;
}

Matrix operator+(const Matrix & m1, const Matrix & m2)
{
	m1.DimSameCheck(m2);
	Matrix m = m1;
	for (int i = 0; i < m1.NRows(); i++)
		for (int j = 0; j < m2.NCols(); j++)
			m[i][j] += m2[i][j];
	return m;
}

Matrix operator-(const Matrix & m1, const Matrix & m2)
{
	m1.DimSameCheck(m2);
	Matrix m = m1;
	for (int i = 0; i < m1.NRows(); i++)
		for (int j = 0; j < m2.NCols(); j++)
			m[i][j] -= m2[i][j];
	return m;
}

Matrix operator*(double s, const Matrix & m)
{
	Matrix ret = m;
	for (int i = 0; i < m.NRows(); i++)
		for (int j = 0; j < m.NCols(); j++)
			ret[i][j] *= s;
	return ret;
}

Matrix operator*(const Matrix & m, double s)
{
	Matrix ret = m;
	for (int i = 0; i < m.NRows(); i++)
		for (int j = 0; j < m.NCols(); j++)
			ret[i][j] *= s;
	return ret;
}

Matrix operator*(const Matrix & m1, const Matrix & m2)
{
	m1.DimCheck(m2);
	Matrix ret(m1.NRows(), m2.NCols());
	for (int i = 0; i < m1.NRows(); i++)
		for (int j = 0; j < m2.NCols(); j++)
			for (int k = 0; k < m1.NCols(); k++)
				ret.mat[i][j] += (m1[i][k] * m2[k][j]);
	return ret;
}

Vector operator*(const Matrix & m, const Vector & v)
{
	m.DimCheck(v);
	Vector ret = Vector(m.NRows());
	for (int i = 0; i < m.NRows(); i++)
		for (int j = 0; j < m.NCols(); j++)
			ret[i] += m[i][j] * v[j];
	return ret;
}

Matrix Transpose(const Matrix & m)
{
	Matrix ret = Matrix(m.NCols(), m.NRows());
	for (int i = 0; i < ret.NRows(); i++)
		for (int j = 0; j < ret.NCols(); j++)
			ret[i][j] = m[j][i];
	return ret;
}

Matrix LeftDiv(Matrix A, Matrix B)
{
	A.SquareCheck();
	A.DimCheck(B);

	int n = A.NRows();
	int m = B.NCols();

	for (int k = 1; k <= n; k++)
	{
		int p = k;
		for (int i = k + 1; i <= n; i++)
			if (std::abs(A[i - 1][k - 1]) > std::abs(A[p - 1][k - 1]))
				p = i;

		if (std::abs(A(p, k)) <= EPS)
			throw std::domain_error("Divisor matrix is singular");

		if (p != k)
		{
			std::swap(A(k), A(p));
			std::swap(B(k), B(p));
		}


		for (int i = k + 1; i <= n; i++)
		{
			double mi = A[i - 1][k - 1] / A[k][k];

			A(i) -= mi * A(k);
			B(i) -= mi * B(k);
		}
	}

	Matrix X = Matrix(n, m);

	for (int k = 1; k <= m; k++)
	{
		for (int i = n; i >= 1; i--)
		{
			double s = B(i, k);
			for (int j = i + 1; j <= n; j++)
				s -= A(i, j) * X(j, k);
			X(i, k) = s / A(i, i);
		}
	}

	return X;
}

Vector LeftDiv(Matrix A, Vector B)
{
	A.SquareCheck();
	A.DimCheck(B);

	int n = A.NRows();
	int m = B.NElems();

	for (int k = 1; k <= n; k++)
	{
		int p = k;
		for (int i = k + 1; i <= n; i++)
			if (std::abs(A(i, k)) > std::abs(A(p, k)))
				p = i;

		if (std::abs(A(p, k)) <= EPS)
			throw std::domain_error("Divisor matrix is singular");

		if (p != k)
		{
			std::swap(A(k), A(p));
			std::swap(B(k), B(p));
		}

		for (int i = k + 1; i <= n; i++)
		{
			double mi = A[i - 1] [k - 1] / A[k - 1] [k - 1];
			A(i) -= mi * A(k);
			B(i) -= mi * B(k);
		}
	}

	Vector X = Vector(n);

	for (int k = 1; k <= m; k++)
	{
		for (int i = n; i >= 1; i--)
		{
			double s = B [i - 1];
			for (int j = i + 1; j <= n; j++)
				s -= A(i, j) * X(j);
			X(i) = s / A[i - 1] [i - 1];
		}
	}

	return X;
}

Matrix operator/(const Matrix & m, double s)
{
	m.CheckZero(s);
	Matrix ret = m;
	for (int i = 0; i < ret.NRows(); i++)
		for (int j = 0; j < ret.NCols(); j++)
			ret[i][j] /= s;
	return ret;
}

Matrix operator/(Matrix A, Matrix B)
{
	B.SquareCheck();
	A.DimCheck(B);

	int n = B.NRows();
	int m = A.NCols();

	for (int k = 1; k <= B.NCols(); k++)
	{
		int p = k;
		for (int i = k + 1; i <= n; i++)
			if (std::abs(B(k, i)) > std::abs(B(k, p)))
				p = i;

		if (std::abs(B(k, p)) <= EPS)
			throw std::domain_error("Divisor matrix is singular");

		if (p != k)
		{
			for (int j = 1; j <= n; j++)
				std::swap(B[j - 1][k - 1], B[j - 1][p - 1]);
			for (int j = 1; j <= A.NRows(); j++)
				std::swap(A[j - 1][k - 1], A[j - 1][p - 1]);
		}

		for (int i = k + 1; i <= B.NCols(); i++)
		{
			double mi = B(k, i) / B(k, k);

			for (int j = 1; j <= B.NRows(); j++)
				B[j - 1][i - 1] -= mi * B[j - 1][k - 1];

			for (int j = 1; j <= A.NRows(); j++)
				A[j - 1][i - 1] -= mi * A[j - 1][k - 1];
		}
	}


	Matrix X = Matrix(A.NRows(), B.NCols());

	for (int k = 1; k <= A.NRows(); k++)
	{
		for (int i = A.NCols(); i >= 1; i--)
		{
			double s = A(k, i);
			for (int j = i + 1; j <= A.NCols(); j++)
				s -= B(j, i) * X(k, j);
			X(k, i) = s / B(i, i);
		}
	}

	return X;
}

double Det(Matrix m)
{
	m.SquareCheck();
	double d = 1;
	int n = m.NRows();

	// Ne oduzimati bodove zbog ovog jer ne pravim novi objekat.
	Matrix& a = m;

	for (int k = 0; k < n; k++)
	{
		int p = k;
		for (int i = k + 1; i < n; i++)
			if (std::abs(a[i][k]) > std::abs(a[p][k]))
				p = i;

		if (std::abs(a[p][k]) < EPS)
			return 0.0;

		if (p != k)
		{
			d *= -1.0;
			std::swap(a(k + 1), a(p + 1));
		}

		for (int i = k + 1; i < n; i++)
		{
			double mi = a[i][k] / a[k][k];
			for (int j = k + 1; j < n; j++)
				a[i][j] -= mi * a[k][j];
		}
	}

	for (int i = 0; i < n; i++)
		d *= a[i][i];

	return d;
}

Matrix Inverse(Matrix m)
{
	m.Invert();
	return m;
}

int Rank(Matrix a)
{
	int k = 0;
	int l = 0;
	int n = a.NRows();
	int m = a.NCols();
	std::vector<int>w(n, 0);

	while (k <= m && l <= n)
	{
		l++;
		k++;
		double v = 0;
		int p = 0;

		while (v < EPS && l <= n)
		{
			p = k;
			for (int i = k; i <= m; i++)
			{
				if (std::abs(a[i - 1][l - 1]) > v)
				{
					v = std::abs(a[i - 1][l - 1]);
					p = i;
				}
			}
			if (v < EPS)
				l++;
		}

		if (l <= n)
		{
			w[l - 1] = true;
			if (p != k)
				std::swap(a(k), a(p));
			double mi = a[k - 1][l - 1];
			for (int j = l; j <= n; j++)
				a[k - 1][j - 1] /= mi;
			for (int i = 1; i <= m; i++)
			{
				if (i != k)
				{
					mi = a[i - 1][l - 1];
					for (int j = l; j <= n; j++)
						a[i - 1][j - 1] -= mi * a[k - 1][j - 1];
				}
			}
		}
	}

	return k - 1;
}

Matrix & Matrix::operator*=(const Matrix & m)
{
	DimCheck(m);
	Matrix ret(NRows(), m.NCols());
	for (int i = 0; i < NRows(); i++)
		for (int j = 0; j < m.NCols(); j++)
			for (int k = 0; k < NCols(); k++)
				ret.mat[i][j] += (mat[i][k] * m[k][j]);
	(*this) = ret;
	return (*this);
}

template<class T>
T fast_pow(const T &base, const T &e, int power)
{
	if (power == 0)
		return e;
	else if (power == 1)
		return base;
	else if (power % 2 == 0)
	{
		T t = fast_pow(base, e, power / 2);
		return t * t;
	}
	else
	{
		return fast_pow(base, e, power - 1) * base;
	}
}

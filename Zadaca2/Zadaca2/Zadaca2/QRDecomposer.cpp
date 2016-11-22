#include "QRDecomposer.h"

#include <cmath>
#include <cstdlib>
#include <algorithm>

Matrix QRDecomposer::GetQ() const
{
	int m = a.NRows();
	int n = a.NCols();
	Matrix q(m, n);

	for (int j = 0; j < m; j++)
	{
		q[j][j] = 1;
		for (int k = n - 1; k > -1; k--)
		{
			double s = 0;
			for (int i = k; i < m; i++)
				s += a[i][k] * q[i][j];
			for (int i = k; i < m; i++)
				q[i][j] -= s * a[i][k];
		}
	}
	return q;
}

Matrix QRDecomposer::GetR() const
{
	Matrix r(a);

	for (int i = 0; i < a.NRows(); i++)
	{
		r[i][i] = d[i];
		for (int j = i + 1; j < a.NCols(); j++)
			r[j][i] = 0.0;
	}
	return r;
}

QRDecomposer::~QRDecomposer()
{
}

QRDecomposer::QRDecomposer(Matrix ma) : a(ma), d(a.NRows())
{
	a.SquareCheck();
	int m = a.NRows();
	int n = a.NCols();

	double mi;

	for (int k = 0; k < n; k++)
	{
		double s = 0;

		for (int i = k; i < m; i++)
			s += (a[i][k] * a[i][k]);

		s = sqrt(s);

		mi = sqrt(s * (s + std::abs(a[k][k])));

		if (a[k][k] < 0.0)
			s = -s;

		a[k][k] = (a[k][k] + s) / mi;

		for (int i = k + 1; i < m; i++)
			a[i][k] /= mi;

		d[k] = -s;

		for (int j = k + 1; j < n; j++)
		{
			s = 0.0;
			for (int i = k; i < m; i++)
				s += a[i][k] * a[i][j];
			for (int i = k; i < m; i++)
				a[i][j] -= s * a[i][k];
		}
	}
}

void QRDecomposer::Solve(const Vector & b, Vector & x) const
{
	x = MulQTWith(b);
	RSolve(x, x);
}

Vector QRDecomposer::Solve(Vector b) const
{
	Vector x(b.NElems());
	Solve(b, x);
	return x;
}

void QRDecomposer::Solve(Matrix & b, Matrix & x) const
{
	int n = b.NRows();
	int m = b.NCols();

	Vector xx(n);
	for (int j = 0; j < m; j++)
	{
		for (int i = 0; i < n; i++)
			xx[i] = b[i][j];
		Solve(xx, xx);
		for (int i = 0; i < n; i++)
			x[i][j] = xx[i];
	}
}

Matrix QRDecomposer::Solve(Matrix b) const
{
	Matrix ret = b;
	Solve(b, ret);
	return ret;
}

void QRDecomposer::RSolve(Vector &b, Vector &x) const
{
	double s = 0;
	int n = a.NRows();

	for (int i = n - 1; i >= 0; i--)
	{
		s = b[i];
		for (int j = i + 1; j < n; j++)
			s -= a[i][j] * x[j];
		x[i] = s / d[i];
	}
}

Vector QRDecomposer::MulQWith(Vector y) const
{
	int n = a.NRows();
	int m = a.NCols();

	for (int k = n - 1; k > -1; k--)
	{
		double s = 0;
		for (int i = k; i < m; i++)
			s += a[i][k] * y[i];
		for (int i = k; i < m; i++)
			y[i] -= s * a[i][k];
	}

	return y;
}

Matrix QRDecomposer::MulQWith(Matrix y) const
{
	int n = a.NRows();
	int m = a.NCols();

	for (int j = 0; j < y.NCols(); j++)
	{
		for (int k = n - 1; k > -1; k--)
		{
			double s = 0;
			for (int i = k; i < y.NRows(); i++)
				s += a[i][k] * y[i] [j];
			for (int i = k; i < y.NRows(); i++)
				y[i][j] -= s * a[i][k];
		}
	}

	return y;
}

Vector QRDecomposer::MulQTWith(Vector y) const
{
	int n = a.NRows();
	int m = a.NCols();

	for (int k = 0; k < n; k++)
	{
		double s = 0;
		for (int i = k; i < m; i++)
			s += a[i][k] * y[i];
		for (int i = k; i < m; i++)
			y[i] -= s * a[i][k];
	}

	return y;
}

Matrix QRDecomposer::MulQTWith(Matrix y) const
{
	int n = a.NRows();

	for (int j = 0; j < y.NCols(); j++)
	{
		for (int k = 0; k < n; k++)
		{
			double s = 0;
			for (int i = k; i < y.NRows(); i++)
				s += a[i][k] * y[i][j];
			for (int i = k; i < y.NRows(); i++)
				y[i][j] -= s * a[i][k];
		}
	}

	return y;
}


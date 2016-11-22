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

// QR dimension check.
// Singular check.
QRDecomposer::QRDecomposer(Matrix ma) : a(ma), d(a.NRows())
{
	QRDimCheck(a);

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

		SingularZeroCheck(mi);

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


// Format check
// QR square check
void QRDecomposer::Solve(const Vector & b, Vector & x) const
{
	a.SquareCheck();
	b.DimCheck(x);
	a.DimCheck(b); // Transitive!!!

	x = MulQTWith(b);
	RSolve(x, x);
}

// Format check
// QR square check
Vector QRDecomposer::Solve(Vector b) const
{
	a.SquareCheck();
	a.DimCheck(b);

	Vector x(b.NElems());
	Solve(b, x);
	return x;
}

// QR Square check
// Format check
void QRDecomposer::Solve(Matrix & b, Matrix & x) const
{
	a.SquareCheck();
	a.DimCheck(b);
	b.DimSameCheck(x);

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

// QR Square check
// Format check
Matrix QRDecomposer::Solve(Matrix b) const
{
	a.SquareCheck();
	a.DimCheck(b);

	Matrix ret = b;
	Solve(b, ret);
	return ret;
}

// Protected method, does not throw any exceptions
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

void QRDecomposer::QRDimCheck(const Matrix &m) const
{
	if (m.NRows() < m.NCols())
		throw std::domain_error("Invalid matrix format");
}

void QRDecomposer::SingularZeroCheck(double x, double Eps) const
{
	if (std::abs(x) < Eps)
		throw std::domain_error("Matrix is singular");
}

// Format check
Vector QRDecomposer::MulQWith(Vector y) const
{
	a.DimCheck(y);

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

// Format check
Matrix QRDecomposer::MulQWith(Matrix y) const
{
	a.DimCheck(y);

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

// Format check
Vector QRDecomposer::MulQTWith(Vector y) const
{
	a.DimCheck(y);

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

// Format check
Matrix QRDecomposer::MulQTWith(Matrix y) const
{
	a.DimCheck(y);

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


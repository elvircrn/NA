#include "QRDecomposer.h"

#include <cmath>
#include <cstdlib>
#include <algorithm>

Matrix QRDecomposer::GetQ() const
{
	int m = v.NRows();
	int n = v.NCols();
	Matrix q(m, n);

	for (int j = 0; j < m; j++)
	{
		q[j][j] = 1;
		for (int k = n - 1; k > -1; k--)
		{
			double s = 0;
			for (int i = k; i < m; i++)
				s += v[i][k] * q[i][j];
			for (int i = k; i < m; i++)
				q[i][j] -= s * v[i][k];
		}
	}
	return q;
}

Matrix QRDecomposer::GetR() const
{
	Matrix r(v.NRows(), v.NRows());
	for (int i = 0; i < v.NRows(); i++)
		r[i][i] = d[i];
	return r;
}

QRDecomposer::~QRDecomposer()
{
}

QRDecomposer::QRDecomposer(Matrix a) : v(a.NRows(), a.NRows()), d(a.NRows())
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

		if (a[k][k] < 0)
			s = -s;

		v[k][k] = (a[k][k] + s) / mi;

		for (int i = k + 1; i < m; i++)
			v[i][k] = a[i][k] / mi;

		d[k] = -s;

		for (int j = k + 1; j < n; j++)
		{
			s = 0.0;
			for (int i = k; i < m; i++)
				s += v[i][k] * a[i][j];
			for (int i = k; i < m; i++)
				a[i][j] -= s * v[i][k];
		}
	}
}

Vector QRDecomposer::MulQWith(Vector y) const
{
	int n = v.NRows();
	int m = v.NCols();

	for (int k = n - 1; k > -1; k--)
	{
		double s = 0;
		for (int i = k; i <= m; i++)
			s += v[i][k] * y[i];
		for (int i = k; i <= m; i++)
			y[i] -= s * v[i][k];
	}

	return y;
}

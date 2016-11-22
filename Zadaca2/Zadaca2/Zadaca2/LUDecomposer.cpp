#include "LUDecomposer.h"

// NOTE: Only used for testing purposes
bool LUDecomposer::operator==(const LUDecomposer & lud) const
{
	return lu == lud.lu;
}

LUDecomposer::~LUDecomposer()
{

}

// Square check.
// Singular check.
LUDecomposer::LUDecomposer(Matrix a) : lu(a), w(a.NRows())
{
	lu.SquareCheck();

	int n = lu.NRows();
	int m = lu.NRows();
	int p = 0;
	double s, sum = 0.0;

	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i <= j; i++)
		{
			sum += std::abs(lu[i][j]);
			s = lu[i][j];
			for (int k = 0; k < i; k++)
				s -= lu[i][k] * lu[k][j];
			lu[i][j] = s;
		}

		p = j;

		for (int i = j + 1; i < n; i++)
		{
			sum += std::abs(lu[i][j]);
			s = lu[i][j];

			for (int k = 0; k <= j - 1; k++)
				s -= lu[i][k] * lu[k][j];
			lu[i][j] = s;
			if (std::abs(s) > std::abs(lu[p][j]))
				p = i;
		}

		if (std::abs(lu[p][j]) < EPS * sum)
			throw std::domain_error("Matrix is singular");

		if (p != j)
			std::swap(lu(j + 1), lu(p + 1));

		w[j] = p;

		double mi = 1 / lu[j][j];
		for (int i = j + 1; i < n; i++)
			lu[i][j] *= mi;
	}
}

/*
Jos ovu noc za njene oci
jos ovu noc za njeno lice
hej sviracu stimaj zice
*/

// Incompatible formats.
void LUDecomposer::Solve(const Vector & b, Vector & x) const
{
	lu.DimCheck(b);
	b.DimCheck(x); // It works, trust me.

	x = b;
	int n = b.NElems();
	Matrix l = GetL();
	Matrix u = GetU();

	for (int i = 0; i < n; i++)
	{
		double s = x[(int)w[i]];
		x[(int)w[i]] = x[i];
		for (int j = 0; j < i; j++)
			s -= l[i][j] * x[j];
		x[i] = s;	
	}

	for (int i = n - 1; i > -1; i--)
	{
		double s = x[i];
		for (int j = i + 1; j < n; j++)
			s -= u[i][j] * x[j];
		x[i] = s / u[i][i];
	}
}

// Incompatible formats.
Vector LUDecomposer::Solve(Vector b) const
{
	lu.DimCheck(b);

	int n = b.NElems();
	Vector y(n);
	Matrix l = GetL();
	Matrix u = GetU();
	Vector x(n);
	double s;
	for (int i = 0; i < n; i++)
	{
		std::swap(b[i], b[(int)w[i]]);
		s = b[i];
		for (int j = 0; j < i; j++)
			s -= l[i][j] * y[j];
		y[i] = s;
	}
	for (int i = n - 1; i > -1; i--)
	{
		s = y[i];
		for (int j = i + 1; j < n; j++)
			s -= u[i][j] * y[j];
		x[i] = s / u[i][i];
	}
	return x;
}

// Incompatible formats.
void LUDecomposer::Solve(Matrix & b, Matrix & x) const
{
	b.ColSameCheck(x);
	lu.DimCheck(b);
	lu.DimCheck(x);

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

// Incompatible formats.
Matrix LUDecomposer::Solve(Matrix b) const
{
	lu.DimCheck(b);
	Matrix ret(b.NRows(), b.NCols());
	Solve(b, ret);
	return ret;
}

Matrix LUDecomposer::GetCompactLU() const
{
	return lu;
}

Matrix LUDecomposer::GetL() const
{
	Matrix l(lu);
	for (int i = 0; i < lu.NRows() - 1; i++)
	{
		l[i][i] = 1.0;
		for (int j = i + 1; j < lu.NCols(); j++)
			l[i][j] = 0.0;
	}
	l[lu.NRows() - 1][lu.NRows() - 1] = 1.0;
	return l;
}

Matrix LUDecomposer::GetU() const
{
	Matrix u(lu);
	for (int i = 0; i < lu.NRows() - 1; i++)
		for (int j = i + 1; j < lu.NCols(); j++)
			u[j][i] = 0.0;
	return u;
}

Vector LUDecomposer::GetPermuation() const
{
	return w;
}

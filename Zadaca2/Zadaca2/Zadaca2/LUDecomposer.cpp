#include "LUDecomposer.h"

bool LUDecomposer::operator==(const LUDecomposer & lud) const
{
	return lu == lud.lu;
}

LUDecomposer::~LUDecomposer()
{

}

LUDecomposer::LUDecomposer(Matrix a) : lu(a)
{
	lu.SquareCheck();

	int n = lu.NRows();
	int m = lu.NRows();
	int p = 0;
	double s;
	std::vector<int>w(n);
	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i <= j; i++)
		{
			s = lu[i][j];
			for (int k = 0; k < i; k++)
				s -= lu[i][k] * lu[k][j];
			lu[i][j] = s;
		}

		p = j;

		for (int i = j + 1; i < n; i++)
		{
			s = lu[i][j];

			for (int k = 0; k <= j - 1; k++)
				s -= lu[i][k] * lu[k][j];
			lu[i][j] = s;
			if (std::abs(s) > std::abs(lu[p][j]))
				p = i;
		}

		if (std::abs(lu[p][j]) < EPS)
			throw std::domain_error("Matrix is singular");
		if (p != j)
			std::swap(lu(j + 1), lu(p + 1));

		w[j] = p;
		double mi = 1 / lu[j][j];
		for (int i = j + 1; i < n; i++)
			lu[i][j] *= mi;
	}
}

Matrix LUDecomposer::GetCompactLU() const
{
	return lu;
}

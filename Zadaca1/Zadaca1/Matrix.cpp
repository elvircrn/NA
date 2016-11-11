#include "Matrix.h"

void Matrix::ListCheck(const std::initializer_list<std::vector<double>> &l) const
{
	if (l.size() == 0)
		return;
	int first = l.begin()->size();
	for (auto item : l)
		if (item.size() != first)
			throw std::logic_error("Bad matrix");
}

void Matrix::RangeCheck(int x, int y) const
{
	if (mat.empty() || mat.size() < x || mat[0].size() < y)
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

void Matrix::DimCheck(const Matrix & m1, const Matrix & m2) const
{
	m1.DimCheck(m2);
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

Matrix::Matrix()
{
}

Matrix::Matrix(int n, int m)
{
	DimCheck(n, m);
	mat.resize(n, std::vector<double>(m, 0));
}

Matrix::Matrix(const Vector & v)
{
	mat.resize(v.NElems(), std::vector<double>(1, 0));
	for (int i = 0; i < v.NElems(); i++)
		mat[i][0] = v[i];
}

Matrix::Matrix(std::initializer_list<std::vector<double>> l)
{
	ListCheck(l);
	mat = l;
}

int Matrix::NRows() const
{
	return mat.size();
}

int Matrix::NCols() const
{
	return mat[0].size();
}

double * Matrix::operator[](int i)
{
	DimCheck(i);
	return mat[i].data();
}

const double * Matrix::operator[](int i) const
{
	DimCheck(i);
	return mat[i].data();
}

double & Matrix::operator()(int i, int j)
{
	DimCheck(i, j);
	return mat[i][j];
}

double Matrix::operator()(int i, int j) const
{
	DimCheck(i, j);
	return mat[i][j];
}

void Matrix::Print(int width) const
{
	for (int i = 0; i < mat.size(); i++, std::putchar('\n'))
		for (int j = 0; j < mat[i].size(); j++)
			std::cout << std::setw(width) << mat[i][j];
}

Matrix & Matrix::operator+=(const Matrix & m)
{
	DimSameCheck(m);
	for (int i = 0; i < m.NRows(); i++)
		for (int j = 0; j < m.NCols(); j++)
			(*this)(i, j) += m[i][j];
	return (*this);
}

Matrix & Matrix::operator-=(const Matrix & m)
{
	DimSameCheck(m);
	for (int i = 0; i < m.NRows(); i++)
		for (int j = 0; j < m.NCols(); j++)
			(*this)(i, j) -= m[i][j];
	return (*this);
}

Matrix & Matrix::operator*=(double s)
{
	for (int i = 0; i < NRows(); i++)
		for (int j = 0; j < NCols(); j++)
			operator()(i, j) *= s;
	return (*this);
}


void Matrix::Transpose()
{
	Matrix help = Matrix(NCols(), NRows());
	for (int i = 0; i < help.NRows(); i++)
		for (int j = 0; j < help.NCols(); j++)
			help(i, j) = operator()(j, i);
	(*this) = help;
}

Matrix::~Matrix()
{
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
				ret.mat[i][j] += (m1(i, k) * m2(k, j));
	return ret;
}

Vector operator*(const Matrix & m, const Vector & v)
{
	m.DimCheck(v);
	return m * v;
}

Matrix Transpose(const Matrix & m)
{
	Matrix ret = Matrix(ret.NCols(), ret.NRows());
	for (int i = 0; i < ret.NRows(); i++)
		for (int j = 0; j < ret.NCols(); j++)
			ret(i, j) = m[j][i];
	return ret;
}

Matrix & Matrix::operator*=(const Matrix & m)
{
	DimCheck(m);
	Matrix ret(NRows(), m.NCols());
	for (int i = 0; i < NRows(); i++)
		for (int j = 0; j < m.NCols(); j++)
			for (int k = 0; k < NCols(); k++)
				ret.mat[i][j] += (operator()(i, k) * m(k, j));
	(*this) = ret;
	return (*this);
}

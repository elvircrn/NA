/*
    Svaka test metoda testira jednu funkcionalnost jedne metode a svaka
    test_exc testira jedan exception jedne metode.
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <functional>
#include <vector>


#include <cmath>
#include <vector>
#include <limits>
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

#include <cmath>

class Matrix
{
protected:
	std::vector<Vector> mat;
	void ListCheck(const std::initializer_list<std::vector<double>>&) const;
	void RangeCheck(int x) const;
	void RangeCheck(int x, int y) const;
	void DimCheck(int, int) const;
	void DimCheck(int) const;
	void DimCheck(const Matrix &m) const;
	void DimCheck(const Matrix &m1, const Matrix &m2) const;
	void DimCheck(const Vector &v1) const;
	void DimSameCheck(const Matrix &m1, const Matrix &m2) const;
	void DimSameCheck(const Matrix &m1) const;
	void CheckZero(double x, double Eps) const;
	void SquareCheck() const;
	void ColSameCheck(const Matrix &m) const;
	void RowSameCheck(const Matrix &m) const;

	// Does not do out of bound check!
	Vector& operator()(int i);
	Vector operator()(int i) const;

	double SumAbs() const;

public:
	Matrix(int m, int n);
	Matrix(const Vector &v);
	Matrix(std::initializer_list<std::vector<double>> l);
	int NRows() const;
	int NCols() const;
	double* operator[](int i);
	const double* operator[](int i) const;
	double &operator()(int i, int j);
	double operator()(int i, int j) const;
	void Print(int width = 10) const;
	friend Matrix operator +(const Matrix &m1, const Matrix &m2);
	Matrix &operator +=(const Matrix &m);
	friend Matrix operator -(const Matrix &m1, const Matrix &m2);
	Matrix &operator -=(const Matrix &m);
	friend Matrix operator *(double s, const Matrix &m);
	friend Matrix operator *(const Matrix &m, double s);
	Matrix &operator *=(double s);
	friend Matrix operator *(const Matrix &m1, const Matrix &m2);
	Matrix &operator *=(const Matrix &m);
	friend Vector operator *(const Matrix &m, const Vector &v);
	friend Matrix Transpose(const Matrix &m);
	void Transpose();

	friend Matrix LeftDiv(Matrix m1, Matrix m2);
	friend Vector LeftDiv(Matrix m, Vector v);
	friend Matrix operator /(const Matrix &m, double s);
	Matrix operator /=(double s);
	friend Matrix operator /(Matrix m1, Matrix m2);
	Matrix operator /=(Matrix m);
	double Det() const;
	friend double Det(Matrix m);
	void Invert();
	friend Matrix Inverse(Matrix m);
	void ReduceToRREF();
	Matrix RREF(Matrix m);
	int Rank() const;
	friend int Rank(Matrix a);

	bool operator==(const Matrix &m) const;
	bool JesuLiJednaki(double x, double y, double Eps) const;

	~Matrix();

	friend class LUDecomposer;
	friend class QRDecomposer;
};

class LUDecomposer
{
protected:
	Matrix lu;
	Vector w;

	bool operator== (const LUDecomposer &lud) const;

public:
	LUDecomposer(Matrix m);
	void Solve(const Vector &b, Vector &x) const;
	Vector Solve(Vector b) const;
	void Solve(Matrix &b, Matrix &x) const;
	Matrix Solve(Matrix b) const;
	Matrix GetCompactLU() const;
	Matrix GetL() const;
	Matrix GetU() const;
	Vector GetPermutation() const;

	~LUDecomposer();
};

class QRDecomposer
{
protected:
	Matrix a;
	Vector d;

	void RSolve(Vector &b, Vector &x) const;
	void QRDimCheck(const Matrix &m) const;
	void QTDimCheck(const Matrix &m) const;
	void QTDimCheck(const Vector &v) const;
	void SingularZeroCheck(double x, double Eps = EPS) const;

public:
	QRDecomposer(Matrix m);
	void Solve(const Vector &b, Vector &x) const;
	Vector Solve(Vector b) const;
	void Solve(Matrix &b, Matrix &x) const;
	Matrix Solve(Matrix b) const;
	Vector MulQWith(Vector v) const;
	Matrix MulQWith(Matrix m) const;
	Vector MulQTWith(Vector v) const;
	Matrix MulQTWith(Matrix m) const;
	Matrix GetQ() const;
	Matrix GetR() const;

	~QRDecomposer();
};



bool test_1()
{
	Matrix AA({ {2, 1, 3}, {2, 6, 8}, {6, 8, 18} });
	Matrix BB({ {1}, {3}, {5} });

	return LeftDiv(AA, BB) == Matrix({ {0.3}, {0.4}, {0.0} });
}

bool test_2()
{
	Matrix AA({ { 2, 1, 3 },{ 2, 6, 8 },{ 6, 8, 18 } });
	Vector BB({ 1, 3, 5 });

	return LeftDiv(AA, BB) == Vector({ 0.3, 0.4, 0.0 });
}

bool test_3()
{
	Matrix A = Matrix({ { -2, -1, 3 }, { 2, 6, 8 }, { 6, 8, 18 } });
	Matrix B = Matrix({ { 10, 3, 5 } });

	return (B / A) == Matrix({ { -2.35, -1.925, 1.525 } });
}

bool test_4()
{
	Matrix mat = { {9, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	return mat.JesuLiJednaki(-24.0, mat.Det(), 1e-12);
}

bool test_5()
{
	Matrix mat = { {9, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	return mat.JesuLiJednaki(-24.0, Det(mat), 1e-12);
}

bool test_6()
{
	Matrix A = Matrix({ { -2, -1, 3 },{ 2, 6, 8 },{ 6, 8, 18 } });
	Matrix B = Matrix({ { 10, 3, 5 } });

	B /= A;

	return B == Matrix({ { -2.35, -1.925, 1.525 } });
}

bool test_7()
{
	Matrix A = Matrix({ { -2, -1, 3 },{ 2, 6, 8 },{ 6, 8, 18 } });

	A.Invert();

	return A == Matrix({ {-0.275, -0.2625, 0.1625},
	{ -0.075, 0.3375, -0.1375 },
	{ 0.125, -0.0625, 0.0625} });
}


bool test_8()
{
	Matrix A = Matrix({ { -2, -1, 3 },{ 2, 6, 8 },{ 6, 8, 18 } });
	return Inverse(A) == Matrix({ { -0.275, -0.2625, 0.1625 },
	{ -0.075, 0.3375, -0.1375 },
	{ 0.125, -0.0625, 0.0625 } });
}


bool test_9()
{
	Matrix m = { {3, 4, 18, 34, 0, 2, 31}, {1, -3, -7, -6, 2, 4, 26}, {2, 1, 7, 16, 3, -1, 27}, {5, 11, 43, 74, 2, 0, 56}, {3, -3, -3, 6, -1, 14, 55}, {-2, 0, -4, -12, 1, 5, 6}, {1, -6, -16, -18, 4, 4, 33} };

	m.ReduceToRREF();

	return m == Matrix(
	{
		{ 1, 0, 2, 6, 0, 0, 7 },
		{ 0,    1,    3,    4,    0,    0,    1 },
		{ 0,    0,    0,    0,    1,    0,    5 },
		{ 0,    0,    0,    0,    0,    1,    3 },
		{ 0,    0,    0,    0,    0,    0,    0 },
		{ 0,    0,    0,    0,    0,    0,    0 },
		{ 0,    0,    0,    0,    0,    0,    0 }
	});
}

bool test_10()
{
	Matrix m = { { 3, 4, 18, 34, 0, 2, 31 },{ 1, -3, -7, -6, 2, 4, 26 },{ 2, 1, 7, 16, 3, -1, 27 },{ 5, 11, 43, 74, 2, 0, 56 },{ 3, -3, -3, 6, -1, 14, 55 },{ -2, 0, -4, -12, 1, 5, 6 },{ 1, -6, -16, -18, 4, 4, 33 } };

	return m.RREF(m) == Matrix(
	{
		{ 1, 0, 2, 6, 0, 0, 7 },
		{ 0,    1,    3,    4,    0,    0,    1 },
		{ 0,    0,    0,    0,    1,    0,    5 },
		{ 0,    0,    0,    0,    0,    1,    3 },
		{ 0,    0,    0,    0,    0,    0,    0 },
		{ 0,    0,    0,    0,    0,    0,    0 },
		{ 0,    0,    0,    0,    0,    0,    0 }
	});
}

bool test_11()
{
	Matrix m = { { 3, 4, 18, 34, 0, 2, 31 },{ 1, -3, -7, -6, 2, 4, 26 },{ 2, 1, 7, 16, 3, -1, 27 },{ 5, 11, 43, 74, 2, 0, 56 },{ 3, -3, -3, 6, -1, 14, 55 },{ -2, 0, -4, -12, 1, 5, 6 },{ 1, -6, -16, -18, 4, 4, 33 } };
	return m.Rank() == 4;
}

bool test_12()
{
	Matrix m = { { 3, 4, 18, 34, 0, 2, 31 },{ 1, -3, -7, -6, 2, 4, 26 },{ 2, 1, 7, 16, 3, -1, 27 },{ 5, 11, 43, 74, 2, 0, 56 },{ 3, -3, -3, 6, -1, 14, 55 },{ -2, 0, -4, -12, 1, 5, 6 },{ 1, -6, -16, -18, 4, 4, 33 } };
	return Rank(m) == 4;
}

bool test_13()
{
	Matrix Z = { { 11,9,24,2 },{ 1,5,2,6 },{ 3,17,18,1 },{ 2,5,7,1 } };
	LUDecomposer d(Z);
	Matrix L = d.GetL();
	Matrix U = d.GetU();
	Vector W = d.GetPermutation();

	Matrix res = L * U;
	for (int i = 0; i < W.NElems(); i++)
		for (int j = 0; j < res.NCols(); j++)
			std::swap(res[i][j], res[(int)W[i]][j]);

	return (Z == res) && (W == Vector({ 0, 2, 2, 3 }));
}

bool test_14()
{
	Matrix Z = { { 1,9,2,2 },{ 1,5,-2,6 },{ 3,7,8,1 },{ 2,5,7,1 } };
	Vector V = { 5,9,2,2 };
	LUDecomposer d(Z);
	Vector X(4);
	d.Solve(V, X);

	return (Inverse(Z) * V) == X;
}

bool test_15()
{
	Matrix Z = { { 1,9,2,2 },{ 1,5,-2,6 },{ 3,7,8,1 },{ 2,5,7,1 } };
	Matrix A = { { 5,9,2,2 },{ -1,5,-2,6 },{ -3,10,8,-1 },{ 2,-5,7,1 } };

	LUDecomposer d(Z);
	Matrix X(Z.NRows(), Z.NCols());

	d.Solve(A, X);

	return (Inverse(Z) * A == X);
}

bool test_16()
{
	Matrix A = Matrix(
	{ {6, 8, 2},
	{5, 7, 4},
	{3, 1,9} }
	);

	QRDecomposer qr = QRDecomposer(A);

	Matrix Q = qr.GetQ();
	Matrix R = qr.GetR();

	Matrix E = Matrix(Q.NRows(), Q.NCols());
	for (int i = 0; i < E.NRows(); i++)
		E[i][i] = 1.0;

	return (Q * R == A) && (Q * Transpose(Q) == E);
}

bool test_17()
{
	Matrix Z = { { 1,9,2,2 },{ 1,5,-2,6 },{ 3,7,8,1 },{ 2,5,7,1 } };
	Vector V = { 5,9,2,2 };
	Vector X(V.NElems());
	QRDecomposer qr = QRDecomposer(Z);

	qr.Solve(V, X);

	return (Inverse(Z) * V == X);
}

bool test_18()
{
	Matrix Z = { { 1,9,2,2 },{ 1,5,-2,6 },{ 3,7,8,1 },{ 2,5,7,1 } };
	Matrix A = { { 5,9,2,2 },{ -1,5,-2,6 },{ -3,10,8,-1 },{ 2,-5,7,1 } };
	Matrix X = A;
	QRDecomposer qr = QRDecomposer(Z);

	qr.Solve(A, X);

	return (Inverse(Z) * A) == X;
}


bool exc_test1()
{
	Matrix singular = { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 9, 10, 11, 12 },{ 13, 14, 15, 16 } };
	Matrix A = { { -1, 2, 0, 1 }, { 4, 5, 1, 2 }, {3, 2, 6, 8 }, {1, 5, 0, 3} };

	putchar('\n');
	putchar('\n');
	try
	{
		(LeftDiv(singular, A)).Print();
	}
	catch (std::domain_error d) { return true; }
	catch (...) { return false; }

	return false;
}

bool exc_test2()
{
	Matrix singular = { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 9, 10, 11, 12 },{ 13, 14, 15, 16 } };
	Matrix A = { { -1, 2, 0, 1 },{ 4, 5, 1, 2 },{ 3, 2, 6, 8 },{ 1, 5, 0, 3 } };

	Vector v = { 1, 4, 2, 1 };
	try
	{
		LeftDiv(singular, v);
	}
	catch (std::domain_error d) { return true; }
	catch (...) { return false; }

	return false;
}

bool exc_test3()
{
	Matrix badFormat = { {4, 5, 12 },{ 3, 2, 8 },{ 1, 0, 3 } };
	Vector v = { 1, 4, 2, 1 };

	try
	{
		LeftDiv(badFormat, v);
	}
	catch (std::domain_error d) { return true; }
	catch (...) { return false; }

	return false;
}

bool exc_test4()
{
	Matrix A = { { 1, 2, 3, 4 }, { 2, 2, 1, 1, } };

	try
	{
		A /= 0.0;
	}
	catch (std::domain_error r) { return true; }
	catch (...) { return false; }

	return false;
}

bool exc_test5()
{
	Matrix singular = { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 9, 10, 11, 12 },{ 13, 14, 15, 16 } };
	Matrix b = { { 1, 2, 3, 4 }, { 3, 3, 3, 3 }, {2, 2, 2, 2}, {8, 1, 2, 4 } };

	try
	{
		b / singular;
	}
	catch (std::domain_error d) { return true; }
	catch (...) { return false; }

	return false;
}

bool exc_test6()
{
	Matrix singular = { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 9, 10, 11, 12 },{ 13, 14, 15, 16 } };

	try
	{
		singular.Invert();
	}
	catch (std::domain_error d) { return true; }
	catch (...) { return false; }

	return false;
}

bool exc_test7()
{
	Matrix singular = { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 9, 10, 11, 12 },{ 13, 14, 15, 16 } };

	try
	{
		Inverse(singular);
	}
	catch (std::domain_error d) { return true; }
	catch (...) { return false; }

	return false;
}

bool exc_test8()
{
	Matrix singular = { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 9, 10, 11, 12 },{ 13, 14, 15, 16 } };

	try
	{
		LUDecomposer lu = LUDecomposer(singular);
	}
	catch (std::domain_error d) { return true; }
	catch (...) { return false; }

	return false;
}

bool exc_test9()
{
	Matrix m = { { 5, 6, 7, 8 },{ 9, 10, 11, 12 },{ 13, 14, 15, 16 } };

	try
	{
		LUDecomposer lu = LUDecomposer(m);
	}
	catch (std::domain_error d) { return true; }
	catch (...) { return false; }

	return false;
}

bool exc_test10()
{
	Vector v3 = { 1, 2, 3 };
	Vector v4 = { 1, 2, 3, 4 };
	Matrix z = { { 1,19,2,2 },{ 1,50,-2,6 },{ 30,7,8,1 },{ 2,5,7,1 } };

	LUDecomposer lu = LUDecomposer(z);

	try
	{
		lu.Solve(v3, v4);
	}
	catch (std::domain_error d) { return true; }
	catch (...) { return false; }

	return false;
}

bool exc_test11()
{
	Vector v3 = { 1, 2, 3 };
	Vector v4 = { 1, 2, 3 };
	Matrix z = { { 1,19,2,2 },{ 1,50,-2,6 },{ 30,7,8,1 },{ 2,5,7,1 } };

	LUDecomposer lu = LUDecomposer(z);

	try
	{
		lu.Solve(v3, v4);
	}
	catch (std::domain_error d) { return true; }
	catch (...) { return false; }

	return false;
}

bool exc_test12()
{
	Vector v3 = { 1, 2, 3 };
	Matrix z = { { 1,19,2,2 },{ 1,50,-2,6 },{ 30,7,8,1 },{ 2,5,7,1 } };

	LUDecomposer lu = LUDecomposer(z);

	try
	{
		lu.Solve(v3);
	}
	catch (std::domain_error d) { return true; }
	catch (...) { return false; }

	return false;
}

bool exc_test13()
{
	Matrix z = { { 1,-19,122,2 },{ 1,50,-2,6 },{ 130,7,8,1 },{ -12,500,7,221 } };
	Matrix a = { { 1,50,-2,6 },{ 130,7,8,1 },{ -12,500,7,221 } };

	LUDecomposer lu = LUDecomposer(z);

	try
	{
		lu.Solve(a);
	}
	catch (std::domain_error d) { return true; }
	catch (...) { return false; }

	return false;
}

bool exc_test14()
{
	Matrix z = { { 1,-19,122,2 },{ 1,50,-2,6 },{ 130,7,8,1 },{ -12,500,7,221 } };
	Matrix a = { { 1,-19,122,2 },{ 1,50,-2,6 },{ 130,7,8,1 },{ -12,500,7,221 } };
	Matrix x(4, 3);

	LUDecomposer lu = LUDecomposer(z);

	try
	{
		lu.Solve(a, x);
	}
	catch (std::domain_error d) { return true; }
	catch (...) { return false; }

	return false;
}

// NRows() > NCols()
bool exc_test15()
{
	Matrix m = { { 1,-19,122,2 },{ 1,50,-2,6 },{ 130,7,8,1 } };

	try
	{
		QRDecomposer qr = QRDecomposer(m);
	}
	catch (std::domain_error d) { return true; }
	catch (...) { return false; }
	return false;
}

bool exc_test16()
{
	Matrix m(4, 4);

	try
	{
		QRDecomposer qr = QRDecomposer(m);
	}
	catch (std::domain_error d) { return true; }
	catch (...) { return false; }
	return false;
}

// QR square check.
bool exc_test17()
{
	Matrix z = { { 1,-19,122,2 },{ 1,50,-2,6 },{ 130,7,8,1 },{ -12,500,7,221 }, {1, 2, 1, 1} };
	QRDecomposer qr(z);
	Vector v{ 1, 2, 3, 4 };
	Vector a(4);

	try
	{
		qr.Solve(v, a);
	}
	catch (std::domain_error e) { return true; }
	catch (...) { return false; }

	return false;
}

// QR square check.
bool exc_test18()
{
	Matrix z = { { 1,-19,122,2 },{ 1,50,-2,6 },{ 130,7,8,1 },{ -12,500,7,221 },{ 1, 2, 1, 1 } };
	QRDecomposer qr(z);
	Vector v{ 1, 2, 3, 4 };
	Vector a(4);

	try
	{
		qr.Solve(v);
	}
	catch (std::domain_error e) { return true; }
	catch (...) { return false; }

	return false;
}

// QR Format check
bool exc_test19()
{
	Matrix z = { { 1,-19,122,2 },{ 1,50,-2,6 },{ 130,7,8,1 },{ -12,500,7,221 },{ 1, 2, 1, 1 } };
	QRDecomposer qr(z);
	Vector v{ 1, 2, 3, 4 };
	Vector a(4);

	try
	{
		qr.Solve(v);
	}
	catch (std::domain_error e) { return true; }
	catch (...) { return false; }

	return false;
}

bool exc_test20()
{
	Matrix z = { { 1,-19,122,2 },{ 1,50,-2,6 },{ 130,7,8,1 },{ -12,500,7,221 },{ 1, 2, 1, 1 } };
	QRDecomposer qr(z);

	Matrix x = { { 1 } };

	try
	{
		qr.MulQTWith(x);
	}
	catch (std::domain_error e) { return true; }
	catch (...) { return false; }

	return false;
}

bool exc_test21()
{
	Matrix z = { { 1,-19,122,2 },{ 1,50,-2,6 },{ 130,7,8,1 },{ -12,500,7,221 },{ 1, 2, 1, 1 } };
	QRDecomposer qr(z);

	Vector x { 1, 2 };

	try
	{
		qr.MulQTWith(x);
	}
	catch (std::domain_error e) { return true; }
	catch (...) { return false; }

	return false;
}

bool exc_test22()
{
	Matrix z = { { 1,-19,122,2 },{ 1,50,-2,6 },{ 130,7,8,1 },{ -12,500,7,221 },{ 1, 2, 1, 1 } };
	QRDecomposer qr(z);

	Matrix x{ { 1, 2 } };

	try
	{
		qr.MulQTWith(x);
	}
	catch (std::domain_error e) { return true; }
	catch (...) { return false; }

	return false;
}

std::vector<std::function<bool()>> tests;
std::vector<std::function<bool()>> exc_tests;

void initTests()
{
	tests.push_back(test_1);
	tests.push_back(test_2);
	tests.push_back(test_3);
	tests.push_back(test_4);
	tests.push_back(test_5);
	tests.push_back(test_6);
	tests.push_back(test_7);
	tests.push_back(test_8);
	tests.push_back(test_9);
	tests.push_back(test_10);
	tests.push_back(test_11);
	tests.push_back(test_12);
	tests.push_back(test_13);
	tests.push_back(test_14);
	tests.push_back(test_15);
	tests.push_back(test_16);
	tests.push_back(test_17);
	tests.push_back(test_18);
}

void initExcTests()
{
	exc_tests.push_back(exc_test1);
	exc_tests.push_back(exc_test2);
	exc_tests.push_back(exc_test3);
	exc_tests.push_back(exc_test4);
	exc_tests.push_back(exc_test5);
	exc_tests.push_back(exc_test6);
	exc_tests.push_back(exc_test7);
	exc_tests.push_back(exc_test8);
	exc_tests.push_back(exc_test9);
	exc_tests.push_back(exc_test10);
	exc_tests.push_back(exc_test11);
	exc_tests.push_back(exc_test12);
	exc_tests.push_back(exc_test13);
	exc_tests.push_back(exc_test14);
	exc_tests.push_back(exc_test15);
	exc_tests.push_back(exc_test16);
	exc_tests.push_back(exc_test17);
	exc_tests.push_back(exc_test18);
	exc_tests.push_back(exc_test19);
	exc_tests.push_back(exc_test20);
	exc_tests.push_back(exc_test21);
	exc_tests.push_back(exc_test22);
}

void runTests()
{
	for (int i = 0; i < (int)tests.size(); i++)
		std::cout << "Test number " << i + 1 << ": " << ((tests[i]()) ? "OK\n" : "BAD\n");
}

void runExcTests()
{
	for (int i = 0; i < (int)exc_tests.size(); i++)
		std::cout << "Exception test number " << i + 1 << ": " << ((exc_tests[i]()) ? "OK\n" : "BAD\n");
}

void test()
{
	initTests();
	initExcTests();
	runTests();
	putchar('\n');
	runExcTests();
}

int main()
{
	test();
	return 0;
}

#include <iostream>

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


#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>

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
	if (mat.empty() || x < 0 || (int)mat.size() <= x)
		throw std::range_error("Invalid index");
}

void Matrix::RangeCheck(int x, int y) const
{
	if (mat.empty() || (int)mat.size() < x || mat[0].NElems() < y)
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

void Matrix::CheckZero(double x, double Eps) const
{
	if (std::abs(x) < Eps)
		throw std::domain_error("Division by zero");
}

// assumes matrix is not empty
void Matrix::SquareCheck() const
{
	if (NCols() != NRows())
		throw std::domain_error("Divisor matrix is singular");
}

void Matrix::ColSameCheck(const Matrix & m) const
{
	if (NCols() != m.NCols())
		throw std::domain_error("Incompatible formats");
}

void Matrix::RowSameCheck(const Matrix & m) const
{
	if (NRows() != m.NRows())
		throw std::domain_error("Incompatible formats");
}

Vector & Matrix::operator()(int i)
{
	return mat[i - 1];
}

Vector Matrix::operator()(int i) const
{
	return mat[i - 1];
}

double Matrix::SumAbs() const
{
	double sum = 0;
	for (int i = 0; i < NRows(); i++)
		for (int j = 0; j < NCols(); j++)
			sum += std::abs(mat[i][j]);
	return sum;
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
	for (int i = 0; i < (int)mat.size(); i++)
	{
		for (int j = 0; j < mat[i].NElems(); j++)
			std::cout << std::setw(width) << mat[i][j];
		if (i < (int)mat.size() - 1)
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
	if (NRows() != m.NRows() || NCols() != m.NCols())
		return false;

	for (int i = 0; i < m.NRows(); i++)
		for (int j = 0; j < m.NCols(); j++)
			if (!JesuLiJednaki(mat[i][j], m[i][j], 1e-12))
				return false;
	return true;
}

bool Matrix::JesuLiJednaki(double x, double y, double Eps) const
{
	if (std::abs(x) < Eps)
		x = 0;
	if (std::abs(y) < Eps)
		y = 0;

	return std::abs(x - y) <= Eps * (std::abs(x) + std::abs(y));
}

Matrix::~Matrix()
{
}

Matrix Matrix::operator/=(double s)
{
	CheckZero(s, EPS);
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

	double sum = B.SumAbs();

	for (int k = 1; k <= B.NCols(); k++)
	{
		int p = k;
		for (int i = k + 1; i <= n; i++)
			if (std::abs(B[k - 1][i - 1]) > std::abs(B[k - 1][p - 1]))
				p = i;

		if (std::abs(B[k - 1][p - 1]) <= EPS * sum)
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
			double s = A[k - 1][i - 1];
			for (int j = i + 1; j <= A.NCols(); j++)
				s -= B[j - 1][i - 1] * X[k - 1][j - 1];
			X[k - 1][i - 1] = s / B[i - 1][i - 1];
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

	double sum = SumAbs();

	for (int k = 0; k < n; k++)
	{
		int p = k;
		for (int i = k + 1; i < n; i++)
			if (std::abs(a[i][k]) > std::abs(a[p][k]))
				p = i;

		if (std::abs(a[p][k]) < EPS * sum)
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

// Square check
void Matrix::Invert()
{
	SquareCheck();

	Matrix& a = (*this); // NOTE: Does not create another matrix!

	int n = NRows();
	std::vector<int>w(n);

	double sum = a.SumAbs();

	for (int k = 1; k <= n; k++)
	{
		int p = k;
		for (int i = k + 1; i <= n; i++)
			if (std::abs(a[i - 1][k - 1]) > std::abs(a[p - 1][k - 1]))
				p = i;

		if (std::abs(a[p - 1][k - 1]) < EPS * sum)
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

	double sum = SumAbs();

	while (k <= m && l <= n)
	{
		l++;
		k++;
		double v = 0;
		int p = 0;

		while (v < EPS * sum && l <= n)
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
			if (v < EPS * sum)
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

	double sum = SumAbs();

	while (k <= m && l <= n)
	{
		l++;
		k++;
		double v = 0;
		int p = 0;

		while (v < EPS * sum && l <= n)
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
			if (v < EPS * sum)
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

// Square check
// Format check
// Singular check
Matrix LeftDiv(Matrix A, Matrix B)
{
	A.SquareCheck();
	A.DimCheck(B);

	int n = A.NRows();
	int m = B.NCols();

	double sum = 0.0;

	for (int k = 1; k <= n; k++)
	{
		int p = k;
		for (int i = k + 1; i <= n; i++)
		{
			sum += std::abs(A[i - 1][k - 1]);
			if (std::abs(A[i - 1][k - 1]) > std::abs(A[p - 1][k - 1]))
				p = i;
		}

		if (std::abs(A[p - 1][k - 1]) <= EPS * sum)
			throw std::domain_error("Divisor matrix is singular");

		if (p != k)
		{
			std::swap(A(k), A(p));
			std::swap(B(k), B(p));
		}

		for (int i = k + 1; i <= n; i++)
		{
			double mi = A[i - 1][k - 1] / A[k - 1][k - 1];

			A(i) -= mi * A(k);
			B(i) -= mi * B(k);
		}
	}

	Matrix X = Matrix(n, m);

	for (int k = 1; k <= m; k++)
	{
		for (int i = n; i >= 1; i--)
		{
			double s = B[i - 1][k - 1];
			for (int j = i + 1; j <= n; j++)
				s -= A[i - 1][j - 1] * X[j - 1][k - 1];
			X[i - 1][k - 1] = s / A[i - 1][i - 1];
		}
	}

	return X;
}

// Square check
// Format check
// Singular check
Vector LeftDiv(Matrix A, Vector B)
{
	A.SquareCheck();
	A.DimCheck(B);

	int n = A.NRows();
	int m = B.NElems();

	double sum = 0.0;

	for (int k = 1; k <= n; k++)
	{
		int p = k;
		for (int i = k + 1; i <= n; i++)
		{
			sum += std::abs(A[i - 1][k - 1]);
			if (std::abs(A[i - 1][k - 1]) > std::abs(A[p - 1][k - 1]))
				p = i;
		}

		if (std::abs(A[p - 1][k - 1]) <= EPS * sum)
			throw std::domain_error("Divisor matrix is singular");

		if (p != k)
		{
			std::swap(A(k), A(p));
			std::swap(B(k), B(p));
		}

		for (int i = k + 1; i <= n; i++)
		{
			double mi = A[i - 1][k - 1] / A[k - 1][k - 1];
			A(i) -= mi * A(k);
			B(i) -= mi * B(k);
		}
	}

	Vector X = Vector(n);

	for (int k = 1; k <= m; k++)
	{
		for (int i = n; i >= 1; i--)
		{
			double s = B[i - 1];
			for (int j = i + 1; j <= n; j++)
				s -= A(i, j) * X(j);
			X(i) = s / A[i - 1][i - 1];
		}
	}

	return X;
}


// Zero check
Matrix operator/(const Matrix & m, double s)
{
	m.CheckZero(s, EPS);
	Matrix ret = m;
	for (int i = 0; i < ret.NRows(); i++)
		for (int j = 0; j < ret.NCols(); j++)
			ret[i][j] /= s;
	return ret;
}

// Format check
// Singular check
// Square check
Matrix operator/(Matrix A, Matrix B)
{
	B.SquareCheck();
	A.DimCheck(B);

	int n = B.NRows();
	int m = A.NCols();

	double sum = 0.0;

	for (int k = 1; k <= B.NCols(); k++)
	{
		int p = k;
		for (int i = k + 1; i <= n; i++)
		{
			sum += std::abs(B[k - 1][i - 1]);
			if (std::abs(B(k, i)) > std::abs(B(k, p)))
				p = i;
		}

		if (std::abs(B(k, p)) <= EPS * sum)
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

// Square check
double Det(Matrix m)
{
	m.SquareCheck();
	double d = 1;
	int n = m.NRows();

	// Ne oduzimati bodove zbog ovog jer ne pravim novi objekat.
	Matrix& a = m;

	double sum = 0.0;

	for (int k = 0; k < n; k++)
	{
		int p = k;
		for (int i = k + 1; i < n; i++)
		{
			if (std::abs(a[i][k]) > std::abs(a[p][k]))
				p = i;
			sum += a[i][k];
		}

		if (std::abs(a[p][k]) < EPS * sum)
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

// Square check
// Singular check
Matrix Inverse(Matrix m)
{
	m.SquareCheck();
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

	double sum = a.SumAbs();

	while (k <= m && l <= n)
	{
		l++;
		k++;
		double v = 0;
		int p = 0;

		while (v < EPS * sum && l <= n)
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
			if (v < EPS * sum)
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
	double s;

	double sum = lu.SumAbs();

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

Vector LUDecomposer::GetPermutation() const
{
	return w;
}



#include <cmath>
#include <cstdlib>
#include <algorithm>

Matrix QRDecomposer::GetQ() const
{
	int m = a.NRows();
	int n = a.NCols();
	Matrix q(m, m);

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

void QRDecomposer::QTDimCheck(const Matrix & m) const
{
	if (a.NRows() != m.NRows())
		throw std::domain_error("Incompatible formats");
}

void QRDecomposer::QTDimCheck(const Vector & v) const
{
	if (a.NRows() != v.NElems())
		throw std::domain_error("Incompatible formats");
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




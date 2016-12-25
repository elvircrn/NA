#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <functional>
#include <vector>

#include "QRDecomposer.h"
#include "LUDecomposer.h"
#include "Matrix.h"
#include "Vector.h"

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

	Vector x{ 1, 2 };

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
	/*
	initTests();
	initExcTests();
	runTests();
	putchar('\n');
	runExcTests();
	*/
	/*
		Matrix m
		{
			{ 0.4 - 1, 0.1, 0.3, 1.0 },
			{ 0.5 - 1, 0.05, 0.25, 1.0 },
			{ 0.05 - 1, 0.45, 0.15, 1.0 },
			{ 0.4 - 1, 0.1, 0.3, 1.0 }
		};*/

		//Matrix m
		//{
		//	{ 0.4 - 1, 0.5, 0.05, 0.4 },
		//	{ 0.1, 0.05 - 1, 0.45, 0.1 },
		//	{ 0.3, 0.25, 0.15 - 1, 0.3 },
		//	{ 1.0, 1.0, 1.0, 1.0 }
		//};

		//QRDecomposer qr(m);
		//Vector v({ 0, 0, 0, 1 });

		//v = qr.Solve(v);

		//std::cout << '\n';

		//for (int i = 0; i < 4; i++, std::cout << "\\\\\n")
		//{
		//	std::cout << v[i] << " &= ";
		//	for (int j = 0; j < 4; j++)
		//		std::cout << m[i][j] << " p(S_" << char('a' + i) << ") ";
		//}

		//for (int i = 0; i < 4; i++)
		//	std::cout << "p(S_" << char('a' + i) << ") &= " << v[i] << '\n';

		//Matrix og
		//{
		//	{ 0.4, 0.1, 0.3, 1.0 },
		//	{ 0.5, 0.05, 0.25, 1.0 },
		//	{ 0.05, 0.45, 0.15, 1.0 },
		//	{ 0.4, 0.1, 0.3, 1.0 }
		//};

		//std::vector<double> H(4, 0.0);

		//std::cout << '\n';

		//for (int i = 0; i < 4; i++)
		//{
		//	for (int j = 0; j < 4; j++)
		//		H[i] += og[i][j] * std::log2(og[i][j]);
		//	H[i] *= -1.0;

		//	std::cout << "H(S_" << i + 1 << ") &= " << H[i] << "\\\\\n";
		//}

		//double hinf = 0.0;
		//for (int i = 0; i < 4; i++)
		//	hinf += v[i] * H[i];

		//std::cout << "hinf = " << hinf << '\n';

		//std::cout << "p(adbbdb) = " << v[0] * og[0][3] * og[3][1] * og[1][1] * og[1][3] * og[3][1] << '\n';
		//	
		//double H1 = 0.0, H4 = 0.0;
		//for (int i = 0; i < 4; i++)
		//	H1 += v[i] * std::log2(v[i]);

		//H1 *= -1.0;
		//std::cout << "H1 = " << H1 << '\n';

		//H4 = H1 + 3 * hinf;

		//std::cout << "H4 = " << H4 << '\n';
	/*
		Matrix m
		{
			{ 0.2 - 1.0, 0.0, 0.3, 0.0 },
			{ 0.8, 0.0 - 1.0, 0.7, 0.0 },
			{ 0.0, 0.6, 0.0 - 1.0, 0.2 },
			{ 1.0, 1.0, 1.0, 1.0 }
		};

		QRDecomposer qr(m);
		Vector v({ 0, 0, 0, 1 });


		std::cout << '\n';

		for (int i = 0; i < 4; i++, std::cout << "\\\\\n")
		{
			std::cout << v[i] << " &= ";
			for (int j = 0; j < 4; j++)
				std::cout << m[i][j] << " p(S_{" << ((i & 2) > 0) << ((i & 1) > 0) << "}) + ";
		}
		v = qr.Solve(v);

		for (int i = 0; i < 4; i++)
			std::cout << "p(S_" << char('a' + i) << ") &= " << v[i] << '\n';

		Matrix og
		{
			{ 0.2, 0.8, 0.0, 0.0 },
			{ 0.0, 0.0, 0.6, 0.4 },
			{ 0.3, 0.7, 0.0, 0.0 },
			{ 0.0, 0.0, 0.2, 0.8 }
		};

		std::vector<double> H(4, 0.0);

		std::cout << '\n';

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				if (og[i][j] > std::numeric_limits<double>::epsilon())
					H[i] += og[i][j] * std::log2(og[i][j]);
			H[i] *= -1.0;

			std::cout << "H(S_{" << ((i & 2) > 0) << ((i & 1) > 0) << "}" << ") &= " << H[i] << "\\\\\n";
		}

		double hinf = 0.0;
		for (int i = 0; i < 4; i++)
			hinf += v[i] * H[i];

		std::cout << "hinf = " << hinf << '\n';

		std::cout << "p(adbbdb) = " << v[0] * og[0][3] * og[3][1] * og[1][1] * og[1][3] * og[3][1] << '\n';

		double H2 = 0.0, H7 = 0.0;
		for (int i = 0; i < 4; i++)
			H2 += v[i] * std::log2(v[i]);
		H2 *= -1.0;

		std::cout << "H1 = " << H2 << '\n';

		H7 = H2 + 6 * hinf;

		std::cout << "H7 = " << H7 << '\n';

		std::cout << "red = " << (2 - hinf) / 2.0 << '\n';

		std::string str = "1110110";

		double pstr = v[3];*/



	Matrix m
	{
		{ 0.4 - 1.0, 0.4, 0.3 },
		{ 0.2, 0.2 - 1.0, 0.1 },
		{ 1.0, 1.0, 1.0 }
	};

	QRDecomposer qr(m);
	Vector v({ 0, 0, 1 });

	std::cout << '\n';

	for (int i = 0; i < 3; i++, std::cout << "\\\\\n")
	{
		std::cout << v[i] << " &= ";
		for (int j = 0; j < 3; j++)
			std::cout << m[i][j] << " p(S_{" << ((i & 2) > 0) << ((i & 1) > 0) << "}) + ";
	}
	v = qr.Solve(v);

	for (int i = 0; i < 3; i++)
		std::cout << "p(S_" << char('a' + i) << ") &= " << v[i] << '\n';

	Matrix og
	{
		{ 0.4, 0.2, 0.4 },
		{ 0.4, 0.2, 0.4 },
		{ 0.3, 0.1, 0.6 }
	};

	std::vector<double> H(3, 0.0);

	std::cout << '\n';

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			if (og[i][j] > std::numeric_limits<double>::epsilon())
				H[i] += og[i][j] * std::log2(og[i][j]);
		H[i] *= -1.0;

		std::cout << "H(S_{" << ((i & 2) > 0) << ((i & 1) > 0) << "}" << ") &= " << H[i] << "\\\\\n";
	}

	double hinf = 0.0;
	for (int i = 0; i < 3; i++)
		hinf += v[i] * H[i];

	std::cout << "hinf = " << hinf << '\n';

	//std::cout << "p(cbbbbcacbccabb) = " << v[0] * og[0][3] * og[3][1] * og[1][1] * og[1][3] * og[3][1] << '\n';
}

int main()
{
	test();
	char c = getchar();
	return 0;
}


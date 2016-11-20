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
	return mat.JesuLiJednaki(-24.0, mat.Det());
}

bool test_5()
{
	Matrix mat = { {9, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	return mat.JesuLiJednaki(-24.0, Det(mat));
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
	Matrix A = { {1, -2, -2, -3}, {3, -9, 0, -9}, {-1, 2, 4, 7}, {-3, -6, 26, 2} };
	Matrix B = { {6, 8, 2}, {3, 7, 4}, {3, 1, 9} };

	LUDecomposer lu = LUDecomposer(A);


	putchar('\n');
	lu.GetCompactLU().Print(); putchar('\n'); putchar('\n');
	lu.GetL().Print(); putchar('\n'); putchar('\n');
	lu.GetU().Print(); putchar('\n'); putchar('\n');
	

	return true;
	
	/*
	return lu.GetCompactLU() == Matrix(

	);
	*/
}

bool test_16()
{
	Matrix A = Matrix(
	{ {6, 8, 2},
	{5, 7, 4},
	{3, 1,9} }
	);

	putchar('\n');
	putchar('\n');
	QRDecomposer qr = QRDecomposer(A);
	qr.GetQ().Print();
	putchar('\n');
	putchar('\n');
	qr.GetR().Print();
	putchar('\n');
	putchar('\n');

	((qr.GetQ()) * (qr.GetR())).Print();

	putchar('\n');
	putchar('\n');
	
	return true;
}


std::vector<std::function<bool()>> tests;

int main()
{
	/*
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
	*/
	tests.push_back(test_16);


	for (int i = 0; i < tests.size(); i++)
		std::cout << "Test number " << i + 1 << ": " << ((tests[i]()) ? "OK\n" : "BAD\n");
	getchar();
	return 0;
}
























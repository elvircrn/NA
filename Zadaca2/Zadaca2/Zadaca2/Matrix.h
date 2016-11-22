#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <cmath>

#include "Vector.h"

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
	Matrix operator /=(Matrix m); //Vidi moze li bolje
	double Det() const;
	friend double Det(Matrix m);
	void Invert();
	friend Matrix Inverse(Matrix m);
	void ReduceToRREF();
	Matrix RREF(Matrix m);
	int Rank() const;
	friend int Rank(Matrix a);

	bool operator==(const Matrix &m) const;
	bool JesuLiJednaki(double x, double y, double Eps = EPS) const;

	~Matrix();

	friend class LUDecomposer;
	friend class QRDecomposer;
};
#endif // !_MATRIX_H_

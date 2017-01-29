#pragma once
#include <iostream>
#include <iomanip>
#include <stdexcept>

#include "Vector.h"
/*
Hej kafano necu vise 
Drug mi nisi bila
Te zena me ispracala
*/

class Matrix
{
protected:
	std::vector<std::vector<double>> mat;
	void ListCheck(const std::initializer_list<std::vector<double>>&) const;
	void RangeCheck(int x, int y) const;
	void DimCheck(int, int) const;
	void DimCheck(int) const;
	void DimCheck(const Matrix &m) const;
	void DimCheck(const Matrix &m1, const Matrix &m2) const;
	void DimSameCheck(const Matrix &m1, const Matrix &m2) const;
	void DimSameCheck(const Matrix &m1) const;

public:
	Matrix();

	Matrix(int m, int n);
	Matrix(const Vector &v);
	Matrix(std::initializer_list<std::vector<double>> l);
	int NRows() const;
	int NCols() const;
	double *operator[](int i);
	const double *operator[](int i) const;
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

	~Matrix();
};


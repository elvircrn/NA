#ifndef _QRDECOMPOSER_H_
#define _QRDECOMPOSER_H_

#include "Vector.h"
#include "Matrix.h"

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

#endif // !_QRDECOMPOSE_H_

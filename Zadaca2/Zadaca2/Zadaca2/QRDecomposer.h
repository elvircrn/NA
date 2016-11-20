#ifndef _QRDECOMPOSER_H_
#define _QRDECOMPOSER_H_

#include "Vector.h"
#include "Matrix.h"

class QRDecomposer
{
	Matrix v;
	Vector d;
public:
	QRDecomposer(Matrix m);
	void Solve(const Vector &b, Vector &x) const; // belaj
	Vector Solve(Vector b) const;
	void Solve(Matrix &b, Matrix &x) const; // belaj
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

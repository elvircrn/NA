#ifndef _LUDECOMPOSER_H_
#define _LUDECOMPOSER_H_

#include "Matrix.h"
#include "Vector.h"

class LUDecomposer
{
	Matrix lu;
public:
	LUDecomposer(Matrix m);
	Matrix Solve(const Vector &b, Vector &x) const; // belaj
	Vector Solve(Vector b) const;
	Matrix Solve(Matrix &b, Matrix &x) const; // belaj
	Matrix Solve(Matrix b) const;
	Matrix GetCompactLU() const;
	Matrix GetL() const;
	Matrix GetU() const;
	Vector GetPermuation() const;

	bool operator== (const LUDecomposer &lud) const;

	~LUDecomposer();
};

#endif // !_LUDECOMPOSER_H_

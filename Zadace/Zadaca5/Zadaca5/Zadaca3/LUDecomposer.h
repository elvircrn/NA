#ifndef _LUDECOMPOSER_H_
#define _LUDECOMPOSER_H_

#include "Matrix.h"
#include "Vector.h"

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

#endif // !_LUDECOMPOSER_H_

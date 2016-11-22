#ifndef _LUDECOMPOSER_H_
#define _LUDECOMPOSER_H_

#include "Matrix.h"
#include "Vector.h"

// TODO: Throw exceptions
class LUDecomposer
{
	Matrix lu;
	std::vector<int> w;
public:
	LUDecomposer(Matrix m);
	void Solve(const Vector &b, Vector &x) const; 
	Vector Solve(Vector b) const;
	void Solve(Matrix &b, Matrix &x) const; 
	Matrix Solve(Matrix b) const;
	Matrix GetCompactLU() const;
	Matrix GetL() const;
	Matrix GetU() const;
	Vector GetPermuation() const;

	bool operator== (const LUDecomposer &lud) const;

	~LUDecomposer();
};

#endif // !_LUDECOMPOSER_H_

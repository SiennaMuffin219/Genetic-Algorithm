#pragma once
#include <iostream>

class Matrix
{
private:
	double* cells;
	unsigned sizex;
	unsigned sizey;
public:
	Matrix();
	Matrix(unsigned, unsigned);
	Matrix(const Matrix&);
	Matrix operator*(const Matrix&);
	Matrix operator~();
	double get(unsigned, unsigned) const;
	void set(unsigned, unsigned, double);
	unsigned getSizex();
	unsigned getSizey();
	void matrixTanh();
	friend std::ostream& operator<<(std::ostream&, const Matrix&);
	virtual ~Matrix();
};
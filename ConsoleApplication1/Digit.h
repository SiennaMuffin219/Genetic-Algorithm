#pragma once

class Digit
{
private:
	int label;
	double* pixels;
	Matrix mPixels;
	unsigned size;
public:
	Digit();
	Digit(int, double*, unsigned);
	Digit(const Digit&);
	virtual ~Digit();
	int getLabel() const;
	void setLabel(int);
	double*& getPixels();
	void createmPixels();
	//double* getPixels();
	Matrix getMatrixPixels() const;
};


#include "pch.h"


void Digit::createmPixels()
{
	mPixels = Matrix(1, size);
	for (unsigned i = 0; i < size; i++)
	{
		mPixels.set(0, i, pixels[i]);
	}
}

Digit::Digit()
{
	pixels = new double[28*28];
	label = 0;
	size = 28*28;
}

Digit::Digit(int l, double* p, unsigned s) : label(l), size(s)
{
	pixels = new double[s];
	mPixels = Matrix(1, s);
	for (unsigned i = 0; i < s; i++)
	{
		pixels[i] = p[i];
		mPixels.set(0, i, p[i]);
	}
}

Digit::Digit(const Digit& other) : Digit(other.label, other.pixels, other.size)
{
}

Digit::~Digit()
{
	delete[] pixels;
}

int Digit::getLabel() const
{
	return label;
}

void Digit::setLabel(int l)
{
	label = l;
}

double*& Digit::getPixels()
{
	return pixels;
}

//double* Digit::getPixels()
//{
//	return pixels;
//}

Matrix Digit::getMatrixPixels() const
{
	return mPixels;
}



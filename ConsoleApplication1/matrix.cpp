#include "pch.h"
#include <cmath>

Matrix::Matrix() : Matrix(0, 0)
{
}

Matrix::Matrix(unsigned x, unsigned y) : sizex(x), sizey(y)
{
	cells = new double[x*y];
}

Matrix::Matrix(const Matrix& other) : Matrix(other.sizex, other.sizey)
{
	//cells = new double[other.sizex * other.sizey];

	for (size_t i = 0; i < other.sizex * other.sizey; i++)
	{
		cells[i] = other.cells[i];
	}
}

Matrix Matrix::operator*(const Matrix& other)
{
	if (sizex != other.sizey)
		throw "A.sizeX != B.sizeY";

	Matrix result(other.sizex, sizey);

	for (size_t i = 0; i < other.sizex; i++)
	{
		for (size_t j = 0; j < sizey; j++)
		{
			double toAdd = 0;
			for (size_t k = 0; k < other.sizey; k++)
			{
				toAdd += other.get(i, k) * get(k, j);
			}
			result.set(i, j, toAdd);
		}
	}

	return result;
}

Matrix Matrix::operator~()
{
	Matrix result(sizey, sizex);

	for (int i = sizey - 1; i >= 0; i--)
	{
		for (size_t j = 0; j < sizex; j++)
		{
			result.set(i, j, get(j, i));
		}
	}

	return result;
}

double Matrix::get(unsigned x, unsigned y) const
{
	if (x < 0 || x >= sizex || y < 0 || y >= sizey)
		throw "Out of bounds";
	return cells[x * sizey + y];
}

void Matrix::set(unsigned x, unsigned y, double value)
{
	if (x < 0 || x >= sizex || y < 0 || y >= sizey)
		throw "Out of bounds";
	cells[x * sizey + y] = value;
}

unsigned Matrix::getSizex()
{
	return sizex;
}

unsigned Matrix::getSizey()
{
	return sizey;
}

void Matrix::matrixTanh()
{
	for (size_t i = 0; i < sizex * sizey; i++)
	{
		cells[i] = tanh(cells[i]);
	}
}

Matrix::~Matrix()
{
	delete[] cells;
	cells = nullptr;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
	for (size_t i = 0; i < m.sizey; i++)
	{
		for (size_t j = 0; j < m.sizex; j++)
		{
			os << m.cells[j * m.sizey + i] << " ";
		}
		os << std::endl;
	}
	return os;
}
#include "pch.h"
#include <random>

static const unsigned genomeShapeData[] = { 28 * 28, 7 * 7, 10, 10 };
const unsigned* Individual::genomeShape = genomeShapeData;
const unsigned Individual::genomeShapeLength = 4;
const unsigned Individual::genomeSize = 28 * 28 * 7 * 7 + 7 * 7 * 10 + 10 * 10;
int Individual::lastId = -1;
bool Individual::incrId = true;

void Individual::createADN()
{
	for (unsigned i = 0; i < genomeSize; i++)
	{
		ADN[i] = (rand() / (double)RAND_MAX) * 2 - 1;
	}
}

void Individual::createGenome()
{
	if (ADN == nullptr)
		createADN();

	genome = new Matrix[genomeShapeLength];

	int index = 0;
	for (unsigned i = 0; i < genomeShapeLength - 1; i++)
	{
		genome[i] = Matrix(genomeShape[i], genomeShape[i + 1]);
		for (unsigned j = 0; j < genomeShape[i + 1]; j++)
		{
			for (unsigned k = 0; k < genomeShape[i]; k++)
			{
				genome[i].set(k, j, ADN[index++]);
			}
		}
	}
}

void Individual::mutate(const Individual& A, const Individual& B)
{
	bool parentA = true;
	int nbCuts = genomeSize / 100;

	for (unsigned i = 0; i < genomeSize; i++)
	{
		if (rand() % nbCuts == 0)
			parentA = !parentA;
		if (rand() % nbCuts == 0)
		{
			ADN[i] = rand() / (double)RAND_MAX * 2 - 1;
		}
		else
		{
			ADN[i] = parentA ? A.ADN[i] : B.ADN[i];
		}
	}
}

Individual::Individual()
{
	if (Individual::incrId)
		id = ++lastId;
	else
		id = lastId;

	ADN = new double[genomeSize];
	createADN();
	createGenome();
	fitness = 0;
}

Individual::Individual(const Individual & other)
{
	id = other.id;

	ADN = new double[genomeSize];
	for (unsigned i = 0; i < genomeSize; i++)
		ADN[i] = other.ADN[i];

	createGenome();
	fitness = other.fitness;
}

Individual::Individual(const Individual& A, const Individual& B)
{
	id = ++lastId;

	ADN = new double[genomeSize];
	mutate(A, B);
	createGenome();
	fitness = 0;
}

Individual Individual::operator=(const Individual& other)
{
	id = other.id;
	//ADN = new double[genomeSize];

	delete[] genome;
	for (unsigned i = 0; i < genomeSize; i++)
		ADN[i] = other.ADN[i];
	//genome = other.genome;
	createGenome();
	fitness = other.fitness;

	return *this;
}

Matrix Individual::getResults(const Matrix& inputs)
{
	Matrix secondMatrix = inputs;

	for (unsigned i = 0; i < genomeShapeLength - 1; i++)
	{
		secondMatrix = genome[i] * secondMatrix;
		secondMatrix.matrixTanh();
	}

	return secondMatrix;
}

int Individual::getId()
{
	return id;
}

int Individual::getFitness()
{
	return fitness;
}

void Individual::setFitness(int fit)
{
	fitness = fit;
}

void Individual::incrementFitness()
{
	fitness++;
}

void Individual::stopId()
{
	Individual::incrId = false;
}

void Individual::backId()
{
	Individual::incrId = true;
}

Individual::~Individual()
{
	delete[] ADN;
	delete[] genome;
}

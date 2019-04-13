#pragma once
class Individual
{
private:
	static const unsigned* genomeShape;
	static const unsigned genomeShapeLength;
	static const unsigned genomeSize;
	static int lastId;
	static bool incrId;

	int id;
	Matrix* genome;
	double* ADN;
	int fitness;

	void createADN();
	void createGenome();
	void mutate(const Individual&, const Individual&);
public:
	Individual();
	Individual(const Individual& other);
	Individual(const Individual& A, const Individual& B);
	Individual operator=(const Individual&);
	Matrix getResults(const Matrix&);
	int getId();
	int getFitness();
	void setFitness(int);
	void incrementFitness();
	static void stopId();
	static void backId();
	virtual ~Individual();
};


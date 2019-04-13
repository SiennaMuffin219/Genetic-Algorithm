#pragma once
#include "Individual.h"

class AG
{
private:
	unsigned popSize;
	unsigned nbTurns;
	Individual* population;
	//void sortPop();
	static void sort(Individual*, unsigned);
public:
	AG(unsigned popSize, unsigned nbTurns);
	void evolve(const Digit*, unsigned);
	virtual ~AG();
};


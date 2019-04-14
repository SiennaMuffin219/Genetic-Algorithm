#pragma once
#include "Individual.h"

#define RST	"\x1B[0m"
#define RED	"\x1B[31m"
#define GRN	"\x1B[32m"
#define YEL	"\x1B[33m"
#define BLU	"\x1B[34m"
#define CONS_COLOR(X) (no_color ? "" : X)

class AG
{
private:
	unsigned popSize;
	unsigned nbTurns;
	Individual* population;
	bool no_color;
	static void sort(Individual*, unsigned);
public:
	AG(unsigned popSize, unsigned nbTurns, bool no_color);
	void evolve(const Digit*, unsigned);
	virtual ~AG();
};


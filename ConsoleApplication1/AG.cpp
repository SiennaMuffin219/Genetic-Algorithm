#include "pch.h"



void AG::sort(Individual* pop, unsigned size) {
	Individual::stopId();
	Individual* sortedPop = new Individual[size];
	int minFitness;
	unsigned minInd;

	for (size_t i = 0; i < size; i++)
	{
		minFitness = INT32_MIN;
		minInd = -1;
		for (unsigned j = 0; j < size; j++)
		{
			if (pop[j].getFitness() > minFitness)
			{
				minFitness = pop[j].getFitness();
				minInd = j;

			}
		}

		sortedPop[i] = pop[minInd];
		pop[minInd].setFitness(INT32_MIN);
	}


	for (size_t i = 0; i < size; i++)
	{
		pop[i] = sortedPop[i];
	}

	delete[] sortedPop;
	Individual::backId();
}

AG::AG(unsigned popSize, unsigned nbTurns, bool no_color) : popSize(popSize), nbTurns(nbTurns), no_color(no_color)
{
	population = new Individual[popSize];
}

void AG::evolve(const Digit* inputs, unsigned inputsSize)
{
	int lastFit = 0;
	for (unsigned turn = 0; turn < nbTurns; turn++)
	{
		std::cout << "Turn " << CONS_COLOR(RED) << turn << CONS_COLOR(RST) << std::endl;
		int meanFit = 0;

		for (unsigned i = 0; i < popSize; i++)
		{
			if (population[i].getFitness() != 0)
			{
				meanFit += population[i].getFitness();
				std::cout << "Already done " << CONS_COLOR(BLU) << population[i].getId() << CONS_COLOR(RST) 
					<< " => fitness = " << CONS_COLOR(GRN) << population[i].getFitness() << CONS_COLOR(RST) << std::endl;
				continue;
			}

			std::cout << "Started individual " << CONS_COLOR(BLU) << population[i].getId() << CONS_COLOR(RST) << "...";

			for (unsigned j = 0; j < inputsSize; j++)
			{
				//int result = static_cast<int>(population[i].getResults(inputs[j].getMatrixPixels()).get(0, 0) * 5 + 5);

				Matrix results = population[i].getResults(inputs[j].getMatrixPixels());

				int result = 0;
				double max = results.get(0, 0);
				for (int i = 1; i < 10; i++)
				{
					double cur = results.get(0, i);
					if (cur > max)
					{
						max = cur;
						result = i;
					}
				}

				if (result == inputs[j].getLabel())
					population[i].incrementFitness();
			}
			std::cout << " Finished" << " => fitness = " << (population[i].getFitness() > lastFit ? CONS_COLOR(GRN) : CONS_COLOR(RED))
				<< population[i].getFitness() << CONS_COLOR(RST) << std::endl;
			meanFit += population[i].getFitness();
		}
		meanFit /= popSize;
		std::cout << "Mean fitness = " << CONS_COLOR(GRN) << meanFit << CONS_COLOR(RST) << std::endl;
		lastFit = meanFit;

		sort(population, popSize);

		unsigned nbKeep = popSize / 4;
		nbKeep = nbKeep != 0 ? nbKeep : 1;

		for (unsigned i = nbKeep; i < popSize; i++)
		{
			int parA = rand() % nbKeep;
			int parB = rand() % nbKeep;
			population[i] = Individual(population[parA], population[parB]);
		}
	}
}

AG::~AG()
{
	delete[] population;
}

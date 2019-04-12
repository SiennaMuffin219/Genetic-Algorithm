#include "pch.h"


void AG::sortPop()
{
	bool sorted;

	for (unsigned i = 0; i < popSize - 1; i++)
	{
		sorted = true;
		for (unsigned j = 0; j < popSize - i - 1; j++)
		{
			if (population[i].getFitness() > population[i + 1].getFitness())
			{
				sorted = false;
				Individual temp = population[i];
				population[i] = population[i + 1];
				population[i + 1] = temp;
			}
		}
		if (sorted)
			break;
	}
}

AG::AG(unsigned popSize, unsigned nbTurns) : popSize(popSize), nbTurns(nbTurns)
{
	population = new Individual[popSize];

	for (unsigned i = 0; i < popSize; i++)
	{
		//population[i] = Individual();
		std::cout << population[i].getId() << std::endl;
	}
}

void AG::evolve(const Digit* inputs, unsigned inputsSize)
{
	for (unsigned turn = 0; turn < nbTurns; turn++)
	{
		std::cout << "Turn #" << turn << std::endl;
		int meanFit = 0;

		for (unsigned i = 0; i < popSize; i++)
		{
			std::cout << "Started individual #" << i << std::endl;

			for (unsigned j = 0; j < inputsSize; j++)
			{
				int result = static_cast<int>(population[i].getResults(inputs[j].getMatrixPixels()).get(0, 0)) * 5 + 5;
				if (result == inputs[j].getLabel())
					population[i].incrementFitness();

				if (j % 100 == 0)
					std::cout << j << " : " << result << " => " << inputs[j].getLabel() << std::endl;
			}
			std::cout << "Finished individual #" << i << " => fitness = " << population[i].getFitness() << std::endl;
			meanFit += population[i].getFitness();
		}
		meanFit /= popSize;
		std::cout << "Mean fitness = " << meanFit << std::endl;

		sortPop();

		unsigned nbKeep = popSize / 2;

		for (unsigned i = 0; i < nbKeep; i++)
		{
			population[i].setFitness(0);
		}

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

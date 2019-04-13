#include "pch.h"


//void AG::sortPop()
//{
//	bool sorted;
//
//	for (unsigned i = 0; i < popSize - 1; i++)
//	{
//		sorted = true;
//		for (unsigned j = 0; j < popSize - i - 1; j++)
//		{
//			if (population[i].getFitness() > population[i + 1].getFitness())
//			{
//				sorted = false;
//				Individual temp = population[i];
//				population[i] = population[i + 1];
//				population[i + 1] = temp;
//			}
//		}
//		if (sorted)
//			break;
//	}
//}

void AG::sort(Individual* pop, int size) {
	Individual* sortedPop = new Individual[size];
	int minFitness;
	int minInd;

	for (size_t i = 0; i < size; i++)
	{
		minFitness = INT32_MIN;
		minInd = -1;
		for (size_t j = 0; j < size; j++)
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
				int result = static_cast<int>(population[i].getResults(inputs[j].getMatrixPixels()).get(0, 0) * 5 + 5);
				if (result == inputs[j].getLabel())
					population[i].incrementFitness();

				//if (j % 100 == 0)
				//	std::cout << j << " : " << result << " => " << inputs[j].getLabel() << std::endl;
			}
			std::cout << "Finished individual #" << i << " => fitness = " << population[i].getFitness() << std::endl;
			meanFit += population[i].getFitness();
		}
		meanFit /= popSize;
		std::cout << "Mean fitness = " << meanFit << std::endl;

		sort(population, popSize);

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

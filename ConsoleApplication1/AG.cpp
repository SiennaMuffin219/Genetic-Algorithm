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

void AG::sort(Individual* pop, unsigned size) {
	Individual::stopId();
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
	Individual::backId();
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
	int lastFit = 0;
	for (unsigned turn = 0; turn < nbTurns; turn++)
	{
		std::cout << "Turn \x1B[31m#" << turn << "\x1B[0m" << std::endl;
		int meanFit = 0;

		for (unsigned i = 0; i < popSize; i++)
		{
			if (population[i].getFitness() != 0)
			{
				meanFit += population[i].getFitness();
				std::cout << "Already done \x1B[34m#" << population[i].getId() << "\x1B[0m => fitness = \x1B[32m" << population[i].getFitness() << "\x1B[0m" << std::endl;
				continue;
			}

			std::cout << "Started individual \x1B[34m#" << population[i].getId() << "\x1B[0m...";

			for (unsigned j = 0; j < inputsSize; j++)
			{
				//int result = static_cast<int>(population[i].getResults(inputs[j].getMatrixPixels()).get(0, 0) * 5 + 5);

				Matrix results = population[i].getResults(inputs[j].getMatrixPixels());

				int result = 0;
				double max = results.get(0, 0);
				for (size_t i = 1; i < 10; i++)
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
			std::cout << " Finished" << " => fitness = " << (population[i].getFitness() > lastFit ? "\x1B[32m" : "\x1B[31m") << population[i].getFitness() << "\x1B[0m" << std::endl;
			meanFit += population[i].getFitness();
		}
		meanFit /= popSize;
		std::cout << "Mean fitness = \x1B[32m" << meanFit << "\x1B[0m" << std::endl;
		lastFit = meanFit;

		sort(population, popSize);

		unsigned nbKeep = popSize / 4;

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

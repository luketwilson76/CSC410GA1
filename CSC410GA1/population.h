#include <cstdlib>
#include <random>
#include <time.h>
#include <iostream>
#include <vector>
#ifndef POPULATION_H
#define POPULATION_H
#include "genome.cpp"

using namespace std;

class population
{
public:
	population()
	{
		individuals = NULL;
		nIndividuals = 0;
	}

	~population()
	{
		deallocate();
	}

	void deallocate()
	{
		if (individuals == NULL && nIndividuals == 0)
		{
			return;
		}
		delete individuals;
		nIndividuals = 0;
	}

	void generate_population(int popSize, int nGenes)
	{
		nIndividuals = popSize;
		nGenesPerGenome = nGenes;

		if (individuals != NULL) 
		{
			deallocate();
			nIndividuals = 0;
		}

		individuals = new genome[popSize];

		for (int i = 0; i < popSize; i++)
		{
			individuals[i].allocate(nGenes);
			individuals[i].randomize();
		}
	}

	//check child by checking rgb values, needs to belong to parent
	void set_target(Pixel target, int imageSize)
	{
		targetGenome = target;
	}

	void select_parents()
	{
		double p1fitness = 0;
		double p2fitness = 0;
		for (int i = 0; i < nIndividuals; i++)
		{
			double fitness = individuals[i].calculate_overall_fitness(targetGenome,nGenesPerGenome);
			if (fitness > p1fitness)
			{
				p2fitness = p1fitness;
				p1fitness = fitness;
				if (i != 0)
				{
					p2 = p1;
				}
				p1 = i;
				continue;
			}
			if (fitness > p2fitness) 
			{
				p2fitness = fitness;
				p2 = i;
			}
		}
	}

	void set_nCrossover(int nCrossover) 
	{
		numCrossOvers = nCrossover;
	}

	void set_mutation(double mRate) 
	{
		mutationRate = mRate;
	}

	void generate_new_population(int useRoulette=1)
	{
		generation += 1;
		for (int i = 0; i < nIndividuals - 2; i++)
		{
			if (i == p1 || p2) 
			{
				continue;
			}
			else{
				int crossover = (rand() % numCrossOvers) + 1;
				for (int j = 0; j < 2; j++) 
				{
					individuals[i].set_red(j, int(individuals[p1].genes[nGenesPerGenome - j + 1].red));
					individuals[i].set_green(j, int(individuals[p1].genes[nGenesPerGenome - j + 1].green));
					individuals[i].set_blue(j, int(individuals[p1].genes[nGenesPerGenome - j + 1].blue));

					individuals[i].set_mRate(mutationRate);
					individuals[i].mutate_gene(j);
				}
				for (int j = 0; j < nGenesPerGenome - 2; j++)
				{
					individuals[i].set_red(nGenesPerGenome - (j + 1), int(individuals[p2].genes[j].red));
					individuals[i].set_green(nGenesPerGenome - (j + 1), int(individuals[p2].genes[j].green));
					individuals[i].set_blue(nGenesPerGenome - (j + 1), int(individuals[p2].genes[j].blue));

					individuals[i].mutate_gene(nGenesPerGenome - j + 1);
					individuals[i];
					cout << endl;
				}
			}
		}
	}

	double calculate_overall_fitness()
	{
		double avgFitness = 0;
		for (int i = 0; i < nIndividuals; i++) 
		{
			avgFitness += individuals[i].calculate_overall_fitness(targetGenome, nGenesPerGenome);
		}
		return avgFitness / nIndividuals;
	}

	void print_parents()
	{
		cout << "parent 1: ";
		individuals[p1].print();
		cout << endl;
		cout << "parent 2: ";
		individuals[p2].print();
		cout << endl;
	}

	void print_population() 
	{
		cout << "generation " << generation << endl;
		for (int i = 0; i < nIndividuals; i++) 
		{
			cout << "Crossover points: " << numCrossOvers << " " << "Mutation Rate: " << mutationRate << " ";
			individuals[i].print();
			cout << endl;
		}
	}

private:
	genome* individuals = NULL;
	int nIndividuals = 0;

	int numCrossOvers = 1;
	double mutationRate;
	int nGenesPerGenome;

	int generation = 0;
	Pixel targetGenome;

	int p1;
	int p2;
};

#endif
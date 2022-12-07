#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

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
		srand((unsigned)time(NULL));
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

	void generate_new_population(int useRoulette=0)
	{
		//stores crossover points
		vector <int> crossoverPoints;

		//store crossover points and make sure there's no duplicates
		for (int i = 0; i < numCrossOvers;i++) 
		{
			int randNum = rand() % (nGenesPerGenome - 0 + 1) + 0;
			while (find(crossoverPoints.begin(), crossoverPoints.end(), randNum) != crossoverPoints.end())
			{
				int randNum = rand() % (nGenesPerGenome - 0 + 1) + 0;
			}
			crossoverPoints.push_back(randNum);
		}
		
		//sort in decending order of crossover points
		sort(crossoverPoints.begin(), crossoverPoints.end());

		
		if (crossoverPoints[numCrossOvers-1] != nGenesPerGenome - 1)
		{
			crossoverPoints.push_back(nGenesPerGenome - 1);
		}
		
		//crossover children
		for (int i = 0; i < nIndividuals / 2; i++) {
			//set children
			int c1 = i;
			int c2 = i + 1;

			//makes sure parents aren't written over in population
			if (i == p1) 
			{
				continue;
			}
			while (c2 == p1 || c2 == p2) 
			{
				c2 += 1;
			}

			//set mutation rate
			individuals[c1].set_mRate(mutationRate);
			individuals[c2].set_mRate(mutationRate);

			for (int j = 0; j < crossoverPoints.size(); j++)
			{
				int startPoint;
				bool flip = false;

				if (j == 0) 
				{
					startPoint = 0;
				}
				else
				{
					startPoint = crossoverPoints[j-1];
				}

				for (int k = startPoint; k < crossoverPoints[j]; k++) 
				{
					if (flip == false) 
					{
						//crossover
						individuals[c1].genes[k] = individuals[p1].genes[k];
						individuals[c2].genes[k] = individuals[p2].genes[k];
						//mutate genes
						individuals[c1].mutate_gene(k);
						individuals[c2].mutate_gene(k);
						//flip crossover points
						bool flip = true;
						continue;
					}
					if (flip == true)
					{
						//crossover
						individuals[c1].genes[k] = individuals[p2].genes[k];
						individuals[c2].genes[k] = individuals[p1].genes[k];
						//mutate genes
						individuals[c1].mutate_gene(k);
						individuals[c2].mutate_gene(k);
						//flip crossover points
						bool flip = false;
						continue;
					}
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
	}

	void print_population() 
	{
		cout << endl;
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

	Pixel targetGenome;

	int p1;
	int p2;
};

#endif
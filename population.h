#include <cstdlib>
#include <random>
#include <iostream>
#include <genome.cpp>

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

	vector<genome> get_pop() 
	{
		return pop;
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
		for (int i = 0; i < popSize; i++)
		{
			genome gene;
			gene.allocate(nGenes);
			gene.randomize();
			pop[i] = gene;
		}
	}

	void set_target(Pixel target, int imageSize)
	{
			targetGenome = target;
			int imageS = imageSize;
	}

	void select_parents() 
	{
		genome g;
		vector <float> fitnesses;
		for (int i = 0; i < nIndividuals; i++)
		{
			fitnesses[i] = float(g.calculate_overall_fitness(targetGenome, imageS));
		}
		float parent1Value = 0.0;
		float parent2Value = 0.0;

		for (int i = 0; i < nIndividuals; i++) 
		{
			if (fitnesses[i] > parent1Value) 
			{
			    parent2Value = parent1Value;
				parent2 = parent1;
				parent1Value = fitnesses[i];
				parent1 = &pop[i];
				continue;
			}
			if (fitnesses[i] > parent2Value) 
			{
				parent2Value = fitnesses[i];
				parent2 = &pop[i];
			}
		}
	}

	void set_nCrossover(int nCrossover=1)
	{
		crossovers = nCrossover;
	}

	int get_nCrossover() 
	{
		return crossovers;
	}

	void set_mutation(double mRate) 
	{
		mutationRate = mRate;
	}

	void generate_new_population(int useRoulette=0)
	{

	}

private:
	genome* parent1;
	genome* parent2;

	genome* individuals;
	int nIndividuals = 0;

	vector<genome> pop;
	Pixel targetGenome;
	int imageS = 0;

	int crossovers = 0;
	double mutationRate;
};

void test_suite()
{
	population Pop;
	Pop.generate_population(4, 1);
	vector<genome> vect = Pop.get_pop();
	vect[1].print();
}

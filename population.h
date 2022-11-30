#include <cstdlib>
#include <random>
#include <iostream>
#include <genome.cpp>
#include <vector>

using namespace std;

class population
{
public:
	population()
	{
		indivduals = NULL;
		nIndivduals = 0;
	}
	~population()
	{
		deallocate();
	}

	void deallocate()
	{
		if (indivduals == NULL && nIndivduals ==0)
		{
			return;
		}
		delete indivduals;
		nIndivduals = 0;
	}

	void generate_population(int popSize, int nGenes) 
	{
		nIndivduals = popSize;
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
		for (int i = 0; i < imageSize; i++) 
		{
			targetGenome[i] = target;
		}
	}

private:

	genome* indivduals = NULL;
	int nIndivduals = 0;
	vector<genome> pop;
	vector<Pixel> targetGenome;
};

void test_suite() 
{

}

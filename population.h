#include <cstdlib>
#include <random>
#include <iostream>
#include <genome.cpp>
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

	}
private:
	genome* indivduals = NULL;
	int nIndivduals = 0;
};

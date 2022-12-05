#include <iostream>
#include <cstdlib>
#include <time.h>
#include "genome.cpp"
#include "population.cpp"


using namespace std;

int main()
{
    srand(time(0));
    population pop;
    pop.deallocate();
    pop.generate_population(3, 3);
    pop.set_target({ 100,100,100 }, 3);
    pop.select_parents();
    pop.print_parents();
    pop.set_mutation(0.5);
   
    pop.generate_new_population();
  
    for (int i = 0; i < 10; i++)
    {
        pop.generate_new_population(1);
        pop.print_population();
    }
    
    return 0;
}
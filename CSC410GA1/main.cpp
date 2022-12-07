#include <iostream>
#include <cstdlib>
#include "genome.cpp"
#include "population.cpp"


using namespace std;

int main()
{
    population pop;
    pop.deallocate();
    pop.generate_population(10, 5);
    pop.set_target({ 100,100,100 }, 5);
    pop.select_parents();
    pop.set_mutation(0.1);
    pop.set_nCrossover(2);
    
    pop.print_population();
    cout << "average fitness: " << pop.calculate_overall_fitness() << endl;
    for (int i = 0; i < 100; i++)
    {
        cout << endl;
        pop.print_parents();
        pop.generate_new_population();
        pop.print_population();
        cout << "average fitness: " << pop.calculate_overall_fitness() << endl;
    }
    
    return 0;
}
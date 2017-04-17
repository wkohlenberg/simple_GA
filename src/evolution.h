#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "fitness.h"
#include "population.h"

#define POPULATION_SIZE     50
#define TOURNAMENT_SIZE     5

// Evolution
class EVOLUTION
{
public:
  int crossover(int **newPop,
                int **pop,
                int index,
                int tournament1,
                int tournament2,
                FITNESS Fitness);
  int tournamentSelection(int **population, FITNESS Fitness);
  int evolve(int **population, FITNESS Fitness);

};

#endif

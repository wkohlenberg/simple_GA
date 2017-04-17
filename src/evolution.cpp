#include <iostream>

#include "evolution.h"

int EVOLUTION::crossover(int **newPop,
              int **pop,
              int index,
              int tournament1,
              int tournament2,
              FITNESS Fitness)
{
  // Get the number of genes
  int solutionLength = Fitness.getSolutionLength(Fitness.getSolution());

  for (int i = 0; i < solutionLength; i++)
  {
    double random = ((double)rand()/RAND_MAX);
    if (random <= 0.5)
    {
      newPop[index][i] = pop[tournament1][i];
    }
    else
    {
      newPop[index][i] = pop[tournament2][i];
    }
  }

  return 0;
}

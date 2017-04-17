#include <iostream>
#include <cstdlib>

#include "population.h"

int **POPULATION::initializePopulation(int individuals, int genes, bool FILL_ZERO)
{
  int **population;

  if (!FILL_ZERO)
  {
    population = (int **) malloc(individuals * sizeof(int *));
    for (int i = 0; i < individuals; i++)
      population[i] = (int *) malloc(genes * sizeof(int));
  }
  else
  {
    population = (int **) calloc(individuals, sizeof(int *));
    for (int i = 0; i < individuals; i++)
      population[i] = (int *) calloc(genes, sizeof(int));
  }


  return population;
}

int POPULATION::createRandomPopulation(int **population, int individuals, int genes)
{
  // Fill the 2d array with random genes
  for (int pop = 0; pop < individuals; pop++)
  {
    for (int gene = 0; gene < genes; gene++)
    {
      population[pop][gene] = rand() % 2;
    }
  }
  return 1;
}

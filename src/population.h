#ifndef POPULATION_H
#define POPULATION_H

#define POPULATION_SIZE     50

class POPULATION
{
public:
  int populationSize;

  int **initializePopulation(int individuals, int genes, bool FILL_ZERO = false);
  int **createRandomPopulation(int **population, int individuals, int genes);
};

#endif

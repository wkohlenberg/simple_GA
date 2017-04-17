#ifndef POPULATION_H
#define POPULATION_H

class POPULATION
{
public:
  int **initializePopulation(int individuals, int genes, bool FILL_ZERO = false);
  int **createRandomPopulation(int **population, int individuals, int genes);
};

#endif

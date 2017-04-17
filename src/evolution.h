#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "fitness.h"

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

};

#endif

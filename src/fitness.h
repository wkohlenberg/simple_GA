#ifndef   FITNESS_H
#define   FITNESS_H

#include <cstring>

class FITNESS
{
public:
  int setSolution(std::string solution);
  std::string getSolution();
  int getSolutionLength(std::string solution);
  int getFitness(int *individual);
  int getFittest(int **pop, int popSize);

private:
  std::string fitnessSolution;
};

#endif

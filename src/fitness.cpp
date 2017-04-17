#include <iostream>
#include <cstring>

#include "fitness.h"

int FITNESS::setSolution(std::string solution)
{
  fitnessSolution = solution;

  return 0;
}

std::string FITNESS::getSolution()
{
  return fitnessSolution;
}

int FITNESS::getSolutionLength(std::string solution)
{
  return solution.length();
}

int FITNESS::getFitness(int *individual)
{
  int fitness = 0;

  // Solution string to array
  int solutionLength = getSolutionLength(getSolution());
  int solution_array[solutionLength];
  for (int i = 0; i < solutionLength; i++)
  {
    solution_array[i] = stoi(fitnessSolution.substr(i, 1), nullptr, 2);
  }

  for (int i = 0; i < solutionLength; i++)
  {
    if (individual[i] == solution_array[i])
    {
      fitness++;
    }
  }

  return fitness;
}

int FITNESS::getFittest(int **pop, int popSize)
{
  int fittestIndividual = 0;
  for (int i = 0; i < popSize; i++)
  {
    if (getFitness(pop[fittestIndividual]) <= getFitness(pop[i]))
      fittestIndividual = i;
  }

  return fittestIndividual;
}

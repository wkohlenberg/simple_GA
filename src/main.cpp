#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include "fitness.h"
#include "evolution.h"
#include "population.h"

// Class Definitions
FITNESS Fitness;
EVOLUTION Evolution;
POPULATION Population;

int main()
{
  int generation = 0;
  int fitness = 0;
  int fittest = 0;
  int geneSize = 0;
  srand(time(NULL));

  // Initialize the solution
  Fitness.setSolution("1111000011110000000000001111000011110000111100000000000011110000");

  // Get geneSize
  geneSize = Fitness.getSolutionLength();

  // Initialize population
  int **population;
  population = Population.initializePopulation(POPULATION_SIZE, geneSize);
  if (!Population.createRandomPopulation(population, POPULATION_SIZE, geneSize))
    return 1; // Exit if random population can not be created

  // Calculate the the fitness of the fittest of the population
  fittest = Fitness.getFittest(population, POPULATION_SIZE);
  fitness = Fitness.getFitness(population[fittest]);
  std::cout << "Gene size: " << geneSize << std::endl;
  while(fitness < geneSize)
  {
    generation++;
    std::cout << "Generation: " << generation
              << "; fitness: " << fitness
              << "; Fittest individu: " << fittest
              << std::endl;

    Evolution.evolve(population, Fitness);

    // Calculate the fitness for the next generation
    fittest = Fitness.getFittest(population, POPULATION_SIZE);
    fitness = Fitness.getFitness(population[fittest]);
  }
  generation++;

  std::cout << "Solution found!" << std::endl;
  std::cout << "Generation: " << generation << std::endl;
  std::cout << "Fitness: " << fitness << std::endl;
  std::cout << "Genes: ";

  int fittestIndividual = Fitness.getFittest(population, POPULATION_SIZE);
  for (int i = 0; i < geneSize; i++)
    std::cout << population[fittestIndividual][i];

  std::cout << std::endl;

  return 0;
}

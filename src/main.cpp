#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include "fitness.h"
#include "evolution.h"
#include "population.h"
#include "cmdline.h"

// Class Definitions
FITNESS Fitness;
EVOLUTION Evolution;
POPULATION Population;
cmdoptions_t CMDoptions;

int main(int argc, char *argv[])
{
  int generation = 0;
  int fitness = 0;
  int fittest = 0;
  int geneSize = 0;
  srand(time(NULL));

  CMDLINE Cmdline (argc, argv);
  Cmdline.parseCommandLine(&CMDoptions);
  std::cout << std::endl << std::endl;

  Population.populationSize = CMDoptions.populationSize;

  // Initialize the solution
  Fitness.setSolution("1111000011110000000000001111000011110000111100000000000011110000");

  // Get geneSize
  geneSize = Fitness.getSolutionLength();

  // Initialize population
  int **population;
  population = Population.initializePopulation(Population.populationSize, geneSize);
  Population.createRandomPopulation(population, Population.populationSize, geneSize);

  // Calculate the the fitness of the fittest of the population
  fittest = Fitness.getFittest(population, Population.populationSize);
  fitness = Fitness.getFitness(population[fittest]);
  std::cout << "Gene size: " << geneSize << std::endl;
  while(fitness < geneSize)
  {
    generation++;
    std::cout << "Generation: " << generation
              << "; fitness: " << fitness
              << "; Fittest individu: " << fittest
              << std::endl;

    Evolution.evolve(population, Population.populationSize ,Fitness);

    // Calculate the fitness for the next generation
    fittest = Fitness.getFittest(population, Population.populationSize);
    fitness = Fitness.getFitness(population[fittest]);
  }
  generation++;

  std::cout << "Solution found!" << std::endl;
  std::cout << "Generation: " << generation << std::endl;
  std::cout << "Fitness: " << fitness << std::endl;
  std::cout << "Genes: ";

  int fittestIndividual = Fitness.getFittest(population, Population.populationSize);
  for (int i = 0; i < geneSize; i++)
    std::cout << population[fittestIndividual][i];

  std::cout << std::endl;

  return 0;
}

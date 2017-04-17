#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include "fitness.h"
#include "evolution.h"

// Class Definitions
FITNESS Fitness;
EVOLUTION Evolution;

int main(int argc, char *argv[])
{
  int generation = 0;
  int fitness = 0;
  int fittest = 0;
  int geneSize = 0;
  srand(time(NULL));

  // Check for arguments and print the arguments in the console
  std::cout << "Number of arguments: " << argc << std::endl;
  std::cout << "Arguments: ";
  for (int i = 0; i < argc; i++)
    std::cout << argv[i] << " ";
  std::cout << std::endl << std::endl;

  // Initialize the solution
  Fitness.setSolution("1111000011110000000000001111000011110000111100000000000011110000");

  // Get geneSize
  geneSize = Fitness.getSolutionLength();

  // Initialize population
  int **population;
  population = (int **) malloc(POPULATION_SIZE * sizeof(int *));
  for (int i = 0; i < POPULATION_SIZE; i++)
    population[i] = (int *) malloc(geneSize * sizeof(int));

  // Generate population
  for (int pop = 0; pop < POPULATION_SIZE; pop++)
  {
    for (int gene = 0; gene < geneSize; gene++)
    {
      population[pop][gene] = rand() % 2;
    }
  }

  // Calculate the the fitness of the fittest of the population
  fittest = Fitness.getFittest(population, POPULATION_SIZE);
  fitness = Fitness.getFitness(population[fittest]);
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

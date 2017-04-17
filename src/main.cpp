#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include "fitness.h"
#include "evolution.h"

// Definitions
#define POPULATION_SIZE     50
#define GENE_SIZE           64
#define TOURNAMENT_SIZE     5

// Class Definitions
FITNESS Fitness;
EVOLUTION Evolution;

// Function tournament selection
// Chooses 5 random individuals and selects the fittest
int tournamentSelection(int **population)
{
  int fittest = 0;
  int individu[TOURNAMENT_SIZE] = {0, 0, 0, 0, 0};

  // Initialize tournament population
  int **tournamentPop = (int **) malloc(TOURNAMENT_SIZE * sizeof(int *));
  for (int i = 0; i < TOURNAMENT_SIZE; i++)
    tournamentPop[i] = (int *) malloc(GENE_SIZE * sizeof(int));

  for (int i = 0; i < TOURNAMENT_SIZE; i++)
  {
    for (int j = 0; j < GENE_SIZE; j++)
    {
      tournamentPop[i][j] = 0;
    }
  }

  // Copy random individuals to tournament population
  for (int i = 0; i < TOURNAMENT_SIZE; i++)
  {
    double random = ((double)rand() / RAND_MAX);
    int randomId = (int)(random * POPULATION_SIZE);
    individu[i] = randomId;
    for (int j = 0; j < GENE_SIZE; j++)
    {
      tournamentPop[i][j] = population[randomId][j];
    }
  }

  fittest = Fitness.getFittest(tournamentPop, TOURNAMENT_SIZE);

  return individu[fittest];
}

// Evolve population
// The fittest of the population is copied to the new generation
// The others individuals are created by parents
// Mutate some random genes of the individuals
int evolve(int **population)
{
  // Initialize the new populism
  int **newPop = (int **) calloc(POPULATION_SIZE, sizeof(int *));
  for (int i = 0; i < POPULATION_SIZE; i++)
    newPop[i] = (int *) calloc(GENE_SIZE, sizeof(int));

  // Copy the fittest to the first position
  int fittestIndividual = Fitness.getFittest(population, POPULATION_SIZE);
  for (int i = 0; i < GENE_SIZE; i++)
  {
    newPop[0][i] = population[fittestIndividual][i];
  }

  // Select parents and let them pair
  for (int index = 0; index < POPULATION_SIZE; index++)
  {
    int firstTournament = tournamentSelection(population);
    int secondTournament = tournamentSelection(population);
    Evolution.crossover(newPop, population, index, firstTournament, secondTournament, Fitness);
  }

  // Mutate genes
  for (int i = 0; i < POPULATION_SIZE; i++)
  {
    for (int j = 0; j < GENE_SIZE; j++)
    {
      double random = ((double)rand() / RAND_MAX);
      if (random <= 0.015)      // Just a chosen number to change a small percentage of the genes
      {
        newPop[i][j] = (rand() % 2);
      }
    }
  }

  // Copy the evolved population to the population
  for (int i = 0; i < POPULATION_SIZE; i++)
  {
    for (int j = 0; j < GENE_SIZE; j++)
    {
      population[i][j] = newPop[i][j];
    }
  }

  return 0;
}

int main()
{
  int generation = 0;
  int fitness = 0;
  int fittest = 0;
  srand(time(NULL));

  // Initialize the solution
  Fitness.setSolution("1111000011110000000000001111000011110000111100000000000011110000");

  // Initialize population
  int **population;
  population = (int **) malloc(POPULATION_SIZE * sizeof(int *));
  for (int i = 0; i < POPULATION_SIZE; i++)
    population[i] = (int *) malloc(GENE_SIZE * sizeof(int));

  // Generate population
  for (int pop = 0; pop < POPULATION_SIZE; pop++)
  {
    for (int gene = 0; gene < GENE_SIZE; gene++)
    {
      population[pop][gene] = rand() % 2;
    }
  }

  // Calculate the the fitness of the fittest of the population
  fittest = Fitness.getFittest(population, POPULATION_SIZE);
  fitness = Fitness.getFitness(population[fittest]);
  while(fitness < GENE_SIZE)
  {
    generation++;
    std::cout << "Generation: " << generation
              << "; fitness: " << fitness
              << "; Fittest individu: " << fittest
              << std::endl;

    evolve(population);

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
  for (int i = 0; i < GENE_SIZE; i++)
    std::cout << population[fittestIndividual][i];

  std::cout << std::endl;

  return 0;
}

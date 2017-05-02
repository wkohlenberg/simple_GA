#include <iostream>

#include "evolution.h"
#include "population.h"

int EVOLUTION::crossover(int **newPop,
              int **pop,
              int index,
              int tournament1,
              int tournament2,
              FITNESS Fitness)
{
  // Get the number of genes
  int solutionLength = Fitness.getSolutionLength();

  for (int i = 0; i < solutionLength; i++)
  {
    double random = ((double)rand()/RAND_MAX);
    if (random <= 0.5)
    {
      newPop[index][i] = pop[tournament1][i];
    }
    else
    {
      newPop[index][i] = pop[tournament2][i];
    }
  }

  return 0;
}

// Function tournament selection
// Chooses 5 random individuals and selects the fittest
int EVOLUTION::tournamentSelection(int **population, int populationSize, FITNESS Fitness)
{
  int fittest = 0;
  int geneSize = 0;
  int individu[TOURNAMENT_SIZE] = {0, 0, 0, 0, 0};

  // Get gene size
  geneSize = Fitness.getSolutionLength();

  // Initialize tournament population
  POPULATION Population;
  int **tournamentPop = Population.initializePopulation(TOURNAMENT_SIZE, geneSize, true); // True for calloc use

  for (int i = 0; i < TOURNAMENT_SIZE; i++)
  {
    for (int j = 0; j < geneSize; j++)
    {
      tournamentPop[i][j] = 0;
    }
  }

  // Copy random individuals to tournament population
  for (int i = 0; i < TOURNAMENT_SIZE; i++)
  {
    double random = ((double)rand() / RAND_MAX);
    int randomId = (int)(random * populationSize);
    individu[i] = randomId;
    for (int j = 0; j < geneSize; j++)
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
int EVOLUTION::evolve(int **population, int populationSize, FITNESS Fitness)
{
  int geneSize = 0;

  // Get gene size
  geneSize = Fitness.getSolutionLength();

  // Initialize the new population
  POPULATION Population;
  int **newPop = Population.initializePopulation(populationSize, geneSize);


  // Copy the fittest to the first position
  int fittestIndividual = Fitness.getFittest(population, populationSize);
  for (int i = 0; i < geneSize; i++)
  {
    newPop[0][i] = population[fittestIndividual][i];
  }

  // Select parents and let them pair
  for (int index = 0; index < populationSize; index++)
  {
    int firstTournament = tournamentSelection(population, populationSize, Fitness);
    int secondTournament = tournamentSelection(population, populationSize, Fitness);
    crossover(newPop, population, index, firstTournament, secondTournament, Fitness);
  }

  // Mutate genes
  for (int i = 0; i < populationSize; i++)
  {
    for (int j = 0; j < geneSize; j++)
    {
      double random = ((double)rand() / RAND_MAX);
      if (random <= 0.015)      // Just a chosen number to change a small percentage of the genes
      {
        newPop[i][j] = (rand() % 2);
      }
    }
  }

  // Copy the evolved population to the population
  for (int i = 0; i < populationSize; i++)
  {
    for (int j = 0; j < geneSize; j++)
    {
      population[i][j] = newPop[i][j];
    }
  }

  return 0;
}

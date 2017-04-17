#include <iostream>

#include "evolution.h"

int EVOLUTION::crossover(int **newPop,
              int **pop,
              int index,
              int tournament1,
              int tournament2,
              FITNESS Fitness)
{
  // Get the number of genes
  int solutionLength = Fitness.getSolutionLength(Fitness.getSolution());

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
int EVOLUTION::tournamentSelection(int **population, FITNESS Fitness)
{
  int fittest = 0;
  int geneSize = 0;
  int individu[TOURNAMENT_SIZE] = {0, 0, 0, 0, 0};

  // Get gene size
  geneSize = Fitness.getSolutionLength(Fitness.getSolution());

  // Initialize tournament population
  int **tournamentPop = (int **) malloc(TOURNAMENT_SIZE * sizeof(int *));
  for (int i = 0; i < TOURNAMENT_SIZE; i++)
    tournamentPop[i] = (int *) malloc(geneSize * sizeof(int));

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
    int randomId = (int)(random * POPULATION_SIZE);
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
int EVOLUTION::evolve(int **population, FITNESS Fitness)
{
  int geneSize = 0;

  // Get gene size
  geneSize = Fitness.getSolutionLength(Fitness.getSolution());

  // Initialize the new populism
  int **newPop = (int **) calloc(POPULATION_SIZE, sizeof(int *));
  for (int i = 0; i < POPULATION_SIZE; i++)
    newPop[i] = (int *) calloc(geneSize, sizeof(int));

  // Copy the fittest to the first position
  int fittestIndividual = Fitness.getFittest(population, POPULATION_SIZE);
  for (int i = 0; i < geneSize; i++)
  {
    newPop[0][i] = population[fittestIndividual][i];
  }

  // Select parents and let them pair
  for (int index = 0; index < POPULATION_SIZE; index++)
  {
    int firstTournament = tournamentSelection(population, Fitness);
    int secondTournament = tournamentSelection(population, Fitness);
    crossover(newPop, population, index, firstTournament, secondTournament, Fitness);
  }

  // Mutate genes
  for (int i = 0; i < POPULATION_SIZE; i++)
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
  for (int i = 0; i < POPULATION_SIZE; i++)
  {
    for (int j = 0; j < geneSize; j++)
    {
      population[i][j] = newPop[i][j];
    }
  }

  return 0;
}
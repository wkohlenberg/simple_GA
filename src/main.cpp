#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#define POPULATION_SIZE     50
#define GENE_SIZE           64
#define TOURNAMENT_SIZE     5

std::string solution = "1111000011110000000000001111000011110000111100000000000011110000";

int getFitness(int individual[GENE_SIZE])
{
  int fitness = 0;

  // Solution string to array
  int solutionLength = solution.length();
  int solution_array[solutionLength];
  for (int i = 0; i < solutionLength; i++)
  {
    solution_array[i] = stoi(solution.substr(i, 1), nullptr, 2);
  }

  for (int i = 0; (i < GENE_SIZE) && (i < solutionLength); i++)
  {
    if (individual[i] == solution_array[i])
    {
      fitness++;
    }
  }

  return fitness;
}

int getFittest(int pop[][GENE_SIZE], int popSize)
{
  int fittestIndividual = 0;
  for (int i = 0; i < popSize; i++)
  {
    if (getFitness(pop[fittestIndividual]) <= getFitness(pop[i]))
      fittestIndividual = i;
  }

  return fittestIndividual;
}


int tournamentSelection(int population[][GENE_SIZE])
{
  int fittest = 0;
  int individu[TOURNAMENT_SIZE] = {0, 0, 0, 0, 0};

  // Init tournament population
  int tournamentPop[TOURNAMENT_SIZE][GENE_SIZE];
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

  fittest = getFittest(tournamentPop, TOURNAMENT_SIZE);

  return individu[fittest];
}

int crossover(int (&newPop)[POPULATION_SIZE][GENE_SIZE],
              int pop[POPULATION_SIZE][GENE_SIZE],
              int index, int tournament1,
              int tournament2)
{
  for (int i = 0; i < GENE_SIZE; i++)
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


// Evolve population
int evolve(int (&population)[POPULATION_SIZE][GENE_SIZE])
{
  // Init the new populism
  int newPop[POPULATION_SIZE][GENE_SIZE];

  // Copy the fittest to the first position
  int fittestIndividual = getFittest(population, POPULATION_SIZE);
  for (int i = 0; i < GENE_SIZE; i++)
  {
    newPop[0][i] = population[fittestIndividual][i];
  }

  // Loop tournament
  for (int index = 0; index < POPULATION_SIZE; index++)
  {
    int firstTournament = tournamentSelection(population);
    int secondTournament = tournamentSelection(population);
    crossover(newPop, population, index, firstTournament, secondTournament);
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

  int population[POPULATION_SIZE][GENE_SIZE];

  // Generate population
  for (int pop = 0; pop < POPULATION_SIZE; pop++)
  {
    for (int gene = 0; gene < GENE_SIZE; gene++)
    {
      population[pop][gene] = rand() % 2;
    }
  }

  // Calculate the the fitness of the fittest of the population
  fittest = getFittest(population, POPULATION_SIZE);
  fitness = getFitness(population[fittest]);
  while(fitness < GENE_SIZE)
  {
    generation++;
    std::cout << "Generation: " << generation
              << "; fitness: " << fitness
              << "; Fittest inidividu: " << fittest
              << std::endl;

    evolve(population);

    // Calculate the fitness for the next generation
    fittest = getFittest(population, POPULATION_SIZE);
    fitness = getFitness(population[fittest]);
  }
  generation++;

  std::cout << "Solution found!" << std::endl;
  std::cout << "Generation: " << generation << std::endl;
  std::cout << "Fitness: " << fitness << std::endl;
  std::cout << "Genes: ";

  int fittestIndividual = getFittest(population, POPULATION_SIZE);
  for (int i = 0; i < GENE_SIZE; i++)
    std::cout << population[fittestIndividual][i];

  std::cout << std::endl;

  return 0;
}

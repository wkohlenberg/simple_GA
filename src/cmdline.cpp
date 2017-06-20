#include <iostream>

#include "cmdline.h"

CMDLINE::CMDLINE(int argC, char **argV)
{
  argc = argC;
  for (int i = 0; i < argc; i++)
    argv[i] = argV[i];
}

int CMDLINE::help()
{
  std::cout << "Simple genetic algorithm:\nThis is a simple implementation of the genetic algorithm. The goal is to find " << std::endl;
  std::cout << "the (optimal) solution. The solution is by default or given by the user. " << std::endl;
  std::cout << "Normaly, the solution depends on the evolution of individuals of the population." << std::endl;
  std::cout << "But in this case the evelution of the individuals continiuos until an individual" << std::endl;
  std::cout << "has the same gene string as the solution. This results in a different number of " << std::endl;
  std::cout << "generations every time the programm executes." << std::endl << std::endl;
  std::cout << "Version: 0.1.0.0" << std::endl;
  std::cout << std::endl;
  std::cout << "Usage: genalg [OPTIONS]" << std::endl;
  std::cout << std::endl;
  std::cout << "Options: " << std::endl;
  std::cout << "  --population, -p\tSelect the size of the population [default: 50]." << std::endl;
  std::cout << "  --solution, -s\tSet a solution [default: 1111000011110000000000001111000" << std::endl;
  std::cout << "\t\t\t011110000111100000000000011110000]" << std::endl;
  std::cout << "  --version, -v\t\tDisplay the software version" << std::endl;
  std::cout << "  --help, -h, -?\tShow help" << std::endl;

  exit(0);

  return 0;
}

int CMDLINE::version()
{
  std::cout << "Simple genetic algorithm" << std::endl;
  std::cout << "Version: 0.1.0.0" << std::endl;

  exit(0);

  return 0;
}

int CMDLINE::parseCommandLine(cmdoptions_t *CMDoptions)
{
  // Set default values for cmd options
  CMDoptions->populationSize = 50;
  strcpy(CMDoptions->solution,
          "1111000011110000000000001111000011110000111100000000000011110000");

  for (int i = 0; i < argc; i++)
  {
    char *option = argv[i];
    if ((strcmp(option, "--help") == 0)
        || (strcmp(option, "-h") == 0)
        || (strcmp(option, "-?") == 0))
    {
        help();
    }
    else if ((strcmp(option, "--version") == 0)
          || (strcmp(option, "-v") == 0))
    {
      version();
    }
    else if ((strcmp(option, "--population") == 0)
          || (strcmp(option, "-p") == 0))
    {
      // give a population size (the number of individuals)
      sscanf(argv[++i], "%d", &CMDoptions->populationSize);
    }
    else if ((strcmp(option, "--solution") == 0)
          || (strcmp(option, "-s") == 0))
    {
      // Give the solution
      strcpy(CMDoptions->solution, argv[++i]);
    }
  }

  return 0;
}

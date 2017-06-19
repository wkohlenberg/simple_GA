#include <iostream>
#include <cstring>

#include "cmdline.h"

CMDLINE::CMDLINE(int argC, char **argV)
{
  argc = argC;
  for (int i = 0; i < argc; i++)
    argv[i] = argV[i];
}

int CMDLINE::help()
{
  std::cout << "This is a simple implementation of the genetic algorithm." << std::endl;
               version();
  std::cout << std::endl;
  std::cout << "Usage: main [OPTIONS]" << std::endl;
  std::cout << std::endl;
  std::cout << "Options: " << std::endl;
  std::cout << "  --population, -p\tSelect the size of the population [default: 50]." << std::endl;
  std::cout << "  --genes, -g\t\tSelect the gene size of the individu [default: 64]" << std::endl;
  std::cout << "  --version, -v\t\tDisplay the software version" << std::endl;
  std::cout << "  --help, -h, -?\tShow help" << std::endl;

  exit(0);

  return 0;
}

int CMDLINE::version()
{
  std::cout << "Version: no version numbering yet." << std::endl;
  return 0;
}

int CMDLINE::parseCommandLine(cmdoptions_t *CMDoptions)
{
  // Set default values for cmd options
  CMDoptions->populationSize = 50;
  CMDoptions->geneSize = 64;

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
    else if ((strcmp(option, "--genes") == 0)
          || (strcmp(option, "-g") == 0))
    {
      // Give a gene size of the individual
      sscanf(argv[++i], "%d", &CMDoptions->geneSize);
    }
  }

  return 0;
}

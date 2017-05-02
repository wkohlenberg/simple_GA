#ifndef CMDLINE_H
#define CMDLINE_H

typedef struct cmdOptions{
  int populationSize;
  int geneSize;
}cmdoptions_t;

class CMDLINE
{
  int argc;
  char *argv[];
public:
  CMDLINE (int, char**);    // Constructor
  int parseCommandLine(cmdoptions_t *CMDoptions);

private:
  // Function like help and version
  int help();
  int version();
};

#endif

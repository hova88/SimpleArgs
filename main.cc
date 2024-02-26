#include <stdio.h>

#include "utils/parser.h"
#include "utils/args.h"


int main(int argc, char** argv) {
  utils::ArgsParser parser(argc, argv);

  if (utils::HasHelp(argc, argv)) {
    parser.Help();
  }

  parser.Print(parser.verbosity);
  
  return 0;
}

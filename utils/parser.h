#pragma once 

#include "utils/args.h"

namespace utils {

class ArgsParser : public ArgsBase<ArgsParser> {
public:
  int verbosity;
  Path log;
  float f_value;
  bool if_flag;

  ArgsParser(int argc, char* argv[]) {
    InitAndParse(argc, argv);
  }

  template <class Visitor>
  void ForEach(const Visitor& visitor) {

    visitor(verbosity, "verbosity", 1,
        "Show verbose developer information\n   0 = only print help"
        "output\n   1 = both print help and paraments\n  Default = 1.",
        1);

    visitor(log, "log", Path{"/tmp/log.txt"}, "A string/Path variable for testing", 1);

    visitor(f_value, "f_value", 1.0f, "A float value for testing", 1);

    visitor(if_flag, "if_flag", true, "A bool value for testing", 1);

  }
};

} // namespace utils


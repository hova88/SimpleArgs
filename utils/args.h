#pragma once

#include <stdio.h>
#include <string>
#include <algorithm> // std::transform


namespace utils {

struct Path {
  std::string path;

  Path& operator=(const char* other) {
    path = other;
    return *this;
  }

  std::string Shortened() const {
    constexpr size_t max_len = 48;
    constexpr size_t cut_point = max_len / 2 - 5;
    if (path.size() > max_len) {
      return std::string(begin(path), begin(path) + cut_point) + " ... " +
             std::string(end(path) - cut_point, end(path));
    }
    if (path.empty()) return "[no path specified]";
    return path;
  }

};

template <class Args>
class ArgsBase {
  struct InitVisitor {
    template <typename T>
    void operator()(T& t, const char* /*name*/, const T& init, 
                    const char* /*help*/, int /*print_verbosity*/ = 0) const {
      t = init;
    }
  };

  struct HelpVisitor {
    template <typename T>
    void operator()(T&, const char* name, T /*init*/, const char* help,
                    int /*print_verbosity*/ = 0) const {
      fprintf(stderr, "  --%-20s %s\n", name, help);
    }
  };

  class PrintVisitor {
    public:
      explicit PrintVisitor( int verbosity) : verbosity_(verbosity) {}

      template <typename T>
      void operator()(const T& t, const char* name, const T& /*init*/, 
                      const char* /*help*/, int print_verbosity) const {
        if (verbosity_ >= print_verbosity) {
          fprintf(stderr, "%-30s: %s\n", name, std::to_string(t).c_str());
        }
      }

      void operator()(const std::string& t, const char* name,
                      const std::string& /*init*/, const char* /*help*/,
                      int print_verbosity) const {
        if (verbosity_ >= print_verbosity) {
          fprintf(stderr, "%-30s: %s\n", name, t.c_str());
        }
      }

      void operator()(const Path& t, const char* name, const Path& /*init*/,
                      const char* /*help*/, int print_verbosity) const {
        if (verbosity_ >= print_verbosity) {
          fprintf(stderr, "%-30s: %s\n", name, t.Shortened().c_str());
        }
      }

    private:
      int verbosity_;
  };

  class ParseVisitor {
    public:
      ParseVisitor(int argc, char* argv[]) : argc_(argc), argv_(argv) {}

      template <typename T>
      void operator()(T& t, const char* name, const T& /*init*/,
                      const char* /*help*/, int /*print_verbosity*/ = 0) const {
        const std::string prefixed = std::string("--") + name;
        for (int i = 1; i < argc_; ++i) {
          if (std::string(argv_[i]) == prefixed) {
            if (i + 1 < argc_) {
              if (!SetValue(argv_[i + 1], t)) {
                fprintf(stderr, "Invalid value for %s: %s\n", name, argv_[i + 1]);
              }
            } else {
              fprintf(stderr, "Missing value for %s\n", name);
            }
          } 
        }
      }
    private:
      int argc_;
      char** argv_;

      // Returns false if an invalid value is detected
      static bool SetValue(const char* string, int& t) {
        t = std::stoi(string);
        return true;
      }

      static bool SetValue(const char* string, float& t) {
        t = std::stof(string);
        return true;
      }

      static bool SetValue(const char* string, std::string& t) {
        t = string;
        return true;
      }

      static bool SetValue(const char* string, Path& t) {
        t.path = string;
        return true;
      }

      static bool  SetValue(const char* string, bool& t) {
        std::string value(string);
        // Lower-case. Arg names are expected to be ASCII-only
        std::transform(value.begin(), value.end(), value.begin(), [](char c) {
          return 'A' <= c && c <= 'Z' ? c - ('Z' - 'z') : c;
        });

        if (value == "true" || value == "on" || value == "1") {
          t = true;
          return true;
        } else if (value == "false" || value == "off" || value == "0") {
          t = false;
          return true;
        } else {
          return false;
        }
      }
  };

  template <class Visitor>
  void ForEach(Visitor& visitor) {
    static_cast<Args*>(this)->ForEach(visitor);
  }



public:
  void Init() {
    InitVisitor visitor;
    ForEach(visitor);
  }

  void Help() {
    HelpVisitor visitor;
    ForEach(visitor);
  }

  void Print(int verbosity = 0) {
    PrintVisitor visitor(verbosity);
    ForEach(visitor);
  }

  void Parse(int argc, char* argv[]) {
    ParseVisitor visitor(argc, argv);
    ForEach(visitor);
  }

  // For convenience,  enables single-line constructor.
  void InitAndParse(int argc, char* argv[]) {
    Init();
    Parse(argc, argv);
  }
};

static bool HasHelp(int argc, char* argv[]){
  if (argc == 1) {
    // no arguments - print help
    return true;
  }

  for (int i = 1; i < argc; ++i) {
    if (std::string(argv[i]) == "--help") {
      return true;
    }
  }
  return false;
}

} // namespace utils


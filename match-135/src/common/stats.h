#include <iostream>
#include "common/state.h"

#ifdef STATS
#define ENABLE(x) x
#else
#define ENABLE(x)
#endif

struct Stats {
  Stats() {
    ENABLE(
      std::cerr << "@0\n";
    )
  }

  ~Stats() {
    ENABLE(
      std::cerr << "@1\n";
    )
  }

  void log(const State& state) const {
    ENABLE(
      std::cerr << "@S ";
      std::cerr << state.get_stats();
      std::cerr << "\n";
    )
  }

  void log_invalid(const State& state) const {
    ENABLE(
      std::cerr << "@I ";
      std::cerr << state.get_stats();
      std::cerr << "\n";
    )
  }

private:
};


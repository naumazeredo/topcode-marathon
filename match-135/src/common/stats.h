#include <chrono>
#include <iostream>
#include "common/state.h"

#ifdef STATS
#define ENABLE(x) x
#else
#define ENABLE(x)
#endif

const int PRINT_TIME_IN_MS = 1'000;
const int MAX_PROGRAM_TIME_IN_MS = 9'500;

struct Stats {
  std::chrono::high_resolution_clock::time_point program_start_time;
  std::chrono::high_resolution_clock::time_point last_print_time;

  Stats() {
    program_start_time = std::chrono::high_resolution_clock::now();
    last_print_time = program_start_time;

    ENABLE(
      std::cerr << "@0\n";
    )
  }

  ~Stats() {
    ENABLE(
      std::cerr << "@1\n";
    )

    auto now = std::chrono::high_resolution_clock::now();
    std::cerr <<
      "Submitting best result... " <<
      std::chrono::duration_cast<std::chrono::milliseconds>(now - program_start_time).count() / 1000.0 <<
      " s" <<
      std::endl;
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

  bool should_end_search() {
    auto now = std::chrono::high_resolution_clock::now();

    auto last_print_duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(now - last_print_time);

    if (last_print_duration.count() > PRINT_TIME_IN_MS) {
      std::cerr <<
        "Calculating... " <<
        std::chrono::duration_cast<std::chrono::seconds>(now - program_start_time).count() <<
        "s\n";

      last_print_time = now;
    }

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - program_start_time);
    return duration.count() >= MAX_PROGRAM_TIME_IN_MS;
  }
};


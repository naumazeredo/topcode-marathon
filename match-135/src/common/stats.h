#include <chrono>
#include <iostream>
#include "common/state.h"

const int PRINT_TIME_IN_MS = 1'000;
const int MAX_PROGRAM_TIME_IN_MS = 9'500;

struct VarStat {
  int min = 0;
  int max = 0;
  int sum = 0;

  void process(int value) {
    min = std::min(min, value);
    max = std::max(max, value);
    sum += value;
  }

  friend std::ostream& operator<<(std::ostream& out, const VarStat& stat) {
    out << stat.min << "/" << stat.max << "/" << stat.sum;
    return out;
  }
};

struct CaseStats {
  int     state_count = 0;
  VarStat depth;
  VarStat branching;
  VarStat closed_score;
  VarStat open_score;
  VarStat component_size;
  VarStat component_count;

  void add_state(const State& state) {
    StateStats stats = state.get_stats();

    state_count += 1;
    depth.process(stats.depth);
    branching.process(stats.branching);
    closed_score.process(stats.closed_score);
    open_score.process(stats.open_score);
    component_size.process(stats.component_size);
    component_count.process(stats.component_count);
  }

  friend std::ostream& operator<<(std::ostream& out, const CaseStats& stats) {
    out <<
      "========= Stats ========="                   << "\n" <<
      "State count     : " << stats.state_count     << "\n" <<
      "Depth           : " << stats.depth           << "\n" <<
      "Branching       : " << stats.branching       << "\n" <<
      "Closed Score    : " << stats.closed_score    << "\n" <<
      "Open Score      : " << stats.open_score      << "\n" <<
      "Component Size  : " << stats.component_size  << "\n" <<
      "Component Count : " << stats.component_count << "\n" <<
      "=========================";

    return out;
  }
};

struct Stats {
  std::chrono::high_resolution_clock::time_point program_start_time;
  std::chrono::high_resolution_clock::time_point last_print_time;
  CaseStats case_stats;

  Stats() {
    program_start_time = std::chrono::high_resolution_clock::now();
    last_print_time = program_start_time;
  }

  ~Stats() {
    auto now = std::chrono::high_resolution_clock::now();
    std::cerr <<
      "Submitting ... " <<
      std::chrono::duration_cast<std::chrono::milliseconds>(now - program_start_time).count() / 1000.0 <<
      "s\n\n";

    std::cerr << case_stats << "\n\n";
  }

  void add_state(const State& state) {
    case_stats.add_state(state);
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


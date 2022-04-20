#include <chrono>
#include <iostream>

static const int PRINT_TIME_IN_MS = 500;
static const int MAX_PROGRAM_TIME_IN_MS = 9'750;

struct State;

struct StateStats {
  int depth;
  int branching;
  int closed_score;
  int open_score;
  int component_size;
  int component_count;

  StateStats(const State& state);

  friend std::ostream& operator<<(std::ostream& out, const StateStats& stats);
  friend std::istream& operator>>(std::istream& in, StateStats& stats);
};

struct VarStat {
  int min = 0;
  int max = 0;
  int sum = 0;

  void process(int value);
  friend std::ostream& operator<<(std::ostream& out, const VarStat& stat);
};

struct CaseStats {
  int     state_count = 0;
  VarStat depth;
  VarStat branching;
  VarStat closed_score;
  VarStat open_score;
  VarStat component_size;
  VarStat component_count;

  void add_state(const State& state);

  friend std::ostream& operator<<(std::ostream& out, const CaseStats& stats);
};

struct Stats {
  std::chrono::high_resolution_clock::time_point program_start_time;
  std::chrono::high_resolution_clock::time_point last_print_time;
  CaseStats case_stats;

  Stats();
  ~Stats();

  void add_state(const State& state);
  bool should_end_search();
};


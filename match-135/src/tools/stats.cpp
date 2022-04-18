#include <algorithm>
#include <iostream>
#include "common/state.h"

struct VarStat {
  int min = 0;
  int max = 0;
  int sum = 0;

  void process(int value) {
    min = std::min(min, value);
    max = std::max(max, value);
    sum += value;
  }
};

struct TestStats {
  int state_count = 0;
  int invalid_state_count = 0;

  VarStat depth;
  VarStat branching;
  VarStat closed_score;
  VarStat open_score;
  VarStat component_size;
  VarStat component_count;

  bool process_line() {
    char char_code;
    std::cin >> char_code;

    if (char_code != '@')
      return false;

    char log_type;
    std::cin >> log_type;

    if (log_type != 'S' and log_type != 'I')
      return false;

    StateStats stats;
    std::cin >> stats;

    state_count += 1;
    invalid_state_count += (log_type == 'I');

    depth.process(stats.depth);
    branching.process(stats.branching);
    closed_score.process(stats.closed_score);
    open_score.process(stats.open_score);
    component_size.process(stats.component_size);
    component_count.process(stats.component_count);

    return true;
  }

  void process() {
  }
};

/*
struct FullStats {
}:
*/

int main() {
  TestStats test_stats;

  return 0;
}

#include "common/state.h"
#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& out, const StateStats& stats) {
  out << stats.depth           << " ";
  out << stats.branching       << " ";
  out << stats.closed_score    << " ";
  out << stats.open_score      << " ";
  out << stats.component_size  << " ";
  out << stats.component_count << " ";
  return out;
}

std::istream& operator>>(std::istream& in, StateStats& stats) {
  in >> stats.depth;
  in >> stats.branching;
  in >> stats.closed_score;
  in >> stats.open_score;
  in >> stats.component_size;
  in >> stats.component_count;
  return in;
}

StateStats State::get_stats() const {
  return StateStats {
    .depth           = row,
    .branching       = 0,
    .closed_score    = 0,
    .open_score      = 0,
    .component_size  = 0,
    .component_count = 0
  };
}

State::State(int i, int n)
  : row(i), bridges_from_above(n, 0)
{}

State::State(int i, std::vector<int> _bridges_from_above)
  : row(i), bridges_from_above(std::move(_bridges_from_above))
{}

std::ostream& operator<<(std::ostream& out, const State& state) {
  out << state.row << ": [";
  for(int i: state.bridges_from_above) {
    out << i << ", ";
  }
  out << "]" << std::endl;

  return out;
}

bool State::operator<(const State& s) const {
  return row < s.row;
}

#pragma once

#include <iostream>
#include <vector>

struct StateStats {
  int depth;
  int branching;
  int closed_score;
  int open_score;
  int component_size;
  int component_count;

  friend std::ostream& operator<<(std::ostream& out, const StateStats& stats) {
    out << stats.depth           << " ";
    out << stats.branching       << " ";
    out << stats.closed_score    << " ";
    out << stats.open_score      << " ";
    out << stats.component_size  << " ";
    out << stats.component_count << " ";
    return out;
  }

  friend std::istream& operator>>(std::istream& in, StateStats& stats) {
    in >> stats.depth;
    in >> stats.branching;
    in >> stats.closed_score;
    in >> stats.open_score;
    in >> stats.component_size;
    in >> stats.component_count;
    return in;
  }
};

struct State {
  int row;
  std::vector<int> bridges_from_above;

  State(int i, int n)
    : row(i), bridges_from_above(n, 0)
  {}

  State(int i, std::vector<int> _bridges_from_above)
    : row(i), bridges_from_above(std::move(_bridges_from_above))
  {}

  State(const State& state) = default;
  State(State&& state) = default;

  StateStats get_stats() const {
    return StateStats {
      .depth           = row,
      .branching       = 0,
      .closed_score    = 0,
      .open_score      = 0,
      .component_size  = 0,
      .component_count = 0
    };
  }

  friend std::ostream& operator<<(std::ostream& out, const State& state) {
    out << state.row << ": ";
    for(int i: state.bridges_from_above) {
      out << i << ", ";
    }
    out << std::endl;

    return out;
  }
};



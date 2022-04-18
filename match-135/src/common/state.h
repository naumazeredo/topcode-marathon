#pragma once

#include <iostream>

struct StateStats {
  int depth;
  int branching;
  int closed_score;
  int open_score;
  int component_size;
  int component_count;
};

struct State {
  StateStats get_stats() const {
    return StateStats {
      .depth           = 1,
      .branching       = 2,
      .closed_score    = 3,
      .open_score      = 4,
      .component_size  = 5,
      .component_count = 6
    };
  }
};

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

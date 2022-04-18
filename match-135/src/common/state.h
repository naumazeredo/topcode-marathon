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

  friend std::ostream& operator<<(std::ostream& out, const StateStats& stats);
  friend std::istream& operator>>(std::istream& in, StateStats& stats);
};

struct State {
  int row;
  std::vector<int> bridges_from_above;

  State(int i, int n);
  State(int i, std::vector<int> _bridges_from_above);
  State(const State& state) = default;
  State(State&& state) = default;

  StateStats get_stats() const;

  friend std::ostream& operator<<(std::ostream& out, const State& state);
};

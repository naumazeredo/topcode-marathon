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
  State* parent_state;
  std::vector<int> bridges_from_above;

  State(int i, int n, State* parent_state);
  State(int i, std::vector<int> _bridges_from_above, State* parent_state);
  State(const State& state) = default;
  State(State&& state) = default;

  State& operator=(const State&) = default;
  State& operator=(State&&) = default;

  StateStats get_stats() const;

  friend std::ostream& operator<<(std::ostream& out, const State& state);
  bool operator<(const State& s) const;
};

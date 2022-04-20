#pragma once

#include <iostream>
#include <vector>

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

  friend std::ostream& operator<<(std::ostream& out, const State& state);
  bool operator<(const State& s) const;
};

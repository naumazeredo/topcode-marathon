#include "common/state.h"
#include <iostream>
#include <vector>

State::State(int i, int n, State* parent_state)
  : row(i), bridges_from_above(n, 0), parent_state(parent_state)
{}

State::State(int i, std::vector<int> _bridges_from_above, State* parentState)
  : row(i), bridges_from_above(std::move(_bridges_from_above)), parent_state(parent_state)
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

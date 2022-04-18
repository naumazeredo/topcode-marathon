#pragma once

#include <bits/stdc++.h>
using namespace std;

struct State {
  int row_id;
  vector<int> bridges_from_above;
  
  State(int i, int n): row_id(i) { bridges_from_above.assign(n, 0); }
  State(State* state): row_id(state->row_id) { 
    for (int i = 0; i < bridges_from_above.size(); i++) {
      bridges_from_above[i] = state->bridges_from_above[i];
    }
  }
  State(int i, const vector<int>& _bridges_from_above): State(i, _bridges_from_above.size()) {
    bridges_from_above = _bridges_from_above;
  }
};


std::ostream& operator<<(std::ostream& out, const State& state) {
  out << state.row_id << ": ";
  for(int i: state.bridges_from_above) {
    out << i << ", ";
  }
  out << endl;

  return out;
}
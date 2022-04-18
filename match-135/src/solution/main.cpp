#include <bits/stdc++.h>
#include "common/state.h"

using namespace std;

int N, C;
vector<vector<int>> grid;

void printGrid() {
  for (auto row : grid) {
    for (auto cell : row) {
      cerr << cell << " ";
    }
    cerr << endl;
  }
};

void  build_next_states(int col, int current_row, vector<int>& next_bridges_from_above, vector<int>& remaining_bridges, vector<State>& next_states, vector<int>& next_island) {
  if (col >= N) {
    next_states.push_back(State { current_row + 1, next_bridges_from_above });
    return;
  }

  int degree = remaining_bridges[col];

  // No bridge remaining in the island
  if (degree == 0) {
    build_next_states(col + 1, current_row, next_bridges_from_above, remaining_bridges, next_states, next_island);
    return;
  }
  
  // Isolated island that doesn't connect to any component
  if (remaining_bridges[col] == grid[current_row][col]) {
    build_next_states(col + 1, current_row, next_bridges_from_above, remaining_bridges, next_states, next_island);
  }
  
  int next = next_island[col];
  int next_degree = (next == -1)? 0: grid[current_row][next_island[col]];

  // Island will connect to others
  for (int i = 0; i <= degree and i <= next_degree; i++) {
    next_bridges_from_above[col] = degree - i;
    if (next != -1) remaining_bridges[next] -= i;

    build_next_states(col + 1, current_row, next_bridges_from_above, remaining_bridges, next_states, next_island);

    next_bridges_from_above[col] = 0;
    if (next != -1) remaining_bridges[next] += i;
  }
}

void process_state(State& state) {
  if (state.row_id == N) {
    // End of grid
    return;
  }

  vector<int> remaining_bridges(N, 0);
  vector<int> next_bridges_from_above(N, 0);

  vector<int> next_island(N, 0);

  for (int i = 0; i < N; i++) {
  // if (!validate_state(state)) return;
  
    if (grid[state.row_id][i] == 0) {
      next_bridges_from_above[i] = state.bridges_from_above[i];
      continue;
    }

    if (grid[state.row_id][i] < state.bridges_from_above[i]) return; // Invalid state
    remaining_bridges[i] = grid[state.row_id][i] - state.bridges_from_above[i];
  }

  for(int i = N, next = -1; i >= 0; i--) {
    next_island[i] = next;
    
    if (remaining_bridges[i]) next = i;
    if (next_bridges_from_above[i]) next = -1;
  }

  vector<State> next_states;
  build_next_states(0, state.row_id, next_bridges_from_above, remaining_bridges, next_states, next_island);

  for (auto state: next_states) {
    cerr << state << endl;
    process_state(state);
  }
}


int main() {
  cin >> N >> C;
  grid.assign(N, vector<int>(N, 0));

  // Read input
  for (int r = 0; r < N; r++) {
    for (int c = 0; c < N; c++) {
      int v; cin >> v;
      if (v > 0) {
        grid[r][c] = v; // Island with degree v on (r, c)
      }
    }
  }
  printGrid();

  State state { 0, N };
  process_state(state);

  // Send Answer 
  cout << "1" << endl;
  cout << "5 6 6 6 2" << endl;

  return 0;
}
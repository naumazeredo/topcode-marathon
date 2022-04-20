#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <chrono>

#include "common/state.h"
#include "common/stats.h"

using namespace std;
using namespace std::chrono;

int N, C;
vector<vector<int>> grid;
deque<State> allStates;

void print_grid() {
  for (auto row : grid) {
    for (auto cell : row) {
      cerr << cell << " ";
    }
    cerr << endl;
  }
};

void build_next_states_backtracking(
  int col,
  int current_row,
  vector<int>& next_bridges_from_above,
  vector<int>& remaining_bridges,
  vector<State>& next_states,
  vector<int>& next_island,
  State* parent_state) {
  if (col >= N) {
    next_states.push_back(State { current_row + 1, next_bridges_from_above, parent_state});
    return;
  }

  int degree = remaining_bridges[col];

  // No bridge remaining in the island
  if (degree == 0) {
    build_next_states_backtracking(col + 1, current_row, next_bridges_from_above, remaining_bridges, next_states, next_island, parent_state);
    return;
  }

  // Isolated island that doesn't connect to any component
  if (remaining_bridges[col] == grid[current_row][col]) {
    build_next_states_backtracking(col + 1, current_row, next_bridges_from_above, remaining_bridges, next_states, next_island, parent_state);
  }

  int next = next_island[col];
  int next_degree = (next == -1)? 0: grid[current_row][next_island[col]];

  // Island will connect to others
  for (int i = 0; i <= degree and i <= next_degree; i++) {
    next_bridges_from_above[col] = degree - i;
    if (next != -1) remaining_bridges[next] -= i;

    build_next_states_backtracking(col + 1, current_row, next_bridges_from_above, remaining_bridges, next_states, next_island, parent_state);

    next_bridges_from_above[col] = 0;
    if (next != -1) remaining_bridges[next] += i;
  }
}

vector<State> build_next_states(State& state) {
  vector<State> next_states;
  if (state.row == N) {
    // End of grid
    return next_states;
  }

  vector<int> remaining_bridges(N, 0);
  vector<int> next_bridges_from_above(N, 0);
  vector<int> next_island(N, 0);

  for (int i = 0; i < N; i++) {
    // if (!validate_state(state)) return;

    if (grid[state.row][i] == 0) {
      next_bridges_from_above[i] = state.bridges_from_above[i];
      continue;
    }

    if (grid[state.row][i] < state.bridges_from_above[i]) return next_states; // Invalid state
    remaining_bridges[i] = grid[state.row][i] - state.bridges_from_above[i];
  }

  for(int i = N, next = -1; i >= 0; i--) {
    next_island[i] = next;

    if (remaining_bridges[i]) next = i;
    if (next_bridges_from_above[i]) next = -1;
  }

  build_next_states_backtracking(0, state.row, next_bridges_from_above, remaining_bridges, next_states, next_island, &state);
  return next_states;
}

void search_best_solution(Stats& stats) {
  priority_queue<State> pq;
  pq.push(State{ 0, N , nullptr});

  while (!pq.empty()) {
    State s = pq.top();
    pq.pop();

    stats.add_state(s);

    vector<State> next_states = build_next_states(s);

    if (stats.should_end_search())
      return;

    for (auto state : next_states)
      pq.push(state);
  }
}

int main() {
  Stats stats;

  cin >> N >> C;
  grid.assign(N, vector<int>(N, 0));
  cerr << N << endl;

  // Read input
  for (int r = 0; r < N; r++) {
    for (int c = 0; c < N; c++) {
      int v; cin >> v;
      if (v > 0) {
        grid[r][c] = v; // Island with degree v on (r, c)
      }
    }
  }

  print_grid();

  search_best_solution(stats);

  // Send Dummy Answer
  cout << "1" << endl;
  cout << "5 6 6 6 2" << endl;

  return 0;
}

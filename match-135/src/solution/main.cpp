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
  State& current_state,
  vector<int>& next_bridges_from_above, // construindo
  vector<State>& next_states,
  vector<int>& next_island) {
  if (col >= N) {
    next_states.push_back(State { current_state.row + 1, next_bridges_from_above, &current_state});
    return;
  }

  int island_degree = grid[current_state.row][col];
  int incoming_bridges = current_state.bridges_from_above[col];

  // Nao tem ilha, passa tudo pra frente
  if (island_degree == 0) {
    next_bridges_from_above[col] = incoming_bridges;
    build_next_states_backtracking(col + 1, current_state, next_bridges_from_above, next_states, next_island);
    return;
  }

  // Tem ilha
  if (island_degree < incoming_bridges) {
    // Caso inválido
    return;
  }

  if (incoming_bridges == 0) {
    // Ilha não adicionada a nehuma componente
    build_next_states_backtracking(col + 1, current_state, next_bridges_from_above, next_states, next_island);
  }

  int remaining_degree = island_degree - incoming_bridges;

  int col_next_island = next_island[col];

  int max_bridges_to_right;
  if (col_next_island != -1) max_bridges_to_right = min(min(C, grid[current_state.row][col_next_island]), remaining_degree);
  else max_bridges_to_right = 0;

  // Adicionando ilha à componente de cima ou criando uma nova
  // Todas as conexões são pra baixo
  if (remaining_degree <= C) {
    next_bridges_from_above[col] = min(remaining_degree, C);
    build_next_states_backtracking(col + 1, current_state, next_bridges_from_above, next_states, next_island);
    next_bridges_from_above[col] = 0;
  }

  // Adicionando ilha da direita à componente atual
  for (int i = 1; i <= max_bridges_to_right; i++) {

    // Criando i pontes para lado e (remaining_degree - i) pontes para baixo
    next_bridges_from_above[col] = remaining_degree - i;
    current_state.bridges_from_above[col_next_island] += i;

    build_next_states_backtracking(col + 1, current_state, next_bridges_from_above, next_states, next_island);

    next_bridges_from_above[col] = 0;
    current_state.bridges_from_above[col_next_island] -= i;

  }
  // Removendo ilha da direita da componente atual
}

vector<State> build_next_states(State& state) {
  vector<State> next_states;
  if (state.row == N) {
    // End of grid
    return next_states;
  }

  vector<int> next_island(N, 0);

  for (int i = N-1, index = -1; i >= 0; i--) {
    next_island[i] = index;

    if (state.bridges_from_above[i]) index = -1;
    if (grid[state.row][i]) index = i;
  }

  vector<int> next_bridges_from_above(N, 0);
  build_next_states_backtracking(0, state, next_bridges_from_above, next_states, next_island);
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

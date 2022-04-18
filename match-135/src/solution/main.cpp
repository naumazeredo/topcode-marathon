#include <iostream>
#include <vector>
#include <string>

#include "common/state.h"
#include "common/stats.h"

using namespace std;

int main() {
  Stats stats;

  int N, C;
  cin >> N >> C;

  vector<string> ans;
  for (int row = 0; row < N; row++) {
    int prev_col = -1;
    int prev_v = -1;
    for (int col = 0; col < N; col++) {
      int v; cin >> v;
      if (v) {
        if (prev_v == v && v <= C) {
          ans.push_back(to_string(row) + " " + to_string(col) + " " + to_string(row) + " " + to_string(prev_col) + " " + to_string(v));
          prev_v = -1;
        } else {
          prev_col = col;
          prev_v = v;
        }
      }
    }
  }

  State state;

  stats.log(state);
  cerr << "test test" << endl;
  stats.log_invalid(state);

  cout << ans.size() << endl;
  for (const string& bridge : ans) {
    cout << bridge << endl;
  }

  return 0;
}

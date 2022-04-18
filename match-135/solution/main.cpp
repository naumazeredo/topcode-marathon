#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
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

  cerr << "test err!" << endl;

  cout << ans.size() << endl;
  for (const string& bridge : ans) {
    cout << bridge << endl;
  }

  cerr << "2 test err!" << endl;

  return 0;
}

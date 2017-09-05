#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <memory>  
#include <cstring>
using namespace std;

#include <stdio.h>
#include <stdlib.h>

const int D = 7;
vector<vector<int>> dcount(D * D, vector<int>());
vector<vector<int>> G(D, vector<int>(D, 0));
void dfs_euler(int idx, vector<int>& ret) {
  for (int i = 0; i < G[idx].size(); ++i) {
    while (G[idx][i]) {
      G[idx][i]--;
      G[i][idx]--;
      dfs_euler(i, ret);
      ret.insert(ret.end(), {i, idx});
    }
  }
}

int main() {
  int N;
  cin >> N;
  for (int i = 0; i < N; ++i) {
    int a, b;
    cin >> a >> b;
    G[a][b]++;
    G[b][a]++;
    dcount[a * D + b].push_back(i + 1);
  }
  int odd = 0;
  int first = -1;
  int second = -1;
  int third = -1;
  vector<int> degree(D, 0);
  for (int i = 0; i < D; ++i) {
    for (int j = 0; j < D; ++j) {
      degree[i] += G[i][j];
    }
    if (degree[i] % 2) {
      if (first == -1) first = i;
      else second = i;
      odd++;
    }
    if (degree[i]) {
      if (third == -1) third = i;
    }
  }
  if (odd != 0 && odd != 2) {
    cout << "No solution" << endl;
  } else {
    int start = third;
    if (first != -1) start = first;
    vector<int> seq;
    dfs_euler(start, seq);
    for (int i = 0; i < D; ++i) {
      for (int j = 0; j < D; ++j) {
        if (G[i][j]) { //not connected
          cout << "No solution" << endl;
          return 0;
        }
      }
    }
    reverse(seq.begin(), seq.end());
    for (int i = 0; i < seq.size(); i += 2) {
      int a = seq[i];
      int b = seq[i + 1];
      int w = a * D + b;
      int rw = b * D + a;
      if (dcount[w].size()) {
        cout << dcount[w].back() << " +" << endl;
        dcount[w].pop_back();
      } else {
        cout << dcount[rw].back() << " -" << endl;
        dcount[rw].pop_back();
      }
    }
  }
  return 0;
}


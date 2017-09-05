#include <iostream>
#include <vector>
#include <list>
#include <map>
#ifdef _MSC_VER
#include <hash_map>
using namespace stdext;
#define unordered_map hash_map
#else
#include <unordered_map>
#endif
#include <algorithm>
#include <string>
#include <memory>  
#include <cstring>
#include <queue>
using namespace std;

#include <stdio.h>
#include <stdlib.h>

#ifdef LOCAL_DEBUG
#define dprintf(...) printf (__VA_ARGS__)
#else
#define dprintf(...)
#endif

int main() {
  int F, V;
  cin >> F >> V;
  vector<vector<int>> val(F, vector<int>(V, 0));
  for (int i = 0; i < F; ++i) {
    for (int j = 0; j < V; ++j) {
      cin >> val[i][j];
    }
  }
  vector<vector<int>> opt(F, vector<int>(V, 0));
  vector<vector<int>> prev(F, vector<int>(V, 0)); //0 - NA; 1 - left, 2 - up left
  for (int i = 0; i < F; ++i) {
    if (i == 0) {
      opt[0][0] = val[0][0];
      prev[0][0] = 2;
    } else {
      opt[i][i] = val[i][i] + opt[i - 1][i - 1];
      prev[i][i] = 2;
    }
    for (int j = i + 1; j < V; ++j) {
      int left = opt[i][j - 1]; //no we don't choose this one. 
      int upleft = i == 0 ? 0 : opt[i - 1][j - 1];
      upleft += val[i][j];
      if (left > upleft) {
        prev[i][j] = 1;
        opt[i][j] = left;
      } else {
        prev[i][j] = 2;
        opt[i][j] = upleft;
      }
    }
  }
  cout << opt[F - 1][V - 1] << endl;
  vector<int> path;
  int i = F - 1;
  int j = V - 1;
  while (i >= 0) {
    if (prev[i][j] == 1) {
      j--;
    } else {
      path.push_back(j);
      i--;
      j--;
    }
  }
  reverse(path.begin(), path.end());
  for (int i = 0; i < path.size(); ++i) {
    cout << path[i] + 1 << " ";
  }
  cout << endl;
  return 0;
}


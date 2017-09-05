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

void euler_path(int cur, vector<vector<int>>& G, vector<int>& path) {
  while(G[cur].size()) {
    int next = G[cur].back();
    G[cur].pop_back();
    euler_path(next, G, path);
  }
  path.push_back(cur);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    vector<vector<int>> G(26);
    unordered_map<int, vector<string>> e2s;
    char w[30];
    for (int i = 0; i < n; ++i) {
      scanf("%s", w);
      int len = strlen(w);
      int c1 = s[0] - 'a';
      int c2 = s[len - 1] - 'a';
      e2s[c1 * 26 + c2].push_back(w);
      G[c1].push_back(c2);
    }
    
  }
  return 0;
}


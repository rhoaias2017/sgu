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

char buf[2048];

void euler_path(int cur, vector<vector<int>>& G, list<int>& path, int& count) {
  list<int> ending;
  path.push_back(cur);
  for (int i = 0; i < G[cur].size(); ++i) {
    while(G[cur][i]) {
      G[cur][i]--;
      list<int> npath;
      euler_path(i, G, npath, count);
      if (npath.back() == cur) {
        path.splice(path.end(), npath);
      } else {
        ending.splice(ending.end(), npath);
      }
    }
  }
  path.splice(path.end(), ending);
  count++;
}

void dfs(int cur, vector<vector<int>>& G, vector<bool>& vis) {
  if (vis[cur]) return;
  vis[cur] = true;
  for (int i = 0; i < G[cur].size(); ++i) {
    if (G[cur][i]) dfs(i, G, vis);
  }
}


  int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    int N;
    scanf("%d", &N);
    vector<vector<int>> G(26, vector<int>(26, 0));
    int M = N;
    while(N--) {
      scanf("%s", buf);
      int len = strlen(buf);
      int u = buf[0] - 'a';
      int v = buf[len - 1] - 'a';
      G[u][v]++;
    }
    bool flag = true;
    int start = -1;
    int end = -1;
    vector<int> in(26, 0);
    vector<int> out(26, 0);
    for (int i = 0; i < 26; ++i) {
      for (int j = 0; j < 26; ++j) {
        in[j] += G[i][j];
        out[i] += G[i][j];
      }
    }
    for (int i = 0; i < 26; ++i) {
      if (out[i] - in[i] == 1) {
        if (start != -1) flag = false;
        start = i;
      } else if (in[i] - out[i] == 1) {
        if (end != -1) flag = false;
        end = i;
      } else if (in[i] != out[i]) {
        flag = false;
      }
    }
    
    if (!flag) {
      printf("The door cannot be opened.\n");
      continue;
    }
    if (start == -1) {
      for (int i = 0; i < 26; ++i) {
        if (in[i]) {
          start = i;
          end = i;
          break;
        }
      }
    }
    list<int> path;
    int count = 0;
    //euler_path(start, G, count);  
    vector<bool> vis(26, false);
    dfs(start, G, vis);
    for (int i = 0; i < 26; ++i) {
      if (in[i] + out[i] != 0 && !vis[i]) flag = false;
    }
    if (flag) {
      printf("Ordering is possible.\n");
    } else {
      printf("The door cannot be opened.\n");
    }
  }
  return 0;
}


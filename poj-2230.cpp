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

//This needs to be fixed - in the original question G is the matrix not adj list.
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

void euler_cycle(int cur, vector<vector<int>>& G, list<int>& path) {
  while(G[cur].size()) {
    int next = G[cur].back();
    G[cur].pop_back();
    euler_cycle(next, G, path);
  }
  path.push_front(cur);
}

void add_edge(int u, int v, vector<vector<int>>& G) {
  G[u].push_back(v);
  G[v].push_back(u);
}


int main() {
  int N, M;
  scanf("%d%d", &N, &M);
  vector<vector<int>> G(N);
  for (int i = 0; i < M; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    add_edge(u, v, G);
  }
  list<int> path;
  for (int i = 0; i < M; ++i) {
    if (G[i].size()) {
      euler_cycle(i, G, path);
      break;
    }
  }
  for (list<int>::iterator it = path.begin(); it != path.end(); ++it) {
    printf("%d\n", *it + 1);
  }
  return 0;
}

